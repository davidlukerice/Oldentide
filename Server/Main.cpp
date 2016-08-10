// Filename:    Main.cpp
// Author:      Joseph DeVictoria
// Date:        Jan_31_2016
// Purpose:     Contains the main method for the Oldentide dedicated server.

#include "Server.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    // TODO: Parameter checking
    // Have parameter checking and exit gracefully if server address and port aren't specified
    if(argc != 2){
        cout << "Invalid number of arguments passed to " << argv[0] << "; Exiting..." << endl;
        return 1;
    }
    int port = atoi(argv[1]);
    Server * server = new Server(port);
    server->run();
    delete server;
    return 0;
}
