
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

class Client
{
  public:
    Client();
    ~Client();

    void ConnectToServer();

  private:
    void CreateSocket();
    void SendMessage();
    void GetResponse();

  int socket_ = 0;
  struct sockaddr_in server_address_;
  const u_int16_t port = 1234;
};
