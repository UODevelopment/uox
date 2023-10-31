//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef packet0x82_hpp
#define packet0x82_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include "packet/packet.hpp"
/*
 Packet Name: Login Denied
 Last Modified: 2009-03-02 08:18:11
 Modified By: Turley

 Packet: 0x82
 Sent By: Server
 Size: 2 Bytes

 Packet Build
 BYTE[1] cmd
 BYTE[1] reason

 Subcommand Build
 N/A

 Notes
 Login denied reasons (gump message):

 0x00 - Incorrect name/password.
 0x01 - Someone is already using this account.
 0x02 - Your account has been blocked.
 0x03 - Your account credentials are invalid.
 0x04 - Communication problem.
 0x05 - The IGR concurrency limit has been met.
 0x06 - The IGR time limit has been met.
 0x07 - General IGR authentication failure.
 */
//======================================================================
class Packet0x82 : public  Packet {
public:
    enum reason_t:std::uint8_t {
        BADUSER=0,INUSE,BLOCKED,INVALID,COMMUNICATION,IGRCONCURRENCY,IGRTIMELIMIT,IGRGENERAL
    };
    Packet0x82():Packet(0x82,2){
    }
    auto setReason(reason_t reason) -> void {
        this->write(static_cast<std::uint8_t>(reason),1);
    }

};


#endif /* packet0x82_hpp */
