//Copyright © 2023 Charles Kerr. All rights reserved.

#include "createpacket0xb9.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "packet/packet.hpp"
#include "configuration/serverconfig.hpp"
using namespace std::string_literals ;

extern ServerConfig serverConfig;
/*
 Packet Name: Enable locked client features
 Last Modified: 2018-08-17 05:48:00
 Modified By: Tomi

 Packet: 0xB9
 Sent By: Server
 Size: 3/5 Bytes

 Packet Build
 Original Legacy Client Version
 BYTE[1] 0xB9
 BYTE[2] Feature Bitflag

 From Legacy Client 6.0.14.2+
 BYTE[1] 0xB9
 BYTE[4] Feature Bitflag

 Subcommand Build
 N/A

 Notes
 feature flags:

 0x01: enable T2A features: chat, regions
 0x02: enable renaissance features
 0x04: enable third dawn features
 0x08: enable LBR features: skills, map
 0x10: enable AOS features: skills, map, spells, fightbook
 0x20: 6th character slot
 0x40: enable SE features
 0x80: enable ML features: elven race, spells, skills
 0x100: enable 8th age splash screen
 0x200: enable 9th age splash screen
 0x400: enable 10th age
 0x800: enable increased housing and bank storage
 0x1000: 7th character slot
 0x2000: enable KR faces
 0x4000: enable trial account
 0x8000: enable live account
 0x10000: enable SA features: gargoyle race, spells, skills
 0x20000: enable HSA features
 0x40000: enable Gothic housing tiles
 0x80000: enable Rustic housing tiles
 0x100000: enable Jungle housing tiles
 0x200000: enabled Shadowguard housing tiles
 0x400000: enable TOL features
 0x800000: enable Endless Journey account

 This packet is send immediatly after login.
 If you need several features you have to summ the flags.


 Older notes (not sure which are correct!):

 if (MSB not set)
 Bit# 1 T2A upgrade, enables chatbutton
 Bit# 2 enables LBR update. (of course LBR installation is required)(plays MP3 instead of midis, 2D LBR client shows new LBR monsters,...)
 if (MSB set)
 Bit# 3 T2A upgrade, enables chatbutton
 Bit# 4 enables LBR update
 Bit#5 enables AOS update (Aos monsters/map (AOS installation required for that) , AOS skills/necro/paladin/fight book stuff - works for ALL clients 4.0 and above)


 Examples:
 ML: B980FB
 AOS-7AV: B9803B
 AOS: B9801B
 LBR: B90003


 Custom housing uses these flags to enable some parts.

 for FeatureMask check floors.txt, roofs.txt etc in client folder

 FeatureMask 0 = AOS ( flag 0x10 )
 FeatureMask 64 = SE ( flag 0x40 )
 FeatureMask 128 = ML ( flag 0x80 )
 FeatureMask 512 = 9th age ( flag 0x200 )
 FeatureMash 65536 = SA ( flag 0x10000 )
 */
//======================================================================
auto createPacket0xB9(Client *client) -> Packet{
    auto packet = Packet(0xb9,1) ;
    packet.setExtend(true );
    // We are getting this server wide. But frankly the server wide should be the default, and the
    // account entry should have that.  So one could set by account. That is in line with OSI
    
    auto feature = static_cast<std::uint32_t>(serverConfig.intValue[IntCollection::CLIENTFEATURE]) ;
    if (client->version() >= ClientVersion(6,0,14,2)) {
        packet.write(feature,1,false) ;
    }
    else {
        // Use the old one
        packet.write(static_cast<std::uint16_t>(feature),1,false);
    }
    return packet ;
}

