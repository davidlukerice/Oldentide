// Filename:    AdminShell.cpp
// Author:      Joseph DeVictoria
// Date:        Mar_6_2016
// Purpose:     Provide an interface for the administrator to interact with
//              the server.  This class will handle all server admin commands.

#include "AdminShell.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

AdminShell::AdminShell(SQLConnector * input){
    sql = input;
    gethostname(serverHostname, HOST_NAME_MAX);
}

AdminShell::~AdminShell(){
    return;
}

void AdminShell::operator()(){
    run();
}

void AdminShell::run(){
    string adminCommand; 
    cout << "Starting Server Administrator Shell.\n";
    printLogo();
    while(true){
	    do
	    {
            cout << "OldentideAdmin@" << serverHostname << ": ";
            getline(cin,adminCommand);
	    }while(adminCommand.empty());
        vector<string> adminTokens = Utils::tokenfy(adminCommand, ' ');
        if (adminTokens[0] == "/shutdown"){
            cout << "Oldentide Dedicated Server is shutting down..." << endl;
            exit(EXIT_SUCCESS);
            return;
        }
        else if (adminTokens[0] == "/list"){
            if (adminTokens.size() == 2){
                cout << adminTokens[1];
                if (adminTokens[1] == "players"){
                    cout << "PCSSSSSS" << endl;          
                }
                if (adminTokens[1] == "npcs"){
                    cout << "NPCSSSSS" << endl;    
                }
            }
            else{
                printUsage();
            }
        }
        else if (adminTokens[0] == "/db"){
            string cmd = adminCommand.erase(0,4);
            sql->execute(cmd);
        }
        else{
            printUsage();
        }
    }
}

void AdminShell::printUsage(){
    cout << "Dedicated Server Admin Usage:" << endl;
    cout << "/shutdown    = Shuts down the server." << endl;
    cout << "/list <var>  = Lists all entities of given <var> on server, where <var> is [players, npcs]." << endl;
    cout << "/db <query>  = Runs a given sql query on the sqlite3 database." << endl;
}

void AdminShell::printLogo(){
    cout << "  ____           ___   _____         _____  _____  ___   _____" << endl;
    cout << " /    \\  |      |   \\  |      |   |    |      |    |  \\  |" << endl;
    cout << "/      \\ |      |    \\ |      |\\  |    |      |    |   \\ |" << endl;
    cout << "|      | |      |    | |___   | \\ |    |      |    |   | |___" << endl;
    cout << "\\      / |      |   /  |      |  \\|    |      |    |   / |" << endl;
    cout << " \\____/  |_____ |__/   |____  |   \\    |    __|__  |__/  |____" << endl;
    cout << " " << endl; 
    cout << "                              |" << endl;
    cout << "                             / \\" << endl;
    cout << "                            /\\_/\\" << endl;
    cout << "                           / | | \\" << endl;
    cout << "                           \\ |_| /" << endl;
    cout << "                            \\/ \\/" << endl;
    cout << "                             \\ /" << endl;
    cout << "                              |" << endl;
    cout << " " << endl;
}
