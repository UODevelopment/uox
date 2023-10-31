//Copyright © 2023 Charles Kerr. All rights reserved.

#include "mobile.hpp"

#include <algorithm>
#include <stdexcept>

#include "gameobject/factory/itemfactory.hpp"
#include "gameobject/object/item.hpp"

#include "utility/strutil.hpp"

using namespace std::string_literals ;
Attribute strength ;
Attribute intellect ;
Attribute dexterity ;
Attribute fame ;
Attribute karma ;

//======================================================================
Mobile::Mobile() : BaseObject(BaseObject::MOBILE),active(false),strength(Attribute::STRENGTH),intellect(Attribute::INTELLECT),dexterity(Attribute::DEXTERITY),fame(Attribute::FAME),karma(Attribute::KARMA) {
    
}
//======================================================================
Mobile::Mobile(serial_t serial) :Mobile() {
    this->serialNumber = serial ;
}

//======================================================================
auto Mobile::saveData(std::ostream &output) const -> void {
    BaseObject::saveData(output);
    output <<"\tDIRECTION = " << direction.describe()<<"\n";
    output <<"\tATTRIBUTE = " << strength.describe()<<"\n";
    output <<"\tATTRIBUTE = " << dexterity.describe()<<"\n";
    output <<"\tATTRIBUTE = " << intellect.describe()<<"\n";
    output <<"\tATTRIBUTE = " << fame.describe()<<"\n";
    output <<"\tATTRIBUTE = " << karma.describe()<<"\n";
    layer.save(output) ;
}

//======================================================================
auto Mobile::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = BaseObject::setKeyValue(key, value) ;
    if (!rvalue){
        if (key == "DIRECTION"){
            this->direction = Direction(value) ;
            rvalue = true ;
        }
        else if (key=="ATTRIBUTE"){
            rvalue = true ;
            auto att = Attribute(value) ;
            if (att.type == Attribute::STRENGTH){
                strength = att ;
            }
            else if (att.type == Attribute::INTELLECT){
                intellect = att ;
            }
            else if (att.type == Attribute::DEXTERITY){
                dexterity = att ;
            }
            else if (att.type == Attribute::FAME){
                fame = att ;
            }
            else if (att.type == Attribute::KARMA){
                karma = att ;
            }
       }
       else {
           rvalue = layer.setKeyValue(key, value);
        }
    }
    return rvalue ;
}
//======================================================================
auto Mobile::setDelete() const ->void {
    BaseObject::setDelete() ;
    // We need to mark everthing we have deleted
    for (const auto &serial:layer.value){
        if (serial != INVALIDSERIAL) {
            /*
            if (ItemFactory::shared().exists(serial)){
                ItemFactory::shared()[serial]->setDelete();
            }
             */
        }
    }
}
