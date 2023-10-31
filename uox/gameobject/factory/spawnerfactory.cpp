//Copyright © 2023 Charles Kerr. All rights reserved.

#include "spawnerfactory.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
//======================================================================
SpawnerFactory::SpawnerFactory():serialGenerator(SpawnerFactory::lowSerial, SpawnerFactory::highSerial){
}

//======================================================================
auto SpawnerFactory::exists(serial_t serial) const -> bool {
    return object.find(serial) != object.end() ;
}
//======================================================================
auto SpawnerFactory::erase(serial_t serial) -> void {
    auto iter = object.find(serial) ;
    if (iter != object.end() ) {
        object.erase(iter) ;
    }
}
//======================================================================
auto SpawnerFactory::create(serial_t serial ) -> Spawner* {
    if (serial == INVALIDSERIAL) {
        serial = serialGenerator.next();
    }
    else {
        serialGenerator.used(serial) ;
    }
    auto spawner = new Spawner() ;
    spawner->serialNumber = serial ;
    object.insert_or_assign(serial,std::unique_ptr<Spawner>(spawner));

    return spawner ;
}
//======================================================================
auto SpawnerFactory::operator[](serial_t serial) const -> const Spawner* {
    auto iter = object.find(serial) ;
    if (iter != object.end()){
        return iter->second.get() ;
    }
    throw std::out_of_range("Serial not a valid spawner: "s+util::ntos(serial,16,true,8)) ;
}
//======================================================================
auto SpawnerFactory::operator[](serial_t serial) -> Spawner* {
    auto iter = object.find(serial) ;
    if (iter != object.end()){
        return iter->second.get() ;
    }
    throw std::out_of_range("Serial not a valid spawner: "s+util::ntos(serial,16,true,8)) ;

}


