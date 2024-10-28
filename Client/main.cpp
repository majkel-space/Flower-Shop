#include "client.hpp"

int main()
{
    Client client, client2;
    for(auto it = 0U; it < 5; ++it)
    {
        client.ConnectToServer();
        // client2.ConnectToServer();
    }
    return 0;
}
