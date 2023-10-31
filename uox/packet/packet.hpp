//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef packet_hpp
#define packet_hpp

#include <cstdint>
#include <ostream>
#include <unordered_map>
#include <string>

#include "utility/buffer.hpp"
#include "clientversion.hpp"
#include "type/typedef.hpp"
//======================================================================
class Packet : public util::Buffer {
    static const std::vector<std::string> PACKETNAME ;
public:
    static auto nameFor(packetid_t id) -> const std::string & ;
    Packet() ;
    virtual ~Packet() = default ;
    Packet(packetid_t id, int size) ;
    Packet(const util::Buffer &buffer) ;
    Packet( util::Buffer &&buffer) ;
    Packet(const Packet &buffer) ;
    Packet( Packet &&buffer) ;
    Packet(const std::vector<std::uint8_t> &data) ;
    Packet( std::vector<std::uint8_t> &&data) ;

    auto name() const -> const std::string& ;
    
    auto finalize(bool variable = false) -> void ;
    auto packetID() const -> packetid_t ;
    auto setPacketID(packetid_t id) -> void ;
    auto bufferSize() -> int ;
    auto size(bool variable = false) const -> int ;
    auto packetData() const -> std::vector<std::uint8_t>  ;
    auto huffmanData() const -> std::vector<std::uint8_t> ;
    auto dump(std::ostream &output) const -> void ;
};

#endif /* packet_hpp */
