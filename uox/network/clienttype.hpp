//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef clienttype_hpp
#define clienttype_hpp

#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>

//======================================================================
class ClientType {
    std::bitset<32> type ;
    
public:
    enum type_t {
        T2A = 0, RENNAISSANCE = 1, THIRDDAWN = 2 ,
        LBR = 4, AOS = 0x08, SE = 0x10, SA = 0x20 ,
        UO3D = 0x40, RESERVED = 0x80 , CLIENT3D = 0x100 ,
        UNDEFINED = 0xFFFF 
    };
    ClientType() = default ;
    ClientType(int value) ;
    auto operator==(type_t type) const ->bool ;
    auto operator!=(type_t type) const ->bool ;
};

#endif /* clienttype_hpp */
