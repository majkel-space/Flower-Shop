## Flower-Shop
Client Server multithreaded application

#Project description
Flower Shop
-  Warehouse
 
10 Clients who process orders in random durations
QUESTION: not process but generate orders?
QUESTION: they will have to use one of 3 sockets (delivery cars) and mind if it is not actually taken (mocked)
 
Server / Warehouse&Management
Infinite Stock
We only have 3 different Delivery Cars
QUESTION: this would be 3 threads with separate adress to which they are binded?
 
1 Server Thread : listener of its main server port -> place the order in a PRODUCER-CONSUMER structure
Delivery Car Threads will consume jobs as FIFO from the queue
Delivery times will be random in their own loop
QUESTION: "random in their own loop"
 
Goals: POSIX
Using blocking/non-blocking socket connections
Using mutex/conditional_variables for shared memory spaces between threads
 
- select, epoll
 
Emplace threads starting and joining in ctors and dtors
Should have a signal handler 
use std::atomic, std::conditional_variables, std::mutex, lock_guards....
