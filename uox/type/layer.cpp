//Copyright © 2023 Charles Kerr. All rights reserved.

#include "layer.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
// Layer
//======================================================================
//======================================================================
const std::map< Layer::type_t,std::string> Layer::TYPENAMEMAP {
    {NONE,"NONE"s},{RIGHTHAND,"RIGHTHAND"s},{LEFTHAND,"LEFTHAND"s},{FOOTWEAR,"FOOTWEAR"s},{PANTS,"PANTS"s},{INNERSHIRT,"INNERSHIRT"s},
    {HELMET,"HELMET"s},{GLOVE,"GLOVE"s},{RING,"RING"s},{TALISMAN,"TALISMAN"s},{NECK,"NECK"s},{HAIR,"HAIR"s},
    {WAIST,"HELWAISTMET"s},{TUNIC,"TUNIC"s},{BRACELET,"BRACELET"s},{FACE,"FACE"s},{FACIALHAIR,"FACIALHAIR"s},{OUTERSHIRT,"OUTERSHIRT"s},
    {EARRING,"EARRING"s},{SLEEVE,"SLEEVE"s},{CLOAK,"CLOAK"s},{PACKITEM,"PACKITEM"s},{ROBE,"ROBE"s},{OUTERLEGGING,"OUTERLEGGING"s},
    {INNERLEGGING,"INNERLEGGING"s},{MOUNT,"MOUNT"s},{SELLCONTAINER,"SELLCONTAINER"s},{BOUGHTCONTAINER,"BOUGHTCONTAINER"s},{BUYCONTAINER,"BUYCONTAINER"s},{UNUSED,"UNUSED"s},
    {SECURETRADE,"SECURETRADE"s}
};
//======================================================================
auto Layer::typeForName(const std::string & name) -> type_t {
    auto iter = std::find_if(TYPENAMEMAP.begin(),TYPENAMEMAP.end(),[&name](const std::pair<type_t,std::string> &entry){
        return entry.second == name ;
    });
    if (iter != TYPENAMEMAP.end()){
        return iter->first;
    }
    throw std::out_of_range("Layer not in collection: "s+name);
}
//======================================================================
auto Layer::nameForType(type_t type) -> const std::string& {
    auto iter = TYPENAMEMAP.find(type) ;
    if (iter != TYPENAMEMAP.end()){
        return iter->second;
    }
    throw std::out_of_range("Layer not in collection: "s+std::to_string(type));

}

//======================================================================
// LayerCollection
//======================================================================
const std::string LayerCollection::KEY = "LAYER"s;
//======================================================================
LayerCollection::LayerCollection() {
    value = std::vector<serial_t>(31,INVALIDSERIAL);
}
//======================================================================
auto LayerCollection::operator[](Layer::type_t index) const -> const serial_t& {
    return value.at(static_cast<int>(index)) ;
}
//======================================================================
auto LayerCollection::operator[](Layer::type_t index)  ->  serial_t& {
    return value.at(static_cast<int>(index)) ;
}
//======================================================================
auto LayerCollection::setKeyValue(const std::string &key, const std::string &value) -> bool {
    auto rvalue = false ;
    if (key == KEY){
        auto [stype,svalue] = util::split(value,",");
        auto type = Layer::typeForName(stype);
        this->value.at(static_cast<int>(type)) = static_cast<serial_t>(std::stoul(svalue,nullptr,0)) ;
        rvalue = true ;
    }
    return rvalue ;
}
//======================================================================
auto LayerCollection::save(std::ostream &output) const ->void {
    for (size_t i = 0 ; i < this->value.size();i++){
        if (value.at(i) != INVALIDSERIAL){
            output <<"\t"<< KEY << " = " << Layer::nameForType(static_cast<Layer::type_t>(i))<<"," << util::ntos(value.at(i),16,true,8)<<"\n";
        }
    }
}
