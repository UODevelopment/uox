//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef boat_hpp
#define boat_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "multi.hpp"


//======================================================================
class Boat : public Multi {
 
public:
    auto saveData(std::ostream &output) const -> void final ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool final ;

    Boat();
    Boat(serial_t serial);
    ~Boat() = default ;
};

#endif /* boat_hpp */
