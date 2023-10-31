//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef direction_hpp
#define direction_hpp

#include <cstdint>
#include <iostream>
#include <map>
#include <string>

//======================================================================
struct Direction {
    enum direction_t {
        NORTH=0,NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,NORTHWEST,UNKNOWN=0xFF
    };
    static const std::map<direction_t,std::string> DIRECTIONNAMEMAP ;
    static auto directionForName(const std::string &name) ->direction_t ;
    direction_t facing ;
    Direction();
    Direction(direction_t dir);
    Direction(const std::string &line) ;
    auto describe() const -> const std::string & ;
    auto operator==(direction_t dir) const ->bool ;
    auto operator!=(direction_t dir) const ->bool ;

};

#endif /* direction_hpp */
