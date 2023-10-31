//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef range_hpp
#define range_hpp

#include <cstdint>
#include <iostream>
#include <string>

//======================================================================
struct Range {
    int low ;
    int high ;
    auto random() const -> int ;
    Range() ;
    Range(int lowvalue,int highvalue);
    Range(const std::string &line) ;
    auto describe() const -> std::string ;
};

#endif /* range_hpp */
