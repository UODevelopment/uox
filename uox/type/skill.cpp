//Copyright © 2023 Charles Kerr. All rights reserved.

#include "skill.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "utility/strutil.hpp"
using namespace std::string_literals ;

//======================================================================
// SkillEntry
//======================================================================
//======================================================================
//======================================================================
const std::map<SkillEntry::type_t,std::string> SkillEntry::TYPENAMEMAP{
    {ALCHEMY,"ALCHEMY"s},{ANATOMY,"ANATOMY"s},{ANIMALLORE,"ANIMALLORE"s},{ITEMID,"ITEMID"s},{ARMSLORE,"ARMSLORE"s},{PARRYING,"PARRYING"s},
    {BEGGING,"BEGGING"s},{BLACKSMITHING,"BLACKSMITHING"s},{BOWCRAFT,"BOWCRAFT"s},{PEACEMAKING,"PEACEMAKING"s},{CAMPING,"CAMPING"s},{CARPENTRY,"CARPENTRY"s},
    {CARTOGRAPHY,"CARTOGRAPHY"s},{COOKING,"COOKING"s},{DETECTINGHIDDEN,"DETECTINGHIDDEN"s},{ENTICEMENT,"ENTICEMENT"s},{EVALUATINGINTEL,"EVALUATINGINTEL"s},{HEALING,"HEALING"s},
    {FISHING,"FISHING"s},{FORENSICS,"FORENSICS"s},{HERDING,"HERDING"s},{HIDING,"HIDING"s},{PROVOCATION,"PROVOCATION"s},{INSCRIPTION,"INSCRIPTION"s},
    {LOCKPICKING,"LOCKPICKING"s},{MAGERY,"MAGERY"s},{MAGICRESISTANCE,"MAGICRESISTANCE"s},{TACTICS,"TACTICS"s},{SNOOPING,"SNOOPING"s},{MUSICIANSHIP,"MUSICIANSHIP"s},
    {POISONING,"POISONING"s},{ARCHERY,"ARCHERY"s},{SPIRITSPEAK,"SPIRITSPEAK"s},{STEALING,"STEALING"s},{TAILORING,"TAILORING"s},{TAMING,"TAMING"s},
    {TASTEID,"TASTEID"s},{TINKERING,"TINKERING"s},{TRACKING,"TRACKING"s},{VETERINARY,"VETERINARY"s},{SWORDSMANSHIP,"SWORDSMANSHIP"s},{MACEFIGHTING,"MACEFIGHTING"s},
    {FENCING,"FENCING"s},{WRESTLING,"WRESTLING"s},{LUMBERJACKING,"LUMBERJACKING"s},{MINING,"MINING"s},{MEDITATION,"MEDITATION"s},{STEALTH,"STEALTH"s},
    {REMOVETRAP,"REMOVETRAP"s},{NECROMANCY,"NECROMANCY"s},{FOCUS,"FOCUS"s},{CHIVALRY,"CHIVALRY"s},{BUSHIDO,"BUSHIDO"s},{NINJITSU,"NINJITSU"s},
    {SPELLWEAVING,"SPELLWEAVING"s},{IMBUING,"IMBUING"s},{MYSTICISM,"MYSTICISM"s},{THROWING,"THROWING"s}
};
//======================================================================
auto SkillEntry::skillForName(const std::string &name) -> type_t {
    auto iter = std::find_if(TYPENAMEMAP.begin(),TYPENAMEMAP.end(),[&name](const std::pair<type_t,std::string> &entry){
        return entry.second == name ;
    });
    if (iter != TYPENAMEMAP.end() ){
        return iter->first ;
    }
    throw std::out_of_range("Skill/Attribute name not in collection: "s+name) ;
}
//======================================================================
auto SkillEntry::nameForSkill(type_t skill)  -> const std::string& {
    auto iter = TYPENAMEMAP.find(skill) ;
    if (iter != TYPENAMEMAP.end()){
        return iter->second;
    }
    throw std::out_of_range("Skill/Attribute not in collection: "s+std::to_string(static_cast<int>(skill))) ;
}
//======================================================================
auto SkillEntry::size() -> size_t{
    return TYPENAMEMAP.size() ;
}
//======================================================================
auto SkillEntry::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = false ;
    if (key == "STRENGTH"){
        this->strength = std::stoi(value,nullptr,0) ;
        rvalue = true ;
    }
    else if (key == "DEXTERITY"){
        this->dexterity = std::stoi(value,nullptr,0) ;
        rvalue = true ;
    }
    else if (key == "INTELLIGENCE"){
        this->intelligence = std::stoi(value,nullptr,0) ;
        rvalue = true ;
    }
    else if (key == "ADVANCEMENT"){
        this->advancement.addEntry(AdvanceEntry(value));
        rvalue = true ;
    }
    else if (key == "VERB"){
        this->useVerb = value ;
        rvalue = true ;
    }
    else if (key == "DELAY"){
        this->delay = std::stoi(value,nullptr,0) ;
        rvalue = true ;
    }
    return rvalue;
}
//======================================================================
SkillEntry::SkillEntry():type(type_t::ANATOMY),delay(0),strength(0),dexterity(0),intelligence(0),useVerb("created"){
    
}
//======================================================================
SkillEntry::SkillEntry(type_t type):SkillEntry() {
    this->type = type ;
}
//======================================================================
auto SkillEntry::gain(int currentValue,bool success) const ->int {
    return advancement.gain(currentValue, success) ;
}

