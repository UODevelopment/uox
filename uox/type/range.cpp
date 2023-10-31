//Copyright © 2023 Charles Kerr. All rights reserved.

#include "range.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"
#include "random/random.hpp"
using namespace std::string_literals ;
using Random = effolkronium::random_static ;
//======================================================================
auto Range::random() const -> int {
    return Random::get(low,high) ;
}
//======================================================================
Range::Range():low(0),high(0){
    
}
//======================================================================
Range::Range(int lowvalue,int highvalue):low(lowvalue),high(highvalue){
    
}
//======================================================================
Range::Range(const std::string &line):Range() {
    auto values = util::parse(line,"-") ;
    switch (values.size()) {
        default:
        case 2:
            high = std::stoi(values[1],nullptr,0);
            [[fallthrough]];
        case 1:
            low = std::stoi(values[1],nullptr,0) ;
            if (high == 0) {
                high = low ;
            }
            [[fallthrough]];
        case 0:
            break;
    }
    
}
//======================================================================
auto Range::describe() const -> std::string {
    return std::to_string(low) + "-"s + std::to_string(high) ;
}

