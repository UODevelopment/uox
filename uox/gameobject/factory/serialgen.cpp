//Copyright © 2023 Charles Kerr. All rights reserved.

#include "serialgen.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
SerialGenerator::SerialGenerator(serial_t lowvalue, serial_t highvalue):lowValue(lowvalue),currentValue(lowvalue),highValue(highvalue){
    
}
//======================================================================
auto SerialGenerator::next() -> serial_t {
    auto rvalue = currentValue ;
    currentValue++ ;
    if (currentValue>=highValue){
        throw std::runtime_error("Serial Generator would exceed range: "s + std::to_string(highValue));
    }
    return rvalue ;
}
//======================================================================
auto SerialGenerator::current() -> serial_t {
    return currentValue ;
}
//======================================================================
auto SerialGenerator::used(serial_t value) ->void {
    if (value < lowValue || value>= highValue || value == INVALIDSERIAL){
        throw std::out_of_range("Serial number exceed acceptable range. Serial: "s + util::ntos(value,16,true,8) + " Range: "s + util::ntos(lowValue,16,true,8) + "-"s+ util::ntos(highValue,16,true,8)) ;
    }
    currentValue = std::max(value+1,currentValue) ;
}

