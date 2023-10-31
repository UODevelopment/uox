//Copyright © 2023 Charles Kerr. All rights reserved.

#include "direction.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
enum direction_t {
    NORTH=0,NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,NORTHWEST,UNKNOWN=0xFF
};
//======================================================================
const std::map<Direction::direction_t,std::string> Direction::DIRECTIONNAMEMAP{
    {NORTH,"NORTH"},{NORTHEAST,"NORTHEAST"},{EAST,"EAST"},{SOUTHEAST,"SOUTHEAST"},
    {SOUTH,"SOUTH"},{SOUTHWEST,"SOUTHWEST"},{WEST,"WEST"},{NORTHWEST,"NORTHWEST"},
    {UNKNOWN,"UNKNOWN"}
};
//======================================================================
auto Direction::directionForName(const std::string &name) ->direction_t {
    auto iter = std::find_if(DIRECTIONNAMEMAP.begin(),DIRECTIONNAMEMAP.end(),[name](const std::pair<direction_t,std::string> &entry){
        return entry.second == name ;
    });
    if (iter != DIRECTIONNAMEMAP.end()){
        return iter->first;
    }
    throw std::out_of_range("Direction is invalid: "s+name);
}

//======================================================================
Direction::Direction():facing(Direction::UNKNOWN){
}
//======================================================================
Direction::Direction(direction_t dir):facing(dir){
    
}
//======================================================================
Direction::Direction(const std::string &line):Direction(){
    facing = directionForName(line) ;
}
//======================================================================
auto Direction::describe() const -> const std::string & {
    return DIRECTIONNAMEMAP.at(facing);
}
//======================================================================
auto Direction::operator==(direction_t dir) const ->bool {
    return facing == dir ;
}
//======================================================================
auto Direction::operator!=(direction_t dir) const ->bool {
    return !operator==(dir) ;
}
