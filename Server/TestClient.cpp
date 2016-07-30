// Filename:    TestClient.cpp
// Author:      Joseph DeVictoria
// Date:        2_10_2013
// Purpose:     Act as an intermediate test platform for proving server functionality.

#include "Packets.h"
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include "LoginManager.h"
#include "Utils.h"
#include <thread>

using namespace std;

void parseCommands(){
    long long int i = 0;
    while(1){
        string str;
        getline(cin,str);
        cout << i << ": " << endl;
        ++i;
    }
    // Listen until disconnect is recieved from server?
    return;
}


int main(int argc, char * argv[]){

    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    char * server_address;
    char * names[10];
    int session = 0;
    int packetNumber = 1;
    bool running = true;
    // Save the name of the logged in user
    char loggedInAccount[30];
    // This will be a thread to handle listening to the server
    thread shell;

    // TODO: Parameter checking
    // Have parameter checking and exit gracefully if server address and port aren't specified
    if(argc != 3){
        cout << "Invalid number of arguments passed to " << argv[0] << "; Exiting..." << endl;
        return 1;
    }

    // Read in server address.
    server_address = argv[1];
    int port = atoi(argv[2]);
    cout << server_address << endl;
    cout << port << endl;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(server_address);
    servaddr.sin_port = htons(port);

    int clientState = 0;

    while (running){
        switch (clientState){
            // Initial State.
            case 0: {
                cout << "Connect? (Y/N) " << endl;
                string response;
                getline (cin, response);
                if ((response.compare("y") == 0) || (response.compare("Y") == 0)){
                    PACKET_CONNECT packet;
                    packet.packetId = packetNumber;
                    packetNumber++;
                    packet.sessionId = session;
                    sendto(sockfd,(void*)&packet,sizeof(packet),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    PACKET_CONNECT * returnPacket = (PACKET_CONNECT*) malloc(sizeof(PACKET_CONNECT));
                    sockaddr_in servret;
                    socklen_t len = sizeof(servret);
                    int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&servret, &len);
                    cout << "Connected! Given the session id: " << returnPacket->sessionId << endl;
                    session = returnPacket->sessionId;
                    free(returnPacket);
                    clientState = 1;
                }
                else {
                    cout << "Shutting down!" << endl;
                    running = false;
                }
                break;
            }
            // Connected.
            case 1: {
                // First packet - check if account exists and get salt
                PACKET_GETSALT packetSalt;
                packetSalt.packetId = packetNumber;
                packetSalt.sessionId = session;
                cout << "Account: ";
                cin.getline(packetSalt.account, sizeof(packetSalt.account));
                if(!Utils::sanitize_account_name(packetSalt.account)){
                    cout << "Invalid account name!" << endl;
                    break;
                }
                sendto(sockfd,(void*)&packetSalt,sizeof(packetSalt),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                PACKET_GETSALT *returnPacketSalt = (PACKET_GETSALT*) malloc(sizeof(PACKET_GETSALT));
                sockaddr_in servretSalt;
                socklen_t lenSalt = sizeof(servretSalt);
                int n = recvfrom(sockfd, (void *)returnPacketSalt, sizeof(PACKET_GETSALT), 0, (struct sockaddr *)&servretSalt, &lenSalt);
                cout << "Account retrieved from get salt:" << returnPacketSalt->account << endl;
                cout << "Account on hand:" << packetSalt.account << endl;
                if ((strcmp(returnPacketSalt->account, packetSalt.account)) == 0) {
                    cout << "Account exists! Recieved salt, calculating key..." << endl;
                    // Second packet - calculate key from salt and send key and account name
                    PACKET_LOGIN packetLogin;
                    packetLogin.packetId = packetNumber;
                    packetLogin.sessionId = session;
                    strcpy(packetLogin.account, packetSalt.account);
                    cout << "Password: ";
                    // TODO: Get a system-wide define for max password length
                    // TODO: Is there any way to allocate only what is needed?
                    // TODO: How to make password size match the length of the password?
                    char password[1000];
                    cin.getline(password, sizeof(password));
                    if(!Utils::check_password_length(password)){
                        break;
                    }
                    cout << "Salt used in login generating key: " << returnPacketSalt->saltStringHex << endl;
                    LoginManager::generate_key((char *)password, (char *)returnPacketSalt->saltStringHex, (char *) packetLogin.keyStringHex);
                    cout << "Generated key used for login: " << packetLogin.keyStringHex << endl;
                    sendto(sockfd,(void*)&packetLogin,sizeof(packetLogin),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                    PACKET_LOGIN * returnPacket = (PACKET_LOGIN*) malloc(sizeof(PACKET_LOGIN));
                    sockaddr_in servret;
                    socklen_t len = sizeof(servret);
                    int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_LOGIN), 0, (struct sockaddr *)&servret, &len);
                    if ((strcmp(returnPacket->account, packetLogin.account)) == 0) {
                        cout << "Logged in as " << returnPacket->account << "!" << endl;
                        cout << "(" << packetLogin.account << ")" << endl;
                        // Save off the logged-in account name
                        strcpy(loggedInAccount, returnPacket->account);
                        // Spawn thread to start listening to server broadcasts
                        shell = thread(parseCommands);
                        // Now that user is logged in, start up client console 
                        clientState = 2;
                    }
                    else {
                        cout << "Login Failed! Please try again." << endl;
                    }
                    free(returnPacket);
                }
                else {
                    cout << "Account doesn't exist..." << endl;
                    cout << "Did you want to create a new account called " << packetSalt.account << "? (Y/N) " << endl;
                    string response;
                    getline(cin, response);
                    if ((response.compare("y") == 0) || (response.compare("Y") == 0)){
                        char password[1000];
                        char password2[1000];
                        bool repeat_try; 
                        do {
                            repeat_try = false;
                            cout << "Enter password, or press c to cancel: ";
                            // TODO: Get a system-wide define for max password length
                            // TODO: Is there any way to allocate only what is needed?
                            // TODO: How to make password size match the length of the password?
                            cin.getline(password, sizeof(password));
                            if(strcmp(password, "c") == 0){
                                continue;
                            }
                            cout << "Repeat password: ";
                            cin.getline(password2, sizeof(password2));
                            if(strcmp(password, password2) != 0){
                                cout << "Passwords were not the same... Please retype the password" << endl;                                repeat_try = true;
                                continue; 
                            }
                            if(!Utils::check_password_length(password)){
                                cout << "Password needs to be at least 8 characters... Please choose a different password" << endl;
                                repeat_try = true;
                                continue;
                            }
                            // If user made it this far, then password must be good
                            // Start assembling the create account packet
                            PACKET_CREATEACCOUNT packetCreate;
                            packetCreate.packetId = packetNumber;
                            packetCreate.sessionId = session;
                            strcpy(packetCreate.account, packetSalt.account);
                            LoginManager::generate_salt_and_key(password, packetCreate.saltStringHex, packetCreate.keyStringHex);
                            sendto(sockfd,(void*)&packetCreate,sizeof(packetCreate),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
                            // Print success if account was successfully created
                            PACKET_CREATEACCOUNT *returnPacket = (PACKET_CREATEACCOUNT*) malloc(sizeof(PACKET_CREATEACCOUNT));
                            sockaddr_in servret;
                            socklen_t len = sizeof(servret);
                            int n = recvfrom(sockfd, (void *)returnPacket, sizeof(PACKET_LOGIN), 0, (struct sockaddr *)&servret, &len);
                            if ((strcmp(returnPacket->account, packetCreate.account)) == 0) {
                                cout << "New account \"" << returnPacket->account << "\" successfully created!" << endl;
                            }
                            else {
                                cout << "New account \"" << packetCreate.account << "\" failed to create..." << endl;
                            }
                            free(returnPacket);
                        }
                        while(repeat_try);
                    }
                }
                free(returnPacketSalt);
                break;
            }
            // Logged In - User can execute commands
            case 2: {
                // TODO: How to listen to server broadcast?
                // TODO: Spawn a thread to listen to the server broadcasts,
                // and keep this thread to handle incoming text
                string command;
	            do{
                    cout << loggedInAccount << "@OldentideConsole$ ";
                    getline(cin, command);
	            }
                while(command.empty());
                vector<string> tokens = tokenfy(command, ' ');
                if (tokens[0] == "/quit" || tokens[0] == "/q"){
                    cout << "\nQuitting oldentide..." << endl;
                    // TODO: Exit program to close all threads... right?
                    exit(EXIT_SUCCESS);
                    //running = false;
                    // Wait for the shell to return
                    //shell.join();
                }
                else {
                    cout << command << endl;
                    // TODO: Send player command packet
                    // Send text to server to rebroadcast to all clients
                    //PACKET_SENDPLAYERCOMMAND *packet;
                }
                //else if (adminTokens[0] == "/list"){
                //    if (adminTokens.size() == 2){
                //        cout << adminTokens[1];
                //        if (adminTokens[1] == "players"){
                //            cout << "PCSSSSSS" << endl;          
                //        }
                //        if (adminTokens[1] == "npcs"){
                //            cout << "NPCSSSSS" << endl;    
                //        }
                //    }
                //    else{
                //        printUsage();
                //    }
                //}
                shell.join();
                break;
            }
            // 
            case 3: {
            
            }
            default: {
                cout << "Default case statement" << endl;
            }
                
        }
    }
    // Exit main program
}
