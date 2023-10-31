//Copyright © 2023 Charles Kerr. All rights reserved.

#include "createpacket0xa9.hpp"

#include <algorithm>
#include <stdexcept>

#include "account/accountentry.hpp"
#include "network/client.hpp"
#include "packet/packet.hpp"
#include "configuration/serverconfig.hpp"
using namespace std::string_literals ;
extern ServerConfig serverConfig;
/*
 Packet Name: Characters / Starting Locations
 Last Modified: 2011-10-25 16:50:42
 Modified By: Tomi

 Packet: 0xA9
 Sent By: Server
 Size: Variable

 Packet Build
 BYTE[1] cmd
 BYTE[2] packet length
 BYTE[1] number of characters (slots 5, 6 or 7)
 loop characters (5, 6 or 7):
 BYTE[30] character name
 BYTE[30] character password
 endloop(characters)
 BYTE[1] number of starting locations (cities)

 IF Client Version >= 7.0.13.0

 loop # of cities:
 BYTE[1] locationIndex (0-based)
 BYTE[32] city name(general name)
 BYTE[32] area of city or town
 BYTE[4] City X Coordinate
 BYTE[4] City Y Coordinate
 BYTE[4] City Z Coordinate
 BYTE[4] CIty Map ( Probably Map ID same as in mul files have to make sure )
 BYTE[4] Cliloc Description
 BYTE[4] Always 0
 endloop(# of cities)

 ELSE

 loop # of cities:
 BYTE[1] locationIndex (0-based)
 BYTE[31] city name(general name)
 BYTE[31] area of city or town
 endloop(# of cities)

 BYTE[4] Flags (see notes)

 IF SA ENCHANCED CLIENT
 BYTE[2] Last Character Slot ( for highlight )

 Subcommand Build
 N/A

 Notes
 Flags list:
 0x01: unknown
 0x02: send config/req logout (IGR?, overwrite configuration button?)
 0x04: single character (siege - limit 1 character/account)
 0x08: enable npcpopup/context menus
 0x10: limit character slots?
 0x20: enable common AOS features (tooltip thing/fight system book, but not AOS monsters/map/skills, necromancer/paladin classes)
 0x40: 6th character slot
 0x80: samurai and ninja classes
 0x100: elven race
 0x200: KR support flag1 ?
 0x400: send UO3D client type (client will send 0xE1 packet)
 0x800: unknown
 0x1000: 7th character slot, only 2D client
 0x2000: unknown (SA?)
 0x4000: new movement packets 0xF0 -> 0xF2
 0x8000: unlock new felucca areas

 Flags can be combined as literals to view. Such as to have NPC Popup Menus AND Common AOS Features, send as 0x28, not 0x8 plus 0x20 form.
 Another example: elven race, samurai classes and AOS will be 0x1A0.

 0x8000 flag is used for unlocking new Felucca factions areas, note that you have to use "_x" versions of map/statics if you want to move through new areas.

 Since 7.0.13.0 City Name and Building Name have length of 32 chars, also added city x,y,z,map,cliloc description and BYTE[4] always 0 to city structure.
 */
//======================================================================
auto createPacket0xA9(Client *client) -> Packet{
    auto startloc = serverConfig.startingLocation.location;
    auto old = (client->version() >= ClientVersion(7,0,13,0)?false:true) ;
    
    Packet packet = Packet(0xa9,3+1+(AccountEntry::MAXCHARACTER * 60)+1+(startloc.size() * (old? 67 : 89)) + 4);
    packet.setOffset(3);
    packet.write(static_cast<std::uint8_t>(AccountEntry::MAXCHARACTER));
    for (auto i=0 ; i < AccountEntry::MAXCHARACTER;i++){
        if (i >= client->account->size()){
            packet.write(""s, 30);
        }
        else {
            packet.write(client->account->at(i).name,30);
        }
        packet.write(client->account->pwd(),30);
    }
    packet.setOffset(AccountEntry::MAXCHARACTER*60+3+1);
    packet.write(static_cast<std::uint8_t>(startloc.size()));
    for (size_t i = 0 ; i < startloc.size();i++){
        packet.write(static_cast<std::uint8_t>(i));
        if (old){
            packet.write(startloc.at(i).town,31);
            packet.write(startloc.at(i).description,31);
        }
        else {
            packet.write(startloc.at(i).town,32);
            packet.write(startloc.at(i).description,32);
            packet.write(startloc.at(i).location.coord.x);
            packet.write(startloc.at(i).location.coord.y);
            packet.write(startloc.at(i).location.coord.z);
            packet.write(startloc.at(i).location.world);
            packet.write(startloc.at(i).cli);
            packet.write(0);
        }

    }
    packet.write(static_cast<std::uint32_t>(serverConfig.intValue[IntCollection::SERVERFEATURE]),-1,false);
    packet.finalize(true) ;
    return packet ;
}
