//Copyright © 2023 Charles Kerr. All rights reserved.

#include "packetinfo.hpp"

#include <algorithm>
#include <stdexcept>

#include "clientversion.hpp"

using namespace std::string_literals ;

//======================================================================
const std::vector<std::string> PACKETNAME{
    "Create Character"s,
    "Disconnect Notification"s,
    "Move Request"s,
    "Talk Request"s,
    "Request God Mode"s,
    "Request Attack"s,
    "Double Click"s,
    "Pickup Item"s,
    "Drop Item"s,
    "Single Click"s,
    "Edit (God)"s,
    "Damage"s,
    "Edit Tile Data"s,
    "Packet0x0D"s,
    "Packet0x0E"s,
    "Packet0x0F"s,
    "Packet0x10"s,
    "Status Bar Info"s,
    "Request Skill/etc use"s,
    "Drop->Wear Item"s,
    "Send Elevation (God)"s,
    "Follow"s,
    "New Health Bar status update (SA)"s,
    "Health Bar status update (KR)"s,
    "Packet0x18"s,
    "Packet0x19"s,
    "Object Info"s,
    "Char Locale and Body"s,
    "Send Speech"s,
    "Delete Object"s,
    "Control Animation"s,
    "Explosion"s,
    "Draw Game Player"s,
    "Char Move Rejection"s,
    "Character Move Act/Resync"s,
    "Dragging of Item"s,
    "Draw Container"s,
    "Add Item To Container"s,
    "Kick Player"s,
    "Reject Move Item Request"s,
    "Drop Item Failed/Clear Square (God Client?)"s,
    "Drop Item Approved"s,
    "Blood"s,
    "God Mode (God Client)"s,
    "Resurrection Menu"s,
    "Mob Attributes"s,
    "Worn Item"s,
    "Fight Occurring"s,
    "Attack OK"s,
    "Attack Ended"s,
    "Unknown"s,
    "Pause Client"s,
    "Get Player Status"s,
    "Add Resource (God)"s,
    "Resource Tile Data (God Client)"s,
    "Move Item (God)"s,
    "Pathfinding in Client"s,
    "Remove (Group)"s,
    "Send Skills"s,
    "Buy Items"s,
    "Add Multiple Items in Container"s,
    "Packet0x3D"s,
    "Versions (God Client)"s,
    "Update Statics (God Client)"s,
    "Packet0x40"s,
    "Packet0x41"s,
    "Packet0x42"s,
    "Packet0x43"s,
    "Packet0x44"s,
    "Version OK"s,
    "New Artwork"s,
    "New Terrain"s,
    "New Animation"s,
    "New Hues"s,
    "Delete Art"s,
    "Check Client Version"s,
    "Script Names"s,
    "Edit Script File"s,
    "Personal Light Level"s,
    "Overall Light Level"s,
    "Board Header"s,
    "Board Message"s,
    "Board Post Message"s,
    "Reject Character Logon"s,
    "Play Sound Effect"s,
    "Login Complete"s,
    "Map Packet (cartography/treasure)"s,
    "Update Regions"s,
    "Add Region"s,
    "New Context FX"s,
    "Update Context FX"s,
    "Time"s,
    "Restart Version"s,
    "Login Character"s,
    "Server Listing"s,
    "Server List Add Entry"s,
    "Server List Remove Entry"s,
    "Remove Static Object"s,
    "Move Static Object"s,
    "Load Area"s,
    "Load Area Request"s,
    "Set Weather"s,
    "Books (Pages)"s,
    "Packet0x67"s,
    "Packet0x68"s,
    "Change Text/Emote Colors"s,
    "Packet0x6A"s,
    "Packet0x6B"s,
    "Target Cursor Commands"s,
    "Play MIDI Music"s,
    "Character Animation"s,
    "Secure Trading"s,
    "Graphical Effect"s,
    "Bulletin Board Messages"s,
    "Request War Mode"s,
    "Ping Message"s,
    "Open Buy Window"s,
    "Rename Character"s,
    "New Subserver"s,
    "Update Player"s,
    "Draw Object"s,
    "Packet0x79"s,
    "Packet0x7A"s,
    "Packet0x7B"s,
    "Open Dialog Box"s,
    "Respond to Dialog Box"s,
    "Packet0x7E"s,
    "Packet0x7F"s,
    "Login Request"s,
    "Packet0x81"s,
    "Login Denied"s,
    "Delete Character"s,
    "Packet0x84"s,
    "Delete Character Failed"s,
    "Resend Characters After Delete"s,
    "Packet0x87"s,
    "Open Paperdoll"s,
    "Corpse Clothing"s,
    "Packet0x8A"s,
    "Packet0x8B"s,
    "Connect To Game Server"s,
    "Character Creation (KR/3D)"s,
    "Packet0x8E"s,
    "Packet0x8F"s,
    "Map Message"s,
    "Game Server Login"s,
    "Packet0x92"s,
    "Book Header (Old)"s,
    "Packet0x94"s,
    "Dye Window"s,
    "Packet0x96"s,
    "Move Player"s,
    "All Names (3D)"s,
    "Give Boat/House Placement View"s,
    "Console Entry Prompt"s,
    "Request Help"s,
    "Request Assistance"s,
    "Packet0x9D"s,
    "Sell List"s,
    "Sell List Reply"s,
    "Select Server"s,
    "Update Current Health"s,
    "Update Current Mana"s,
    "Update Current Stamina"s,
    "Client Spy"s,
    "Open Web Browser"s,
    "Tip/Notice Window"s,
    "Request Tip/Notice Window"s,
    "Game Server List"s,
    "Characters/Starting Location"s,
    "Allow/Refuse Attack"s,
    "Gump Text Entry Dialog"s,
    "Gump Text Entry Dialog Reply"s,
    "Unicode/ASCII speech request"s,
    "Unicode Speech Message"s,
    "Display Death Action"s,
    "Send Gump Menu Dialog"s,
    "Gump Menu Selection"s,
    "Chat Message"s,
    "Chat Text"s,
    "Packet0xB4"s,
    "Open Chat Window"s,
    "Send Help/Tip Request"s,
    "Help/Tip Data"s,
    "Request/Char Profile"s,
    "Enable Locked Client Features"s,
    "Quest Arrow"s,
    "Request/Char Profile"s,
    "Seasonal Information"s,
    "Client Version"s,
    "Assist Version"s,
    "General Information"s,
    "Graphical Effect"s,
    "Cliloc Message"s,
    "Unicode TextEntry"s,
    "Packet0xC3"s,
    "Semivisible (Smurf it!)"s,
    "Invalid Map (Request?)"s,
    "Invalid Map Enable"s,
    "3D Partical Effect"s,
    "Client View Range"s,
    "Get Area Server Ping"s,
    "Get User Server Ping"s,
    "Packet0xCB"s,
    "Cliloc Message Affix"s,
    "Packet0xCD"s,
    "Packet0xCE"s,
    "Packet0xCF"s,
    "Configuration File"s,
    "Logout Status"s,
    "Extended 0x20"s,
    "Extended 0x78"s,
    "Book Header (New)"s,
    "Packet0xD5"s,
    "Mega Cliloc"s,
    "Generic AOS Commands"s,
    "Send Custom House"s,
    "Spy on Client"s,
    "Packet0xDA"s,
    "Character Transfer Log"s,
    "SE Introduced Revision"s,
    "Compressed Gump"s,
    "Update Mobile Status"s,
    "Buff/Debuff System"s,
    "Bug Report (KR)"s,
    "Client Type (KR/SA)"s,
    "New Character Animation (KR)"s,
    "KR Encryption Response"s,
    "Packet0xE4"s,
    "Packet0xE5"s,
    "Packet0xE6"s,
    "Packet0xE7"s,
    "Packet0xE8"s,
    "Packet0xE9"s,
    "Packet0xEA"s,
    "Packet0xEB"s,
    "Equip Macro (KR)"s,
    "Unequip Macro (KR)"s,
    "Packet0xEE"s,
    "KR/2D Client Login/Seed"s,
    "Krrios client special"s,
    "Freeshard List"s,
    "Packet0xF2"s,
    "Object Information (SA)"s,
    "Packet0xF4"s,
    "New Map Message"s,
    "Packet0xF6"s,
    "Packet0xF7"s,
    "Character Creation"s,
    "Packet0xF9"s,
    "Open UO Store"s,
    "Update View Public House Contents"s,
    "Packet0xFC"s,
    "Packet0xFD"s,
    "Packet0xFE"s
};

