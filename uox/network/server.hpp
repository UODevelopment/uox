//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef server_hpp
#define server_hpp

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include "utility/ip4util.hpp"
#include "asio.hpp"
//======================================================================
class Server {
    asio::io_service io_service ;
    asio::ip::tcp::acceptor acceptor ;
    asio::ip::tcp::socket serverSocket ;
    util::net::IP4List allow ;
    util::net::IP4List deny ;
    util::net::IP4Relay relay ;
    
    auto allowIP(util::net::ip4_t ipaddress) -> bool ;
    auto relayIP(util::net::ip4_t ipaddress) -> util::net::ip4_t ;
    
public:
    Server(int port) ;
    auto setAccess(const std::filesystem::path &allowpath, const std::filesystem::path &denypath) -> void ;
    auto setPublicIP(const std::string &ip) -> void ;
};

#endif /* server_hpp */
