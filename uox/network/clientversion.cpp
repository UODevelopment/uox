//Copyright © 2023 Charles Kerr. All rights reserved.

#include "clientversion.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
ClientVersion::ClientVersion(int major ,int minor ,int revision ,int prototype ):majorVersion(major),minorVersion(minor),revisionVersion(revision),prototypeVersion(prototype){
    
}
//======================================================================
ClientVersion::ClientVersion(const std::string &line):ClientVersion() {
    auto values = util::parse(line,".");
    switch (values.size()) {
        default:
        case 4:
            prototypeVersion = std::stoi(values[3],nullptr,0) ;
            [[fallthrough]];
        case 3:
            revisionVersion = std::stoi(values[2],nullptr,0) ;
            [[fallthrough]];
        case 2:
            minorVersion = std::stoi(values[1],nullptr,0) ;
            [[fallthrough]];
        case 1:
            majorVersion = std::stoi(values[0],nullptr,0) ;
            [[fallthrough]];
        case 0:
            break;
    }
}
//======================================================================
auto ClientVersion::describe() const -> std::string {
    return std::to_string(majorVersion) + "."s + std::to_string(minorVersion) + "."s + std::to_string(revisionVersion) + "."s + std::to_string(prototypeVersion) ;
}
//======================================================================
auto ClientVersion::major() const -> int {
    return majorVersion;
}
//======================================================================
auto ClientVersion::minor() const -> int {
    return minorVersion;
}
//======================================================================
auto ClientVersion::revision() const -> int {
    return revisionVersion;
}
//======================================================================
auto ClientVersion::prototype() const -> int {
    return prototypeVersion;
}
//======================================================================
auto ClientVersion::invalid() const -> bool {
    return majorVersion == 0 && minorVersion == 0 && revisionVersion == 0 && prototypeVersion == 0 ;
}

//======================================================================
auto ClientVersion::operator==(const ClientVersion &version) const -> bool {
    return (version.minorVersion == this->minorVersion) && (version.majorVersion == this->majorVersion) && (version.revisionVersion == this->revisionVersion) && (version.prototypeVersion == this->prototypeVersion);
}
//======================================================================
auto ClientVersion::operator!=(const ClientVersion &version) const -> bool {
    return !operator==(version) ;
}
//======================================================================
auto ClientVersion::operator<(const ClientVersion &version) const -> bool {
    if (this->majorVersion < version.majorVersion) {
        if (this->minorVersion < version.minorVersion) {
            if (this->revisionVersion < version.revisionVersion) {
                if (this->prototypeVersion < version.prototypeVersion) {
                    return true ;
                }
            }
        }
    }
    return false ;
}
//======================================================================
auto ClientVersion::operator<=(const ClientVersion &version) const -> bool {
    return operator<(version) || operator==(version) ;
}
//======================================================================
auto ClientVersion::operator>(const ClientVersion &version) const -> bool {
    return !operator<=(version) ;
}
//======================================================================
auto ClientVersion::operator>=(const ClientVersion &version) const -> bool {
    return !operator<(version) ;
}
//======================================================================
auto ClientVersion::operator=(const std::string &version) -> ClientVersion& {
    prototypeVersion = 0;
    revisionVersion = 0 ;
    minorVersion = 0 ;
    majorVersion = 0 ;
    auto values = util::parse(version,".");
    switch (values.size()) {
        default:
        case 4:
            prototypeVersion = std::stoi(values[3],nullptr,0) ;
            [[fallthrough]];
        case 3:
            revisionVersion = std::stoi(values[2],nullptr,0) ;
            [[fallthrough]];
        case 2:
            minorVersion = std::stoi(values[1],nullptr,0) ;
            [[fallthrough]];
        case 1:
            majorVersion = std::stoi(values[0],nullptr,0) ;
            [[fallthrough]];
        case 0:
            break;
    }
    return *this ;
}
