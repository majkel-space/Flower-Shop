#include "connection_handler.hpp"

using tcpip = boost::asio::ip::tcp;

tcpip::socket& ConnectionHandler::GetSocket()
{
    return socket_;
}

void ConnectionHandler::Start()
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

void ConnectionHandler::HandleRead(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << data_ << std::endl;
    }
    else
    {
        std::cerr << "error: " << error.message() << std::endl;
        socket_.close();
    }
}
void ConnectionHandler::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Server sent Hello message!"<< std::endl;
    }
    else
    {
        std::cerr << "error: " << error.message() << std::endl;
        socket_.close();
    }
}
