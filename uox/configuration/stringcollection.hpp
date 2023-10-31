//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef stringcollection_hpp
#define stringcollection_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
//======================================================================
struct StringCollection {
    enum type_t {
        NAME,LANGUAGE,PUBLICIP,COUNT
    };
    static const std::map<std::string, type_t> NAMETYPEMAP ;
    static auto typeForName(const std::string &name) -> type_t ;
    std::vector<std::string> stringValue ;
    StringCollection() ;
    auto reset() -> void ;
    auto postLoad() -> void ;
    auto operator[](type_t type) const -> const std::string& ;
    auto operator[](type_t type)  ->  std::string& ;
    auto setKeyValue(const std::string &key, const std::string &value) -> bool ;
};

#endif /* stringcollection_hpp */
