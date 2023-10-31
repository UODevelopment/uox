//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef packet0x8c_hpp
#define packet0x8c_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "packet/packet.hpp"
//======================================================================
/*
 Packet Name: Connect To Game Server
 Last Modified: 2008-10-11 12:57:22
 Modified By: MuadDib

 Packet: 0x8C
 Sent By: Server
 Size: 11 Bytes

 Packet Build
 BYTE[1] cmd
 BYTE[4] gameServer IP
 BYTE[2] gameServer port
 BYTE[4] new key

 Subcommand Build
 N/A

 Notes
 N/A
 */
class Packet0x8C : public Packet {
public:
    Packet0x8C();
    auto setIPPort(util::net::ip4_t ipaddress, int port) -> void ;
    auto setKey(std::uint32_t key) -> void ;
};
#endif /* packet0x8c_hpp */
