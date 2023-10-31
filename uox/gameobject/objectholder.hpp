//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef objectholder_hpp
#define objectholder_hpp

#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <string>

#include "type/typedef.hpp"
#include "gameobject/object/baseobject.hpp"
//======================================================================
struct ObjectHolder {
    std::unordered_map<serial_t, BaseObject*> container ;
    auto add(BaseObject * object) -> void ;
    auto find(serial_t serial) -> BaseObject * ;
    auto remove(serial_t serial) -> void ;
    auto contains(serial_t serial) const -> bool ;
    auto size() const -> size_t ;
    auto empty() const -> bool ;
};

#endif /* objectholder_hpp */
