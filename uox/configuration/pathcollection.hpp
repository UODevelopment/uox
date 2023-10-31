//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef pathcollection_hpp
#define pathcollection_hpp

#include <cstdint>
#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include <vector>
//======================================================================
struct PathCollection {
    enum type_t {
        UODATA=0,SERVERHOME,ACCOUNT,WORLD,LANGUAGE,LOG,DEFINITION,CONFIGURATION,COUNT
    };
    static const std::map<std::string, type_t> NAMETYPEMAP ;
    static auto typeForName(const std::string &name) -> type_t ;
    std::vector<std::filesystem::path> pathValue ;
    PathCollection() ;
    auto reset() ->void ;
    auto postLoad(int numworld) -> void ;
    auto operator[](type_t type) const -> const std::filesystem::path &;
    auto operator[](type_t type)  ->  std::filesystem::path &;
    auto setKeyValue(const std::string &key,const std::string &value) ->bool ;
};

#endif /* pathcollection_hpp */
