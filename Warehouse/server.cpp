#include <iostream>
#include <unistd.h>
#include "connection_handler.hpp"
#include "server.hpp"

void* HandleClient(void* arg)
{
    int client_socket = *(int*)arg;
    ConnectionHandler handler(client_socket);
    handler.HandleConnection();
    delete (int*)arg;
    return nullptr;
}

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
    while (true)
    {
        puts("Waiting for incoming connections...");
        listen(socket_, 3);
        auto* client_socket = new int(AcceptMessage());
        if (*client_socket >= 0)
        {
            if (pthread_create(&client_thread_, nullptr, HandleClient, client_socket) != 0)
            {
                std::cerr << "Error: Unable to create thread\n";
                delete client_socket;
            }
            else
            {
                pthread_detach(client_thread_);
            }
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

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if( bind(socket_, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        std::cerr << "Error: Bind Failed\n";
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
