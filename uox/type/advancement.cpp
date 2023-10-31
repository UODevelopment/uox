//Copyright © 2023 Charles Kerr. All rights reserved.

#include "advancement.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"
#include "random/random.hpp"
using namespace std::string_literals ;
using Random = effolkronium::random_static ;
//======================================================================
// AdvanceEntry
//======================================================================
//======================================================================
AdvanceEntry::AdvanceEntry():startValue(0),chanceOnFailure(0),chanceOnSuccess(0){
    
}
//======================================================================
AdvanceEntry::AdvanceEntry(int start,int success,int failure, const Range &range):startValue(start),chanceOnFailure(failure),chanceOnSuccess(success),amountGain(range){
    
}
//======================================================================
AdvanceEntry::AdvanceEntry(const std::string &line):AdvanceEntry(){
    auto values = util::parse(line,",") ;
    if (values.size()>=3){
        startValue = std::stoi(values[0],nullptr,0);
        chanceOnSuccess = std::stoi(values[1],nullptr,0);
        chanceOnFailure = std::stoi(values[2],nullptr,0);
        amountGain = Range(1,1) ;
    }
    if (values.size() >=4){
        amountGain = Range(values[3]) ;
    }
}
//======================================================================
auto AdvanceEntry::describe() const -> std::string {
    return std::to_string(startValue) + ","s + std::to_string(chanceOnSuccess) + ","s + std::to_string(chanceOnFailure) + ","s + amountGain.describe() ;
}
//======================================================================
auto AdvanceEntry::operator<(const AdvanceEntry &entry) const -> bool {
    return this->startValue < entry.startValue ;
}
//======================================================================
auto AdvanceEntry::gain(bool success) const -> int {
    auto value = Random::get(1,1000) ;
    auto chance =  chanceOnSuccess ;

    if (!success){
        chance =  chanceOnFailure ;
    }
    auto amount =  0;
    if (value <= chance){
        amount = amountGain.random() ;
    }
    return amount ;
}
//======================================================================
// Advancement
//======================================================================

//======================================================================
Advancement::Advancement() {
    // we add a value of -1 to just ensure there is something
    entry.push_back(AdvanceEntry(-1,0,0,{0,0}));
}
//======================================================================
auto Advancement::addEntry(const AdvanceEntry &value) -> void {
    entry.push_back(value) ;
    std::sort(entry.begin(),entry.end()) ;
}

//======================================================================
auto Advancement::entryFor(int currentValue) const ->const AdvanceEntry& {
    auto iter = std::find_if(entry.rbegin(),entry.rend(),[currentValue](const AdvanceEntry &entry){
        return currentValue >= entry.startValue;
    });
    if (iter != entry.rend()){
        return *iter;
    }
    throw std::out_of_range("No advancement entry was found for current value: "s + std::to_string(currentValue));
}
//======================================================================
auto Advancement::entryFor(int currentValue) -> AdvanceEntry& {
    auto iter = std::find_if(entry.rbegin(),entry.rend(),[currentValue](const AdvanceEntry &entry){
        return currentValue >= entry.startValue;
    });
    if (iter != entry.rend()){
        return *iter;
    }
    throw std::out_of_range("No advancement entry was found for current value: "s + std::to_string(currentValue));
}

//======================================================================
auto Advancement::gain(int currentValue, bool success) const -> int {
    return this->entryFor(currentValue).gain(success) ;
}
