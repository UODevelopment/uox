//Copyright © 2023 Charles Kerr. All rights reserved.

#include "character.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
Character::Character():Mobile(){
    objectType = BaseObject::CHARACTER ;
}
//======================================================================
Character::Character(serial_t serial):Character(){
    this->serialNumber = serial ;
}

//======================================================================
auto Character::saveData(std::ostream &output) const -> void {
    Mobile::saveData(output);
}
//======================================================================
auto Character::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = Mobile::setKeyValue(key, value) ;
    if (!rvalue){
        
    }
    return rvalue ;
}
