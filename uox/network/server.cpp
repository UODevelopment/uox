//Copyright © 2023 Charles Kerr. All rights reserved.

#include "server.hpp"

#include <algorithm>
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
Server::Server(int port):acceptor(io_service),serverSocket(io_service) {
    acceptor = tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port ));
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

