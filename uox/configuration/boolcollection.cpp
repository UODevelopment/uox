//Copyright © 2023 Charles Kerr. All rights reserved.

#include "boolcollection.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
const std::map<std::string, BoolCollection::type_t> BoolCollection::NAMETYPEMAP{
    {"CLIENTLOG",CLIENTLOG},{"CREATEACCOUNT",CREATEACCOUNT}
};
//======================================================================
auto BoolCollection::typeForName(const std::string &name) -> type_t {
    auto iter = NAMETYPEMAP.find(name) ;
    if (iter!= NAMETYPEMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("BoolCollection name out of range for: "s+name);
}
//======================================================================
BoolCollection::BoolCollection(){
    reset() ;
}
//======================================================================
auto BoolCollection::reset() ->void {
    toggleValue = std::vector<bool>(static_cast<int>(COUNT),false) ;
}
//======================================================================
auto BoolCollection::postLoad() ->void {
}

//======================================================================
auto BoolCollection::operator[](type_t type) const -> bool{
    return toggleValue.at(static_cast<size_t>(type));
}
//======================================================================
auto BoolCollection::setToggle(type_t type,bool state) -> void {
    toggleValue.at(static_cast<size_t>(type)) = state ;
}
//======================================================================
auto BoolCollection::setKeyValue(const std::string &key,const std::string &value) ->bool {
    auto iter = NAMETYPEMAP.find(key) ;
    if (iter == NAMETYPEMAP.end()){
        return false ;
    }
    if (!value.empty()){
        toggleValue.at(static_cast<size_t>(iter->second)) = (std::stoi(value,nullptr,0) == 1) ;
    }
    return true ;
}

