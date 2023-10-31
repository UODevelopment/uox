//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef userinfo_hpp
#define userinfo_hpp

#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>


//======================================================================
struct UserInfo {
    enum infotype_t {
        BANNED=0,SUSPENDED,SEER=13,COUNSELOR,ADMIN
    };
    std::bitset<16> userInfo ;
    
    template<typename T>
    auto operator=(T value) -> UserInfo& {
        userInfo = std::bitset<16>(value) ;
    }
    
    auto operator[](infotype_t bit) const -> bool ;
    auto setInfo(infotype_t bit, bool state) ->void ;
    auto describe() const -> std::string ;
    UserInfo() = default;
    UserInfo(int value) ;
    UserInfo(const std::string &value) ;
};

#endif /* userinfo_hpp */
