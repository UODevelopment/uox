//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef multi_hpp
#define multi_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "baseobject.hpp"
class MultiFactory;
//======================================================================
class Multi : public BaseObject {
    friend class MultiFactory ;
public:
    auto saveData(std::ostream &output) const -> void override ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool override ;

    Multi();
    Multi(serial_t serial);
    virtual ~Multi() = default ;
};
#endif /* multi_hpp */
