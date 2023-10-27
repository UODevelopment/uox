//Copyright © 2023 Charles Kerr. All rights reserved.

#include "client.hpp"

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <utility>

#include "incoming/packet0xef.hpp"

using namespace std::string_literals ;


//======================================================================
auto Client::createPointer(asio::io_service &io_service) -> ClientPointer {
    return ClientPointer(new Client(io_service));
}
//======================================================================
Client::Client(asio::io_service& io_service):netSocket(io_service),packetReady(false),firstPacket(true),dataRequested(0) {
    packetData = std::vector<std::uint8_t>(1,0) ;
}
//===================================================================
auto Client::socket() -> asio::ip::tcp::socket& {
    return netSocket ;
}
//===================================================================
auto Client::start() -> void {
    // Initiate read
    netSocket.async_read_some( asio::buffer(packetData.data(), 1), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

//===================================================================
// This isn't most effecient, we could/should do a "pump" type reads, just taking as
// much as we can, and then parse it. This makes us do up to three reads for a packet:
// Inital byte (for the packet id), then two bytes for size (if variable), then the rest of the data
// But for now, this is  good enough, and easier to follow in terms of data input
auto Client::processFirstPacket() -> void {
    if (packetData.size()==1){
        // Ok, we need to determine if the data is 
        if (packetData.at(0) == 0xEF){
            // This is 0xEF packet!
            packetData.resize(packetInfo.sizeFor(0xEF));
        }
        else {
            packetData.resize(4);
        }
        dataRequested = static_cast<int>(packetData.size()) -1 ;
        netSocket.async_read_some( asio::buffer(packetData.data()+1, dataRequested), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
    else {
        if (packetData.size() == packetInfo.sizeFor(0xEF)) {
            // We got an EF packet
            auto packet = Packet0xEF(packetData) ;
            packetInfo.update(packet.version());
        }
        firstPacket = false ;
        packetData.resize(1);
        dataRequested = 1 ;
        netSocket.async_read_some( asio::buffer(packetData.data(), dataRequested), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
    
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
            if (packetData.size() == 1 && packetInfo.sizeFor(packetData.at(0))!=1){
                // We need to get the actual data for this packet
                auto size = packetInfo.sizeFor(packetData.at(0)) ;
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
            else if (packetData.size()==3 && packetInfo.sizeFor(packetData.at(0))<0){
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
                packetReady = true ;
            }
        }
    }
}
//===================================================================
auto handle_write(const asio::error_code& err, size_t bytes_transferred) -> void {
    
}
//===================================================================
auto Client::grabPacket() -> std::vector<std::uint8_t> {
    auto empty = std::vector<std::uint8_t>() ;
    if (packetReady){
        std::swap(empty,packetData) ;
        packetReady = false ;
        // Initiate read
        netSocket.async_read_some( asio::buffer(packetData.data(), 1), std::bind(&Client::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    }
    return empty ;
}
