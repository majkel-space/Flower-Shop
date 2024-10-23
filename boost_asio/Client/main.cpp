#include "client.hpp"

int main()
{
    Client client;
    for (auto it = 0U; it < 5U; ++it)
    {
        client.SendMessage();
    }
    return 0;
}
