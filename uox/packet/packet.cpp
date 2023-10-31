//Copyright © 2023 Charles Kerr. All rights reserved.

#include "packet.hpp"

#include <algorithm>
#include <stdexcept>

#include "huffman.hpp"
#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
// Packet
//======================================================================
//======================================================================
const std::vector<std::string> Packet::PACKETNAME{
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
auto Packet::nameFor(packetid_t id) -> const std::string & {
    static const std::string INVALID = "INVALID"s ;
    if (id < 0 || id >= 0xFF) {
        return INVALID ;
    }
    return PACKETNAME.at(id);
}


//====================================================================
Packet::Packet():util::Buffer() {
}
//====================================================================
Packet::Packet(packetid_t id, int size):Packet(){
    data.resize((size>-1 ? size : 3),0);
    data.at(0) = static_cast<std::uint8_t>(id) ;
}
//====================================================================
Packet::Packet(const util::Buffer &buffer):util::Buffer(buffer) {
}
//====================================================================
Packet::Packet( util::Buffer &&buffer): util::Buffer(std::move(buffer)) {
}
//====================================================================
Packet::Packet(const Packet &packet):util::Buffer(packet) {
}
//====================================================================
Packet::Packet( Packet &&packet):util::Buffer(std::move(packet)) {
}
//====================================================================
Packet::Packet(const std::vector<std::uint8_t> &data) : util::Buffer(data){
}
//====================================================================
Packet::Packet( std::vector<std::uint8_t> &&data): util::Buffer(std::move(data))  {
}

//====================================================================
auto Packet::name() const -> const std::string& {
    static const std::string& invalid = "Invalid"s;
    if (data.size() > 0) {
        return Packet::nameFor(this->packetID());
    }
    return invalid;
}
//====================================================================
auto Packet::finalize(bool variable) -> void {
    if (variable){
        this->write(static_cast<std::uint16_t>(data.size()),1);
    }
}
//====================================================================
auto Packet::packetID() const -> packetid_t {
    if (!data.empty()){
        return static_cast<packetid_t>(this->read<std::uint8_t>(0));
    }
    return -1 ;
}
//====================================================================
auto Packet::setPacketID(packetid_t id) -> void {
    if (data.empty()){
        data.resize(1) ;
    }
    this->write(static_cast<std::uint8_t>(id),0);
}

//====================================================================
auto Packet::bufferSize() -> int {
    return static_cast<int>(data.size());
}
//====================================================================
auto Packet::size(bool variable) const -> int {
    
    if (variable && data.size()>=3){
        return static_cast<int>(this->read<std::uint16_t>(1));
    }
    return static_cast<int>(data.size());
}
//====================================================================
auto Packet::packetData() const -> std::vector<std::uint8_t>  {
    return data ;
}
//====================================================================
auto Packet::huffmanData() const -> std::vector<std::uint8_t> {
    return packHuffman(data);
}

//====================================================================
auto Packet::dump(std::ostream &output) const -> void {
    output <<"Packet#: "<< util::ntos(packetID(),16,true,2)<< " Length: " << data.size() << " Name: " << name() <<"\n";
    util::Buffer::dump(output) ;
}
