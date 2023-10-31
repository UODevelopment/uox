//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef mobile_hpp
#define mobile_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "baseobject.hpp"
#include "type/direction.hpp"
#include "type/attribute.hpp"
#include "type/layer.hpp"
//======================================================================
class Mobile : public BaseObject {
    
public:
    auto saveData(std::ostream &output) const -> void override ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool override ;

    Mobile() ;
    Mobile(serial_t serial) ;

    virtual ~Mobile()= default ;
    bool active ;

    Direction direction ;
    Attribute strength ;
    Attribute intellect ;
    Attribute dexterity ;
    Attribute fame ;
    Attribute karma ;
    
    LayerCollection layer ;
    
    
    auto setDelete() const ->void override;

};


#endif /* mobile_hpp */
