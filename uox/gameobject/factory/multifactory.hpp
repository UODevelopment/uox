//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef multifactory_hpp
#define multifactory_hpp

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "type/typedef.hpp"
#include "serialgen.hpp"
#include "gameobject/object/multi.hpp"
class Multi ;
//======================================================================
class MultiFactory {
public:
    enum type_t {
        BUILDING, BOAT
    };
protected:
    static constexpr auto lowSerial = serial_t(0xF0000000);
    static constexpr auto highSerial = serial_t(0xFFFFFFF0) ;
    SerialGenerator serialGenerator ;
    std::unordered_map<serial_t, std::unique_ptr<Multi>> object ;
public:
    MultiFactory() ;
    

    auto exists(serial_t serial) const -> bool ;
    auto erase(serial_t serial) -> void ;
    auto create(type_t type, serial_t serial = INVALIDSERIAL) -> Multi* ;
    auto operator[](serial_t serial) const -> const Multi* ;
    auto operator[](serial_t serial) -> Multi* ;
    

    
};

#endif /* multifactory_hpp */
