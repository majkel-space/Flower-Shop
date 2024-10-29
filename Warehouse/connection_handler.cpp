#include <cstring>
#include <iostream>
#include <unistd.h>
#include "connection_handler.hpp"

ConnectionHandler::ConnectionHandler(int client_socket)
    : client_socket_{client_socket}
{}

void ConnectionHandler::HandleConnection()
{
    ReadMessage();
    WriteMessage();
    close(client_socket_);
}

void ConnectionHandler::ReadMessage()
{
    const int size = 1024;
    char buffer[size] = {0};
    int bytes_read = read(client_socket_, buffer, size - 1);
     if (bytes_read < 0)
    {
        std::cerr << "Error: Reading from Client\n";
    }
    else
    {
        buffer[bytes_read] = '\0';
        std::cout << buffer << std::endl;
    }
}

void ConnectionHandler::WriteMessage()
{
    const char* server_message = "Hello from server\n";
    write(client_socket_, server_message, strlen(server_message) + 1);
}
