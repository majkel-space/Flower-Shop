#include <arpa/inet.h> // inet_addr()
#include <strings.h> // bzero()
#include <iostream>
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 1234
#define SA struct sockaddr

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cout << "socket creation failed...\n";
        exit(0);
    }
    else
        std::cout << "Socket successfully created..\n";
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        std::cout << "connection with the server failed...\n";
        exit(0);
    }
    else
        std::cout << "connected to the server..\n";

    write(sockfd, "Hello from Client2!\n", sizeof("Hello from Client2!\n"));

    close(sockfd);
}

