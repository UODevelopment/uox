//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef realcollection_hpp
#define realcollection_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

//======================================================================
struct RealCollection {
    enum type_t {
        COUNT
    };
    static const std::map<std::string,type_t> NAMETYPEMAP ;
    static auto typeForName(const std::string &name) -> type_t ;
    std::vector<double> realValue ;
    RealCollection() ;
    auto reset() -> void ;
    auto postLoad() -> void ;
    auto operator[](type_t type) const -> const double& ;
    auto operator[](type_t type)  ->  double& ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool ;
};

#endif /* realcollection_hpp */
