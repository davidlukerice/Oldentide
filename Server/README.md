Oldentide Dedicated Server
==
The *Oldentide Dedicated Server* is open source project, built in [C++][1], to implement the 
backend game state for the multiplayer online role-playing game [*Oldentide*][2].  This 
directory contains all of the code necessary to build and run the dedicated server.

The "from scratch" build process breaks down into three main steps, with an additional
step used during the development process:

1. Create the database and generate all of the needed tables.
2. Populate the database with NPC information.
3. Compile the dedicated server.
4. Compile the test client.

Requirements
------------
The *Oldentide Dedicated Server* currently supports a Linux development and runtime environment.  

Operating Systems
------------
All development and testing is currently done on a 64-Bit linux environment.
[Ubuntu 16.04.1 LTS][3] are recommended. 
Other distributions with similar package versions will work, too.

Compilers
------------
Building *Oldentide Dedicated Server* is currently possible with the following compiler:
* *g++* - Currently all development is done on the [g++][4] compiler in a 64-bit 
   environment.  A makefile is included to simplify compilation!

*cmake may possibly be supported in future releases...*

Dependencies
------------
* sqlite3 - To store data, the simple, lightweight [sqlite3][5] database is used.
* libsqlite3-dev - To develop with [sqlite3][5], we need the c++ libraries.  This
  library is the package name on debian based systems.
* openssl 1.0.2h or beyond - [Openssl][6] provides encryption algorithms used when 
  authenticating clients.

Server and Test Client Usage
------------
In linux, cd into Oldentide/Server/ and run

    make 

If everything built properly, run

    bin/Server <Port>

where <Port> is the port the server is using.

To test that the server is running, in a separate terminal, run

    bin/Client <IP> <Port>

Where <IP> is the address of the server and <Port> is the port of the server.

[1]: http://www.cppreference.com/ "C / C++ reference"
[2]: http://www.oldentide.com/ "Oldentide, a game where you can be anyone!"
[3]: http://www.ubuntu.com/ "Ubuntu · The world's most popular free OS"
[4]: https://gcc.gnu.org/ "Gnu C / C++ Compiler"
[5]: https://www.sqlite.org/ "SQLite 3"
[6]: https://www.openssl.org/ "Openssl"
