//Copyright © 2023 Charles Kerr. All rights reserved.

#include "multi.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
Multi::Multi():BaseObject(BaseObject::MULTI){
    
}
//======================================================================
Multi::Multi(serial_t serial):Multi(){
    this->serialNumber = serial ;
}
//======================================================================
auto Multi::saveData(std::ostream &output) const -> void {
    BaseObject::saveData(output);
}
//======================================================================
auto Multi::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = BaseObject::setKeyValue(key, value) ;
    if (!rvalue){
        
    }
    return rvalue ;
}
