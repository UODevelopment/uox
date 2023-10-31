//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef createpacket0xa8_hpp
#define createpacket0xa8_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include "type/typedef.hpp"
class Client ;
class Packet ;
/*
 Packet: 0xA8
 Sent By: Server
 Size: Variable

 Packet Build
 BYTE[1] cmd
 BYTE[2] length
 BYTE[1] System Info Flag
 BYTE[2] # of servers

 Then each server --
 BYTE[2] server index (0-based)
 BYTE[32] server name
 BYTE percent full
 BYTE timezone
 BYTE[4] server ip to ping

 Subcommand Build
 N/A

 Notes
 System Info Flags: 0xCC - Do not send video card info. 0x64 - Send Video card. RunUO And SteamEngine both send 0x5D.

 Server IP has to be sent in reverse order. For example, 192.168.0.1 is sent as 0100A8C0.
 */

auto createPacket0xA8(Client *client) -> Packet;

#endif /* createpacket0xa8_hpp */
