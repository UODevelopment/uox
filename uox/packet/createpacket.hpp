//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef createpacket_hpp
#define createpacket_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include "type/typedef.hpp"
//======================================================================
class Packet ;
class Client ;
auto createPacket(Client *client, packetid_t packetid) -> Packet;
#endif /* createpacket_hpp */
