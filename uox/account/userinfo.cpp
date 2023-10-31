//Copyright © 2023 Charles Kerr. All rights reserved.

#include "userinfo.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
auto UserInfo::operator[](infotype_t bit) const -> bool {
    return userInfo.test(static_cast<size_t>(bit));
}
//======================================================================
auto UserInfo::setInfo(infotype_t bit, bool state) ->void {
    userInfo.set(static_cast<size_t>(bit),state) ;
}
//======================================================================
auto UserInfo::describe() const -> std::string {
    return util::ntos(userInfo.to_ulong(),16,true,4) ;
}
//======================================================================
UserInfo::UserInfo(int value): userInfo(value) {
}
//======================================================================
UserInfo::UserInfo(const std::string &value){
    userInfo = std::bitset<16>(std::stoul(value,nullptr,0));
}

