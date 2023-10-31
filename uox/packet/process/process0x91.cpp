//Copyright © 2023 Charles Kerr. All rights reserved.

#include "process0x91.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "account/account.hpp"
#include "packet/packet.hpp"
#include "packet/create/packet0x82.hpp"
#include "utility/strutil.hpp"

extern Account userAccounts ;

using namespace std::string_literals ;
/*
 Packet Name: Game Server Login
 Last Modified: 2009-03-02 08:09:49
 Modified By: Turley

 Packet: 0x91
 Sent By: Client
 Size: 65 Bytes

 Packet Build
 BYTE[1] cmd
 BYTE[4] key used
 BYTE[30] sid
 BYTE[30] password

 Subcommand Build
 N/A

 Notes
 N/A
 */
//=======================================================================
// Packet 0x91
//=======================================================================
class Packet0x91: public Packet {
public:
    Packet0x91(std::vector<std::uint8_t> &&data):Packet(std::move(data)){
    }
    //======================================================================
    auto shardKey() const -> std::uint32_t {
        return this->read<std::uint32_t>(1) ;
    }
    //======================================================================
    auto username() const -> std::string {
        return this->read<std::string>(30,5) ;
    }
    //======================================================================
    auto password() const -> std::string {
        return this->read<std::string>(30,35) ;
    }

};
//======================================================================
auto processPacket0x91(Client *client, std::vector<std::uint8_t> &&data) -> void {
    auto packet = Packet0x91(std::move(data));
    auto username = packet.username();
    auto password = packet.password();
    auto key = packet.shardKey() ;
    auto account = userAccounts.accountFor(username) ;
    if ( Client::serverKey != key) {
        // This wasn't relayed by us
        // We need to create a response, that they are not allowed on
        auto outpacket = client->createPacket(0x82) ;
        outpacket.write(static_cast<std::uint8_t>(Packet0x82::IGRGENERAL),1);
        client->send(std::move(outpacket),false);
        return ;

    }
    if (!account) {
        // We need to create a response, that they are not allowed on
        auto outpacket = client->createPacket(0x82) ;
        outpacket.write(static_cast<std::uint8_t>(Packet0x82::INVALID),1);
        client->send(std::move(outpacket),false);
        return ;
    }
    // They have an account, now, is the password right ;
    if (!account->valid(username, password)) {
        // We need to create a response, that they are not allowed on
        auto outpacket = client->createPacket(0x82) ;
        outpacket.write(static_cast<std::uint8_t>(Packet0x82::BADUSER),1);
        client->send(std::move(outpacket),false);
        return ;
    }
    // Ok, so we have gotten past the user name and password
    if (account->info(UserInfo::SUSPENDED) || account->info(UserInfo::BANNED) ){
        // This is still bad
        // We need to create a response, that they are not allowed on
        auto outpacket = client->createPacket(0x82) ;
        outpacket.write(static_cast<std::uint8_t>(Packet0x82::BLOCKED),1);
        client->send(std::move(outpacket),false);
        return ;
    }
    // What about if this account is in use?
    if (account->inUse  ){
        // This is still bad
        // We need to create a response, that they are not allowed on
        auto outpacket = client->createPacket(0x82) ;
        outpacket.write(static_cast<std::uint8_t>(Packet0x82::INUSE),1);
        client->send(std::move(outpacket),false);
        return ;
    }
    // Ok, we are good!
    client->account = account ;
    client->account->inUse = true ;
    client->account->setFirstLogin() ;
    client->account->setLastIP(client->ipAddress());
    client->account->setLastLogin();
    // We need to send the feature packet
    auto clientfeature = client->createPacket(0xb9);
    client->send(std::move(clientfeature));
    auto list = client->createPacket(0xa9);
    client->send(std::move(list));
}

