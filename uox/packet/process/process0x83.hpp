//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef process0x83_hpp
#define process0x83_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
//======================================================================

class Client ;

auto processPacket0x83(Client *client, std::vector<std::uint8_t> &&data) -> void ;

#endif /* process0x83_hpp */
