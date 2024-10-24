
#include <arpa/inet.h>	//inet_addr
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
    void ReadMessage(const int&);
    void WriteMessage(const int&);

    struct sockaddr_in server, client;
    int socket_;
    const u_int16_t port = 1234;
    const char* server_message = "Hello from server\n";
};
