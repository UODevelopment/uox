//Copyright © 2023 Charles Kerr. All rights reserved.

#include "createpacket0x8c.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "packet/packet.hpp"
#include "packet0x8c.hpp"
#include "configuration/serverconfig.hpp"

using namespace std::string_literals ;

extern ServerConfig serverConfig ;
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
 N/A */

//======================================================================
auto createPacket0x8C(Client *client) -> Packet{
    auto packet = Packet0x8C() ;
    packet.setIPPort(client->relay(), static_cast<int>(serverConfig.intValue[IntCollection::PORT]));
    packet.setKey(static_cast<std::uint32_t>(serverConfig.intValue[IntCollection::SERVERKEY]));
    return packet ;
}

