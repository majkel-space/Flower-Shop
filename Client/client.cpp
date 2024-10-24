#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "client.hpp"

Client::Client()
{
    CreateSocket();
}

Client::~Client()
{
    close(socket_);
}

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
}


void Client::SendMessage()
{
    const char* msg = "Hello from Client\n";
    send(socket_, msg, strlen(msg), 0);
}

void Client::GetResponse()
{
    const int size = 1024;
    char buffer[size];
    int bytes_read = read(socket_, buffer, size);
    std::cout << buffer << std::endl;

}
