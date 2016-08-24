// Filename:    SQLConnector.cpp
// Author:      Joseph DeVictoria
// Date:        Feb_29_2016
// Purpose:     SQL Connector class to handle SQLite3 queries.

#include "SQLConnector.h"
#include "Utils.h"
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

SQLConnector::SQLConnector(){
    sqls = sqlite3_open("db/Oldentide.db", &database);
    if(sqls){
        cout << "Can't open database!" << endl;
        // Is this needed?
        sqlite3_close(database);
    }
    else{
        cout << "Oldentide database opened successfully." << endl;
    }
}

SQLConnector::~SQLConnector(){
    sqlite3_close(database);
}

// Executes a static SQL statement
// NOTE: Make sure there is no way for a user to inject arbitrary SQL into the passed statement!
// Either sanitize the input thoroughly or don't use this command. You might need to use a
// parameterized query instead, which this command doesn't support.
// @return : The number of rows returned by the query
int SQLConnector::execute(string cmd){
    char *error_message = NULL;
    sqls = sqlite3_exec(database, cmd.c_str(), &execute_callback, 0, &error_message);
    if (sqls != SQLITE_OK){
        cout << "Could not execute SQL query! Return Code:" << sqls << endl;
    }
    else {
        cout << "Executed Successfully. Return Code:" << sqls << endl;
    }
    if(error_message){
        // Print out the error message if any
        cout << "SQL ERROR MESSAGE: " << error_message << endl;
        // Free the error message, since it was alloced in exec()
        sqlite3_free(error_message);
    }
    return 0;
}

// Insert a new account record.
// @param account_name: IN. A c string that has already been sanitized to make sure it only has characters
//                      a-z,A-Z,0-9,_ If not sanitized, could lead to SQL Injection!
// @param key: IN. A c string of the key for the account, already generated. Will be a string of hex.
// @param salt: IN. A c string of the salt used to generate the key. Will be a string of hex.
// @return : 1 if sql executed successfully; 0 otherwise
int SQLConnector::insert_account(char *account_name, char *key, char *salt){
    std::stringstream query;
    // Sanitize key, salt, and account name
    if(!Utils::sanitizeAccountName(account_name)){
        cout << "Account_name is invalid! Cannot insert account record" << endl;
        return 0;
    }
    if(!Utils::sanitizeHexString(key)){
        cout << "Key is invalid! Cannot insert account record" << endl;
        return 0;
    }
    if(!Utils::sanitizeHexString(salt)){
        cout << "Salt is invalid! Cannot insert account record" << endl;
        return 0;
    }
    query << "insert into accounts (account_name, key, salt) values (";
    query << "\"" << account_name << "\",";
    query << "\"" << key << "\",";
    query << "\"" << salt << "\")";
    execute(query.str());
    // TODO: Let user know that it is a constraint fail - i.e. the username is already taken
    // TODO: Do a client-side check first before trying to insert for convenience
    if(sqls == SQLITE_OK){
        return 1;
    }
    else {
        return 0;
    }
}

// TODO: Create a paging mechanism - save a page variable and use LIMIT and OFFSET
// Lists all the accounts
void SQLConnector::list_accounts(){
    std::stringstream query;
    //long long int offset = 0;
    query << "select * from accounts ORDER BY account_name";// LIMIT 5 OFFSET " << offset;
    execute(query.str());
}

// TODO: Create paging functions to determine the limit offset
// next_page
// previous_page
// goto_page
// first_page
// last_page
// function to determine order (id or account_name)

// Return the salt for the passed account
// @param account_name: IN. A c string on the account_name to look the salt up.
// @param salt_string_hex: OUT. An empty c string allocated to 129 bytes.
// @return : Returns 1 if salt was found, 0 otherwise (not found, failure, etc)
int SQLConnector::get_account_salt(char *account_name, char *salt_string_hex){
    // Sanitize the account name before preceeding
    if(!Utils::sanitizeAccountName(account_name)){
        return 0;
    }
    char *error_message = NULL;
    std::stringstream query;
    query << "select salt from accounts where account_name = \"" << account_name << "\"";
    cout << query.str() << endl;
    // The fourth param is passed to the callback function as a void pointer to the first param
    sqls = sqlite3_exec(database, query.str().c_str(), &return_string_callback, salt_string_hex, &error_message);
    if (sqls != SQLITE_OK){
        cout << "Could not execute SQL query! Return Code:" << sqls << endl;
    }
    else {
        cout << "Executed Successfully. Return Code:" << sqls << endl;
    }
    if(error_message){
        // Print out the error message if any
        cout << "SQL ERROR MESSAGE: " << error_message << endl;
        // Free the error message, since it was alloced in exec()
        sqlite3_free(error_message);
        return 0;
    }
    // TODO: There should be a better way to do this, but for now...
    // Check to see if the salt was retrieved
    if(Utils::sanitizeHexString(salt_string_hex)){
        return 1;
    }
    else {
        return 0;
    }

}

