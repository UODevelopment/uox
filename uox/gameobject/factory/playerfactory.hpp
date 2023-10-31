//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef playerfactory_hpp
#define playerfactory_hpp

#include <cstdint>
#include <filesystem>
#include <istream>
#include <ostream>
#include <string>
#include <unordered_map>
#include "gameobject/object/player.hpp"

#include "serialgen.hpp"

class Player ;
//======================================================================

class PlayerFactory {
    static constexpr auto  lowSerial = serial_t(1) ;
    static constexpr auto  highSerial = serial_t(1000000) ;
    SerialGenerator serialGenerator ;
    std::unordered_map<serial_t, Player> playerCollection ;
public:
    PlayerFactory() ;
    static const std::filesystem::path PLAYERFILE ;
    
    auto exists(serial_t serial) const -> bool ;
    auto create(serial_t serial = INVALIDSERIAL) -> Player* ;
    auto obtain(serial_t serial) -> Player* ;
    
    auto load(std::istream &input) ->void ;
    auto save(std::ostream &output) -> void ;
    auto save(const std::filesystem::path &path) -> bool ;
    auto loadPlayer(const std::filesystem::path &path) -> bool ;
    
    auto size() const -> size_t ;
    
    auto erase(serial_t serial) -> bool ;
};

#endif /* playerfactory_hpp */
