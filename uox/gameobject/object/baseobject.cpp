//Copyright © 2023 Charles Kerr. All rights reserved.

#include "baseobject.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;
//======================================================================
const std::map<BaseObject::type_t,std::string> BaseObject::NAMETYPEMAP{
    {BASE,"BASE"s},{ITEM,"ITEM"s},{MOBILE,"MOBILE"s},{CHARACTER,"CHARACTER"s},{PLAYER,"PLAYER"s},
    {MULTI,"MULTI"s},{SPAWNER,"SPAWNER"s},{BUILDING,"BUILDING"s},{BOAT,"BOAT"s}
};
//======================================================================
auto BaseObject::typeForName(const std::string &name) -> type_t{
    auto iter = std::find_if(NAMETYPEMAP.begin(),NAMETYPEMAP.end(),[name](const std::pair<type_t,std::string> &entry){
        return name == entry.second ;
    });
    if (iter != NAMETYPEMAP.end()){
        return iter->first ;
    }
    throw std::runtime_error("Provide name not a valid game object type: "s + name);
}
//======================================================================
BaseObject::BaseObject(type_t objecttype):objectType(objecttype),pendingDelete(false),includeSave(true),uoID(INVALIDID){
    serialNumber = INVALIDSERIAL ;
}
//======================================================================
auto BaseObject::header() const -> std::string {
    return "["s+ util::ntos(serialNumber,16,true,8)+":"s+NAMETYPEMAP.at(this->objectType)+"]"s ;
}
//======================================================================
auto BaseObject::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = false ;
    if (key == "NAME"){
        name = value ;
        rvalue = true ;
    }
    else if (key == "LOCATION") {
        this->location = Location(value) ;
        rvalue = true ;
    }
    else if (key == "VISIBILITY"){
        this->visiblity = Visiblity(value) ;
        rvalue = true ;
    }
    else if (key == "UOID"){
        this->uoID = static_cast<uoid_t>(std::stoul(value,nullptr,0)) ;
        rvalue = true ;
    }
    return rvalue ;
}

//======================================================================
auto BaseObject::saveData(std::ostream &output) const -> void {
    output << "\tNAME = " << name << "\n";
    output << "\tLOCATION = " <<location.describe()<<"\n";
    output << "\tVISIBILITY = " << visiblity.describe()<<"\n" ;
    output << "\tUOID = " << util::ntos(uoID,16,true,4) << "\n" ;
}
//======================================================================
auto BaseObject::save(std::ostream &output) const -> void {
    output << this->header()<<"\n{\n";
    saveData(output) ;
    output <<"}\n\n";
}
//======================================================================
auto BaseObject::setDelete() const -> void {
    objectFlag.set(ObjectFlag::REMOVE,true);
}
