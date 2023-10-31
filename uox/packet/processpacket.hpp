//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef processpacket_hpp
#define processpacket_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Client ;
//======================================================================
auto processPacket(Client *client, std::vector<std::uint8_t> &&data) -> void ;

#endif /* processpacket_hpp */
