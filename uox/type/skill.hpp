//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef skill_hpp
#define skill_hpp

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

#include "advancement.hpp"
//======================================================================
// SkillEntry 
//======================================================================
//======================================================================
struct SkillEntry {
    enum type_t {
        ALCHEMY = 0, ANATOMY, ANIMALLORE, ITEMID, ARMSLORE, PARRYING,
        BEGGING, BLACKSMITHING, BOWCRAFT, PEACEMAKING, CAMPING, CARPENTRY,
        CARTOGRAPHY, COOKING, DETECTINGHIDDEN, ENTICEMENT, EVALUATINGINTEL, HEALING,
        FISHING, FORENSICS, HERDING, HIDING, PROVOCATION, INSCRIPTION,
        LOCKPICKING, MAGERY, MAGICRESISTANCE, TACTICS, SNOOPING, MUSICIANSHIP,
        POISONING, ARCHERY, SPIRITSPEAK, STEALING, TAILORING, TAMING,
        TASTEID, TINKERING, TRACKING, VETERINARY, SWORDSMANSHIP, MACEFIGHTING,
        FENCING, WRESTLING, LUMBERJACKING,  MINING, MEDITATION, STEALTH,
        REMOVETRAP, NECROMANCY, FOCUS, CHIVALRY, BUSHIDO, NINJITSU,
        SPELLWEAVING, IMBUING, MYSTICISM, THROWING
    };
    static const std::map<type_t,std::string> TYPENAMEMAP ;
    static auto skillForName(const std::string &name) -> type_t ;
    static auto nameForSkill(type_t skill)  -> const std::string& ;
    static auto size() -> size_t ;
    Advancement advancement ;
    std::string useVerb ;
    int delay ;
    int strength ;
    int dexterity ;
    int intelligence ;
    type_t type ;
    auto gain(int currentValue,bool success) const ->int ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool ;
    SkillEntry() ;
    SkillEntry(type_t type) ;
};

//======================================================================
// Skill
//======================================================================
//======================================================================
struct Skill {
    static std::map<SkillEntry::type_t,SkillEntry> SKILLENTRYMAP ;
    static auto loadSkillConfiguration(const std::filesystem::path &path) -> bool ;
    static auto skillEntryForType(SkillEntry::type_t type)  -> const SkillEntry& ;
    SkillEntry::type_t type ;
    int currentValue ;
    Skill() ;
    Skill(SkillEntry::type_t type) ;
    Skill(const std::string &line) ;
    auto attribute() const ->const SkillEntry& ;
    auto gain(bool success) const -> int ;
    auto operator+(int value) const ->Skill ;
    auto operator-(int value) const ->Skill ;
    auto operator+(const Skill &value) const ->Skill ;
    auto operator-(const Skill &value) const ->Skill ;
    auto operator==(int value) const -> bool ;
    auto operator==(const Skill &value) const -> bool ;
    auto operator!=(int value) const -> bool ;
    auto operator!=(const Skill &value) const -> bool ;
    auto operator>(int value) const -> bool ;
    auto operator>(const Skill &value) const -> bool ;
    auto operator<(int value) const -> bool ;
    auto operator<(const Skill &value) const -> bool ;
    auto operator>=(int value) const -> bool ;
    auto operator>=(const Skill &value) const -> bool ;
    auto operator<=(int value) const -> bool ;
    auto operator<=(const Skill &value) const -> bool ;
    auto operator=(int value)  ->Skill& ;

    auto name() const -> const std::string & ;
    auto describe() const -> std::string ;
};
//======================================================================
// SkillCollection
//======================================================================
//======================================================================
struct SkillCollection {
    std::vector<Skill> skill ;
    SkillCollection() ;
    auto operator[](SkillEntry::type_t type) -> Skill& ;
    auto operator[](SkillEntry::type_t type) const -> const Skill& ;
};

#endif /* skill_hpp */
