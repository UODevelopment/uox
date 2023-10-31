//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef objectflag_hpp
#define objectflag_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
//======================================================================
struct ObjectFlag {
    enum flag_t{
        REMOVE
    };
    std::vector<bool> flag ;
    ObjectFlag(int flagcount = 1) ;
    auto set(flag_t index,bool state) -> void ;
    auto operator[](flag_t index) const -> bool ;
};

#endif /* objectflag_hpp */
