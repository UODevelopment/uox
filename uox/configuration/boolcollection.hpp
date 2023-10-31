//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef boolcollection_hpp
#define boolcollection_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>

//======================================================================
struct BoolCollection {
    enum type_t {
        CLIENTLOG,CREATEACCOUNT,COUNT
    };
    static const std::map<std::string, type_t> NAMETYPEMAP ;
    static auto typeForName(const std::string &name) -> type_t ;
    std::vector<bool> toggleValue ;
    BoolCollection() ;
    auto reset() ->void ;
    auto postLoad() -> void ;
    auto operator[](type_t type) const -> bool ;
    auto setToggle(type_t type,bool state) -> void ;
    auto setKeyValue(const std::string &key,const std::string &value) ->bool ;
};

#endif /* boolcollection_hpp */
