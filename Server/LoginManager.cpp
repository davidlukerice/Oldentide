// Filename:    LoginManager.cpp
// Author:      Michael Hinton
// Date:        Jul_29_2016
// Purpose:     Login authentication process.
// NOTE:        OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <openssl/bn.h>
#include "LoginManager.h"

#define SALT_BIT_SIZE 512
// Iterations should be calibrated so the whole process takes 200-1000 ms
// If it is any quicker, it defeats the point of salting and stretching!
// 2^20 iterations will effectively add 20 bits to the password
// NOTE: The generated key depends on the number of iterations.
const long long int LoginManager::ITERATIONS = 1 << 20;

// CLIENT. Takes a password of any length and a 512-bit salt and calculates a 512-bit key.
// Uses the OpenSSL implementation of sha512.
// @param password : IN. A c string containing the password of the user.
// @param salt : IN. The salt to use to generate the key.
// @param generated_ke_sring_hex : OUT. A pointer to where the key hex string should be copied to.
void LoginManager::generateKey(char *password, char *salt_string_hex, char *generated_key_string_hex){
    EVP_MD_CTX *md_context;
    const EVP_MD *md_function;
    unsigned int md_len, i;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    // NOTE: EVP_MAX_MD_SIZE is 64 (512 bits)

    printf("Salting and stretching the password...\n");

    printf("Hash Function: SHA-512\n");
    md_function = EVP_sha512();

    printf("Password: \"%s\"\n", password);

    // Initialize salt and generated key BIGNUMs
    BIGNUM *salt = BN_new();
    BIGNUM *generated_key = BN_new();

    BN_hex2bn(&salt, salt_string_hex);


    int salt_bytes = BN_num_bytes(salt);
    int salt_bits = BN_num_bits(salt);
    unsigned char salt_string_bin[salt_bytes];
    int salt_length = BN_bn2bin(salt, salt_string_bin);

    printf("Salt (hex):\n");
    for(int i = 0; i < salt_length; i++){
        printf("%02x", salt_string_bin[i]);
    }
    printf("\n");
    printf("Salt length : bytes : bits\n%d : %d : %d\n", salt_length, salt_bytes, salt_bits);

    // md_value needs to be initialized to all zeros, since it's on the stack
    for(int i = 0; i < EVP_MAX_MD_SIZE; ++i){
        md_value[i] = 0;
    }

    printf("Iterations: %llu\n", ITERATIONS);
    for (long long i = 0; i < ITERATIONS; ++i) {
        md_context = EVP_MD_CTX_create();
        EVP_DigestInit(md_context, md_function);
        // Append the previous hash, pasword, and salt together in this order:
        //x = hash512(x || password || salt);
        EVP_DigestUpdate(md_context, md_value, EVP_MAX_MD_SIZE);
        EVP_DigestUpdate(md_context, password, strlen(password));
        EVP_DigestUpdate(md_context, salt_string_bin, salt_bytes);
        // Execute the hash and store it in md_value
        EVP_DigestFinal_ex(md_context, md_value, &md_len);
        // clean up md_context
        EVP_MD_CTX_destroy(md_context);
        // NOTE: EVP_DigestFinal() should == EVP_DigestFinal_ex() + EVP_MD_CTX_destroy()
    }
    // End loop

    printf("Final salted and stretched password/key is: \n");
    for(int i = 0; i < md_len; i++){
        printf("%02x", md_value[i]);
    }
    printf("\n");

    // Convert from binary big-endian md_value to BIGNUM
    BN_bin2bn(md_value, EVP_MAX_MD_SIZE, generated_key);
    // Convert from BIGNUM to hex string and output it to user
    // Caller will need to deallocate this!
    char *generated_key_string_hex_temp;
    generated_key_string_hex_temp = BN_bn2hex(generated_key);
    // Copy the hex string out
    strcpy(generated_key_string_hex, generated_key_string_hex_temp); 
    printf("Final key in hex:\n%s\n", generated_key_string_hex);
    // Free the malloced temp key string
    OPENSSL_free(generated_key_string_hex_temp);

    // Clear the allocated BIGNUMs
    BN_clear_free(generated_key);
    BN_clear_free(salt);
}

// TODO: Make is so that caller doesn't need to free anything - caller pre-allocates space
// Figure out who needs to free what 
// @param password : IN. The password that will be used to generate the key 
//                   for the new account. It will NOT be stored.
// @param salt_string_hex : OUT. The newly-generated random salt that was used to generate the new key.
// @param generated_key_string_hex : OUT. The newly-generated key.
void LoginManager::generateSaltAndKey(char *password, char *salt_string_hex, char *generated_key_string_hex){
    // Initialize salt and generated key BIGNUMs
    BIGNUM *salt = BN_new();

    // Since argument was not supplied, generate a random salt
    // Create the random number (openssl should auto-seed from /dev/urandom)
    BN_rand(salt, SALT_BIT_SIZE, -1, 0);

    // Convert the salt BIGNUM to a hex string to store in the db as text
    // Store the key as hex, so it is easy to read out
    // Note: This needs to be freed later
    char *salt_string_hex_temp = BN_bn2hex(salt);
    LoginManager::generateKey(password, salt_string_hex_temp, generated_key_string_hex);

    // Instead of making the caller free it, copy the contents to the passed pointers, and then free it
    strcpy(salt_string_hex, salt_string_hex_temp); 

    OPENSSL_free(salt_string_hex_temp);
    BN_clear_free(salt);
    // TODO: Use clear_free() version - might need crypto.h though
    // TODO: Overwrite stack sensitive variables with with 0's,
    // since it doesn't get zeroed out once it's off the stack
    // NOTE: clear_free variants are for sensitive info, opposed to just free.
    // The salts aren't sensitive, but the password and key are.
    // So just use clear_free for everything I can
}

//
//// Terminology:
//
// message = plaintext
// message digest function = hash function
// message digest (MD) = digest = fingerprint = output of a hash function

//
//// Task:
//
// Create a program that will take an input password,
// generate a random salt, stretch the password for n iterations,
// save the salted password and salt in the sqlite db, and
// time the process to see how long it took, sending an error if too quick (< 200ms)

/*
// Pseudocode for salting and stretching a password
// See pg 304 of Cryptography Engineering (21.2.1 - Salting and Stretching)

x = 0
// The salt is simply a random number that is stored alongside the key. Use at least a 256bit salt.
// Each user needs a different salt, so an attacker would always have to recalculate the key per user,
// even if the attacker guesses the same password (e.g. "password") for each user.
salt = rand256()

for (i = 0; i < ITERATIONS; ++i) {
    // (note: || means append)
    x = hash512(x || password || salt)
}

key = x
// Store the salt and the key in the db. The salt can be public.
*/
