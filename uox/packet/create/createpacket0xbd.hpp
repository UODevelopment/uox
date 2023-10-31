//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef createpacket0xbd_hpp
#define createpacket0xbd_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include "type/typedef.hpp"
class Client ;
class Packet ;
//======================================================================
auto createPacket0xBD(Client *client) -> Packet;


#endif /* createpacket0xbd_hpp */
