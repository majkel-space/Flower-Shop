# Flower-Shop
Client Server multithreaded application

## Project description
Flower Shop
- Warehouse with 3 delivery cars (3 order handling threads)
- Warehouse each server thread will listen to its main server port
- Warehouse infninit stock with FIFO queue to gather all the orders
- Warehouse delivery of each order have random time
- Client is placing the order in a PRODUCER-CONSUMER structure
- Client 10 clients with orders generated in random times, all will use same socket

## Goals
- POSIX library to handle connections
- Signal handler
- blocking/non-blocking socket connections
- std::threads, std::atomic
- atomic_bool for handling break of connections
- mutex and conditional_variables for shared memory spaces between threads

Emplace threads starting and joining in ctors and dtors


## TODO
- Cient: random time order generator
- Cient: use 10 clients
- Server: orders queue
- Server: random time generator for handling orders
