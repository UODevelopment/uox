//Copyright © 2023 Charles Kerr. All rights reserved.

#include "objectflag.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
ObjectFlag::ObjectFlag(int flagcount) {
    flag = std::vector<bool>(flagcount,false);
}
//======================================================================
auto ObjectFlag::set(flag_t index,bool state) -> void {
    flag.at(static_cast<int>(index)) = state ;
}
//======================================================================
auto ObjectFlag::operator[](flag_t index) const -> bool {
    return  flag.at(static_cast<int>(index)) ;
}
