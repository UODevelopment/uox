//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef location_hpp
#define location_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "point.hpp"
//======================================================================
struct Location {
    Point3 coord ;
    int world ;
    int realm ;
    
    Location() ;
    Location(const Point3 &coord, int world, int realm);
    Location(const std::string &line) ;
    auto describe() const -> std::string ;
};

#endif /* location_hpp */
