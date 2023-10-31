//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef itemfactory_hpp
#define itemfactory_hpp

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "gameobject/object/item.hpp"
#include "serialgen.hpp"
#include "type/typedef.hpp"

class Item ;
//======================================================================
//======================================================================
class ItemFactory {
    static constexpr auto lowSerial = serial_t(0x80000000);
    static constexpr auto highSerial = serial_t(0xD000000) ;
    SerialGenerator serialGenerator ;
    std::unordered_map<serial_t, std::unique_ptr<Item>> object ;
public:
    ItemFactory() ;

    auto exists(serial_t serial) const -> bool ;
    auto erase(serial_t serial) -> void ;
    auto create(serial_t serial = INVALIDSERIAL) -> Item* ;
    auto operator[](serial_t serial) const -> const Item* ;
    auto operator[](serial_t serial) -> Item* ;
};


#endif /* itemfactory_hpp */