//======================================================================
// Skill
//======================================================================
//======================================================================
 std::map<SkillEntry::type_t,SkillEntry> Skill::SKILLENTRYMAP{
     {SkillEntry::type_t::ALCHEMY,SkillEntry()},{SkillEntry::type_t::ANATOMY,SkillEntry()},
     {SkillEntry::type_t::ANIMALLORE,SkillEntry()},{SkillEntry::type_t::ITEMID,SkillEntry()},
     {SkillEntry::type_t::ARMSLORE,SkillEntry()},{SkillEntry::type_t::PARRYING,SkillEntry()},
     {SkillEntry::type_t::BEGGING,SkillEntry()},{SkillEntry::type_t::BLACKSMITHING,SkillEntry()},
     {SkillEntry::type_t::BOWCRAFT,SkillEntry()},{SkillEntry::type_t::PEACEMAKING,SkillEntry()},
     {SkillEntry::type_t::CAMPING,SkillEntry()},{SkillEntry::type_t::CARPENTRY,SkillEntry()},
     {SkillEntry::type_t::CARTOGRAPHY,SkillEntry()},{SkillEntry::type_t::COOKING,SkillEntry()},
     {SkillEntry::type_t::DETECTINGHIDDEN,SkillEntry()},{SkillEntry::type_t::ENTICEMENT,SkillEntry()},
     {SkillEntry::type_t::EVALUATINGINTEL,SkillEntry()},{SkillEntry::type_t::HEALING,SkillEntry()},
     {SkillEntry::type_t::FISHING,SkillEntry()},{SkillEntry::type_t::FORENSICS,SkillEntry()},
     {SkillEntry::type_t::HERDING,SkillEntry()},{SkillEntry::type_t::HIDING,SkillEntry()},
     {SkillEntry::type_t::PROVOCATION,SkillEntry()},{SkillEntry::type_t::INSCRIPTION,SkillEntry()},
     {SkillEntry::type_t::LOCKPICKING,SkillEntry()},{SkillEntry::type_t::MAGERY,SkillEntry()},
     {SkillEntry::type_t::MAGICRESISTANCE,SkillEntry()},{SkillEntry::type_t::TACTICS,SkillEntry()},
     {SkillEntry::type_t::SNOOPING,SkillEntry()},{SkillEntry::type_t::MUSICIANSHIP,SkillEntry()},
     {SkillEntry::type_t::POISONING,SkillEntry()},{SkillEntry::type_t::ARCHERY,SkillEntry()},
     {SkillEntry::type_t::SPIRITSPEAK,SkillEntry()},{SkillEntry::type_t::STEALING,SkillEntry()},
     {SkillEntry::type_t::TAILORING,SkillEntry()},{SkillEntry::type_t::TAMING,SkillEntry()},
     {SkillEntry::type_t::TASTEID,SkillEntry()},{SkillEntry::type_t::TINKERING,SkillEntry()},
     {SkillEntry::type_t::TRACKING,SkillEntry()},{SkillEntry::type_t::VETERINARY,SkillEntry()},
     {SkillEntry::type_t::SWORDSMANSHIP,SkillEntry()},{SkillEntry::type_t::MACEFIGHTING,SkillEntry()},
     {SkillEntry::type_t::FENCING,SkillEntry()},{SkillEntry::type_t::WRESTLING,SkillEntry()},
     {SkillEntry::type_t::LUMBERJACKING,SkillEntry()},{SkillEntry::type_t::MINING,SkillEntry()},
     {SkillEntry::type_t::MEDITATION,SkillEntry()},{SkillEntry::type_t::STEALTH,SkillEntry()},
     {SkillEntry::type_t::REMOVETRAP,SkillEntry()},{SkillEntry::type_t::NECROMANCY,SkillEntry()},
     {SkillEntry::type_t::FOCUS,SkillEntry()},{SkillEntry::type_t::CHIVALRY,SkillEntry()},
     {SkillEntry::type_t::BUSHIDO,SkillEntry()},{SkillEntry::type_t::NINJITSU,SkillEntry()},
     {SkillEntry::type_t::SPELLWEAVING,SkillEntry()},{SkillEntry::type_t::IMBUING,SkillEntry()},
     {SkillEntry::type_t::MYSTICISM,SkillEntry()},{SkillEntry::type_t::THROWING,SkillEntry()}
 };
