//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef attribute_hpp
#define attribute_hpp

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <vector>
struct Advancement ;
//======================================================================
struct Attribute {
    enum type_t {
        STRENGTH=0,DEXTERITY,INTELLECT,FAME,KARMA
    };
    static const std::map<type_t,std::string> TYPENAMEMAP ;
    static std::vector<Advancement> advancement ;
    
    static auto typeForName(const std::string &name) -> type_t ;
    static auto nameForType(type_t type) -> const std::string& ;
    static auto size() -> size_t ;
    static auto loadConfiguration(const std::filesystem::path &path) -> bool ;
    
    
    type_t type ;
    int value ;


    Attribute() ;
    Attribute(type_t type);
    Attribute(type_t type, int value);
    Attribute(const std::string &line) ;
    auto describe() const -> std::string ;
    auto gainAdvancment() -> Advancement& ;
    auto gainAdvancment() const -> const Advancement& ;
    auto gain(bool success) -> int ;
    
    auto operator==(const Attribute &value) const ->bool ;
    auto operator==(int value) const ->bool ;
    auto operator!=(const Attribute &value) const ->bool ;
    auto operator!=(int value) const ->bool ;
    auto operator<(const Attribute &value) const ->bool ;
    auto operator<(int value) const ->bool ;
    auto operator>(const Attribute &value) const ->bool ;
    auto operator>(int value) const ->bool ;
    auto operator<=(const Attribute &value) const ->bool ;
    auto operator<=(int value) const ->bool ;
    auto operator>=(const Attribute &value) const ->bool ;
    auto operator>=(int value) const ->bool ;

    auto operator+(int value) const -> Attribute;
    auto operator+(const Attribute &value) const -> Attribute ;
    auto operator-(int value) const -> Attribute;
    auto operator-(const Attribute &value) const -> Attribute ;
    
    auto operator=(int value) -> Attribute& ;
};

#endif /* attribute_hpp */
