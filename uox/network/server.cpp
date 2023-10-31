//Copyright © 2023 Charles Kerr. All rights reserved.

#include "server.hpp"

#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std::string_literals ;
using namespace asio::ip ;
//======================================================================
auto Server::allowIP(util::net::ip4_t ipaddress) -> bool {
    if (!allow.empty()){
        return allow.contains(ipaddress) ;
    }
    return !deny.contains(ipaddress) ;
}
//======================================================================
auto Server::relayIP(util::net::ip4_t ipaddress) -> util::net::ip4_t {
    return relay.relayFor(ipaddress) ;
}

//======================================================================
auto Server::startAccept() -> void {
    // socket
     Client::ClientPointer connection = Client::createPointer(io_service);

    // asynchronous accept operation and wait for a new connection.
    acceptor.async_accept(connection->socket(),
        std::bind(&Server::handleAccept, this, connection,
        std::placeholders::_1));

}

//=======================================================================
auto Server::loop() -> void {
    io_service.run();
}
//======================================================================
Server::Server():acceptor(io_service) {
}
//======================================================================
Server::~Server(){
    io_service.stop() ;
    if (loopThread.joinable()){
        loopThread.join();
    }
}

//======================================================================
auto Server::listen(int port) -> void {
    acceptor = tcp::acceptor(io_service, tcp::endpoint(asio::ip::address_v4::any(), port ));
    startAccept();
}
//======================================================================
auto Server::setAccess(const std::filesystem::path &allowpath, const std::filesystem::path &denypath) -> void {
    allow.load(allowpath);
    deny.load(denypath) ;
}
//======================================================================
auto Server::setPublicIP(const std::string &ip) -> void {
    relay.setPublicIP(ip);
}
//======================================================================
auto Server::setLogInfo(const std::filesystem::path &logpath,bool shouldLog) -> void {
    this->logPath = logpath ;
    this->shouldLog = shouldLog ;
}

//======================================================================
auto Server::handleAccept(Client::ClientPointer connection,const asio::error_code& err) -> void {
    if (!err) {
        auto ip = connection->ipAddress() ;

        if (allowIP(ip)) {
            connection->setRelay(relayIP(ip));
            connection->initLogging(logPath, shouldLog);
            connection->start() ;
            std::lock_guard<std::mutex> lock(clientAccess);
            clients.push_back(connection);
        }
    }
    startAccept() ;
}
//======================================================================
auto Server::start() -> void {
    loopThread = std::thread(&Server::loop,this) ;
}
//======================================================================
auto Server::stop() -> void {
    io_service.stop() ;
}

//======================================================================
auto Server::grabData() -> std::vector<std::pair<std::shared_ptr<Client>,std::vector<std::uint8_t>>> {
    auto rvalue = std::vector< std::pair<std::shared_ptr<Client>,std::vector<std::uint8_t>>>() ;
    std::lock_guard<std::mutex> lock(clientAccess) ;
    for (auto iter = clients.begin();iter != clients.end();){
        auto data = (*iter)->grabPacket() ;
        if (!data.empty()){
            rvalue.push_back(std::make_pair(*iter, data));
        }
        // Now, lets see if the client is not valid
        if (!(*iter)->netSocket.is_open()){
            std::cout <<"Deleting client" << std::endl;
            iter = clients.erase(iter) ;
        }
        else {
            iter++ ;
        }
    }
    return rvalue ;
}