//======================================================================
auto Skill::skillEntryForType(SkillEntry::type_t type)  -> const SkillEntry& {
    auto iter = SKILLENTRYMAP.find(type) ;
    if (iter != SKILLENTRYMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("Skill not in in collection: "s + std::to_string(static_cast<int>(type)));
}

//======================================================================
auto Skill::loadSkillConfiguration(const std::filesystem::path &path) -> bool {
    auto input = std::ifstream(path.string());
    if (!input.is_open()){
        return false ;
    }
    auto buffer = std::vector<char>(4096,0) ;
    auto entry = SkillEntry() ;
    auto valid = false ;
    while (input.good() && !input.eof()){
        input.getline(buffer.data(),buffer.size()-1);
        if (input.gcount()>0) {
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data() ;
            line = util::trim(util::strip(line,"//"));
            if (!line.empty()){
                if (line[0]=='[' && line[line.size()-1]== ']'){
                    // It is a section header!
                    valid = false ;
                    auto [stype,ssec] = util::split(util::trim(util::contentsOf(line, "[", "]")),":");
                    if (util::upper(ssec) == "SKILL"){
                        try {
                            auto type = SkillEntry::skillForName(util::upper(stype));
                            entry = SkillEntry(type) ;
                            valid = true ;
                        }
                        catch(...){
                        }
                    }
                }
                else if (line[0] == '}' && valid){
                    SKILLENTRYMAP.insert_or_assign(entry.type,entry);
                    valid = false ;
                }
                else if (line[0] != '{' && valid){
                    // this is a data line!
                    auto [skey,svalue] = util::split(line,"=") ;
                    entry.setKeyValue(util::upper(skey),svalue);
                }
            }
        }
    }
    return true ;
}
//======================================================================
Skill::Skill():currentValue(0),type(SkillEntry::type_t::ANATOMY){
    
}
//======================================================================
Skill::Skill(SkillEntry::type_t type):Skill(){
    this->type = type ;
}
//======================================================================
Skill::Skill(const std::string &line):Skill(){
    auto [first,second] = util::split(line,",") ;
    this->type = SkillEntry::skillForName(util::upper(first)) ;
    this->currentValue = std::stoi(second,nullptr,0) ;
}
//======================================================================
auto Skill::attribute() const ->const SkillEntry&{
    return Skill::skillEntryForType(this->type);
}
//======================================================================
auto Skill::gain(bool success) const -> int {
    return Skill::skillEntryForType(this->type).gain(this->currentValue, success) ;
}
//======================================================================
auto Skill::operator+(int value) const ->Skill {
    auto rvalue = *this ;
    rvalue.currentValue += value ;
    return rvalue;
}
//======================================================================
auto Skill::operator-(int value) const ->Skill {
    auto rvalue = *this ;
    rvalue.currentValue += value ;
    return rvalue;
}
//======================================================================
auto Skill::operator+(const Skill &value) const ->Skill {
    auto rvalue = *this ;
    rvalue.currentValue += value.currentValue ;
    return rvalue;
}
//======================================================================
auto Skill::operator-(const Skill &value) const ->Skill {
    auto rvalue = *this ;
    rvalue.currentValue += value.currentValue ;
    return rvalue;
}
//======================================================================
auto Skill::operator==(int value) const ->bool {
    return this->currentValue == value ;
}
//======================================================================
auto Skill::operator==(const Skill &value) const -> bool {
    return this->currentValue == value.currentValue ;
}
//======================================================================
auto Skill::operator!=(int value) const -> bool {
    return !operator==(value) ;
}
//======================================================================
auto Skill::operator!=(const Skill &value) const -> bool {
    return !operator==(value) ;
}
//======================================================================
auto Skill::operator>(int value) const -> bool {
    return this->currentValue>value ;
}
//======================================================================
auto Skill::operator>(const Skill &value) const -> bool {
    return this->currentValue > value.currentValue;
}
//======================================================================
auto Skill::operator<(int value) const -> bool {
    return this->currentValue < value ;
}
//======================================================================
auto Skill::operator<(const Skill &value) const -> bool {
    return this->currentValue < value.currentValue ;
}
//======================================================================
auto Skill::operator>=(int value) const -> bool {
    return operator>(value) || operator==(value) ;
}
//======================================================================
auto Skill::operator>=(const Skill &value) const -> bool {
    return operator>(value) || operator==(value) ;
}
//======================================================================
auto Skill::operator<=(int value) const -> bool {
    return operator<(value) || operator==(value) ;
}
//======================================================================
auto Skill::operator<=(const Skill &value) const -> bool {
    return operator<(value) || operator==(value) ;
}
//======================================================================
auto Skill::operator=(int value)  ->Skill& {
    this->currentValue  = value ;
    return *this ;
}

//======================================================================
auto Skill::name() const -> const std::string&{
    return SkillEntry::nameForSkill(this->type);
}
//======================================================================
auto Skill::describe() const -> std::string {
    return name()+","s+std::to_string(currentValue);
}
//======================================================================
// SkillCollection
//======================================================================
//======================================================================
SkillCollection::SkillCollection() {

    for (size_t i = 0 ; i < SkillEntry::size() ; i++){
        skill.push_back(Skill(static_cast<SkillEntry::type_t>(i)));
    }
}
//======================================================================
auto SkillCollection::operator[](SkillEntry::type_t type) -> Skill& {
    return skill.at(static_cast<size_t>(type));
}
//======================================================================
auto SkillCollection::operator[](SkillEntry::type_t type) const -> const Skill& {
    return skill.at(static_cast<size_t>(type));
}
