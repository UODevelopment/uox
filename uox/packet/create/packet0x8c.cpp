//Copyright © 2023 Charles Kerr. All rights reserved.

#include "packet0x8c.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

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
//===========================================================================================
Packet0x8C::Packet0x8C():Packet(0x8c,11) {
    
}
//===========================================================================================
auto Packet0x8C::setIPPort(util::net::ip4_t ipaddress, int port) -> void {
    this->write(ipaddress,1) ;
    this->write(static_cast<std::uint16_t>(port),5) ;
}
//===========================================================================================
auto Packet0x8C::setKey(std::uint32_t key) -> void {
    this->write(key,7) ;
}
