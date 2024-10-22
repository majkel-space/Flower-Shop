#include <boost/asio.hpp>
#include <iostream>
#include <string>

using tcpip = boost::asio::ip::tcp;

void GenerateMessage(tcpip::socket& socket, boost::system::error_code& error)
{
    const std::string msg = "Hello from Client!\n";

    boost::asio::write( socket, boost::asio::buffer(msg), error );
    if( !error )
    {
        std::cout << "Client sent hello message!" << std::endl;
    }
    else
    {
        std::cout << "send failed: " << error.message() << std::endl;
    }
}

void GetResponse(tcpip::socket& socket, boost::system::error_code& error)
{
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if( error && error != boost::asio::error::eof )
    {
        std::cout << "receive failed: " << error.message() << std::endl;
    }
    else
    {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        std::cout << data << std::endl;
    }
}

void SendMessage()
{
    boost::asio::io_service io_service;
    tcpip::socket socket(io_service);
    socket.connect( tcpip::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234 ));
    boost::system::error_code error;

    GenerateMessage(socket, error);
    GetResponse(socket, error);
}

int main()
{
    SendMessage();
    return 0;
}
