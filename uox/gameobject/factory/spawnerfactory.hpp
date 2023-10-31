//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef spawnerfactory_hpp
#define spawnerfactory_hpp

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "type/typedef.hpp"

#include "serialgen.hpp"
#include "gameobject/object/spawner.hpp"
//======================================================================
//======================================================================
class SpawnerFactory {
    static constexpr auto lowSerial = serial_t(0xD0000000);
    static constexpr auto highSerial = serial_t(0xF000000) ;
    SerialGenerator serialGenerator ;
    std::unordered_map<serial_t, std::unique_ptr<Spawner>> object ;
public:
    SpawnerFactory() ;

    auto exists(serial_t serial) const -> bool ;
    auto erase(serial_t serial) -> void ;
    auto create(serial_t serial = INVALIDSERIAL) -> Spawner* ;
    auto operator[](serial_t serial) const -> const Spawner* ;
    auto operator[](serial_t serial) -> Spawner* ;
};


#endif /* spawnerfactory_hpp */
