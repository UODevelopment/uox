//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef startlocation_hpp
#define startlocation_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "location.hpp"
//======================================================================
struct StartLocation {
    std::string town ;
    std::string description ;
    Location location ;
    int cli ;
    
    StartLocation() ;
    StartLocation(const std::string &line) ;
};

#endif /* startlocation_hpp */
