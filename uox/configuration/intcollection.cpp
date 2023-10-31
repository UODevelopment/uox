//Copyright © 2023 Charles Kerr. All rights reserved.

#include "intcollection.hpp"

#include <algorithm>
#include <stdexcept>

#include "type/typedef.hpp"

using namespace std::string_literals ;
//======================================================================
const std::map<std::string,IntCollection::type_t> IntCollection::NAMETYPEMAP{
    {"PORT"s,PORT},{"SERVERKEY"s,SERVERKEY},{"CLIENTFEATURE"s,CLIENTFEATURE},{"SERVERFEATURE"s,SERVERFEATURE}
};
//======================================================================
auto IntCollection::typeForName(const std::string &name) -> type_t {
    auto iter = NAMETYPEMAP.find(name) ;
    if (iter != NAMETYPEMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("Int type out of range: "s+name);
}
//======================================================================
IntCollection::IntCollection(){
    reset() ;
}
//======================================================================
auto IntCollection::reset() -> void {
    constexpr auto SHARDKEY = std::int64_t(0xFFFFFFFF) ; // This is only if no SERVERKEY is in the uox.cfg file
    intValue = std::vector<std::int64_t>(static_cast<int>(COUNT),0);
    intValue.at(static_cast<std::int64_t>(SERVERKEY)) = SHARDKEY ;
    intValue.at(static_cast<int>(PORT)) = 2593 ;
    intValue.at(static_cast<int>(CLIENTFEATURE)) = static_cast<std::int64_t>(0xf94ffLL);
    intValue.at(static_cast<int>(SERVERFEATURE)) = static_cast<std::int64_t>(0x11e8LL);
}
//======================================================================
auto IntCollection::postLoad() ->void {
}
//======================================================================
auto IntCollection::operator[](type_t type) const -> const std::int64_t& {
    return intValue.at(static_cast<size_t>(type)) ;
}
//======================================================================
auto IntCollection::operator[](type_t type)  ->  std::int64_t& {
    return intValue.at(static_cast<size_t>(type)) ;
}
//======================================================================
auto IntCollection::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto iter = NAMETYPEMAP.find(key) ;
    if (iter == NAMETYPEMAP.end()){
        return false ;
    }
    if (!value.empty()){
        intValue.at(static_cast<size_t>(iter->second)) = std::stoll(value,nullptr,0) ;
    }
    return true ;
}

