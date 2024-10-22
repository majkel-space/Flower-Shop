#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <memory>
#include <string>

using tcpip = boost::asio::ip::tcp;

class ConnectionHandler : public std::enable_shared_from_this<ConnectionHandler>
{
  public:
    using pointer = std::shared_ptr<ConnectionHandler>;
    ConnectionHandler(boost::asio::io_context& io_service): socket_(io_service) {}
    static pointer Create(boost::asio::io_context& io_service)
    {
        return std::make_shared<ConnectionHandler>(io_service);
    }
    tcpip::socket& socket()
    {
        return socket_;
    }
    void Start()
    {
        socket_.async_read_some(
            boost::asio::buffer(data_, max_length),
            boost::bind(&ConnectionHandler::HandleRead,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));

        socket_.async_write_some(
            boost::asio::buffer(message_, max_length),
            boost::bind(&ConnectionHandler::HandleWrite,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
    }

    void HandleRead(const boost::system::error_code& err, size_t bytes_transferred)
    {
        if (!err)
        {
            std::cout << data_ << std::endl;
        }
        else
        {
            std::cerr << "error: " << err.message() << std::endl;
            socket_.close();
        }
    }
    void HandleWrite(const boost::system::error_code& err, size_t bytes_transferred)
    {
        if (!err)
        {
           std::cout << "Server sent Hello message!"<< std::endl;
        }
        else
        {
            std::cerr << "error: " << err.message() << std::endl;
            socket_.close();
        }
    }

  private:
    tcpip::socket socket_;
    const std::string message_ = "Hello From Server!";
    enum { max_length = 1024 };
    char data_[max_length];
};

class Server
{
  public:
//constructor for accepting connection from client
    Server(boost::asio::io_service& io_service): acceptor_(io_service, tcpip::endpoint(tcpip::v4(), 1234))
    {
       StartAccept();
    }
    void handle_accept(ConnectionHandler::pointer connection, const boost::system::error_code& err)
    {
      if (!err)
      {
          connection->Start();
      }
      StartAccept();
  }
  private:
    tcpip::acceptor acceptor_;

    void StartAccept()
    {
         ConnectionHandler::pointer connection = ConnectionHandler::Create(
            static_cast<boost::asio::io_context&>(acceptor_.get_executor().context()));

         acceptor_.async_accept(connection->socket(),
            boost::bind(&Server::handle_accept, this, connection,
            boost::asio::placeholders::error));
    }
};

int main()
{
    try
    {
        boost::asio::io_service io_service;
        Server server(io_service);
        io_service.run();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
  return 0;
}
