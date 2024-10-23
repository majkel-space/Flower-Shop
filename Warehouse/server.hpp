#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include "connection_handler.hpp"

class Server
{
    using tcpip = boost::asio::ip::tcp;
  public:
    //constructor for accepting connection from client
    Server(boost::asio::io_service& io_service);

    void HandleAccept(std::shared_ptr<ConnectionHandler>, const boost::system::error_code&);

  private:
    void StartAccept();

    tcpip::acceptor acceptor_;
};
