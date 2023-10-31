//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef player_hpp
#define player_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "type/layer.hpp"
#include "mobile.hpp"
#include "type/skill.hpp"

//======================================================================
class Client ;
class PlayerFactory;
class Player : public Mobile {
    friend class PlayerFactory ;
protected:
    auto saveData(std::ostream &output) const -> void final ;
public:
    auto setKeyValue(const std::string &key, const std::string &value) ->bool final ;
    Client *client ;
    Player() ;
    Player(serial_t serial) ;
    ~Player()  ;
};

#endif /* player_hpp */
