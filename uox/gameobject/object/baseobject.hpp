//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef baseobject_hpp
#define baseobject_hpp

#include <cstdint>
#include <istream>
#include <map>
#include <ostream>
#include <string>

#include "type/typedef.hpp"
#include "type/location.hpp"
#include "objectflag.hpp"
#include "type/visibility.hpp"
//======================================================================

class BaseObject {
public:
    enum type_t { BASE,ITEM,MOBILE,CHARACTER,PLAYER,MULTI,SPAWNER,BUILDING,BOAT};
    auto typeForName(const std::string &name) -> type_t ;
protected:
    static const std::map<type_t,std::string> NAMETYPEMAP ;
    bool pendingDelete ;
    bool includeSave ;
public:
    type_t objectType ;
    Location location ;
    Visiblity visiblity ;
    uoid_t uoID  ;
    color_t color ;
    mutable ObjectFlag objectFlag ;
    serial_t serialNumber ;
    std::string name ;

protected:
    auto header() const -> std::string ;
    virtual auto saveData(std::ostream &output) const -> void ;
    virtual auto setKeyValue(const std::string &key, const std::string &value) ->bool ;
    virtual auto setDelete() const ->void ;

public:

    BaseObject(type_t objecttype= BASE) ;
    virtual ~BaseObject() = default;
    auto save(std::ostream &output) const -> void ;
};

#endif /* baseobject_hpp */
