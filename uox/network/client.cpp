//Copyright © 2023 Charles Kerr. All rights reserved.

#include "client.hpp"

#include <algorithm>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <utility>

#include "account/accountentry.hpp"
#include "packet/createpacket.hpp"
#include "utility/ip4util.hpp"
#include "packet/huffman.hpp"
#include "packet/packet.hpp"
#include "utility/strutil.hpp"


using namespace std::string_literals ;


//====================================================================
// Packet0xEF
//====================================================================
//======================================================================
class Packet0xEF: public Packet{
    
public:
    Packet0xEF(const std::vector<std::uint8_t> &data) : Packet(data) {
    }
    Packet0xEF( std::vector<std::uint8_t> &&data) : Packet(std::move(data)){
    }
    Packet0xEF(const util::Buffer &data): Packet(data){
    }
    Packet0xEF( util::Buffer &&data): Packet(std::move(data)){
    }
    auto seed() const -> std::uint32_t  {
        return this->read<std::uint32_t>(1) ;
    }
    auto version() const -> ClientVersion {
        return ClientVersion(this->read<std::int32_t>(5),this->read<std::int32_t>(9),this->read<std::int32_t>(13),this->read<std::int32_t>(17)) ;
    }
};
//====================================================================
// Packet0xBD
//====================================================================
//======================================================================
class Packet0xBD : public Packet {
    
public:
    Packet0xBD(std::vector<std::uint8_t> &&data):Packet(std::move(data)){
        
    }
    auto version() const -> ClientVersion {
        if (data.size()<=3){
            throw std::runtime_error("Packet#: "s+util::ntos(packetID(),16,true,2)+" has insufficient size to read version"s);
        }
        return ClientVersion(this->read<std::string>(data.size()-this->size(true),3));

    }
};


//====================================================================
// Client
//====================================================================
//======================================================================

