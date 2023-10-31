//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef accountcharacter_hpp
#define accountcharacter_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include "type/typedef.hpp"

//======================================================================
// A character is comprised of a serial number, a name, and date it was created
//======================================================================
struct AccountCharacter {
    serial_t serialNumber ;
    std::string name ;
    walltime_t creation ;
    AccountCharacter(serial_t serial = INVALIDSERIAL) ;
    AccountCharacter(const std::string &line) ;
    auto describe() const -> std::string ;
    auto age() const -> day_t ;
};

#endif /* accountcharacter_hpp */
