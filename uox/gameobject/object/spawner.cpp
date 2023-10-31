//Copyright © 2023 Charles Kerr. All rights reserved.

#include "spawner.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
Spawner::Spawner() : BaseObject(BaseObject::SPAWNER){
    
}
//======================================================================
Spawner::Spawner(serial_t serial) : Spawner(){
    this->serialNumber = serial ;
}
//======================================================================
auto Spawner::saveData(std::ostream &output)  const -> void {
    BaseObject::saveData(output);
}
//======================================================================
auto Spawner::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = BaseObject::setKeyValue(key, value) ;
    if (!rvalue){
        
    }
    return rvalue ;
}
