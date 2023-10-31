//Copyright © 2023 Charles Kerr. All rights reserved.

#include "realcollection.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
//======================================================================
const std::map<std::string,RealCollection::type_t> RealCollection::NAMETYPEMAP{
    
};
//======================================================================
auto RealCollection::typeForName(const std::string &name) -> type_t {
    auto iter = NAMETYPEMAP.find(name) ;
    if (iter != NAMETYPEMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("Int type out of range: "s+name);
}
//======================================================================
RealCollection::RealCollection(){
    reset();
}
//======================================================================
auto RealCollection::reset() -> void {
    realValue = std::vector<double>(static_cast<int>(COUNT),0.0);
}
//======================================================================
auto RealCollection::postLoad() ->void {
}
//======================================================================
auto RealCollection::operator[](type_t type) const -> const double& {
    return realValue.at(static_cast<size_t>(type)) ;
}
//======================================================================
auto RealCollection::operator[](type_t type)  ->  double& {
    return realValue.at(static_cast<size_t>(type)) ;
}
//======================================================================
auto RealCollection::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto iter = NAMETYPEMAP.find(key) ;
    if (iter == NAMETYPEMAP.end()){
        return false ;
    }
    if (!value.empty()){
        realValue.at(static_cast<size_t>(iter->second)) = std::stod(value) ;
    }
    return true ;
}


