//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef createpacket0x8c_hpp
#define createpacket0x8c_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "type/typedef.hpp"
//======================================================================
class Client ;
class Packet ;
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
 N/A */

auto createPacket0x8C(Client *client) -> Packet;


#endif /* createpacket0x8c_hpp */
