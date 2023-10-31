//Copyright © 2023 Charles Kerr. All rights reserved.

#include "location.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
Location::Location():world(0),realm(0){
}
//======================================================================
Location::Location(const Point3 &coord, int world, int realm):Location(){
    this->coord = coord ;
    this->world = world ;
    this->realm = realm ;
}
//======================================================================
Location::Location(const std::string &line) :Location() {
    auto [first,second]  = util::split(line,":") ;
    this->coord = Point3(first) ;
    auto [sworld,srealm] = util::split(second,",") ;
    this->world = std::stoi(sworld,nullptr,0) ;
    this->world = std::stoi(srealm,nullptr,0);
}
//======================================================================
auto Location::describe() const -> std::string{
    return coord.describe() + ":"s + std::to_string(world) + ","s + std::to_string(realm) ;
}
