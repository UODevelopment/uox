//Copyright © 2023 Charles Kerr. All rights reserved.

#include "packet.hpp"

#include <algorithm>
#include <stdexcept>

#include "huffman.hpp"
#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
// Packet
//======================================================================
//====================================================================
Packet::Packet():util::Buffer() {
}
//====================================================================
Packet::Packet(const util::Buffer &buffer):util::Buffer(buffer) {
}
//====================================================================
Packet::Packet( util::Buffer &&buffer): util::Buffer(std::move(buffer)) {
}
//====================================================================
Packet::Packet(const Packet &packet):util::Buffer(packet) {
}
//====================================================================
Packet::Packet( Packet &&packet):util::Buffer(std::move(packet)) {
}
//====================================================================
Packet::Packet(const std::vector<std::uint8_t> &data) : util::Buffer(data){
}
//====================================================================
Packet::Packet( std::vector<std::uint8_t> &&data): util::Buffer(std::move(data))  {
}

//====================================================================
auto Packet::name() const -> const std::string& {
    static std::string temp ;
    return temp ;
}
//====================================================================
auto Packet::finalize() -> void {
    if (this->variable()){
        this->write(static_cast<std::uint16_t>(data.size()),1);
    }
}
//====================================================================
auto Packet::packetID() const -> packetid_t {
    if (!data.empty()){
        return static_cast<packetid_t>(this->read<std::uint8_t>(0));
    }
    return -1 ;
}
//====================================================================
auto Packet::setPacketID(packetid_t id) -> void {
    if (data.empty()){
        data.resize(1) ;
    }
    this->write(static_cast<std::uint8_t>(id),0);
}

//====================================================================
auto Packet::bufferSize() -> int {
    return static_cast<int>(data.size());
}
//====================================================================
auto Packet::size() -> int {
    
    if (this->variable() && data.size()>=3){
        return static_cast<int>(this->read<std::uint16_t>(1));
    }
    return static_cast<int>(data.size());
}
//====================================================================
auto Packet::packetData() const -> std::vector<std::uint8_t>  {
    return data ;
}
//====================================================================
auto Packet::huffmanData() const -> std::vector<std::uint8_t> {
    return packHuffman(data);
}

//====================================================================
auto Packet::dump(std::ostream &output) const -> void {
    output <<"Packet#: "<< util::ntos(packetID(),16,true,2)<< " Length: " << data.size() << " Name: " << name() <<"\n";
    util::Buffer::dump(output) ;
}
