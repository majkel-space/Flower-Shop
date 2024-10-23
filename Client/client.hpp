#include <boost/asio.hpp>
#include <iostream>
#include <string>

class Client
{
    using tcpip = boost::asio::ip::tcp;
  public:
    void SendMessage();

  private:
    void GenerateMessage(tcpip::socket&, boost::system::error_code&);
    void GetResponse(tcpip::socket&, boost::system::error_code&);
};
