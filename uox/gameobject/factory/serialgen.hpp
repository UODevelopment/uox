//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef serialgen_hpp
#define serialgen_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "type/typedef.hpp"
//======================================================================
struct SerialGenerator {
    serial_t highValue  ;
    serial_t lowValue ;
    serial_t currentValue ;
    SerialGenerator(serial_t lowvalue, serial_t highvalue) ;
    auto next() -> serial_t ;
    auto current() -> serial_t ;
    auto used(serial_t value) ->void ;
};

#endif /* serialgen_hpp */
