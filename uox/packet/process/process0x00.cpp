//Copyright © 2023 Charles Kerr. All rights reserved.

#include "process0x00.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "packet/packet.hpp"

using namespace std::string_literals ;
/*
 Packet Name: Create Character
 Last Modified: 2009-12-03 04:06:03
 Modified By: Turley

 Packet: 0x00
 Sent By: Client
 Size: 104 bytes

 Packet Build
 BYTE[1] Command
 BYTE[4] pattern1 (0xedededed)
 BYTE[4] pattern2 (0xffffffff)
 BYTE[1] pattern3 (0x00)
 BYTE[30] char name
 BYTE[2] unknown0
 BYTE[4] clientflag (see notes)
 BYTE[4] unknown1
 BYTE[4] logincount
 BYTE[1] profession
 BYTE[15] unknown2
 BYTE[1] sex (see notes)
 BYTE[1] str
 BYTE[1] dex
 BYTE[1] int
 BYTE[1] skill1
 BYTE[1] skill1value
 BYTE[1] skill2
 BYTE[1] skill2value
 BYTE[1] skill3
 BYTE[1] skill3value
 BYTE[2] skinColor
 BYTE[2] hairStyle
 BYTE[2] hairColor
 BYTE[2] facial hair
 BYTE[2] facial hair color
 BYTE[2] location # from starting list
 BYTE[2] unknown3 (Usually 0x00 in testing)
 BYTE[2] slot
 BYTE[4] clientIP
 BYTE[2] shirt color
 BYTE[2] pants color

 Subcommand Build
 N/A

 Notes
 Note: pattern3 is set to 0xFF to early signal a Krrios client user, where it expects a 0xF0 | 0x00 before login confirm

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
 Sex: 0=Male Human, 1=Female Human, 2=Male Elf, 3=Female Elf
 Since client 7.0:
 Sex: 0=Male Human, 1=Female Human, 2=Male Human, 3=Female Human, 4=Male Elf, 5=Female Elf, 6=Male Gargoyle, 7=Female Gargoyle
 Str, dex and int should always sum to 65.
 Str, dex and int should always be between 10 and 45, inclusive.
 Skill1, skill2, and skill3 should never be the same value.
 Skill1, skill2, and skill3 should always be between 0 and 45, inclusive.
 Skill1value, skill2value, and skill3value should always sum to 100.
 Skill1value, skill2value, and skill3value should always be between 0 and 50, inclusive.
 SkinColor should always be between 0x3EA and 0x422, exclusive.
 HairColor and facialHairColor should always be between 0x44E and 0x4AD, exclusive.
 HairStyle should be between 0x203B and 0x204A, exclusive, and it should also exclude 0x203D to 0x2044, exclusive.
 FacialHairStyle should be between 0x203E and 0x204D
 Shirt color and Pants color need bounds checking too.
 */
//======================================================================
auto processPacket0x00(Client *client, std::vector<std::uint8_t> &&data) -> void {
    
}

