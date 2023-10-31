//Copyright © 2023 Charles Kerr. All rights reserved.

#include "timerdefault.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
const std::map<std::string, TimerDefault::type_t> TimerDefault::NAMETYPEMAP{
    {"DECAY"s,DECAY}
};
//======================================================================
auto TimerDefault::typeForName(const std::string &name) ->type_t {
    auto iter = NAMETYPEMAP.find(name) ;
    if (iter != NAMETYPEMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("Timer category not in range: "s+name);
}
//======================================================================
TimerDefault::TimerDefault(){
    reset() ;
}
//======================================================================
auto TimerDefault::reset() -> void {
    timerDefault=std::vector<sec_t>(static_cast<int>(COUNT),0);
}
//======================================================================
auto TimerDefault::postLoad() ->void {
}
//======================================================================
auto TimerDefault::operator[](type_t category) const -> const sec_t& {
    return timerDefault.at(static_cast<size_t>(category));
}
//======================================================================
auto TimerDefault::operator[](type_t category)  -> sec_t& {
    return timerDefault.at(static_cast<size_t>(category));
}
//======================================================================
auto TimerDefault::setKeyValue(const std::string &key, const std::string &value) -> bool {
    auto iter = NAMETYPEMAP.find(key) ;
    if (iter != NAMETYPEMAP.end()){
        if (!value.empty()){
            timerDefault.at(static_cast<size_t>(iter->second)) = std::stoi(value,nullptr,0);
        }
        return true ;
    }
    return false ;
}

