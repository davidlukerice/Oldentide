// Filename:    Server.cpp
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Dedicated server class.

#include "Server.h"
#include <cstring>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <limits.h>

using namespace std;

Server::Server(int port){
    sql = new SQLConnector();
    gamestate = new GameState(sql);
    adminshell = new AdminShell(sql);

    // Create server address struct.
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    // Create socket for IP, UDP normal protocol.
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        cout << "Cannot create socket..." << endl;
        exit(EXIT_FAILURE);
    }

    // Bind socket to a port.
    if ((bind(sockfd, (struct sockaddr *)&server, sizeof(server))) < 0){
        cout << "Cannot bind socket..." << endl;
        exit(EXIT_FAILURE); 
    };
}

Server::~Server(){
    delete sql;
    delete gamestate;
    delete adminshell;
}

void Server::run(){
    thread shell(*adminshell);
    sockaddr_in client;
    socklen_t len = sizeof(client);
    cout << "Server Running!\n";
	bool validSession = true;
    bool listen = true;
    while(listen){
        PACKET_GENERIC * packet = (PACKET_GENERIC*) malloc(sizeof(PACKET_GENERIC));
        int n = recvfrom(sockfd, (void *)packet, sizeof(PACKET_GENERIC), 0, (struct sockaddr *)&client, &len);
		if (packet->packetType != CONNECT){
			validSession = gamestate->verifySession(packet->sessionId);
		}
        if (validSession){
            switch (packet->packetType){
                case GENERIC:
                    genericHandler((PACKET_GENERIC*)packet);
                    break;
                case ACK: 
                    ackHandler((PACKET_ACK*)packet);
                    break;
                case CONNECT: 
                    connectHandler((PACKET_CONNECT*)packet, client);
                    break;
                case DISCONNECT: 
                    disconnectHandler((PACKET_DISCONNECT*)packet);
                    break;
                case GETSALT: 
                    saltHandler((PACKET_GETSALT*)packet, client);
                    break;
                case CREATEACCOUNT: 
                    createAccountHandler((PACKET_CREATEACCOUNT*)packet, client);
                    break;
                case LOGIN: 
                    loginHandler((PACKET_LOGIN*)packet, client);
                    break;
                case LISTCHARACTERS: 
                    listCharactersHandler((PACKET_LISTCHARACTERS*)packet);
                    break;
                case SELECTCHARACTER: 
                    selectCharacterHandler((PACKET_SELECTCHARACTER*)packet);
                    break;
                case DELETECHARACTER: 
                    deleteCharacterHandler((PACKET_DELETECHARACTER*)packet);
                    break;
                case CREATECHARACTER: 
                    createCharacterHandler((PACKET_CREATECHARACTER*)packet);
                    break;
                case INITIALIZEGAME: 
                    initializeGameHandler((PACKET_INITIALIZEGAME*)packet);
                    break;
                case UPDATEPC: 
                    updatePcHandler((PACKET_UPDATEPC*)packet);
                    break;
                case UPDATENPC: 
                    updateNpcHandler((PACKET_UPDATENPC*)packet);
                    break;
                case SENDPLAYERCOMMAND: 
                    sendPlayerCommandHandler((PACKET_SENDPLAYERCOMMAND*)packet);
                    break;
                case SENDPLAYERACTION: 
                    sendPlayerActionHandler((PACKET_SENDPLAYERACTION*)packet);
                    break;
                case SENDSERVERACTION: 
                    sendServerActionHandler((PACKET_SENDSERVERACTION*)packet);
                    break;
            }
        }
        else {
            free(packet);
        }
    }
    shell.join();
    return;
}

// Invisible packet case, simply ignore.  We don't want the client to be able to send a generic packet...
void Server::genericHandler(PACKET_GENERIC * packet){
    free(packet);
}

// Respond to any packet that does not have an associated server action.  Those other packets will be acked by response.
void Server::ackHandler(PACKET_ACK * packet){
    free(packet);
}