//======================================================================
auto PacketInfo::nameFor(packetid_t id) -> const std::string & {
    static const std::string INVALID = "INVALID"s ;
    if (id < 0 || id >= 0xFF) {
        return INVALID ;
    }
    return PACKETNAME.at(id);
}

//======================================================================
PacketInfo::PacketInfo::PacketInfo(){
    this->packetSize = std::vector<int>{
        0x0068, // 0x00
        0x0005, // 0x01
        0x0007, // 0x02
        -1,     // 0x03
        0x0002, // 0x04
        0x0005, // 0x05
        0x0005, // 0x06
        0x0007, // 0x07
        0x000E, // 0x08
        0x0005, // 0x09
        0x000B, // 0x0A
        0x010A, // 0x0B
        -1,     // 0x0C
        0x0003, // 0x0D
        -1,     // 0x0E
        0x003D, // 0x0F
        0x00D7, // 0x10
        -1,     // 0x11
        -1,     // 0x12
        0x000A, // 0x13
        0x0006, // 0x14
        0x0009, // 0x15
        0x0001, // 0x16
        -1,     // 0x17
        -1,     // 0x18
        -1,     // 0x19
        -1,     // 0x1A
        0x0025, // 0x1B
        -1,     // 0x1C
        0x0005, // 0x1D
        0x0004, // 0x1E
        0x0008, // 0x1F
        0x0013, // 0x20
        0x0008, // 0x21
        0x0003, // 0x22
        0x001A, // 0x23
        0x0007, // 0x24
        0x0014, // 0x25
        0x0005, // 0x26
        0x0002, // 0x27
        0x0005, // 0x28
        0x0001, // 0x29
        0x0005, // 0x2A
        0x0002, // 0x2B
        0x0002, // 0x2C
        0x0011, // 0x2D
        0x000F, // 0x2E
        0x000A, // 0x2F
        0x0005, // 0x30
        0x0001, // 0x31
        0x0002, // 0x32
        0x0002, // 0x33
        0x000A, // 0x34
        0x028D, // 0x35
        -1,     // 0x36
        0x0008, // 0x37
        0x0007, // 0x38
        0x0009, // 0x39
        -1,     // 0x3A
        -1,     // 0x3B
        -1,     // 0x3C
        0x0002, // 0x3D
        0x0025, // 0x3E
        -1,     // 0x3F
        0x00C9, // 0x40
        -1,     // 0x41
        -1,     // 0x42
        0x0229, // 0x43
        0x02C9, // 0x44
        0x0005, // 0x45
        -1,     // 0x46
        0x000B, // 0x47
        0x0049, // 0x48
        0x005D, // 0x49
        0x0005, // 0x4A
        0x0009, // 0x4B
        -1,     // 0x4C
        -1,     // 0x4D
        0x0006, // 0x4E
        0x0002, // 0x4F
        -1,     // 0x50
        -1,     // 0x51
        -1,     // 0x52
        0x0002, // 0x53
        0x000C, // 0x54
        0x0001, // 0x55
        0x000B, // 0x56
        0x006E, // 0x57
        0x006A, // 0x58
        -1,     // 0x59
        -1,     // 0x5A
        0x0004, // 0x5B
        0x0002, // 0x5C
        0x0049, // 0x5D
        -1,     // 0x5E
        0x0031, // 0x5F
        0x0005, // 0x60
        0x0009, // 0x61
        0x000F, // 0x62
        0x000D, // 0x63
        0x0001, // 0x64
        0x0004, // 0x65
        -1,     // 0x66
        0x0015, // 0x67
        -1,     // 0x68
        -1,     // 0x69
        0x0003, // 0x6A
        0x0009, // 0x6B
        0x0013, // 0x6C
        0x0003, // 0x6D
        0x000E, // 0x6E
        -1,     // 0x6F
        0x001C, // 0x70
        -1,     // 0x71
        0x0005, // 0x72
        0x0002, // 0x73
        -1,     // 0x74
        0x0023, // 0x75
        0x0010, // 0x76
        0x0011, // 0x77
        -1,     // 0x78
        0x0009, // 0x79
        -1,     // 0x7A
        0x0002, // 0x7B
        -1,     // 0x7C
        0x000D, // 0x7D
        0x0002, // 0x7E
        -1,     // 0x7F
        0x003E, // 0x80
        -1,     // 0x81
        0x0002, // 0x82
        0x0027, // 0x83
        0x0045, // 0x84
        0x0002, // 0x85
        -1,     // 0x86
        -1,     // 0x87
        0x0042, // 0x88
        -1,     // 0x89
        -1,     // 0x8A
        -1,     // 0x8B
        0x000B, // 0x8C
        -1,     // 0x8D
        -1,     // 0x8E
        -1,     // 0x8F
        0x0013, // 0x90
        0x0041, // 0x91
        -1,     // 0x92
        0x0063, // 0x93
        -1,     // 0x94
        0x0009, // 0x95
        -1,     // 0x96
        0x0002, // 0x97
        -1,     // 0x98
        0x001A, // 0x99
        -1,     // 0x9A
        0x0102, // 0x9B
        0x0135, // 0x9C
        0x0033, // 0x9D
        -1,     // 0x9E
        -1,     // 0x9F
        0x0003, // 0xA0
        0x0009, // 0xA1
        0x0009, // 0xA2
        0x0009, // 0xA3
        0x0095, // 0xA4
        -1,     // 0xA5
        -1,     // 0xA6
        0x0004, // 0xA7
        -1,     // 0xA8
        -1,     // 0xA9
        0x0005, // 0xAA
        -1,     // 0xAB
        -1,     // 0xAC
        -1,     // 0xAD
        -1,     // 0xAE
        0x000D, // 0xAF
        -1,     // 0xB0
        -1,     // 0xB1
        -1,     // 0xB2
        -1,     // 0xB3
        -1,     // 0xB4
        0x0040, // 0xB5
        0x0009, // 0xB6
        -1,     // 0xB7
        -1,     // 0xB8
        0x0003, // 0xB9
        0x0006, // 0xBA
        0x0009, // 0xBB
        0x0003, // 0xBC
        -1,     // 0xBD
        -1,     // 0xBE
        -1,     // 0xBF
        0x0024, // 0xC0
        -1,     // 0xC1
        -1,     // 0xC2
        -1,     // 0xC3
        0x0006, // 0xC4
        0x00CB, // 0xC5
        0x0001, // 0xC6
        0x0031, // 0xC7
        0x0002, // 0xC8
        0x0006, // 0xC9
        0x0006, // 0xCA
        0x0007, // 0xCB
        -1,     // 0xCC
        0x0001, // 0xCD
        -1,     // 0xCE
        0x004E, // 0xCF
        -1,     // 0xD0
        0x0002, // 0xD1
        0x0019, // 0xD2
        -1,     // 0xD3
        -1,     // 0xD4
        -1,     // 0xD5
        -1,     // 0xD6
        -1,     // 0xD7
        -1,     // 0xD8
        0x010C, // 0xD9
        -1,     // 0xDA
        -1,     // 0xDB
        0x09,   // dc
        -1,     // dd
        -1,     // de
        -1,     // df
        -1,     // e0
        -1,     // e1
        0x0A,   // e2
        -1,     // e3
        -1,     // e4
        -1,     // e5
        0x05,   // e6
        0x0C,   // e7
        0x0D,   // e8
        0x4B,   // e9
        0x03,   // ea
        -1,     // eb
        -1,     // ec
        -1,     // ed
        0x0A,   // ee
        0x0015, // ef
        -1,     // f0
        0x09,   // f1
        0x19,   // f2
        0x1A,   // f3
        -1,     // f4
        0x15,   // f5
        -1,     // f6
        -1,     // f7
        0x6A,   // f8
        -1,     // f9
        -1,     // fa -> UOStore
        -1,     // fb -> public house content
        -1,     // fc
        -1,     // fd
        -1      // ff
    };
}
//======================================================================
PacketInfo::PacketInfo(const ClientVersion &version) :PacketInfo(){
    this->update(version);
}
//======================================================================
auto PacketInfo::update(const ClientVersion &version) ->void {
    if (version >= ClientVersion(5,0,0,static_cast<int>(static_cast<std::uint32_t>('a') &0xFF)) {
        packetSize.at(0x0B) = 0x07;
        packetSize.at(0x16) = -1;
        packetSize.at(0x31) = -1;
    }
    else {
        packetSize.at(0x0B) = 0x10A;
        packetSize.at(0x16) = 0x01;
        packetSize.at(0x31) = 0x01;
    }

    if (version >= ClientVersion(5,0,9,0)) {
        packetSize.at(0xE1) = -1;
    }
    else {
        packetSize.at(0xE1) = 0x09;
    }

    if (version >= ClientVersion(6,0,1,3) {
        packetSize.at(0xE3) = -1;
        packetSize.at(0xE6) = 0x05;
        packetSize.at(0xE7) = 0x0C;
        packetSize.at(0xE8) = 0x0D;
        packetSize.at(0xE9) = 0x4B;
        packetSize.at(0xEA) = 0x03;
    }
    else {
        packetSize.at(0xE3) = 0x4D;
        packetSize.at(0xE6) = -1;
        packetSize.at(0xE7) = -1;
        packetSize.at(0xE8) = -1;
        packetSize.at(0xE9) = -1;
        packetSize.at(0xEA) = -1;
    }

    if (version >= ClientVersion(6,0,1,7)) {
        packetSize.at(0x08) = 0x0F;
        packetSize.at(0x25) = 0x15;
    }
    else {
        packetSize.at(0x08) = 0x0E;
        packetSize.at(0x25) = 0x14;
    }

    if (version >= ClientVersion(6,0,6,0)) {
        packetSize.at(0xEE) = 0x2000;
        packetSize.at(0xEF) = 0x2000;
        packetSize.at(0xF1) = 0x09;
    }
    else {
        packetSize.at(0xEE) = -1;
        packetSize.at(0xEF) = 0x15;
        packetSize.at(0xF1) = -1;
    }

    if (version >= ClientVersion(6,0,14,2)) {
        packetSize.at(0xB9) = 0x05;
    }
    else {
        packetSize.at(0xB9) = 0x03;
    }

    if (version >= ClientVersion(7,0,0,0)) {
        packetSize.at(0xEE) = 0x0A; //0x2000;
        packetSize.at(0xEF) = 0x15; //0x2000;
    }
    else {
        packetSize.at(0xEE) = -1;
        packetSize.at(0xEF) = 0x15;
    }

    if (version >= ClientVersion(7,0,9,0)) {
        packetSize.at(0x24) = 0x09;
        packetSize.at(0x99) = 0x1E;
        packetSize.at(0xBA) = 0x0A;
        packetSize.at(0xF3) = 0x1A;
        packetSize.at(0xF1) = 0x09;
        packetSize.at(0xF2) = 0x19;
    }
    else {
        packetSize.at(0x24) = 0x07;
        packetSize.at(0x99) = 0x1A;
        packetSize.at(0xBA) = 0x06;
        packetSize.at(0xF3) = 0x18;
        packetSize.at(0xF1) = -1;
        packetSize.at(0xF2) = -1;
    }

    if (version >= ClientVersion(7,0,18,0)) {
        packetSize.at(0x00) = 0x6A;
    }
    else {
        packetSize.at(0x00) = 0x68;
    }

    if (version >= ClientVersion(7,0,64,0)) {
        packetSize.at(0xFA) = 0x01;
        packetSize.at(0xFB) = 0x02;
    }
}
//======================================================================
auto PacketInfo::sizeFor(packetid_t id) -> int {
    return -1 ;
}
