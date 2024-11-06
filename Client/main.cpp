#include <atomic>
#include <csignal>
#include <random>
#include <thread>
#include "client.hpp"

std::atomic<bool> run(true);

void SignalHandler(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "Stop signal recieved" << std::endl;
        run = false;
    }
}

void GenerateAndSendMessages(Client& client)
{
    while (run)
    {
        client.ConnectToServer();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(100, 5000);
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
    }
}

int main()
{
    std::signal(SIGINT, SignalHandler);
    Client client;
    GenerateAndSendMessages(client);

    return 0;
}
