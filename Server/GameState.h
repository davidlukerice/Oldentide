// Filename:    GameState.h
// Author:      Joseph DeVictoria
// Date:        Mar_2_2016
// Purpose:     Header for Game State class.
//              This class will be responsible for maintaining the Players,
//              NPCs necessary to preserve the game state.  It will also
//              perform the bulk of database interactions.

#ifndef OLDENTIDE_GAMESTATE_H
#define OLDENTIDE_GAMESTATE_H

#include "Npc.h"
#include "Player.h"
#include "SQLConnector.h"
#include <set>
#include <string>
#include <vector>
#include <map>

class GameState{
    public:
        GameState(SQLConnector * sql);
        ~GameState();
        bool verifySession(int sessionId);
        bool verifyActiveSession(int sessionId);
        bool createAccount(char * account, char * keyStringHex, char * saltStringHex);
        bool loginUser(char * account, char * keyStringHex);
        void disconnectSession(int sessionId);
        void playerCommand(char * command, int);
        void selectPlayer(int sessionId);
        int generateSession(int sessionId);
        long long int getGlobalMessageNumber();
        long long int getMessage(long long int, char *, char *);
        long long int storeMessage(std::string, int);
        void setSessionAccountName(char *, int);

    private:
        SQLConnector * sql;
        std::set<Player> players;
        std::set<Npc> npcs;
        std::set<int> sessions;
        std::set<int> activeSessions;
        // TODO: Make this players instead of accounts?
        std::map<int, std::string> sessionAccounts;
        int curSession;
        // The index of the array will be the global message number
        long long int globalMessageNumber;
        // Create a global array of char pointers for the messages
        // Malloc space for each new message
        std::vector<std::string> globalMessageArray;
        std::vector<int> globalMessageAccountArray;
        Player readPlayer(std::string name);
        void storePlayer(std::string name);
};

#endif // OLDENTIDE_GAMESTATE_H