// Connect a host to the server by generating a session for it, and adding it to the gamestate sessions.  Do not generate new sessions.
void Server::connectHandler(PACKET_CONNECT * packet, sockaddr_in client){
    PACKET_CONNECT returnPacket;
    returnPacket.sessionId = gamestate->generateSession(packet->sessionId);
    cout << "\nNew connection started, session id " << returnPacket.sessionId << " sent to client!" << endl;
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CONNECT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

// Remove the session for a given user, effectively disconnecting it from the server.
void Server::disconnectHandler(PACKET_DISCONNECT * packet){
    gamestate->disconnectSession(packet->sessionId);
    free(packet);
}

// Remove the session for a given user, effectively disconnecting it from the server.
void Server::saltHandler(PACKET_GETSALT *packet, sockaddr_in client){
    PACKET_GETSALT returnPacket;
    cout << "saltHandler" << endl;
    // Check to make sure account already exists
    // If account doesn't exist, notify user
    // else, return the salt so the user can start key calculation
    int account_exists = sql->get_account_salt(packet->account, returnPacket.saltStringHex);
    if(account_exists){
        strcpy(returnPacket.account, packet->account);
        cout << "User " << returnPacket.account << " was found on the server." << endl;
        cout << "Returning salt: " << returnPacket.saltStringHex << endl;
    }
    else {
        cout << "User " << packet->account << " was not found on the server!" << endl;
        //string failedAccount = "FAILED";
        strcpy(returnPacket.account, "failed");
    }
    // Either return the salt or return the response
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_GETSALT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void Server::createAccountHandler(PACKET_CREATEACCOUNT *packet, sockaddr_in client){
    PACKET_CREATEACCOUNT returnPacket;
    if(gamestate->createAccount(packet->account, packet->keyStringHex, packet->saltStringHex)) {
        cout << "User " << packet->account << " was created successfully!" << endl;
        strcpy(returnPacket.account, packet->account);
    }
    else {
        cout << "Failed to create user " << packet->account << endl;
        // Resue the same packet as the return packet
        strcpy(returnPacket.account, "FAILED");
    }
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CREATEACCOUNT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void Server::loginHandler(PACKET_LOGIN * packet, sockaddr_in client){
    PACKET_CREATEACCOUNT returnPacket;
    if(gamestate->loginUser(packet->account, packet->keyStringHex)) {
        cout << "User " << packet->account << " logged in successfully!" << endl;
        strcpy(returnPacket.account, packet->account);
    }
    else {
        cout << "Failed login attempt for user: " << packet->account << endl;
        // Resue the same packet as the return packet
        strcpy(returnPacket.account, "FAILED");
    }
    sendto(sockfd, (void *)&returnPacket, sizeof(PACKET_CREATEACCOUNT), 0, (struct sockaddr *)&client, sizeof(client));
    free(packet);
}

void Server::listCharactersHandler(PACKET_LISTCHARACTERS * packet){
    free(packet);
}

void Server::selectCharacterHandler(PACKET_SELECTCHARACTER * packet){
    gamestate->selectPlayer(packet->sessionId);
    free(packet);
}

void Server::deleteCharacterHandler(PACKET_DELETECHARACTER * packet){
    free(packet);
}

void Server::createCharacterHandler(PACKET_CREATECHARACTER * packet){
    free(packet);
}

void Server::initializeGameHandler(PACKET_INITIALIZEGAME * packet){
    free(packet);
}

void Server::updatePcHandler(PACKET_UPDATEPC * packet){
    free(packet);
}

void Server::updateNpcHandler(PACKET_UPDATENPC * packet){
    free(packet);
}

void Server::sendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet){
    if (gamestate->verifyActiveSession(packet->sessionId)){
        gamestate->playerCommand(packet->command);
    }
    else{
        cout << "Nonactive session requested to send a player command..." << packet->sessionId << endl;
    }
    free(packet);
}

void Server::sendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet){
    free(packet);
}

void Server::sendServerActionHandler(PACKET_SENDSERVERACTION * packet){
    free(packet);
}
