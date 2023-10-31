//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef eracollection_hpp
#define eracollection_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "type/era.hpp"
//======================================================================
struct EraCollection {
    enum type_t {
        SERVER=0,ARMOR,STRENGTH,TATICS,ANATOMY,LUMBERJACK,RACIAL,DAMAGE,SHEILD,WEAPON,WRESTLING,HIT,COUNT
    };
    static const std::map<std::string, type_t> NAMETYPEMAP ;
    static auto typeForName(const std::string &name) ->type_t ;
    std::vector<Era> eraCollectionValue ;
    
    EraCollection() ;
    auto reset() -> void ;
    auto postLoad() -> void ;
    auto operator[](type_t category) const -> const Era& ;
    auto operator[](type_t category)  ->  Era& ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool ;
};

#endif /* eracollection_hpp */
