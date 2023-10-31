//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef building_hpp
#define building_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "multi.hpp"

//======================================================================
class Building : public Multi {
    
public:
    auto saveData(std::ostream &output) const -> void final ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool final ;

    Building();
    Building(serial_t serial);
    ~Building() = default ;
};

#endif /* building_hpp */
