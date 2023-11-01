//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef accountentry_hpp
#define accountentry_hpp

#include <array>
#include <chrono>
#include <cstdint>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "accountcharacter.hpp"
#include "utility/ip4util.hpp"
#include "utility/nettype.hpp"
#include "type/typedef.hpp"
#include "userinfo.hpp"

class Account ;
class ClientVersion ;
//======================================================================
class AccountEntry {
    friend class Account ;
    
    std::vector<AccountCharacter> character;
    std::string username ;
    std::string password ;
    
    UserInfo information ;
    
    util::net::IP4Entry lastIP ;
    std::string clientVersion ;
    std::string firstLogin ;
    std::string lastLogin ;
    int accountNumber ;
public:
    static constexpr auto MAXCHARACTER = 7 ;
    bool inUse ;

    AccountEntry(int number = -1) ;
    [[maybe_unused]] auto setKeyValue(const std::string &key, const std::string &value) -> bool ;
    auto save(std::ostream &output) const -> void ;
    
    auto operator[](int index) const -> const AccountCharacter& ;
    auto operator[](int index)  ->  AccountCharacter& ;
    auto at(int index) const -> const AccountCharacter& ;
    auto at(int index)  ->  AccountCharacter& ;

    auto number() const -> int ;
    
    auto version() const -> const std::string& ;
    auto setVersion(const ClientVersion &version) -> void ;
    
    auto info(UserInfo::infotype_t type) const -> bool ;
    auto setInfo(UserInfo::infotype_t type, bool state) -> void ;
    
    auto user() const -> const std::string & ;
    auto setUsername(const std::string &user) ->void ;
    auto pwd() const -> const std::string & ;
    auto setPassword(const std::string &password) ->void ;
    auto size() const -> size_t ;// returns the number of characters
    auto setLastIP(util::net::ip4_t ip) -> void ;
    auto setLastIP(const std::string &ip) -> void ;
    auto firstlogin() const -> std::optional<std::chrono::system_clock::time_point> ;
    auto lastlogin() const -> std::optional<std::chrono::system_clock::time_point> ;
    auto setFirstLogin() ->void ;
    auto setLastLogin() -> void ;
    auto valid(const std::string &username, const std::string &password) const -> bool ;
    auto deleteCharacter(int slotNumber) -> void ;
    auto allCharacter() const -> const std::vector<AccountCharacter> & ;
    auto addCharacter(serial_t serial,const std::string &name ) -> int ;
};

#endif /* accountentry_hpp */
