//Copyright © 2023 Charles Kerr. All rights reserved.

#include "process0x80.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
#include "account/account.hpp"
#include "packet/packet.hpp"
#include "packet/create/packet0x82.hpp"
#include "configuration/serverconfig.hpp"
#include "utility/strutil.hpp"
using namespace std::string_literals ;

extern Account userAccounts ;
extern ServerConfig serverConfig ;
//======================================================================
/*
 Packet Name: Login Request
 Last Modified: 2009-02-28 18:42:51
 Modified By: MuadDib

 Packet: 0x80
 Sent By: Client
 Size: 62 Bytes

 Packet Build
 BYTE[1] Command
 BYTE[30] Account Name
 BYTE[30] Password
 BYTE[1] NextLoginKey value from uo.cfg on client machine.

 Subcommand Build
 N/A

 Notes
 N/A
 */
//======================================================================
//======================================================================
// Packet0x80
//======================================================================
class Packet0x80 : public Packet {
    
public:

    Packet0x80( std::vector<std::uint8_t> &&data):Packet(std::move(data)){
    }
    auto username() const -> std::string {
        return this->read<std::string>(30,1) ;
    }
    auto password() const ->std::string{
        return this->read<std::string>(30,31) ;
    }
    auto nextLoginKey() -> int {
        return static_cast<int>(this->read<std::int8_t>(61)) ;
    }
};

//======================================================================
// processPacket0x80
//======================================================================
auto processPacket0x80(Client *client, std::vector<std::uint8_t> &&data) -> void{
    auto packet = Packet0x80(std::move(data)) ;
    auto username = packet.username();
    auto password = packet.password();
    auto account = userAccounts.accountFor(username) ;
    if (!account){
        // The account doesn't exist, should we create it?
        if (userAccounts.autoCreate){
            account = userAccounts.createAccount(username, password);
        }
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
    auto outpacket = client->createPacket(0xa8) ;
    client->send(std::move(outpacket),false) ;
}
