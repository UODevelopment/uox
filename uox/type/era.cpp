//Copyright © 2023 Charles Kerr. All rights reserved.

#include "era.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;
//======================================================================
const std::map<std::string , Era::type_t> Era::NAMETOERA{
    {"CORE"s,CORE}, {"UO"s,UO}, {"T2A"s,T2A}, {"UOR"s,UOR},
    {"TD"s,TD}, {"LBR"s,LBR}, {"AOS"s,AOS}, {"SE"s,SE},
    {"ML"s,ML}, {"SA"s,SA}, {"HS"s,HS}, {"TOL"s,TOL}
};
//======================================================================
Era::type_t Era::serverEra = Era::LBR ;

//======================================================================
auto Era::eraForName(const std::string &name) ->type_t{
    auto iter = NAMETOERA.find(name) ;
    if (iter != NAMETOERA.end()){
        return iter->second ;
    }
    throw std::out_of_range("Era name not in acceptable range: "s+name);
}

//======================================================================
Era::Era(){
    eraValue = CORE ;
}
//======================================================================
Era::Era(type_t value):Era() {
    eraValue = value ;
}
//======================================================================
Era::Era(const std::string &line):Era(){
    eraValue = eraForName(line);
}

//======================================================================
auto Era::value() const ->type_t {
    if (eraValue == CORE){
        return serverEra ;
    }
    return eraValue ;
}
//======================================================================
auto Era::operator=(type_t value) -> Era& {
    this->eraValue = value ;
    return *this ;
}
//======================================================================
auto Era::operator==(type_t value) const ->bool{
    return this->value() == value ;
}
