// Filename:    Server.h
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Header for dedicated server class.
//              This server is a traditional Universal Datagram Protocol
//              (UDP) Server which will recieve and handle all game
//              packets sent from client.

#ifndef OLDENTIDE_OLDENTIDESERVER_H
#define OLDENTIDE_OLDENTIDESERVER_H

#include "AdminShell.h"
#include "GameState.h"
#include "Npc.h"
#include "Packets.h"
#include "Player.h"
#include "SQLConnector.h"
#include <arpa/inet.h>
#include <set>
#include <string>

class Server{
    public:
        Server(int port);
        ~Server();
        void run();
    private:
        int sockfd;
        SQLConnector * sql;
        GameState * gamestate;
        AdminShell * adminshell;
        void genericHandler(PACKET_GENERIC * packet);
        void ackHandler(PACKET_ACK * packet);
        void connectHandler(PACKET_CONNECT * packet, sockaddr_in client);
        void disconnectHandler(PACKET_DISCONNECT * packet);
        void saltHandler(PACKET_GETSALT *packet, sockaddr_in client);
        void createAccountHandler(PACKET_CREATEACCOUNT *packet, sockaddr_in client);
        void loginHandler(PACKET_LOGIN * packet, sockaddr_in client);
        void listCharactersHandler(PACKET_LISTCHARACTERS * packet);
        void selectCharacterHandler(PACKET_SELECTCHARACTER * packet);
        void deleteCharacterHandler(PACKET_DELETECHARACTER * packet);
        void createCharacterHandler(PACKET_CREATECHARACTER * packet);
        void initializeGameHandler(PACKET_INITIALIZEGAME * packet);
        void updatePcHandler(PACKET_UPDATEPC * packet);
        void updateNpcHandler(PACKET_UPDATENPC * packet);
        void sendPlayerCommandHandler(PACKET_SENDPLAYERCOMMAND * packet);
        void sendPlayerActionHandler(PACKET_SENDPLAYERACTION * packet);
        void sendServerActionHandler(PACKET_SENDSERVERACTION * packet);
        void getLatestMessageHandler(PACKET_GETLATESTMESSAGE * packet, sockaddr_in client);
        void messageHandler(PACKET_MESSAGE * packet, sockaddr_in client);
};

#endif //OLDENTIDE_SERVER_H
