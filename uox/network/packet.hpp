//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef packet_hpp
#define packet_hpp

#include <cstdint>
#include <ostream>
#include <unordered_map>
#include <string>

#include "buffer.hpp"
#include "clientversion.hpp"
using packetid_t = int ;
//======================================================================
class Packet : public util::Buffer {
public:
    Packet() ;
    Packet(const util::Buffer &buffer) ;
    Packet( util::Buffer &&buffer) ;
    Packet(const Packet &buffer) ;
    Packet( Packet &&buffer) ;
    Packet(const std::vector<std::uint8_t> &data) ;
    Packet( std::vector<std::uint8_t> &&data) ;

    auto name() const -> const std::string& ;
    auto variable() const -> bool ;
    
    auto finalize() -> void ;
    auto packetID() const -> packetid_t ;
    auto setPacketID(packetid_t id) -> void ;
    auto bufferSize() -> int ;
    auto size() -> int ;
    auto packetData() const -> std::vector<std::uint8_t>  ;
    auto huffmanData() const -> std::vector<std::uint8_t> ;
    auto dump(std::ostream &output) const -> void ;
};

#endif /* packet_hpp */
