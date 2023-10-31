//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef process0x91_hpp
#define process0x91_hpp

#include <cstdint>
#include <iostream>
#include <string>

//======================================================================

class Client ;

auto processPacket0x91(Client *client, std::vector<std::uint8_t> &&data) -> void ;

#endif /* process0x91_hpp */
