//Copyright © 2023 Charles Kerr. All rights reserved.

#include "accountcharacter.hpp"

#include <algorithm>
#include <chrono>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
AccountCharacter::AccountCharacter(serial_t serial ):serialNumber(serial){
    this->creation = std::chrono::system_clock::now();
}
//======================================================================
AccountCharacter::AccountCharacter(const std::string &line):AccountCharacter() {
    auto values = util::parse(line,",") ;
    switch (values.size()) {
        default:
        case 3:
            this->creation = util::stringToSysTime(values[2]);
            [[fallthrough]];
        case 2:
            this->name = values[1];
            [[fallthrough]];
        case 1:
            this->serialNumber = static_cast<serial_t>(std::stoul(values[0],nullptr,0)) ;
            [[fallthrough]];
        case 0:
            break;
    }
}
//======================================================================
auto AccountCharacter::describe() const -> std::string{
    return  util::ntos(serialNumber,16,true,8) + ","s+ (name.empty()?""s:name)+","s + util::sysTimeToString(creation);
}
//======================================================================
auto AccountCharacter::age() const -> day_t {
    return static_cast<day_t>(std::chrono::duration_cast<std::chrono::hours>(std::chrono::system_clock::now() - creation).count()/24) ;
}
