#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>
#include "connection_handler.hpp"
#include "server.hpp"

extern std::atomic<bool> run;

Server::Server()
{
    CreateSocket();
}

Server::~Server()
{
    close(socket_);
}

void Server::Listen()
{
    while (run)
    {
        puts("Waiting for incoming connections...");
        listen(socket_, 3);
        auto client_socket = AcceptMessage();
        if (client_socket >= 0)
        {
            ConnectionHandler connection_handler(client_socket);
            std::thread client_thread(connection_handler);
            client_thread.detach();
        }
    }
}

void Server::CreateSocket()
{
    socket_ = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_ == -1)
    {
        std::cerr << "Error: Socket not created\n";
    }

    puts("Socket created");

    // Socket might be block by system for some time (bind might failed then),
    // this method with SO_REUSEADDR allow to reuse the cosket adress once again
    if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        std::cerr << "Error: setsockopt failed\n";
        close(socket_);
        return;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if( bind(socket_, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        std::cerr << "Error: Bind Failed\n";
        close(socket_);
        return;
    }
}

int Server::AcceptMessage()
{
    const auto len = sizeof(sizeof(struct sockaddr_in));
    const auto client_socket = accept(socket_, (struct sockaddr*)&client, (socklen_t*)&len);
    if (client_socket < 0)
    {
        std::cerr << "Error: Accept Failed\n";
    }
    return client_socket;
}
