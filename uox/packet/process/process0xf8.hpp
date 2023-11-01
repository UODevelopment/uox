//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef process0xf8_hpp
#define process0xf8_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
//======================================================================
class Client ;

auto processPacket0xF8(Client *client, std::vector<std::uint8_t> &&data) -> void ;

#endif /* process0xf8_hpp */
