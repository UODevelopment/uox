//Copyright © 2023 Charles Kerr. All rights reserved.

#include "flagcollection.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
const std::map<std::string,FlagCollection::type_t> FlagCollection::NAMETYPEMAP{
    
};
//======================================================================
auto FlagCollection::typeForName(const std::string &name) -> type_t {
    auto iter = NAMETYPEMAP.find(name) ;
    if (iter != NAMETYPEMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("Flag collection name out of range: "s + name);
}

//======================================================================
FlagCollection::FlagCollection(){
    reset();
}
//======================================================================
auto FlagCollection::reset() -> void {
    flagValue = std::vector<std::bitset<64>>(static_cast<int>(COUNT),0) ;
}
//======================================================================
auto FlagCollection::postLoad() ->void {
}
//======================================================================
auto FlagCollection::operator[](type_t type) -> std::bitset<64>& {
    return flagValue.at(static_cast<size_t>(type));
}
//======================================================================
auto FlagCollection::operator[](type_t type) const -> const std::bitset<64>& {
    return flagValue.at(static_cast<size_t>(type));
}
//======================================================================
auto FlagCollection::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto iter = NAMETYPEMAP.find(key) ;
    if (iter == NAMETYPEMAP.end()){
        return false ;
    }
    if (!value.empty()){
        flagValue.at(static_cast<size_t>(iter->second)) = std::stoull(value,nullptr,0) ;
    }
    return true ;
}

