//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef packet0xa8_hpp
#define packet0xa8_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include "type/typedef.hpp"
#include "packet/packet.hpp"
/*
 Packet: 0xA8
 Sent By: Server
 Size: Variable

 Packet Build
 BYTE[1] cmd
 BYTE[2] length
 BYTE[1] System Info Flag
 BYTE[2] # of servers

 Then each server --
 BYTE[2] server index (0-based)
 BYTE[32] server name
 BYTE percent full
 BYTE timezone
 BYTE[4] server ip to ping

 Subcommand Build
 N/A

 Notes
 System Info Flags: 0xCC - Do not send video card info. 0x64 - Send Video card. RunUO And SteamEngine both send 0x5D.

 Server IP has to be sent in reverse order. For example, 192.168.0.1 is sent as 0100A8C0.
 */

//======================================================================
class Packet0xA8: public Packet {
public:
    Packet0xA8() : Packet(0xa8,46){
        this->write(static_cast<std::uint16_t>(46),1);
        this->write(static_cast<std::uint8_t>(0xFF),3) ;
        this->write(static_cast<std::uint16_t>(0x1),4) ;
    }
    auto setServerList(const std::string &shardname,int percentfull,int timezone,util::net::ip4_t pingaddress) -> void {
        this->write(static_cast<std::uint16_t>(0),6) ;
        this->write(shardname,32,8);
        this->write(static_cast<std::uint8_t>(percentfull),40);
        this->write(static_cast<std::uint8_t>(timezone),41);
        this->write(pingaddress,42);
    }
};

#endif /* packet0xa8_hpp */
