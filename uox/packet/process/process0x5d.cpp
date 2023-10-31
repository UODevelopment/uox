//Copyright © 2023 Charles Kerr. All rights reserved.

#include "process0x5d.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "packet/packet.hpp"

using namespace std::string_literals ;

//======================================================================
/*
Packet Name: Login Character
Last Modified: 2009-08-20 04:33:41
Modified By: Turley

Packet: 0x5D
Sent By: Client
Size: 73 Bytes

Packet Build
BYTE[1] cmd
BYTE[4] pattern1 (0xedededed)
BYTE[30] char name (0 terminated)
BYTE[2] unknown0
BYTE[4] clientflag (see notes)
BYTE[4] unknown1
BYTE[4] logincount
BYTE[16] unknown2
BYTE[4] slot choosen
BYTE[4] clientIP

Subcommand Build
N/A

Notes
clientflag:
t2a: 0x00,
renaissance: 0x01,
third dawn: 0x02,
lbr: 0x04,
aos: 0x08,
se: 0x10,
sa: 0x20,
uo3d: 0x40,
reserved: 0x80,
3dclient: 0x100
 */
//======================================================================
auto processPacket0x5D(Client *client, std::vector<std::uint8_t> &&data) -> void {
    
}

