//Copyright © 2023 Charles Kerr. All rights reserved.

#include "serverconfig.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
ServerConfig::ServerConfig(){
    startingLocation = StartCollection("location");
    reset();
}
//======================================================================
ServerConfig::ServerConfig(const std::filesystem::path &path):ServerConfig() {
    this->load(path);
}

//======================================================================
auto ServerConfig::reset() -> void {
    eraValue.reset() ;
    flagValue.reset();
    intValue.reset();
    pathValue.reset();
    realValue.reset();
    startingLocation.reset() ;
    stringValue.reset() ;
    timerDefault.reset() ;
    boolValue.reset() ;
}
//======================================================================
auto ServerConfig::postLoad() ->void {
    constexpr auto numworld = 6 ;
    eraValue.postLoad() ;
    flagValue.postLoad();
    intValue.postLoad();
    pathValue.postLoad(numworld);
    realValue.postLoad();
    startingLocation.postLoad() ;
    stringValue.postLoad() ;
    timerDefault.postLoad() ;
    boolValue.postLoad() ;
    
}

//======================================================================
auto ServerConfig::setKeyValue(const std::string &skey, const std::string &value) ->bool {
    auto key = util::upper(skey) ;
    if (!boolValue.setKeyValue(key,value)){
        if (!eraValue.setKeyValue(key, value)){
            if (!flagValue.setKeyValue(key, value)){
                if (!intValue.setKeyValue(key, value)){
                    if (!pathValue.setKeyValue(key, value)){
                        if (!realValue.setKeyValue(key, value)){
                            if (!startingLocation.setKeyValue(key, value)){
                                if (!stringValue.setKeyValue(key, value)){
                                    if (!timerDefault.setKeyValue(key, value)){
                                        std::clog << "Not handled: "<<key<<" = "<<value <<std::endl;
                                        return false ;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true ;
}

//======================================================================
auto ServerConfig::processStream(std::istream &input) -> void {
    this->reset() ;
    auto buffer = std::vector<char>(4096,0) ;
    while (input.good() && !input.eof()){
        input.getline(buffer.data(),buffer.size()-1);
        if (input.gcount()>0){
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data() ;
            line = util::trim(util::strip(line,"//"));
            if (!line.empty()){
                auto [key,value] = util::split(line,"=");
                setKeyValue(key, value);
            }
        }
    }
    this->postLoad();
}

//======================================================================
auto ServerConfig::load(const std::filesystem::path &path) ->bool {
    auto input = std::ifstream(path.string()) ;
    if (!input.is_open()){
        return false ;
    }
    processStream(input);
    return true ;
}
//======================================================================
auto ServerConfig::processMapEntryInfo(const std::filesystem::path &path) -> std::map<int,MapEntryInfo> {
    auto rvalue = std::map<int,MapEntryInfo>() ;
    auto buffer = std::vector<char>(4096,0) ;
    auto input = std::ifstream(path.string()) ;
    if (!input.is_open()){
        throw std::runtime_error("Unable to load: "s + path.string());
    }
    auto entry = MapEntryInfo();
    auto number = -1 ;
    auto valid = false ;
    while (input.good() && !input.eof()){
        input.getline(buffer.data(),buffer.size()-1);
        if (input.gcount()>0){
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data() ;
            line = util::trim(util::strip(line,"//"));
            if (!line.empty()){
                if (line[0] == '[' && (line[line.size()-1] == ']')) {
                    // Section header
                    auto [first,second] = util::split(util::contentsOf(line, "[", "]"),":") ;
                    if (util::lower(second) == "map"){
                        // We are interested in this
                        try {
                            number = std::stoi(first,nullptr,0);
                            entry = MapEntryInfo();
                        }
                        catch(...) {
                            // This is malformed
                            std::cerr <<"Malformed map entry in: "<<path.string() << std::endl;
                            number = -1 ;
                        }
                        valid = false ;
                    }
                }
                else if (line[0]== '{'){
                    
                    entry = MapEntryInfo();
                    if (number != -1){
                        valid = true ;
                    }
                }
                else if (line[0] == '}'){
                    if (number != -1  && valid){
                        rvalue.insert_or_assign(number,entry) ;
                        entry = MapEntryInfo();
                    }
                    valid = false ;
                    number = -1 ;
                }
                else {
                    auto [key,value] = util::split(line,"=") ;
                    auto lkey = util::lower(key) ;
                    if (key == "terrain") {
                        entry.terrain = std::filesystem::path(value) ;
                    }
                    else if (key == "art"){
                        auto [idx,mul] = util::split(value,",") ;
                        entry.artidx = std::filesystem::path(idx) ;
                        entry.artmul = std::filesystem::path(mul);
                    }
                    else if (key == "size"){
                        auto [width,height] = util::split(value,",") ;
                        entry.size = std::make_pair(std::stoi(width,nullptr,0), std::stoi(height,nullptr,0));
                    }
                    else if (key == "applydiff"){
                        auto [terdiff,artdiff] = util::split(value,",") ;
                        entry.applyDiff = std::make_pair(std::stoi(terdiff,nullptr,0) != 0, std::stoi(artdiff,nullptr,0) != 0);
                    }
                    else if (key == "mapdffl"){
                        entry.terdifl = std::filesystem::path(value) ;
                    }
                    else if (key == "mapdff"){
                        entry.terdif = std::filesystem::path(value) ;
                    }
                    else if (key == "artdiffl"){
                        entry.artdifl = std::filesystem::path(value) ;
                    }
                    else if (key == "artdiffi"){
                        entry.artdifi = std::filesystem::path(value) ;
                    }
                    else if (key == "artdiff"){
                        entry.artdif = std::filesystem::path(value) ;
                    }
                }
            }
        }
    }
    return rvalue ;
}
