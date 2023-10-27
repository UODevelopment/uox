//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef client_hpp
#define client_hpp

#include <atomic>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include "asio.hpp"
#include "packetinfo.hpp"
#include "type/typedef.hpp"
//======================================================================
class Client : public std::enable_shared_from_this<Client> {
private:
    asio::ip::tcp::socket netSocket;
    std::vector<std::uint8_t> packetData ;
    PacketInfo packetInfo ;
    bool firstPacket ;
    int dataRequested ;
    std::atomic<bool> packetReady ;
    
    auto processFirstPacket() -> void ;
    
public:
    typedef std::shared_ptr<Client> ClientPointer;
    static auto createPointer(asio::io_service &io_service) -> ClientPointer ;
    
    Client(asio::io_service &io_service);
    
    auto socket() -> asio::ip::tcp::socket& ;
    auto start() -> void ;
    
    
    auto handle_read(const asio::error_code& err, size_t bytes_transferred) -> void ;
    auto handle_write(const asio::error_code& err, size_t bytes_transferred) -> void ;
    auto grabPacket() -> std::vector<std::uint8_t> ;
};

#endif /* client_hpp */
