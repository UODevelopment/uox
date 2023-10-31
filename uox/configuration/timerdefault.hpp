//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef timerdefault_hpp
#define timerdefault_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "type/typedef.hpp"
//======================================================================
struct TimerDefault {
    enum type_t {
        DECAY = 0,COUNT
    };
    static const std::map<std::string, type_t> NAMETYPEMAP ;
    static auto typeForName(const std::string &name) ->type_t ;
    std::vector<sec_t> timerDefault ;
    
    TimerDefault() ;
    auto reset() -> void ;
    auto postLoad() -> void ;
    auto operator[](type_t category) const -> const sec_t& ;
    auto operator[](type_t category)  -> sec_t& ;
    auto setKeyValue(const std::string &key, const std::string &value) -> bool ;

};

#endif /* timerdefault_hpp */
