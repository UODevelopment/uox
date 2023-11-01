//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef clientversion_hpp
#define clientversion_hpp

#include <cstdint>
#include <iostream>
#include <string>

//======================================================================
class ClientVersion {
    int majorVersion ;
    int minorVersion ;
    int revisionVersion ;
    int prototypeVersion ;
public:
    ClientVersion(int major=0,int minor=0,int revision=0,int prototype=0);
    ClientVersion(const std::string &line) ;

    auto describe() const -> std::string ;
    auto major() const -> int ;
    auto minor() const -> int ;
    auto revision() const -> int ;
    auto prototype() const -> int ;
    auto invalid() const -> bool ;
    auto operator==(const ClientVersion &version) const -> bool ;
    auto operator!=(const ClientVersion &version) const -> bool ;
    auto operator<(const ClientVersion &version) const -> bool ;
    auto operator<=(const ClientVersion &version) const -> bool ;
    auto operator>(const ClientVersion &version) const -> bool ;
    auto operator>=(const ClientVersion &version) const -> bool ;
    auto operator=(const std::string &version) -> ClientVersion& ;

};

#endif /* clientversion_hpp */
