//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef createpacket0xa9_hpp
#define createpacket0xa9_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include "type/typedef.hpp"
class Client ;
class Packet ;
//======================================================================
auto createPacket0xA9(Client *client) -> Packet;

#endif /* createpacket0xa9_hpp */
