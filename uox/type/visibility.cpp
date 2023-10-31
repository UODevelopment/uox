//Copyright © 2023 Charles Kerr. All rights reserved.

#include "visibility.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;
//======================================================================
const std::map<Visiblity::type_t,std::string> Visiblity::TYPENAMEMAP {
    {VISIBLE,"VISIBLE"},{MAGICHIDDEN,"MAGICHIDDEN"},
    {PERMHIDDEN,"PERMHIDDEN"},{GHOSTHIDDEN,"GHOSTHIDDEN"}
};
//======================================================================
auto Visiblity::typeForName(const std::string &name) -> type_t {
    auto iter = std::find_if(TYPENAMEMAP.begin(),TYPENAMEMAP.end(),[&name](const std::pair<type_t,std::string> &entry){
        return entry.second == name ;
    });
    if (iter != TYPENAMEMAP.end()){
        return iter->first ;
    }
    throw std::out_of_range("Visbility type not valid: "s+name);
}
//======================================================================
Visiblity::Visiblity():visibleValue(type_t::VISIBLE) {
}

//======================================================================
Visiblity::Visiblity(type_t type):visibleValue(type){
}
//======================================================================
Visiblity::Visiblity(const std::string &line):Visiblity() {
    if (!line.empty()){
        visibleValue = typeForName(line);
    }
}
//======================================================================
auto Visiblity::describe() const -> const std::string & {
    return Visiblity::TYPENAMEMAP.at(visibleValue);
}
//======================================================================
auto Visiblity::operator==(type_t rhs) const ->bool {
    return !operator!=(rhs) ;
}
//======================================================================
auto Visiblity::operator!=(type_t rhs) const ->bool {
    return this->visibleValue != rhs ;
}
