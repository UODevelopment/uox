//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef visibility_hpp
#define visibility_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>

//======================================================================
struct Visiblity {
    enum type_t {
        VISIBLE,HIDDEN,MAGICHIDDEN,PERMHIDDEN,GHOSTHIDDEN
    };
    static const std::map<type_t,std::string> TYPENAMEMAP ;
    static auto typeForName(const std::string &name) -> type_t ;
    
    type_t visibleValue ;
    
    Visiblity() ;
    Visiblity(type_t type);
    Visiblity(const std::string &line) ;
    auto describe() const -> const std::string & ;

    auto operator==(type_t rhs) const ->bool ;
    auto operator!=(type_t rhs) const ->bool ;
};

#endif /* visibility_hpp */
