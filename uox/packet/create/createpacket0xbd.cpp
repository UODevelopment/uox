//Copyright © 2023 Charles Kerr. All rights reserved.

#include "createpacket0xbd.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "packet/packet.hpp"

using namespace std::string_literals ;
/*
 Packet Name: Client Version
 Last Modified: 2008-10-11 12:57:22
 Modified By: MuadDib

 Packet: 0xBD
 Sent By: Both
 Size: Variable

 Packet Build
 BYTE[1] cmd
 BYTE[2] length
 If (client-version of packet)
 BYTE[len-3] string stating the client version (0 terminated) (like: "1.26.4")

 Subcommand Build
 N/A

 Notes
 Client version : client sends its version string (e.g "3.0.8j")
 Server version : 0xbd 0x0 0x3 (client replies with client version of this packet)

 Clients sends a client version of this packet ONCE at login (without server request.)
 */

//======================================================================
auto createPacket0xBD(Client *client) -> Packet{
    auto packet = Packet(0xBD,3) ;
    packet.write(static_cast<std::uint8_t>(3),2) ;
    return packet ;
}

