//Copyright © 2023 Charles Kerr. All rights reserved.

#include "process0x83.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "packet/packet.hpp"

using namespace std::string_literals ;

/*
 Packet Name: Delete Character
 Last Modified: 2009-03-02 08:09:36
 Modified By: Turley

 Packet: 0x83
 Sent By: Client
 Size: 39 Bytes

 Packet Build
 BYTE[1] cmd
 BYTE[30] password
 BYTE[4] charIndex
 BYTE[4] clientIP

 Subcommand Build
 N/A

 Notes
 N/A
 */
//======================================================================
//======================================================================
auto processPacket0x83(Client *client, std::vector<std::uint8_t> &&data) -> void {
    
}

