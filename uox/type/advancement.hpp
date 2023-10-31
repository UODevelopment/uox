//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef advancement_hpp
#define advancement_hpp

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "range.hpp"
//======================================================================


//======================================================================
// AdvanceEntry
//======================================================================
// All values are *10 , to handle decimals
//======================================================================
struct AdvanceEntry {
    int startValue ;
    int chanceOnSuccess ;
    int chanceOnFailure ;
    Range amountGain ;
    AdvanceEntry() ;
    AdvanceEntry(int start,int success,int failure, const Range &range) ;
    AdvanceEntry(const std::string &line) ;
    auto describe() const -> std::string ;
    auto gain(bool success) const -> int ;
    auto operator<(const AdvanceEntry &entry) const -> bool ;
    
};
//===================================== =================================
// Advancement
//======================================================================
//======================================================================
struct Advancement {
    std::vector<AdvanceEntry> entry ;
    auto entryFor(int currentValue) const ->const AdvanceEntry& ;
    auto entryFor(int currentValue)  -> AdvanceEntry& ;
    auto addEntry(const AdvanceEntry &value) -> void ;
    auto gain(int currentValue, bool success) const -> int ;
    Advancement() ;
};

#endif /* advancement_hpp */
