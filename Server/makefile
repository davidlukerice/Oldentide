BIN = mkdir database server client

all : $(BIN)

mkdir : 
	mkdir -p bin db

database : mkdir
	sqlite3 db/Oldentide.db < InitializeDb.sql

server : mkdir
	g++ -g AdminShell.cpp Character.cpp GameState.cpp Main.cpp Npc.cpp Server.cpp Player.cpp SQLConnector.cpp Utils.cpp AccountManager.cpp -std=c++11 -ldl -lpthread -lsqlite3 -lcrypto -pthread -o bin/Server

client : mkdir
	g++ -g TestClient.cpp Utils.cpp LoginManager.cpp -std=c++11 -lcrypto -lpthread -o bin/Client

clean :
	rm -f bin/Server bin/Client

.PHONY: All, Clean
