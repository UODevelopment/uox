//Copyright © 2023 Charles Kerr. All rights reserved.

#include "item.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
Item::Item() : BaseObject(BaseObject::ITEM){
    
}
//======================================================================
Item::Item(serial_t serial) : Item(){
    this->serialNumber = serial ;
}

//======================================================================
auto Item::saveData(std::ostream &output) const -> void {
    BaseObject::saveData(output);
}
//======================================================================
auto Item::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = BaseObject::setKeyValue(key, value) ;
    if (!rvalue){
        
    }
    return rvalue ;
}
