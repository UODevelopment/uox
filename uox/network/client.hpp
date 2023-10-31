//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef client_hpp
#define client_hpp

#include <atomic>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <queue>
#include <utility>

#include "asio/asio.hpp"
#include "clienttype.hpp"
#include "clientversion.hpp"
#include "packet/packet.hpp"
#include "packet/packetsize.hpp"
#include "type/typedef.hpp"
class Server ;
class Packet ;
class Player ;
class AccountEntry ;
//======================================================================
class Client : public std::enable_shared_from_this<Client> {
private:
    friend class Server ;
    asio::ip::tcp::socket netSocket;
    
    std::vector<std::uint8_t> packetData ;
    PacketSize packetSize ;
    bool firstPacket ;
    int dataRequested ;
    std::atomic<bool> packetReady ;
    timepoint_t lastPacketReceive ;
    
    std::queue<std::pair<Packet,bool>> outgoing ;
    std::atomic<int> amountToSend ;
    std::vector<std::uint8_t> outgoingData ;
    std::mutex outgoingLock ;
    
    std::filesystem::path logpath ;
    bool shouldLog ;
    
    ClientVersion clientVersion ;
    ClientType clientType ;
    
    util::net::ip4_t relayIP ;

    std::shared_ptr<Player> myPlayer ;
    
    auto logKey(const std::vector<std::uint8_t> &data) -> void ;
    auto logData(const std::vector<std::uint8_t> &data,bool sending) -> void ;
    auto processFirstPacket() -> void ;
public:
    using ClientPointer = std::shared_ptr<Client> ;
    
    // **************************************************************
    // Things that the client "holds" for processing or associations
    inline static std::uint32_t serverKey ; // We want to check to ensure this client was relayed by this server (be careful about values, do not end in 0xEF)
    
    AccountEntry *account ; // What account this client is associated with

    // **************************************************************

    static auto createPointer(asio::io_service &io_service) -> ClientPointer ;
    
    Client(asio::io_service &io_service);
    ~Client() ;
    auto initLogging(const std::filesystem::path &path, bool enableLog ) -> void ;
    auto setLogging(bool enable) -> void ;

    auto setVersion(const ClientVersion &version) ->void ;
    auto version() const -> const ClientVersion& ;
    auto setType(const ClientType &type) -> void ;
    auto type() const -> const ClientType& ;
    auto send(Packet &&packet, bool compress = true ) -> void ;
    auto socket() -> asio::ip::tcp::socket& ;
    auto start() -> void ;
    auto relay() const -> util::net::ip4_t ;
    auto setRelay( util::net::ip4_t relay) -> void ;
    auto handle_read(const asio::error_code& err, size_t bytes_transferred) -> void ;
    auto handle_write(const asio::error_code& err, size_t bytes_transferred) -> void ;
    auto grabPacket() -> std::vector<std::uint8_t> ;
    auto setPlayer(std::shared_ptr<Player> &player) -> void ;
    auto player() -> Player* ;
    auto clearPlayer() -> void ;
    auto ipAddress() const -> util::net::ip4_t ;
    auto idleMinutes() const -> int ;
    auto createPacket(packetid_t packetid) -> Packet ;
    auto sizeForPacket(packetid_t packetid) -> int ;
    auto close() ->void ;
};

#endif /* client_hpp */
