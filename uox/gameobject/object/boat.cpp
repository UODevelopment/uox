//Copyright © 2023 Charles Kerr. All rights reserved.

#include "boat.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
Boat::Boat() : Multi(){
    objectType = BaseObject::BOAT;
}
//======================================================================
Boat::Boat(serial_t serial) : Multi(){
    this->serialNumber = serial ;
}
//======================================================================
auto Boat::saveData(std::ostream &output) const -> void {
    Multi::saveData(output);
}
//======================================================================
auto Boat::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = Multi::setKeyValue(key, value) ;
    if (!rvalue){
        
    }
    return rvalue ;
}
