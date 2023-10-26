//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef packet0xef_hpp
#define packet0xef_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "network/packet.hpp"
/*
 Packet Name: KR/2D Client Login/Seed
 Last Modified: 2008-12-16 10:57:46
 Modified By: Pierce

 Packet: 0xEF
 Sent By: Client
 Size: 21 bytes

 Packet Build
 BYTE[1] cmd
 BYTE[4] seed, usually the client local ip
 BYTE[4] client major version
 BYTE[4] client minor version
 BYTE[4] client revision version
 BYTE[4] client prototype version

 Subcommand Build
 N/A

 Notes
 Normally older client send a 4 byte seed (local ip).
 Newer clients 2.48.0.3+ (KR) and 6.0.5.0+ (2D) are sending
 this packet.
 */
//======================================================================
// Forward Declare
//======================================================================
class ClientVersion ;

//======================================================================
class Packet0xEF: public Packet{
    
public:
    Packet0xEF(const std::vector<std::uint8_t> &data) ;
    Packet0xEF( std::vector<std::uint8_t> &&data) ;
    Packet0xEF(const util::Buffer &data) ;
    Packet0xEF( util::Buffer &&data) ;
    auto seed() const -> std::uint32_t ;
    auto version() const -> ClientVersion ;
};

#endif /* packet0xef_hpp */
