//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef layer_hpp
#define layer_hpp

#include <cstdint>
#include <ostream>
#include <map>
#include <string>
#include <vector>
#include "typedef.hpp"
//======================================================================
// Layer
//======================================================================
//======================================================================
struct Layer {
    enum type_t {
        NONE = 0,RIGHTHAND,LEFTHAND,FOOTWEAR,PANTS,INNERSHIRT,
        HELMET,GLOVE,RING,TALISMAN,NECK,HAIR,
        WAIST,TUNIC,BRACELET,FACE,FACIALHAIR,OUTERSHIRT,
        EARRING,SLEEVE,CLOAK,PACKITEM,ROBE,OUTERLEGGING,
        INNERLEGGING,MOUNT,SELLCONTAINER,BOUGHTCONTAINER,BUYCONTAINER,UNUSED,
        SECURETRADE
    };
    static const std::map<type_t,std::string> TYPENAMEMAP ;
    static auto typeForName(const std::string & name) -> type_t ;
    static auto nameForType(type_t type) -> const std::string& ;
};

//======================================================================
// LayerCollection
//======================================================================
//======================================================================
struct LayerCollection {
    std::vector<serial_t> value ;
    static const std::string KEY ;
    auto operator[](Layer::type_t index) const -> const serial_t& ;
    auto operator[](Layer::type_t index)  ->  serial_t& ;

    LayerCollection() ;
    auto setKeyValue(const std::string &key, const std::string &value) -> bool ;
    auto save(std::ostream &output) const ->void ;
};
#endif /* layer_hpp */
