//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef server_hpp
#define server_hpp

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "asio/asio.hpp"

#include "client.hpp"
#include "utility/ip4util.hpp"

//======================================================================
class Server {
    asio::io_service io_service ;
    asio::ip::tcp::acceptor acceptor ;
    util::net::IP4List allow ;
    util::net::IP4List deny ;
    util::net::IP4Relay relay ;
    
    std::thread loopThread ;
    
    std::mutex clientAccess ;
    std::vector<std::shared_ptr<Client>> clients ;
    
    bool shouldLog ;
    std::filesystem::path logPath ;
    
    auto allowIP(util::net::ip4_t ipaddress) -> bool ;
    auto relayIP(util::net::ip4_t ipaddress) -> util::net::ip4_t ;

    auto startAccept() -> void ;
    auto loop() -> void ;

public:
    Server() ;
    ~Server() ;
    auto listen(int port) -> void ;
    auto setAccess(const std::filesystem::path &allowpath, const std::filesystem::path &denypath) -> void ;
    auto setPublicIP(const std::string &ip) -> void ;
    auto setLogInfo(const std::filesystem::path &logpath,bool shouldLog) -> void ;
    auto handleAccept(Client::ClientPointer connection,const asio::error_code& err) -> void ;
    auto start() ->void ;
    auto stop() -> void ;
    auto grabData() -> std::vector<std::pair<std::shared_ptr<Client>,std::vector<std::uint8_t>>> ;
};

#endif /* server_hpp */
