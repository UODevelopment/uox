//Copyright © 2023 Charles Kerr. All rights reserved.

#include "multifactory.hpp"

#include <algorithm>
#include <stdexcept>

#include "gameobject/object/boat.hpp"
#include "gameobject/object/building.hpp"

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
MultiFactory::MultiFactory():serialGenerator(MultiFactory::lowSerial, MultiFactory::highSerial){
}

//======================================================================
auto MultiFactory::exists(serial_t serial) const -> bool {
    return object.find(serial) != object.end() ;
}
//======================================================================
auto MultiFactory::erase(serial_t serial) -> void {
    auto iter = object.find(serial) ;
    if (iter != object.end() ) {
        object.erase(iter) ;
    }
}
//======================================================================
auto MultiFactory::create(type_t type, serial_t serial ) -> Multi* {
    if (serial == INVALIDSERIAL) {
        serial = serialGenerator.next();
    }
    else {
        serialGenerator.used(serial) ;
    }
    Multi *rvalue = nullptr ;
    
    if (type == BOAT){
        auto boat = new Boat() ;
        boat->serialNumber = serial ;
        
        
        object.insert_or_assign(serial,std::unique_ptr<Multi>(static_cast<Multi*>(boat)));
    }
    else {
        auto building = new Building() ;
        building->serialNumber = serial ;
        
        object.insert_or_assign(serial,std::unique_ptr<Multi>(static_cast<Multi*>(building)));
    }
    return rvalue ;
}
//======================================================================
auto MultiFactory::operator[](serial_t serial) const -> const Multi* {
    auto iter = object.find(serial) ;
    if (iter != object.end()){
        return iter->second.get() ;
    }
    throw std::out_of_range("Serial not a valid multi: "s+util::ntos(serial,16,true,8)) ;
}
//======================================================================
auto MultiFactory::operator[](serial_t serial) -> Multi* {
    auto iter = object.find(serial) ;
    if (iter != object.end()){
        return iter->second.get() ;
    }
    throw std::out_of_range("Serial not a valid multi: "s+util::ntos(serial,16,true,8)) ;

}

