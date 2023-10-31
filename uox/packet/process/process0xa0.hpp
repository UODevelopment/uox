//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef process0xa0_hpp
#define process0xa0_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

//======================================================================
/*
 Packet Name: Select Server
 Last Modified: 2009-03-25 15:45:02
 Modified By: MuadDib

 Packet: 0xA0
 Sent By: Client
 Size: 3 Bytes

 Packet Build
 BYTE[1] Command
 BYTE[2] Shard Chosen from Server List

 Subcommand Build
 N/A

 Notes
 N/A
 */
class Client ;

auto processPacket0xA0(Client *client, std::vector<std::uint8_t> &&data) -> void ;


#endif /* process0xa0_hpp */
