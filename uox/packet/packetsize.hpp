//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef packetsize_hpp
#define packetsize_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include <vector>
#include "type/typedef.hpp"
//======================================================================
// ForwardDeclare
//======================================================================
class ClientVersion ;
//======================================================================
struct PacketSize {
    std::vector<int> packetSize ;
    PacketSize() ;
    PacketSize(const ClientVersion &version) ;
    auto update(const ClientVersion &version) ->void ;
    auto sizeFor(packetid_t id) -> int ;
};

#endif /* packetsize_hpp */
