//Copyright © 2023 Charles Kerr. All rights reserved.

#include "building.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
Building::Building():Multi(){
    objectType = BaseObject::BUILDING ;
}
//======================================================================
Building::Building(serial_t serial):Building(){
    this->serialNumber = serial ;
}
//======================================================================
auto Building::saveData(std::ostream &output) const -> void {
    Multi::saveData(output);
}
//======================================================================
auto Building::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = Multi::setKeyValue(key, value) ;
    if (!rvalue){
        
    }
    return rvalue ;
}
