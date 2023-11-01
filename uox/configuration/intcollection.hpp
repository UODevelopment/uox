//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef intcollection_hpp
#define intcollection_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//======================================================================
struct IntCollection {
    enum type_t {
        PORT, SERVERKEY, CLIENTFEATURE, SERVERFEATURE, COUNT
    };
    static const std::map<std::string,type_t> NAMETYPEMAP ;
    static auto typeForName(const std::string &name) -> type_t ;
    std::vector<std::int64_t> intValue ;
    IntCollection() ;
    auto reset() -> void ;
    auto postLoad() -> void ;
    auto operator[](type_t type) const -> const std::int64_t& ;
    auto operator[](type_t type)  ->  std::int64_t& ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool ;

};

#endif /* intcollection_hpp */
