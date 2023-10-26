//Copyright © 2023 Charles Kerr. All rights reserved.

#include "packet0xef.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/clientversion.hpp"
#include "utility/strutil.hpp"

using namespace std::string_literals ;

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
Packet0xEF::Packet0xEF(const std::vector<std::uint8_t> &data) : Packet(data) {
}
//======================================================================
Packet0xEF::Packet0xEF( std::vector<std::uint8_t> &&data) : Packet(std::move(data)){
}
//======================================================================
Packet0xEF::Packet0xEF(const util::Buffer &data): Packet(data){
}
//======================================================================
Packet0xEF::Packet0xEF( util::Buffer &&data): Packet(std::move(data)){
}
    
//======================================================================
auto Packet0xEF::seed() const -> std::uint32_t {
    return this->read<std::uint32_t>(1) ;
}
//======================================================================
auto Packet0xEF::version() const -> ClientVersion {
    return ClientVersion(this->read<std::int32_t>(5),this->read<std::int32_t>(9),this->read<std::int32_t>(13),this->read<std::int32_t>(17)) ;
}

