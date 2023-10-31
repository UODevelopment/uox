//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef process0x5d_hpp
#define process0x5d_hpp

#include <cstdint>
#include <iostream>
#include <string>

//======================================================================

class Client ;

auto processPacket0x5D(Client *client, std::vector<std::uint8_t> &&data) -> void ;

#endif /* process0x5d_hpp */