// Returns the key to the passed account
// @param account_name : IN. The name of the account to authenticate.
// @param key_string_hex : OUT. The key hex string of the user. Should be allocated to 129 bytes.
// @return : 1 on successful authentication, 0 if authentication failed.
int SQLConnector::get_account_key(char *account_name, char *key_string_hex){
    // Sanitize the account name before preceeding
    if(!Utils::sanitizeAccountName(account_name)){
        return 0;
    }
    char *error_message = NULL;
    std::stringstream query;
    query << "select key from accounts where account_name = \"" << account_name << "\"";
    cout << query.str() << endl;
    // The fourth param is passed to the callback function as a void pointer to the first param
    sqls = sqlite3_exec(database, query.str().c_str(), &return_string_callback, key_string_hex, &error_message);
    if (sqls != SQLITE_OK){
        cout << "Could not execute SQL query! Return Code:" << sqls << endl;
    }
    else {
        cout << "Executed Successfully. Return Code:" << sqls << endl;
    }
    if(error_message){
        // Print out the error message if any
        cout << "SQL ERROR MESSAGE: " << error_message << endl;
        // Free the error message, since it was alloced in exec()
        sqlite3_free(error_message);
    }
    return 1;
}


// A generic callback function to sqlite3_exec() that copies a c string in the first column
// of the returned row into string_to_return. This function assumes that only one record will be
// in the result set, or else the return value will be the value in the last row processed.
static int return_string_callback(void *string_to_return, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL");
        cout << " | ";
    }
    cout << endl;
    // The value will auto-destroy soon. So, we need to copy it to a place
    // that won't get destroyed after returning from this function
    strcpy((char *)string_to_return, argv[0]);
    return 0;
}

// This is a generic callback that simply prints to screen all the values
// of the returned row after a query. Callback adapted from https://www.sqlite.org/quickstart.html
// This callback is invoked for each returned ROW
// This can't be a method, since it is being passed as a c function pointer
// Create, update, or delete calls usually don't return rows, so the callback won't be triggered.
// @param NotUsed : A void pointer that can be used as a means of passing a parameter. Not used.
// @param argc : The number of columns in the row
// @param argv : Stores the column value strings of the row
// @param azColName : Stores the column name strings in alphabetical order.
static int execute_callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL");
        cout << " | ";
    }
    cout << endl;
    return 0;
}


// Example code of how to do true parameterization...
//// Whew... paramaterization makes it so I can't use sqlite3_exec, which makes things way more verbose
///**
//    @param account_name: IN. A c string on the account_name to look the salt up. It should be screened
//                                 so it is ONLY an alphanumeric string to prevent SQL injection attacks
//    @param salt_string_hex: OUT. An empty c string allocated to 129 bytes. This is where the salt will
//                             be stored.
//    @return : Returns 1 if salt was found, 0 otherwise (not found, failure, etc)
//**/
//int SQLConnector::get_account_salt(char *account_name, char *salt_string_hex){
//    std::stringstream query;
//    // TODO: Use sanitize account name instead of parameterization
//    // Trim whitespace from account name with trim function
//    query << "select * from accounts where account_name = trim(?)";
//    sqlite3_stmt *statement;
//    sqlite3_prepare_v2(database, query.str().c_str(), -1, &statement, NULL);
//    // Negative number makes it read from account_name until it hits nul character
//    // SQLITE_STATIC indicates that account_name doesn't need a destructor function
//    sqlite3_bind_text(statement, 1, account_name, -1, SQLITE_STATIC);
//    // NOTE: Column 3 should be the salt column! Don't change db definition!
//    // TODO: Do a for loop until I find the clumn index that matches "salt" using sqlite3_column_name?
//    // use strcmp to compare returned column name with "salt" to see if it is accurate
//    // TODO: Change the select statement so that only a single column is possible
//    int column_salt = 3;
//    int rc = sqlite3_step(statement);
//    int return_value = 0;
//    if(rc == SQLITE_ROW){
//        // Process just the first row, since there should only be one record
//        //int salt_bytes = sqlite3_column_bytes(statement, column_salt);
//        //cout << "Account found! The salt is " << salt_bytes << "+1 bytes!" << endl;
//        // Get the salt text
//        char *salt_string_hex_temp = (char *)sqlite3_column_text(statement, column_salt);
//        // sqlite3_column_text returns a string pointer that sqlite will autodeestroy soon
//        // So, we need to copy it to a place that won't get destroyed after returning from this function
//        strcpy(salt_string_hex, salt_string_hex_temp);
//        cout << "Salt hex from db: " <<  salt_string_hex << endl;
//        return_value = 1;
//    }
//    else if(rc == SQLITE_DONE){
//        // User account wasn't found
//        cout << "Account wasn't found..." << endl;
//    }
//    else{
//        cout << "An SQL error occurred. Return code: " << rc << endl;
//    }
//    sqlite3_finalize(statement);
//    return return_value;
//}
