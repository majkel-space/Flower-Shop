#include "server.hpp"

Server::Server(boost::asio::io_service& io_service) : acceptor_(io_service, tcpip::endpoint(tcpip::v4(), 1234))
{
    StartAccept();
}

void Server::HandleAccept(std::shared_ptr<ConnectionHandler> connection, const boost::system::error_code& error)
{
    if (!error)
    {
        connection->Start();
    }
    StartAccept();
}

void Server::StartAccept()
{
    std::shared_ptr<ConnectionHandler> connection =
        ConnectionHandler::Create(static_cast<boost::asio::io_context&>(acceptor_.get_executor().context()));

    acceptor_.async_accept(connection->GetSocket(),
                           boost::bind(&Server::HandleAccept, this, connection, boost::asio::placeholders::error));
}
