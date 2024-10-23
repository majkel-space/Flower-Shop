#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <memory>

class ConnectionHandler : public std::enable_shared_from_this<ConnectionHandler>
{
  public:
    using tcpip = boost::asio::ip::tcp;

    ConnectionHandler(boost::asio::io_context& io_service): socket_(io_service) {}

    static std::shared_ptr<ConnectionHandler> Create(boost::asio::io_context& io_service)
    {
        return std::make_shared<ConnectionHandler>(io_service);
    }

    tcpip::socket& GetSocket();
    void Start();

  private:
    void HandleRead(const boost::system::error_code&, size_t);
    void HandleWrite(const boost::system::error_code&, size_t);

    tcpip::socket socket_;
    const std::string message_ = "Hello From Server!";
    enum { max_length = 1024 };
    char data_[max_length];
};
