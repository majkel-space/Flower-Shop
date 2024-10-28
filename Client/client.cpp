#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "client.hpp"

void Client::CreateSocket()
{
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ < 0)
    {
        std::cerr << "Error: Socket not created\n";
    }

    server_address_.sin_family = AF_INET;
    server_address_.sin_port = htons(port);
}

void Client::ConnectToServer()
{
    CreateSocket();
    if (inet_pton(AF_INET, "127.0.0.1", &server_address_.sin_addr) <= 0)
    {
        std::cerr << "Error: Invalid Server address\n";
    }

    if (connect(socket_, (struct sockaddr *)&server_address_, sizeof(server_address_)) < 0)
    {
        std::cerr << "Error: Connection Failed\n";
    }

    SendMessage();
    GetResponse();
    close(socket_);
}

void Client::SendMessage()
{
    const char* msg = "Hello from Client\n";
    send(socket_, msg, strlen(msg) + 1, 0);
}

void Client::GetResponse()
{
    const int size = 1024;
    char buffer[size] = {0};
    int bytes_read = read(socket_, buffer, size - 1);
    if (bytes_read < 0)
    {
        std::cerr << "Error: Reading from Server\n";
    }
    else
    {
        buffer[bytes_read] = '\0';
        std::cout << buffer << std::endl;
    }
}
