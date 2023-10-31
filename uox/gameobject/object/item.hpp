//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef item_hpp
#define item_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "baseobject.hpp"
class ItemFactory ;
//======================================================================
class Item : public BaseObject {
    friend class ItemFactory ;
public:
    auto saveData(std::ostream &output) const -> void final ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool final ;

    Item() ;
    Item(serial_t serial) ;
    ~Item() = default ;
};

#endif /* item_hpp */
