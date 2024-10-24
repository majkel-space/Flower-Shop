#include <iostream>
#include <unistd.h>	//write
#include "server.hpp"

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
    puts("Waiting for incoming connections...");
    listen(socket_ , 3);

    const auto client_socket = AcceptMessage();
    ReadMessage(client_socket);
    WriteMessage(client_socket);
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

void Server::ReadMessage(const int& client_socket)
{
    char buffer[1000];
    read(client_socket, buffer, sizeof(buffer));
    std::cout << buffer << std::endl;
}

void Server::WriteMessage(const int& client_socket)
{
    write(client_socket, server_message, sizeof(server_message));
}
