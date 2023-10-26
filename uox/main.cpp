#include <cstdint>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "network/packet.hpp"
#include "utility/strutil.hpp"
using namespace std::string_literals;

int main(int argc, const char * argv[]) {
    auto temp = std::map<int,std::string>{
        {0x0C,"Edit Tile Data"s},
        {0x15,"Follow"s},
        {0x22,"Character Move Act/Resync"s},
        {0x2c,"Resurrection Menu"s},
        {0x39,"Remove (Group)"s},
        {0x3A,"Send Skills"s,},
        {0x56,"Map Packet (cartography/treasure)"s},
        {0x66,"Books (Pages)"s},
        {0x6C,"Target Cursor Commands"s},
        {0x6F,"Secure Trading"s},
        {0x71,"Bulletin Board Messages"s},
        {0x72,"Request War Mode"s},
        {0x73,"Ping Message"s},
        {0x93,"Book Header (Old)"s},
        {0x95,"Dye Window"s},
        {0x98,"All Names (3D)"s},
        {0x99,"Give Boat/House Placement View"s},
        {0x9A,"Console Entry Prompt"s},
        {0xB8,"Request/Char Profile"s},
        {0xBB,"Request/Char Profile"s},
        {0xBD,"Client Version"s},
        {0xBE,"Assist Version"s},
        {0xBF,"General Information"s},
        {0xC2,"Unicode TextEntry"s},
        {0xC8,"Client View Range"s},
        {0xC9,"Get Area Server Ping"s},
        {0xCA,"Get User Server Ping"s},
        {0xD0,"Configuration File"s},
        {0xD1,"Logout Status"s},
        {0xD4,"Book Header (New)"s},
        {0xD6,"Mega Cliloc"s},
        {0xD7,"Generic AOS Commands"s},
        {0xF1,"Freeshard List"s},
        
        // Client
        {0x00,"Create Character"s},
        {0x01,"Disconnect Notification"s},
        {0x02,"Move Request"s},
        {0x03,"Talk Request"s},
        {0x04,"Request God Mode"s},
        {0x05,"Request Attack"s},
        {0x06,"Double Click"s},
        {0x07,"Pickup Item"s},
        {0x08,"Drop Item"s},
        {0x09,"Single Click"s},
        {0x0A,"Edit (God)"s},
        {0x12,"Request Skill/etc use"s},
        {0x13,"Drop->Wear Item"s},
        {0x14,"Send Elevation (God)"s},
        {0x1E,"Control Animation"s},
        {0x34,"Get Player Status"s},
        {0x35,"Add Resource (God)"s},
        {0x37,"Move Item (God)"s},
        {0x38,"Pathfinding in Client"s},
        {0x3B,"Buy Items"s},
        {0x45,"Version OK"s},
        {0x46,"New Artwork"s},
        {0x47,"New Terrain"s},
        {0x48,"New Animation"s},
        {0x49,"New Hues"s},
        {0x4A,"Delete Art"s},
        {0x4B,"Check Client Version"s},
        {0x4C,"Script Names"s},
        {0x4D,"Edit Script File"s},
        {0x50,"Board Header"s},
        {0x51,"Board Message"s},
        {0x52,"Board Post Message"s},
        {0x57,"Update Regions"s},
        {0x58,"Add Region"s},
        {0x59,"New Context FX"s},
        {0x5A,"Update Context FX"s},
        {0x5C,"Restart Version"s},
        {0x5D,"Login Character"s},
        {0x5E,"Server Listing"s},
        {0x5F,"Server List Add Entry"s},
        {0x60,"Server List Remove Entry"s},
        {0x61,"Remove Static Object"s},
        {0x62,"Move Static Object"s},
        {0x63,"Load Area"s},
        {0x64,"Load Area Request"s},
        {0x69,"Change Text/Emote Colors"s},
        {0x75,"Rename Character"s},
        {0x7D,"Respond to Dialog Box"s},
        {0x80,"Login Request"s},
        {0x83,"Delete Character"s},
        {0x8D,"Character Creation (KR/3D)"s},
        {0x91,"Game Server Login"s},
        {0x9B,"Request Help"s},
        {0x9F,"Sell List Reply"s},
        {0xA0,"Select Server"s},
        {0xA4,"Client Spy"s},
        {0xA7,"Request Tip/Notice Window"s},
        {0xAC,"Gump Text Entry Dialog Reply"s},
        {0xAD,"Unicode/ASCII speech request"s},
        {0xB1,"Gump Menu Selection"s},
        {0xB3,"Chat Text"s},
        {0xB5,"Open Chat Window"s},
        {0xB6,"Send Help/Tip Request"s},
        {0xC5,"Invalid Map (Request?)"s},
        {0xD9,"Spy on Client"s},
        {0xE0,"Bug Report (KR)"s},
        {0xE1,"Client Type (KR/SA)"s},
        {0xEC,"Equip Macro (KR)"s},
        {0xED,"Unequip Macro (KR)"s},
        {0xEF,"KR/2D Client Login/Seed"s},
        {0xF8,"Character Creation"s},
        {0xFA,"Open UO Store"s},
        {0xFB,"Update View Public House Contents"s},
        
        // Server
        {0x0B,"Damage"s},
        {0x11,"Status Bar Info"s},
        {0x16,"New Health Bar status update (SA)"s},
        {0x17,"Health Bar status update (KR)"s},
        {0x1A,"Object Info"s},
        {0x1B,"Char Locale and Body"s},
        {0x1C,"Send Speech"s},
        {0x1D,"Delete Object"s},
        {0x1F,"Explosion"s},
        {0x20,"Draw Game Player"s},
        {0x21,"Char Move Rejection"s},
        {0x23,"Dragging of Item"s},
        {0x24,"Draw Container"s},
        {0x25,"Add Item To Container"s},
        {0x26,"Kick Player"s},
        {0x27,"Reject Move Item Request"s},
        {0x28,"Drop Item Failed/Clear Square (God Client?)"s},
        {0x29,"Drop Item Approved"s},
        {0x2A,"Blood"s},
        {0x2B,"God Mode (God Client)"s},
        {0x2D,"Mob Attributes"s},
        {0x2E,"Worn Item"s},
        {0x2F,"Fight Occurring"s},
        {0x30,"Attack OK"s},
        {0x31,"Attack Ended"s},
        {0x32,"Unknown"s},
        {0x33,"Pause Client"s},
        {0x36,"Resource Tile Data (God Client)"s},
        {0x3C,"Add Multiple Items in Container"s},
        {0x3E,"Versions (God Client)"s},
        {0x3F,"Update Statics (God Client)"s},
        {0x4E,"Personal Light Level"s},
        {0x4F,"Overall Light Level"s},
        {0x53,"Reject Character Logon"s},
        {0x54,"Play Sound Effect"s},
        {0x55,"Login Complete"s},
        {0x5B,"Time"s},
        {0x65,"Set Weather"s},
        {0x6D,"Play MIDI Music"s},
        {0x6E,"Character Animation"s},
        {0x70,"Graphical Effect"s},
        {0x74,"Open Buy Window"s},
        {0x76,"New Subserver"s},
        {0x77,"Update Player"s},
        {0x78,"Draw Object"s},
        {0x7C,"Open Dialog Box"s},
        {0x82,"Login Denied"s},
        {0x85,"Delete Character Failed"s},
        {0x86,"Resend Characters After Delete"s},
        {0x88,"Open Paperdoll"s},
        {0x89,"Corpse Clothing"s},
        {0x8C,"Connect To Game Server"s},
        {0x90,"Map Message"s},
        {0x97,"Move Player"s},
        {0x9C,"Request Assistance"s},
        {0x9E,"Sell List"s},
        {0xA1,"Update Current Health"s},
        {0xA2,"Update Current Mana"s},
        {0xA3,"Update Current Stamina"s},
        {0xA5,"Open Web Browser"s},
        {0xA6,"Tip/Notice Window"s},
        {0xA8,"Game Server List"s},
        {0xA9,"Characters/Starting Location"s},
        {0xAA,"Allow/Refuse Attack"s},
        {0xAB,"Gump Text Entry Dialog"s},
        {0xAE,"Unicode Speech Message"s},
        {0xAF,"Display Death Action"s},
        {0xB0,"Send Gump Menu Dialog"s},
        {0xB2,"Chat Message"s},
        {0xB7,"Help/Tip Data"s},
        {0xB9,"Enable Locked Client Features"s},
        {0xBA,"Quest Arrow"s},
        {0xBC,"Seasonal Information"s},
        {0xC0,"Graphical Effect"s},
        {0xC1,"Cliloc Message"s},
        {0xC4,"Semivisible (Smurf it!)"s},
        {0xC6,"Invalid Map Enable"s},
        {0xC7,"3D Partical Effect"s},
        {0xC8,"Global Queue Count"s},
        {0xCC,"Cliloc Message Affix"s},
        {0xD2,"Extended 0x20"s},
        {0xD2,"Extended 0x20"s},
        {0xD3,"Extended 0x78"s},
        {0xD8,"Send Custom House"s},
        {0xDB,"Character Transfer Log"s},
        {0xDC,"SE Introduced Revision"s},
        {0xDD,"Compressed Gump"s},
        {0xDE,"Update Mobile Status"s},
        {0xDF,"Buff/Debuff System"s},
        {0xE2,"New Character Animation (KR)"s},
        {0xE3,"KR Encryption Response"s},
        {0xF0,"Krrios client special"s},
        {0xF3,"Object Information (SA)"s},
        {0xF5,"New Map Message"s}
    };

    for (auto i = 0 ; i < 0xFF;i++){
        auto iter = temp.find(i) ;
        if (iter == temp.end()){
            std::cout << "\"Packet0x"<<util::upper(util::ntos(i,16,false,2)) <<"\"s,\n";
        }
        else {
            std::cout << "\"" << iter->second<<"\"s,\n" ;
        }
    }
    return 0;
}