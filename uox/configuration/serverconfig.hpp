//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef serverconfig_hpp
#define serverconfig_hpp

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <istream>
#include <map> 
#include <string>

#include "boolcollection.hpp"
#include "eracollection.hpp"
#include "flagcollection.hpp"
#include "intcollection.hpp"
#include "pathcollection.hpp"
#include "realcollection.hpp"
#include "startcollection.hpp"
#include "stringcollection.hpp"
#include "timerdefault.hpp"
//======================================================================
struct ServerConfig {
    struct MapEntryInfo {
        std::filesystem::path terrain ;
        std::filesystem::path artidx;
        std::filesystem::path artmul ;
        std::pair<int,int> size ;
        std::pair<bool,bool> applyDiff ;
        std::filesystem::path terdifl ;
        std::filesystem::path terdif ;
        std::filesystem::path artdif ;
        std::filesystem::path artdifl ;
        std::filesystem::path artdifi ;
        MapEntryInfo():size({0,0}),applyDiff({false,false}){}
    };

    EraCollection eraValue ;
    FlagCollection flagValue;
    IntCollection intValue ;
    PathCollection pathValue ;
    RealCollection realValue ;
    StartCollection startingLocation;
    StringCollection stringValue ;
    TimerDefault timerDefault ;
    BoolCollection boolValue ;
    static auto processMapEntryInfo(const std::filesystem::path &path) -> std::map<int,MapEntryInfo> ;

    ServerConfig() ;
    ServerConfig(const std::filesystem::path &path) ;
    // ==================================================================================
    // Note about order of intialization of constant variables and constructors.  The constructor can be called
    // before the const variables are initailzied for that constructor, if they are in different compile units.
    // So, to be sure the collections have the correct size, call "reset" before first use ;
    // ==================================================================================
    auto reset() -> void ;
    auto postLoad() -> void ;
    [[maybe_unused]] auto setKeyValue(const std::string &skey, const std::string &value) ->bool ;
    auto processStream(std::istream &input) -> void ;
    auto load(const std::filesystem::path &path) ->bool ;
};

#endif /* serverconfig_hpp */
