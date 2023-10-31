//Copyright © 2023 Charles Kerr. All rights reserved.

#include "attribute.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>

#include "advancement.hpp"
#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================

//======================================================================
const std::map<Attribute::type_t,std::string> Attribute::TYPENAMEMAP{
    {STRENGTH,"STRENGTH"s},{DEXTERITY,"DEXTERITY"s},{INTELLECT,"INTELLECT"s},{FAME,"FAME"s},{KARMA,"KARMA"s},
};
//======================================================================
std::vector<Advancement> Attribute::advancement{
    Advancement(),Advancement(),Advancement(),Advancement(),Advancement()
};
//======================================================================
auto Attribute::typeForName(const std::string &name) -> type_t {
    auto iter = std::find_if(TYPENAMEMAP.begin(),TYPENAMEMAP.end(),[&name](const std::pair<type_t,std::string> &entry){
        return entry.second == name ;
    });
    if (iter != TYPENAMEMAP.end()){
        return iter->first;
    }
    throw std::out_of_range("Attibute is not in collection: "s + name);
}
//======================================================================
auto Attribute::nameForType(type_t type) -> const std::string& {
    auto iter = TYPENAMEMAP.find(type) ;
    if (iter != TYPENAMEMAP.end()){
        return iter->second;
    }
    throw std::out_of_range("Attibute is not in collection: "s + std::to_string(static_cast<int>(type)));
}
//======================================================================
auto Attribute::size() -> size_t{
    return Attribute::advancement.size() ;
}

//======================================================================
auto Attribute::loadConfiguration(const std::filesystem::path &path) -> bool {
    if (Attribute::advancement.empty()){
        for (size_t i = 0 ; i < Attribute::size() ; i++){
            Attribute::advancement.push_back(Advancement());
        }
    }
    auto input = std::ifstream(path.string());
    if (!input.is_open()){
        return false ;
    }
    auto buffer = std::vector<char>(4096,0) ;
    auto valid = false ;
    auto type = Attribute::type_t::STRENGTH ;
    while (input.good() && !input.eof()){
        input.getline(buffer.data(),buffer.size()-1);
        if (input.gcount()>0){
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data() ;
            line = util::trim(util::strip(line,"//"));
            if (!line.empty()){
                if (line[0]=='[' && line[line.size()-1]== ']'){
                    // It is a section header!
                    valid = false ;
                    auto [stype,ssec] = util::split(util::trim(util::contentsOf(line, "[", "]")),":");
                    if (util::upper(ssec) == "ATTRIBUTE"){
                        try {
                            type = Attribute::typeForName(util::upper(stype));
                            valid = true ;
                        }
                        catch(...){
                        }
                    }
                }
                else if (line[0] == '}' && valid){
                    valid = false ;
                }
                else if (line[0] != '{' && valid){
                    // this is a data line!
                    auto [skey,svalue] = util::split(line,"=") ;
                    if (util::upper(skey)=="ADVANCEMENT"){
                        Attribute::advancement.at(static_cast<int>(type)).addEntry(AdvanceEntry(svalue));
                    }
                }
            }
        }
    }
    return true ;
}
//======================================================================
Attribute::Attribute():type(type_t::STRENGTH),value(0){
    if (Attribute::advancement.empty()){
        for (size_t i = 0 ; i < Attribute::size() ; i++){
            Attribute::advancement.push_back(Advancement());
        }
    }
}
//======================================================================
Attribute::Attribute(type_t type):Attribute(){
    this->type = type ;
}
//======================================================================
Attribute::Attribute(type_t type, int value):Attribute(type){
    this->value = value ;
}
//======================================================================
Attribute::Attribute(const std::string &line):Attribute(){
    auto [first,second] = util::split(line,",");
    this->type = Attribute::typeForName(util::upper(first));
    this->value = std::stoi(second,nullptr,0);
}
//======================================================================
auto Attribute::describe() const -> std::string {
    return Attribute::nameForType(this->type)+","s+std::to_string(value) ;
}
//======================================================================
auto Attribute::gainAdvancment() -> Advancement& {
    return Attribute::advancement.at(static_cast<int>(type));
}
//======================================================================
auto Attribute::gainAdvancment() const -> const Advancement& {
    return Attribute::advancement.at(static_cast<int>(type));
}
//======================================================================
auto Attribute::gain(bool success) -> int {
    return this->gainAdvancment().gain(this->value, success);
}

//======================================================================
auto Attribute::operator==(const Attribute &value) const ->bool {
    return this->value == value.value ;
}
//======================================================================
auto Attribute::operator==(int value) const ->bool {
    return this->value == value ;
}
//======================================================================
auto Attribute::operator!=(const Attribute &value) const ->bool {
    return !operator==(value) ;
}
//======================================================================
auto Attribute::operator!=(int value) const ->bool {
    return !operator==(value) ;
}
//======================================================================
auto Attribute::operator<(const Attribute &value) const ->bool {
    return this->value < value.value;
}
//======================================================================
auto Attribute::operator<(int value) const ->bool {
    return this->value < value ;
}
//======================================================================
auto Attribute::operator>(const Attribute &value) const ->bool {
    return this->value > value.value;
}
//======================================================================
auto Attribute::operator>(int value) const ->bool {
    return this->value > value;
}
//======================================================================
auto Attribute::operator<=(const Attribute &value) const ->bool {
    return operator<(value) || operator==(value) ;
}
//======================================================================
auto Attribute::operator<=(int value) const ->bool {
    return operator<(value) || operator==(value) ;
}
//======================================================================
auto Attribute::operator>=(const Attribute &value) const ->bool {
    return operator>(value) || operator==(value) ;
}
//======================================================================
auto Attribute::operator>=(int value) const ->bool {
    return operator>(value) || operator==(value) ;
}
//======================================================================
auto Attribute::operator+(int value) const -> Attribute{
    auto rvalue = *this ;
    rvalue.value += value ;
    return rvalue;
}
//======================================================================
auto Attribute::operator+(const Attribute &value) const -> Attribute {
    auto rvalue = *this ;
    rvalue.value += value.value ;
    return rvalue;
}
//======================================================================
auto Attribute::operator-(int value) const -> Attribute{
    auto rvalue = *this ;
    rvalue.value -= value ;
    return rvalue;
}
//======================================================================
auto Attribute::operator-(const Attribute &value) const -> Attribute {
    auto rvalue = *this ;
    rvalue.value -= value.value ;
    return rvalue;
}
//======================================================================
auto Attribute::operator=(int value) -> Attribute& {
    this->value = value ;
    return *this ;
}
