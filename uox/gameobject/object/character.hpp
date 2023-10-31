//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef character_hpp
#define character_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "mobile.hpp"
class CharacterFactory ;
//======================================================================
class Character : public Mobile {
    friend CharacterFactory ;
public:
    auto saveData(std::ostream &output) const -> void final ;
    auto setKeyValue(const std::string &key, const std::string &value) ->bool final ;

    Character() ;
    Character(serial_t serial) ;
    ~Character() = default ;
};

#endif /* character_hpp */
