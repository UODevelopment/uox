//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef era_hpp
#define era_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>

//======================================================================
struct Era {
    enum type_t {
        CORE, UO, T2A, UOR, TD, LBR, AOS, SE, ML, SA, HS, TOL
    };
    static const std::map<std::string , type_t> NAMETOERA ;
    static auto eraForName(const std::string &name) ->type_t ;
    
    static type_t serverEra ;
    
    type_t eraValue ;
    Era() ;
    Era(type_t value);
    Era(const std::string &line) ;
    auto value() const ->type_t ;
    auto operator=(type_t value) -> Era& ;
    auto operator==(type_t value) const ->bool ;
};

#endif /* era_hpp */
