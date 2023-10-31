//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef flagcollection_hpp
#define flagcollection_hpp

#include <bitset>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
//======================================================================
struct FlagCollection {
    enum type_t {
       COUNT
    };
    static const std::map<std::string,type_t> NAMETYPEMAP ;
    static auto typeForName(const std::string &name) -> type_t ;
    std::vector<std::bitset<64>> flagValue ;
    
    FlagCollection() ;
    auto reset() -> void ;
    auto postLoad() -> void ;
    auto operator[](type_t type) -> std::bitset<64>& ;
    auto operator[](type_t type) const -> const std::bitset<64>& ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool ;
};

#endif /* flagcollection_hpp */