//===================================================================
auto Client::logKey(const std::vector<std::uint8_t> &data) -> void {
    if (shouldLog && !logpath.empty() ){
        auto output = std::ofstream(logpath.string(),std::ios::app) ;
        if (output.is_open()){
            output <<"Client->Server - " << util::timeNow()<<"\n";
            output << "Initial Key " << "\n";
            util::dump(output, data.data(), data.size(),16,10);
            output<<"\n";
        }
    }

}
//===================================================================
auto Client::logData(const std::vector<std::uint8_t> &data,bool sending) -> void {
    if (shouldLog && !logpath.empty() ){
        auto output = std::ofstream(logpath.string(),std::ios::app) ;
        if (output.is_open()){
            if (sending){
                output <<"Server->Client - " << util::timeNow()<<"\n";
            }
            else {
                output <<"Client->Server - " << util::timeNow()<<"\n";
            }
            output << "Packet: " << util::ntos(data.at(0),16,true,2)<<" Length: "<< data.size()<<" Name: "<< Packet::nameFor(data.at(0))<<"\n";
            util::dump(output, data.data(), data.size(),16,10);
            output<<"\n";
        }
    }
}
//===================================================================
// This isn't most efficient, we could/should do a "pump" type reads, just taking as
// much as we can, and then parse it. This makes us do up to three reads for a packet:
// Inital byte (for the packet id), then two bytes for size (if variable), then the rest of the data
// But for now, this is  good enough, and easier to follow in terms of data input
auto Client::processFirstPacket() -> void {
    if (packetData.size()==1){
        // Ok, we need to determine if the data is
        if (packetData.at(0) == 0xEF){
            // This is 0xEF packet!
            packetData.resize(packetSize.sizeFor(0xEF));
        }
        else {
            packetData.resize(4);
        }
        dataRequested = static_cast<int>(packetData.size()) -1 ;
        netSocket.async_read_some( asio::buffer(packetData.data()+1, dataRequested), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
    else {
        if (packetData.size() == packetSize.sizeFor(0xEF)) {
            this->logData(packetData, false);
            // We got an EF packet
            auto packet = Packet0xEF(packetData) ;
            packetSize.update(packet.version());
        }
        else {
            this->logKey(packetData);
        }
        firstPacket = false ;
        packetData.resize(1);
        dataRequested = 1 ;
        netSocket.async_read_some( asio::buffer(packetData.data(), dataRequested), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
    
}

//======================================================================
auto Client::createPointer(asio::io_service &io_service) -> ClientPointer {
    return ClientPointer(new Client(io_service));
}
//======================================================================
Client::Client(asio::io_service& io_service):netSocket(io_service),packetReady(false),firstPacket(true),dataRequested(0),relayIP(0),shouldLog(false),amountToSend(0),myPlayer(nullptr),account(nullptr) {
    packetData = std::vector<std::uint8_t>(1,0) ;
    lastPacketReceive =  std::chrono::steady_clock::now() ;
}
//======================================================================
Client::~Client(){
    myPlayer = nullptr ;
    if (account != nullptr){
        account->inUse = false ;
        account = nullptr ;
    }
}
//===================================================================
auto Client::initLogging(const std::filesystem::path &path, bool enableLog ) -> void {
    this->shouldLog = enableLog ;
    auto address = this->ipAddress() ;
    logpath = path / std::filesystem::path(util::format("client-%i_%i_%i_%i.log",(address>>24)&0xFF,(address>>16)&0xFF,(address>>8)&0xFF,address&0xFF));
}
//===================================================================
auto Client::setLogging(bool enable) -> void{
    this->shouldLog = enable ;
}
//===================================================================
auto Client::setVersion(const ClientVersion &version) ->void {
    this->clientVersion = version ;
    packetSize.update(version) ;
    if (account != nullptr){
        account->setVersion(version);
    }
}
//===================================================================
auto Client::version() const -> const ClientVersion& {
    return clientVersion ;
}
//===================================================================
auto Client::setType(const ClientType &type) -> void {
    this->clientType = type ;
}
//===================================================================
auto Client::type() const -> const ClientType& {
    return clientType;
}
//===================================================================
auto Client::send(Packet &&packet, bool compress) -> void {
    std::lock_guard lock(outgoingLock) ;
    if (amountToSend == 0 && outgoing.empty()){
        this->logData(packet.data,true) ;
        outgoingData = std::move(packet.data) ;
        if (compress){
            outgoingData = packHuffman(outgoingData);
        }
        amountToSend = static_cast<int>(outgoingData.size());
        netSocket.async_write_some( asio::buffer(outgoingData.data(), amountToSend), std::bind(&Client::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
    else {
        // We should do a move here,for later
        outgoing.push(std::make_pair(packet,compress) ) ;
    }
}

//===================================================================
auto Client::socket() -> asio::ip::tcp::socket& {
    return netSocket ;
}
//===================================================================
auto Client::start() -> void {
    // Initiate read
    dataRequested = 1 ;
    packetData = std::vector<std::uint8_t>(1,0) ;
    netSocket.async_read_some( asio::buffer(packetData.data(), 1), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}
//===================================================================
auto Client::relay() const -> util::net::ip4_t {
    return relayIP ;
}
//===================================================================
auto Client::setRelay( util::net::ip4_t relay) -> void {
    this->relayIP = relay ;
}
//===================================================================
// This isn't most effecient, we could/should do a "pump" type reads, just taking as
// much as we can, and then parse it. This makes us do up to three reads for a packet:
// Inital byte (for the packet id), then two bytes for size (if variable), then the rest of the data
// But for now, this is  good enough, and easier to follow in terms of data input
auto Client::handle_read(const asio::error_code& err, size_t bytes_transferred) -> void {
    if (err) {
        // We got an error!
        std::cerr << "Socket error: " << err.message()<< std::endl;
        netSocket.close();
        return ;
    }
    // This just looks to see if we got what we asked, if we didn't it requeues it
    if (bytes_transferred != dataRequested){
        // we need to get the rest
        netSocket.async_read_some( asio::buffer(packetData.data()+( packetData.size() - (dataRequested-bytes_transferred)), (dataRequested-bytes_transferred)), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
        dataRequested = (dataRequested-bytes_transferred);
    }
    else {
        // if firstData, we let process it separate
        if (firstPacket){
            processFirstPacket() ;
        }
        else {
            // We have a couple of choices here. If packetData size if 1, we need to see
            // if this is a 1 byte packet, or do we now need to figure out size
            // If the packetData size is 3, we need to check if a variable size packet, and get what
            // what we really need
            // Otherwise, we chould handle the packet
            // Now we do one other check, to see if we are just one byte
            if (packetData.size() == 1 && packetSize.sizeFor(packetData.at(0))!=1){
                // We need to get the actual data for this packet
                auto size = packetSize.sizeFor(packetData.at(0)) ;
                if (size <1){
                    packetData.resize(3);
                    dataRequested = 3 ;
                }
                else {
                    packetData.resize(size) ;
                    dataRequested = size ;
                }
                netSocket.async_read_some( asio::buffer(packetData.data()+( packetData.size() - (dataRequested-bytes_transferred)), (dataRequested-bytes_transferred)), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
                dataRequested = (dataRequested-bytes_transferred);
            }
            else if (packetData.size()==3 && packetSize.sizeFor(packetData.at(0))<0){
                // This was a variable, so now what is the real size?
                auto realsize = static_cast<int>((static_cast<std::uint16_t>(packetData.at(2)) << 8 ) | static_cast<std::uint16_t>(packetData.at(1))) ;
                packetData.resize(realsize);
                dataRequested = realsize ;
                bytes_transferred = 3 ;
                netSocket.async_read_some( asio::buffer(packetData.data()+( packetData.size() - (dataRequested-bytes_transferred)), (dataRequested-bytes_transferred)), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
                dataRequested = (dataRequested-bytes_transferred);
            }
            else {
                // We got everything!
                this->logData(packetData,false);
                // we have a special case for BD, because we want to get that as soon as possible, as it can impact packet sizes!
                if (packetData.at(0) == 0xBD){
                    auto packet = Packet0xBD(std::move(packetData)) ;
                    this->setVersion(packet.version()) ;
                    packetReady = false ;
                    packetData = std::vector<std::uint8_t>(1,0) ;
                    dataRequested = 1 ;
                    // Initiate read
                    netSocket.async_read_some( asio::buffer(packetData.data(), 1), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
                }
                else {
                    packetReady = true ;
                }
            }
        }
    }
}
//===================================================================
auto Client::handle_write(const asio::error_code& err, size_t bytes_transferred) -> void {
    if (err && bytes_transferred != 0) {
        // We got an error!
        std::cerr << "Socket error: " << err.message()<< std::endl;
        netSocket.close();
        return ;
    }
    std::lock_guard<std::mutex> lock(outgoingLock) ;
    if (bytes_transferred != amountToSend){
        // We didn't send the whole amount, resend the remaining
        amountToSend = amountToSend - static_cast<int>(bytes_transferred) ;
        netSocket.async_write_some( asio::buffer(outgoingData.data()+outgoingData.size() - amountToSend, amountToSend), std::bind(&Client::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));

    }
    else {
        amountToSend = 0 ;
    }
    if (amountToSend == 0) {
        if (!outgoing.empty()){
            auto tosend = outgoing.front() ; // maybe a move?
            outgoing.pop() ;
            outgoingData = std::move(tosend.first.data) ;
            logData(outgoingData, true);
            if (tosend.second){
                outgoingData = packHuffman(outgoingData) ;
            }
            amountToSend = static_cast<int>(outgoingData.size());
            netSocket.async_write_some( asio::buffer(outgoingData.data(), amountToSend), std::bind(&Client::handle_write, shared_from_this(),  std::placeholders::_1, std::placeholders::_2));

        }
    }
}
//===================================================================
auto Client::grabPacket() -> std::vector<std::uint8_t> {
    auto empty = std::vector<std::uint8_t>() ;
    if (packetReady){
        std::swap(empty,packetData) ;
        packetReady = false ;
        packetData.resize(1) ;
        dataRequested = 1 ;
        // Initiate read
        netSocket.async_read_some( asio::buffer(packetData.data(), 1), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
    return empty ;
}
//===================================================================
auto Client::setPlayer(std::shared_ptr<Player> &player) -> void {
    myPlayer = player ;
}
//===================================================================
auto Client::player() -> Player * {
    if (myPlayer != nullptr) {
        return myPlayer.get();
    }
    return nullptr ;
}
//===================================================================
auto Client::clearPlayer() -> void {
    myPlayer = nullptr ;
}
//===================================================================
auto Client::ipAddress() const -> util::net::ip4_t {
    return util::net::IP4Entry::describeIP(netSocket.remote_endpoint().address().to_string()) ;
}
//===================================================================
auto Client::idleMinutes() const -> int {
    return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - lastPacketReceive).count() ;
}
//===================================================================
auto Client::createPacket(packetid_t packetid) -> Packet {
    return ::createPacket(this, packetid) ;
}
//===================================================================
auto Client::sizeForPacket(packetid_t packetid) -> int {
    return packetSize.sizeFor(packetid);
}
//===================================================================
auto Client::close() -> void {
    netSocket.close() ;
}
