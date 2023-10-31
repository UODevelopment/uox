//Copyright © 2023 Charles Kerr. All rights reserved.

#include "stringcollection.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
const std::map<std::string, StringCollection::type_t> StringCollection::NAMETYPEMAP{
    {"NAME"s,NAME},{"LANGUAGE",LANGUAGE},{"PUBLICIP",PUBLICIP}
};
//======================================================================
auto StringCollection::typeForName(const std::string &name) -> type_t {
    auto iter = NAMETYPEMAP.find(name) ;
    if (iter != NAMETYPEMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("String type not in range: "s+name);
}
//======================================================================
StringCollection::StringCollection(){
    reset() ;
 }
//======================================================================
auto StringCollection::reset() -> void {
    stringValue = std::vector<std::string>(static_cast<int>(COUNT));
}
//======================================================================
auto StringCollection::postLoad() ->void {
}
//======================================================================
auto StringCollection::operator[](type_t type) const -> const std::string& {
    return stringValue.at(static_cast<size_t>(type));
}
//======================================================================
auto StringCollection::operator[](type_t type)  ->  std::string& {
    return stringValue.at(static_cast<size_t>(type));
}
//======================================================================
auto StringCollection::setKeyValue(const std::string &key, const std::string &value) -> bool {
    auto iter = NAMETYPEMAP.find(key) ;
    if (iter == NAMETYPEMAP.end()){
        return false ;
    }
    if (!value.empty()){
        stringValue.at(static_cast<size_t>(iter->second)) = value ;
    }
    return true ;
}

