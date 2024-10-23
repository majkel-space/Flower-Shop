#include <boost/asio.hpp>
#include <iostream>
#include "server.hpp"

using tcpip = boost::asio::ip::tcp;

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
