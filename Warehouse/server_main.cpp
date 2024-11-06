#include <csignal>
#include <atomic>
#include <iostream>
#include "server.hpp"

std::atomic<bool> run{true};

void SignalHandler(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "Stop signal recieved" << std::endl;
        run = false;
    }
}

int main()
{
    std::signal(SIGINT, SignalHandler);
    Server server;
    server.Listen();
    return 0;
}
