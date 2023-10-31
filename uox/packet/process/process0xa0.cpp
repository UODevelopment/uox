//Copyright © 2023 Charles Kerr. All rights reserved.

#include "process0xa0.hpp"

#include "network/client.hpp"
#include "packet/packet.hpp"

using namespace std::string_literals ;
/*
 Packet Name: Select Server
 Last Modified: 2009-03-25 15:45:02
 Modified By: MuadDib

 Packet: 0xA0
 Sent By: Client
 Size: 3 Bytes

 Packet Build
 BYTE[1] Command
 BYTE[2] Shard Chosen from Server List

 Subcommand Build
 N/A

 Notes
 N/A
 */
//======================================================================
auto processPacket0xA0(Client *client, std::vector<std::uint8_t> &&data) -> void {
    auto packet = Packet(std::move(data)) ;
    auto selection = packet.read<std::uint16_t>(1) ;
    if (selection != 0) {
        // This is an error!
        client->close();
        return ;
    }
    // We need to send the relay
    auto outpacket = client->createPacket(0x8c);
    client->send(std::move(outpacket),false);
}

