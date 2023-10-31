//Copyright © 2023 Charles Kerr. All rights reserved.

#include "eracollection.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
const std::map<std::string, EraCollection::type_t> EraCollection::NAMETYPEMAP {
    {"SERVERERA"s,SERVER}, {"ARMORCALCULATION"s,ARMOR}, {"STRENGTHDAMAGEBONUS"s,STRENGTH},
    {"TACTICSDAMAGEBONUS"s,TATICS}, {"ANATOMYDAMAGEBONUS"s,ANATOMY}, {"LUMBERJACKDAMAGEBONUS"s,LUMBERJACK},
    {"RACIALDAMAGEBONUS"s,RACIAL}, {"DAMAGEBONUSCAP"s,DAMAGE}, {"SHIELDPARRY"s,SHEILD},
    {"WEAPONPARRY"s,WEAPON}, {"WRESTLINGPARRY"s,WRESTLING}, {"COMBATHITCHANCE"s,HIT}
};
//======================================================================
auto EraCollection::typeForName(const std::string &name) ->type_t {
    auto iter = NAMETYPEMAP.find(name) ;
    if (iter != NAMETYPEMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("Era collection category not in range: "s+name);
}
//======================================================================
EraCollection::EraCollection(){
    reset() ;
}
//======================================================================
auto EraCollection::reset() -> void {
    eraCollectionValue = std::vector<Era>(static_cast<int>(COUNT));
}
//======================================================================
auto EraCollection::postLoad() -> void {
    
}
//======================================================================
auto EraCollection::operator[](type_t category) const -> const Era& {
    return eraCollectionValue.at(static_cast<size_t>(category));
}
//======================================================================
auto EraCollection::operator[](type_t category)  ->  Era& {
    return eraCollectionValue.at(static_cast<size_t>(category));
}
//======================================================================
auto EraCollection::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto iter = NAMETYPEMAP.find(key) ;
    if (iter != NAMETYPEMAP.end()){
        if (!value.empty()){
            eraCollectionValue.at(static_cast<size_t>(iter->second)) = Era(value) ;
        }
        return true ;
    }
    return false ;
}

