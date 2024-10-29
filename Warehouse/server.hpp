
#include <arpa/inet.h>	//inet_addr
#include <pthread.h>
#include <stdio.h>
#include <string.h>	//strlen
#include <sys/socket.h>

class Server
{
  public:
    Server();
    ~Server();

    void Listen();

  private:
    void CreateSocket();
    int AcceptMessage();

    struct sockaddr_in server, client;
    int socket_;
    const u_int16_t port = 1234;
    pthread_t client_thread_;
};
