// Filename:    GameState.cpp
// Author:      Joseph DeVictoria
// Date:        Mar_2_2016
// Purpose:     Game State Class implementation.
//              This class will be responsible for maintaining the Players,
//              NPCs necessary to preserve the game state.  It will also
//              perform the bulk of database interactions.

#include "GameState.h"
#include "Utils.h"
#include <iterator>
#include <iostream>
#include "AccountManager.h"
#include <cstring>
#include <map>

using namespace std;

#define MAX_MESSAGES 500
#define MAX_MESSAGE_LENGTH 500


GameState::GameState(SQLConnector * input){
    sql = input;
    curSession = 1;

    // 0 means no messages. The first message will be 1.
    globalMessageNumber = 0;

}

GameState::~GameState(){
    return;
}

// Checks if the session id given by the user is valid before allowing further interaction.
bool GameState::verifySession(int sessionId){
    if (sessions.find(sessionId) != sessions.end()){
        return true;
    }
    else{
        return false;
    }
}

// Active sessions refer to users that have already authenticated and may or may not be already using a character.
bool GameState::verifyActiveSession(int sessionId){
    if (activeSessions.find(sessionId) != activeSessions.end()){
        return true;
    }
    else{
        return false;
    }
}

bool GameState::createAccount(char * account, char * keyStringHex, char * saltStringHex){
    cout << "  Creating Account..." << endl;
    cout << "  Account: " << account << endl;
    cout << "  Key: " << keyStringHex << endl;
    cout << "  Salt: " << saltStringHex << endl;
    bool success = false;
    if(sql->insert_account(account, keyStringHex, saltStringHex)){
        success = true;
    }
    else {
        printf("Unable to insert new account record into database...\n");
    }
    printf("Listing all created accounts...\n");
    sql->list_accounts();
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

bool GameState::loginUser(char * account, char * keyStringHex){
    cout << "  Logging in..." << endl;
    cout << "  Account: " << account << endl;
    cout << "  Key: " << keyStringHex << endl;
    return AccountManager::authenticateAccount(account, keyStringHex);
}

void GameState::disconnectSession(int sessionId){
    activeSessions.erase(sessionId);
    sessions.erase(sessionId);
    return;
}

void GameState::playerCommand(char * command, int sessionId){
    string pCommand(command);
    vector<string> pCommandTokens = Utils::tokenfy(pCommand, ' ');
    if (pCommandTokens[0] == "/s"){
        cout << "Detected a say command!" << endl;
        // Save the incoming message and return the assigned message number
        string saying = pCommand.substr(3,string::npos);
        storeMessage(saying, sessionId);
    }
    else if (pCommandTokens[0] == "/y"){
        cout << "Detected a yell command!" << endl;
    }
    else if (pCommandTokens[0] == "/ooc"){
        cout << "Detected an out of character command!" << endl;
    }
    else if (pCommandTokens[0] == "/h"){
        cout << "Detected a help channel command!" << endl;
    }
    else if (pCommandTokens[0] == "/w"){
        cout << "Detected a whisper command!" << endl;
    }
    cout << "Full player command: " << command << endl;
}

void GameState::selectPlayer(int sessionId){
    if (sessions.find(sessionId) != sessions.end()){
        activeSessions.insert(sessionId);
    }
    return;
}

Player GameState::readPlayer(string name){
    return Player("example", "Shaman", 0, 0, 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, "Poop", "Stain", "Human", "Male", "Scarred", "Pale", 
                  "Newcomers_Guild", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 
                  0.0);
}

void GameState::storePlayer(string name){
    return;
}

int GameState::generateSession(int sessionId){
    if (sessions.find(sessionId) != sessions.end()){
        return sessionId;
    }
    else{
        sessions.insert(curSession);
        curSession++;
        return (curSession - 1);
    }
}


/**
    @return : The number of the most recent message received by the server
**/
long long int GameState::getGlobalMessageNumber() {
    if(globalMessageNumber > MAX_MESSAGES){
        // 0 means either no messages or
        // Ran out of message space
        return 0;
    }
    else {
        // Return the latest message number in the global message buffer
        return globalMessageNumber;
    }
}

/**
    Returns a message and the account that spoke it

    // TODO: Change this to be player-based
    // TODO: Broadcast all messages in realtime instead of storing them

    @param messageNumber : IN. The message number of the message to get
    @param message : OUT. The message to output

    @return : 0 if failed to retrieve message, else the message number of the returned message
**/
long long int GameState::getMessage(long long int messageNumber, char *messageOutput, char *accountNameOutput) {
    // Look up the requested message and return it
    if(messageNumber >= 1 && messageNumber <= MAX_MESSAGES){
        cout << "Looking up message " << messageNumber << endl;

        // Look up the message and account name
        // Remember, index = messageNumber - 1
        string message = globalMessageArray.at(messageNumber-1);
        string accountName = sessionAccounts[globalMessageAccountArray.at(messageNumber-1)];
        // cout << accountName << ": " << message << endl;

        std::strcpy(messageOutput, message.c_str());
        std::strcpy(accountNameOutput, accountName.c_str());
        return messageNumber;
    }
    else {
        // Invalid message
        return 0;
    }
}


/**
    @param message : The message to store
    @param accountName : The name of the account that spoke

    // TODO: Change to players instead of accounts

    @return : the global message number assigned to the message stored.
                If 0, then failed to store message.
**/
long long int GameState::storeMessage(string message, int sessionId) {
    if(globalMessageNumber > MAX_MESSAGES){
        cout << "Ran out of message space! Reached max number of messages" << endl;
        // Ran out of message space
        return 0;
    } else{
        // Increase the global message number (start at 1 - 0 means no messages)
        globalMessageNumber++;
        // cout << "Saving message with number " << globalMessageNumber << ": " << message << endl;
        // TODO: Are things guaranteed to be atomic and reentrant?
        // Atomically assign message a global message number
        // Store the first message at index 0, second message at 1, etc.
        globalMessageArray.push_back(message);
        // Store the username of the account that sent the message
        globalMessageAccountArray.push_back(sessionId);
        return globalMessageNumber;
    }
}


// TODO: Make this player name instead of account name
void GameState::setSessionAccountName(char *accountName, int sessionId){
    std::string accountNameString = accountName;
    sessionAccounts[sessionId] = accountNameString;
    // TODO: Return something if session account was already registered
}
