//Copyright © 2023 Charles Kerr. All rights reserved.

#include "startcollection.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"
using namespace std::string_literals ;

//======================================================================
StartCollection::StartCollection(const std::string &key){
    this->keyword = util::upper(key) ;
}
//======================================================================
auto StartCollection::reset() -> void {
    location.clear() ;
}
//======================================================================
auto StartCollection::postLoad() ->void {
}
//======================================================================
auto StartCollection::size() const ->size_t {
    return location.size() ;
}
//======================================================================
auto StartCollection::setKeyValue(const std::string &key, const std::string &value) ->bool {
    if (key != keyword){
        return false ;
    }
    if (!value.empty()){
        location.push_back(StartLocation(value));
    }
    return true ;
}

