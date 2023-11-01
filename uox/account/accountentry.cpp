//Copyright © 2023 Charles Kerr. All rights reserved.

#include "accountentry.hpp"

#include <algorithm>
#include <stdexcept>
#include "type/clientversion.hpp"
#include "utility/strutil.hpp"

using namespace std::string_literals ;


//======================================================================
AccountEntry::AccountEntry(int number):accountNumber(number),inUse(false){
    
}
//======================================================================
auto AccountEntry::setKeyValue(const std::string &key, const std::string &value) -> bool {
    auto rvalue = true ;
    if (key == "USERNAME"){
        this->username = value ;
    }
    else if (key == "PASSWORD"){
        this->password = value ;
    }
    else if (key == "INFORMATION"){
        this->information = UserInfo(value) ;
    }
    else if (key == "LASTIP") {
        lastIP = util::net::IP4Entry(value) ;
    }
    else if (key == "FIRSTLOGIN") {
        firstLogin = value ;
    }
    else if (key == "LASTLOGIN"){
        lastLogin = value ;
    }
    else if (key == "CLIENTVERSION"){
        clientVersion = value ;
    }
    else if (key == "CHARACTER"){
        character.push_back(AccountCharacter(value));
    }
    else {
        rvalue = false ;
    }
    return rvalue ;
}

//======================================================================
auto AccountEntry::save(std::ostream &output) const -> void{
    output << "\tUSERNAME = " << username << "\n";
    output << "\tPASSWORD = " << password << "\n";
    output << "\tINFORMATION = " << information.describe() << "\n";
    output << "\tLASTIP = " << lastIP.describe() << "\n";
    output << "\tFIRSTLOGIN = " << firstLogin << "\n";
    output << "\tLASTLOGIN = " << lastLogin << "\n";
    output << "\tCLIENTVERSION = " << clientVersion << "\n";
    for (const auto &entry: character){
        output <<"\tCHARACTER = " << entry.describe() << "\n";
    }
}
//======================================================================
auto AccountEntry::operator[](int index) const -> const AccountCharacter& {
    return character.at(index) ;
}
//======================================================================
auto AccountEntry::operator[](int index)  ->  AccountCharacter& {
    return character.at(index) ;
}
//======================================================================
auto AccountEntry::at(int index) const -> const AccountCharacter& {
    return character.at(index) ;
}
//======================================================================
auto AccountEntry::at(int index)  ->  AccountCharacter& {
    return character.at(index) ;
}

//======================================================================
auto AccountEntry::number() const -> int {
    return this->accountNumber ;
}

//======================================================================
auto AccountEntry::version() const -> const std::string& {
    return this->clientVersion;
}
//======================================================================
auto AccountEntry::setVersion(const ClientVersion &version) -> void {
    this->clientVersion = version.describe() ;
}

//======================================================================
auto AccountEntry::info(UserInfo::infotype_t type) const -> bool {
    return information[type];
}
//======================================================================
auto AccountEntry::setInfo(UserInfo::infotype_t type, bool state) -> void {
    information.setInfo(type, state);
}

//======================================================================
auto AccountEntry::user() const -> const std::string & {
    return username ;
}
//======================================================================
auto AccountEntry::setUsername(const std::string &user) ->void {
    this->username = user ;
}
//======================================================================
auto AccountEntry::pwd() const -> const std::string & {
    return this->password ;
}
//======================================================================
auto AccountEntry::setPassword(const std::string &password) ->void {
    this->password = password ;
}
//======================================================================
auto AccountEntry::size() const -> size_t {
    return character.size();
}
//======================================================================
auto AccountEntry::setLastIP(util::net::ip4_t ip) -> void {
    this->lastIP = util::net::IP4Entry(ip) ;
}
//======================================================================
auto AccountEntry::setLastIP(const std::string &ip) -> void {
    this->lastIP = util::net::IP4Entry(ip);
}

//======================================================================
auto AccountEntry::firstlogin() const -> std::optional<std::chrono::system_clock::time_point> {
    if (firstLogin.empty()){
        return {} ;
    }
    return util::stringToSysTime(firstLogin);
}
//======================================================================
auto AccountEntry::lastlogin() const -> std::optional<std::chrono::system_clock::time_point> {
    if (lastLogin.empty()){
        return {} ;
    }
    return util::stringToSysTime(lastLogin);
}
//======================================================================
auto AccountEntry::setFirstLogin() ->void {
    if (firstLogin.empty()){
        firstLogin  = util::timeNow() ;
    }
}
//======================================================================
auto AccountEntry::setLastLogin() -> void {
    lastLogin  = util::timeNow() ;
}
//======================================================================
auto AccountEntry::valid(const std::string &username, const std::string &password) const -> bool {
    return (util::upper(username) == util::upper(this->username)) && (password == this->password) ;
}
//======================================================================
auto AccountEntry::deleteCharacter(int slotNumber) -> void {
    auto iter = character.begin() + slotNumber ;
    character.erase(iter) ;
}
//======================================================================
auto AccountEntry::allCharacter() const ->  const std::vector<AccountCharacter> & {
    return character ;
}
//======================================================================
auto AccountEntry::addCharacter(serial_t serial,const std::string &name ) -> int {
    if (character.size() >= AccountEntry::MAXCHARACTER){
        throw std::runtime_error("All ready at max characters");
    }
    auto newCharacter = AccountCharacter();
    newCharacter.serialNumber = serial ;
    newCharacter.name = name ;
    character.push_back(newCharacter);
    return static_cast<int>(character.size()-1);
}
