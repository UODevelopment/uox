//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef startcollection_hpp
#define startcollection_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "type/startlocation.hpp"
//======================================================================
struct StartCollection {
    std::vector<StartLocation> location ;
    std::string keyword ;
    
    StartCollection(const std::string &key = "") ;
    auto reset() -> void ;
    auto postLoad() -> void ;
    auto size() const -> size_t;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool ;
};

#endif /* startcollection_hpp */
