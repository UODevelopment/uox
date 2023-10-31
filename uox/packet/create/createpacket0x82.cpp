//Copyright © 2023 Charles Kerr. All rights reserved.

#include "createpacket0x82.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "packet/packet.hpp"
#include "packet0x82.hpp"

using namespace std::string_literals ;
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
//=====================================================================
 
//======================================================================
auto createPacket0x82(Client *client) -> Packet{
    
    return Packet0x82() ;
}

