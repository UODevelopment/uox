//Copyright © 2023 Charles Kerr. All rights reserved.

#include "playerfactory.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "utility/strutil.hpp"
using namespace std::string_literals ;

const std::filesystem::path PlayerFactory::PLAYERFILE = std::filesystem::path("player.uox");

//======================================================================
PlayerFactory::PlayerFactory():serialGenerator(PlayerFactory::lowSerial,PlayerFactory::highSerial){
    
}
//======================================================================
auto PlayerFactory::exists(serial_t serial) const -> bool {
    auto iter = playerCollection.find(serial) ;
    return iter != playerCollection.end() ;
}
//======================================================================
auto PlayerFactory::create(serial_t serial) -> Player* {
    if (serial == INVALIDSERIAL){
        serial = serialGenerator.next();
    }
    else {
        serialGenerator.used(serial) ;
    }
    auto player = Player() ;
    player.serialNumber = serial ;
    playerCollection.insert_or_assign(serial,player) ;
    return this->obtain(serial);
}
//======================================================================
auto PlayerFactory::obtain(serial_t serial) -> Player* {
    auto iter = playerCollection.find(serial) ;
    if (iter == playerCollection.end()){
        throw std::out_of_range("Serial number not in Player collection: "s+util::ntos(serial,16,true,8));
    }
    return &iter->second;
}

//======================================================================
auto PlayerFactory::load(std::istream &input) ->void {
    playerCollection.clear() ;
    auto buffer = std::vector<char>(4096,0) ;
    Player *player = nullptr ;
    while (input.good() && !input.eof()){
        input.getline(buffer.data(), buffer.size()-1);
        if (input.gcount()>0){
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data();
            line = util::trim(util::strip(line,"//"));
            if (!line.empty()){
                if (line[0]=='[' && line[line.size()-1] == ']'){
                    player = nullptr ;
                    auto [ser,key] = util::split(util::contentsOf(line, "[", "]"),":");
                    if (key == "PLAYER"){
                        player = this->create(static_cast<serial_t>(std::stoul(ser,nullptr,0))) ;
                    }
                }
                else if (line[0] == '}'){
                    player = nullptr ;
                }
                else if (line[0] != '{' && player != nullptr){
                    auto [key,value] = util::split(line,"=");
                    if (!player->setKeyValue(key,value)) {
                        std::cerr <<"Unhanded key/value while processing player: "<<util::ntos(player->serialNumber,16,true,8)<<" Key: "<< key<<" Value: "<<value <<"\n";
                    }
                }
            }
        }
    }
    std::cout <<"Players loaded: "<< playerCollection.size() <<"\n" ;
}
//======================================================================
auto PlayerFactory::save(std::ostream &output) -> void {
    for (const auto &[serial,player]:playerCollection){
        if (!player.objectFlag[ObjectFlag::REMOVE]){
            player.save(output) ;
       }
    }
}
//======================================================================
auto PlayerFactory::save(const std::filesystem::path &path) -> bool {
    auto output = std::ofstream(path.string()) ;
    if (!output.is_open()){
        return false ;
    }
    save(output) ;
    return true ;
}

//======================================================================
auto PlayerFactory::loadPlayer(const std::filesystem::path &path) -> bool{
    auto input = std::ifstream(path.string());
    if (!input.is_open()){
        return false ;
    }
    this->load(input) ;
    return true ;
}
//======================================================================
auto PlayerFactory::size() const -> size_t {
    return playerCollection.size();
}
//======================================================================
auto PlayerFactory::erase(serial_t serial) -> bool {
    auto iter = playerCollection.find(serial) ;
    if (iter != playerCollection.end()){
        playerCollection.erase(iter) ;
        return true ;
    }
    return false ;
}
