# Client Server multithreaded application

## Project description
Project show client server connection with use of std::thread and POSIX libraries.
There is just one client so there is no need to use asynchronus socket listening with non blocking socket mechanism.
Used methodes:
- read(), write() for handling messages in ClientHandler
- read(), send() for handling messages on Client side
- socket() for creating sockets
- connect() on Client side
- bind() to bind socket with adresses
- listen() for catching any incomming connections
- accept() on Server side for catching connection from Client side

## Run
1. build main CMake
	navigate to build folder
	enter command 'cmake --build .'
2. Run server with ./Warehouse/server.o
3. Run client with ./Client/client.o
4. To stop hit 'Ctrl+C' on server console
