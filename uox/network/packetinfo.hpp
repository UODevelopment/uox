//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef packetinfo_hpp
#define packetinfo_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include <vector>

//======================================================================
// ForwardDeclare
//======================================================================
class ClientVersion ;
//======================================================================
using packetid_t = int ;
struct PacketInfo {
    static const std::vector<std::string> PACKETNAME ;
    static auto nameFor(packetid_t id) -> const std::string & ;
    std::vector<int> packetSize ;

    PacketInfo() ;
    PacketInfo(const ClientVersion &version) ;
    auto update(const ClientVersion &version) ->void ;
    auto sizeFor(packetid_t id) -> int ;
};

#endif /* packetinfo_hpp */
