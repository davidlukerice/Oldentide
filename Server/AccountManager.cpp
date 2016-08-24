// Filename:    AccountManager.cpp
// Author:      Michael Hinton
// Date:        Jul_23_2016
// Purpose:     Account creation and authentication.
// NOTE:        OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#include <stdio.h>
#include <string.h>
#include <openssl/bn.h>
#include "SQLConnector.h"
#include "AccountManager.h"

// Authenticates an account and key
// @param account_name : The account to authenticate with.
// @param candidate_key_string_hex : The user-supplied key to autheticate with.
// @return : 1 if account successfully authenticated; 0 if not.
int AccountManager::authenticateAccount(char *account_name, char *candidate_key_string_hex){
    // Authenticate - perform a key lookup and check
    int success = 0;
    SQLConnector *sql = new SQLConnector();
    // Create a container to hold the canonized key string hex
    char canonized_key_string_hex[129];
    sql->get_account_key(account_name, canonized_key_string_hex);

    // Initialize salt and generated key BIGNUMs
    BIGNUM *candidate_key = BN_new();
    BIGNUM *canonized_key = BN_new();

    // Convert both keys to openssl bn BIGNUM
    BN_hex2bn(&candidate_key, candidate_key_string_hex);
    BN_hex2bn(&canonized_key, canonized_key_string_hex);

    printf("Candidate Key: \n%s\n", candidate_key_string_hex);
    printf("Canonized Key: \n%s\n", canonized_key_string_hex);

    // Compare both BIGNUMs to each other.
    // If the same, then return 1 (success)
    // If not, return 0.
    if(BN_cmp(canonized_key, candidate_key) == 0){
        printf("Authentication is a success!!\n");
        success = 1;
    }
    // Free the BIGNUMs and malloced strings
    BN_clear_free(canonized_key);
    BN_clear_free(candidate_key);
    
    // Free up memory allocations
    delete sql;
    // TODO: Overwrite stack sensitive variables with with 0's,
    // since it doesn't get zeroed out once it's off the stack
    //for(int i = 0; i < EVP_MAX_MD_SIZE; ++i){
    //    generated_key[i] = 0;
    //}
    //for(int i = strlen(); i > 0); --i){
    //    password[i] = 0;
    //}
    // NOTE: clear_free variants are for sensitive info, opposed to just free.
    // The salts aren't sensitive, but the password and key are.
    // So just use clear_free for everything I can
    return success;
}

