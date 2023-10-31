//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef process0x80_hpp
#define process0x80_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
//======================================================================
/*
 Packet Name: Login Request
 Last Modified: 2009-02-28 18:42:51
 Modified By: MuadDib

 Packet: 0x80
 Sent By: Client
 Size: 62 Bytes

 Packet Build
 BYTE[1] Command
 BYTE[30] Account Name
 BYTE[30] Password
 BYTE[1] NextLoginKey value from uo.cfg on client machine.

 Subcommand Build
 N/A

 Notes
 N/A
 */
class Client ;

auto processPacket0x80(Client *client, std::vector<std::uint8_t> &&data) -> void ;
#endif /* process0x80_hpp */
