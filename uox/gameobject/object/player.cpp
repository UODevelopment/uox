//Copyright © 2023 Charles Kerr. All rights reserved.

#include "player.hpp"

#include <algorithm>
#include <stdexcept>

#include "network/client.hpp"
using namespace std::string_literals ;

//======================================================================
Player::Player():Mobile(){
    objectType = BaseObject::PLAYER ;
    client = nullptr;
}
//======================================================================
Player::Player(serial_t serial):Player(){
    this->serialNumber = serial ;
    
}
//======================================================================
Player::~Player(){
    if (client != nullptr){
        client->clearPlayer();
    }
}
//======================================================================
auto Player::saveData(std::ostream &output) const  -> void {
    Mobile::saveData(output);
}
//======================================================================
auto Player::setKeyValue(const std::string &key, const std::string &value) ->bool {
    auto rvalue = Mobile::setKeyValue(key, value) ;
    if (!rvalue){
        
    }
    return rvalue ;
}
