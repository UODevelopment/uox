//Copyright © 2023 Charles Kerr. All rights reserved.

#include "createpacket.hpp"

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

#include "network/client.hpp"
#include "packet/packet.hpp"
#include "packet/create/createpacket0x82.hpp"
#include "packet/create/createpacket0x8c.hpp"
#include "packet/create/createpacket0xa8.hpp"
#include "packet/create/createpacket0xa9.hpp"
#include "packet/create/createpacket0xb9.hpp"
#include "packet/create/createpacket0xbd.hpp"
using namespace std::string_literals ;

//======================================================================
//======================================================================
auto undefinedCreation(Client * client) -> Packet {
    
    return Packet() ;
}

std::vector<std::function<Packet(Client*)>> CREATIONMAPPING{
    &undefinedCreation, // 0x00
    &undefinedCreation, // 0x01
    &undefinedCreation, // 0x02
    &undefinedCreation, // 0x03
    &undefinedCreation, // 0x04
    &undefinedCreation, // 0x05
    &undefinedCreation, // 0x06
    &undefinedCreation, // 0x07
    &undefinedCreation, // 0x08
    &undefinedCreation, // 0x09
    &undefinedCreation, // 0x0a
    &undefinedCreation, // 0x0b
    &undefinedCreation, // 0x0c
    &undefinedCreation, // 0x0d
    &undefinedCreation, // 0x0e
    &undefinedCreation, // 0x0f
    &undefinedCreation, // 0x10
    &undefinedCreation, // 0x11
    &undefinedCreation, // 0x12
    &undefinedCreation, // 0x13
    &undefinedCreation, // 0x14
    &undefinedCreation, // 0x15
    &undefinedCreation, // 0x16
    &undefinedCreation, // 0x17
    &undefinedCreation, // 0x18
    &undefinedCreation, // 0x19
    &undefinedCreation, // 0x1a
    &undefinedCreation, // 0x1b
    &undefinedCreation, // 0x1c
    &undefinedCreation, // 0x1d
    &undefinedCreation, // 0x1e
    &undefinedCreation, // 0x1f
    &undefinedCreation, // 0x20
    &undefinedCreation, // 0x21
    &undefinedCreation, // 0x22
    &undefinedCreation, // 0x23
    &undefinedCreation, // 0x24
    &undefinedCreation, // 0x25
    &undefinedCreation, // 0x26
    &undefinedCreation, // 0x27
    &undefinedCreation, // 0x28
    &undefinedCreation, // 0x29
    &undefinedCreation, // 0x2a
    &undefinedCreation, // 0x2b
    &undefinedCreation, // 0x2c
    &undefinedCreation, // 0x2d
    &undefinedCreation, // 0x2e
    &undefinedCreation, // 0x2f
    &undefinedCreation, // 0x30
    &undefinedCreation, // 0x31
    &undefinedCreation, // 0x32
    &undefinedCreation, // 0x33
    &undefinedCreation, // 0x34
    &undefinedCreation, // 0x35
    &undefinedCreation, // 0x36
    &undefinedCreation, // 0x37
    &undefinedCreation, // 0x38
    &undefinedCreation, // 0x39
    &undefinedCreation, // 0x3a
    &undefinedCreation, // 0x3b
    &undefinedCreation, // 0x3c
    &undefinedCreation, // 0x3d
    &undefinedCreation, // 0x3e
    &undefinedCreation, // 0x3f
    &undefinedCreation, // 0x40
    &undefinedCreation, // 0x41
    &undefinedCreation, // 0x42
    &undefinedCreation, // 0x43
    &undefinedCreation, // 0x44
    &undefinedCreation, // 0x45
    &undefinedCreation, // 0x46
    &undefinedCreation, // 0x47
    &undefinedCreation, // 0x48
    &undefinedCreation, // 0x49
    &undefinedCreation, // 0x4a
    &undefinedCreation, // 0x4b
    &undefinedCreation, // 0x4c
    &undefinedCreation, // 0x4d
    &undefinedCreation, // 0x4e
    &undefinedCreation, // 0x4f
    &undefinedCreation, // 0x50
    &undefinedCreation, // 0x51
    &undefinedCreation, // 0x52
    &undefinedCreation, // 0x53
    &undefinedCreation, // 0x54
    &undefinedCreation, // 0x55
    &undefinedCreation, // 0x56
    &undefinedCreation, // 0x57
    &undefinedCreation, // 0x58
    &undefinedCreation, // 0x59
    &undefinedCreation, // 0x5a
    &undefinedCreation, // 0x5b
    &undefinedCreation, // 0x5c
    &undefinedCreation, // 0x5d
    &undefinedCreation, // 0x5e
    &undefinedCreation, // 0x5f
    &undefinedCreation, // 0x60
    &undefinedCreation, // 0x61
    &undefinedCreation, // 0x62
    &undefinedCreation, // 0x63
    &undefinedCreation, // 0x64
    &undefinedCreation, // 0x65
    &undefinedCreation, // 0x66
    &undefinedCreation, // 0x67
    &undefinedCreation, // 0x68
    &undefinedCreation, // 0x69
    &undefinedCreation, // 0x6a
    &undefinedCreation, // 0x6b
    &undefinedCreation, // 0x6c
    &undefinedCreation, // 0x6d
    &undefinedCreation, // 0x6e
    &undefinedCreation, // 0x6f
    &undefinedCreation, // 0x70
    &undefinedCreation, // 0x71
    &undefinedCreation, // 0x72
    &undefinedCreation, // 0x73
    &undefinedCreation, // 0x74
    &undefinedCreation, // 0x75
    &undefinedCreation, // 0x76
    &undefinedCreation, // 0x77
    &undefinedCreation, // 0x78
    &undefinedCreation, // 0x79
    &undefinedCreation, // 0x7a
    &undefinedCreation, // 0x7b
    &undefinedCreation, // 0x7c
    &undefinedCreation, // 0x7d
    &undefinedCreation, // 0x7e
    &undefinedCreation, // 0x7f
    &undefinedCreation, // 0x80
    &undefinedCreation, // 0x81
    &createPacket0x82, // 0x82
    &undefinedCreation, // 0x83
    &undefinedCreation, // 0x84
    &undefinedCreation, // 0x85
    &undefinedCreation, // 0x86
    &undefinedCreation, // 0x87
    &undefinedCreation, // 0x88
    &undefinedCreation, // 0x89
    &undefinedCreation, // 0x8a
    &undefinedCreation, // 0x8b
    &createPacket0x8C, // 0x8c
    &undefinedCreation, // 0x8d
    &undefinedCreation, // 0x8e
    &undefinedCreation, // 0x8f
    &undefinedCreation, // 0x90
    &undefinedCreation, // 0x91
    &undefinedCreation, // 0x92
    &undefinedCreation, // 0x93
    &undefinedCreation, // 0x94
    &undefinedCreation, // 0x95
    &undefinedCreation, // 0x96
    &undefinedCreation, // 0x97
    &undefinedCreation, // 0x98
    &undefinedCreation, // 0x99
    &undefinedCreation, // 0x9a
    &undefinedCreation, // 0x9b
    &undefinedCreation, // 0x9c
    &undefinedCreation, // 0x9d
    &undefinedCreation, // 0x9e
    &undefinedCreation, // 0x9f
    &undefinedCreation, // 0xa0
    &undefinedCreation, // 0xa1
    &undefinedCreation, // 0xa2
    &undefinedCreation, // 0xa3
    &undefinedCreation, // 0xa4
    &undefinedCreation, // 0xa5
    &undefinedCreation, // 0xa6
    &undefinedCreation, // 0xa7
    &createPacket0xA8, // 0xa8
    &createPacket0xA9, // 0xa9
    &undefinedCreation, // 0xaa
    &undefinedCreation, // 0xab
    &undefinedCreation, // 0xac
    &undefinedCreation, // 0xad
    &undefinedCreation, // 0xae
    &undefinedCreation, // 0xaf
    &undefinedCreation, // 0xb0
    &undefinedCreation, // 0xb1
    &undefinedCreation, // 0xb2
    &undefinedCreation, // 0xb3
    &undefinedCreation, // 0xb4
    &undefinedCreation, // 0xb5
    &undefinedCreation, // 0xb6
    &undefinedCreation, // 0xb7
    &undefinedCreation, // 0xb8
    &createPacket0xB9, // 0xb9
    &undefinedCreation, // 0xba
    &undefinedCreation, // 0xbb
    &undefinedCreation, // 0xbc
    &createPacket0xBD, // 0xbd
    &undefinedCreation, // 0xbe
    &undefinedCreation, // 0xbf
    &undefinedCreation, // 0xc0
    &undefinedCreation, // 0xc1
    &undefinedCreation, // 0xc2
    &undefinedCreation, // 0xc3
    &undefinedCreation, // 0xc4
    &undefinedCreation, // 0xc5
    &undefinedCreation, // 0xc6
    &undefinedCreation, // 0xc7
    &undefinedCreation, // 0xc8
    &undefinedCreation, // 0xc9
    &undefinedCreation, // 0xca
    &undefinedCreation, // 0xcb
    &undefinedCreation, // 0xcc
    &undefinedCreation, // 0xcd
    &undefinedCreation, // 0xce
    &undefinedCreation, // 0xcf
    &undefinedCreation, // 0xd0
    &undefinedCreation, // 0xd1
    &undefinedCreation, // 0xd2
    &undefinedCreation, // 0xd3
    &undefinedCreation, // 0xd4
    &undefinedCreation, // 0xd5
    &undefinedCreation, // 0xd6
    &undefinedCreation, // 0xd7
    &undefinedCreation, // 0xd8
    &undefinedCreation, // 0xd9
    &undefinedCreation, // 0xda
    &undefinedCreation, // 0xdb
    &undefinedCreation, // 0xdc
    &undefinedCreation, // 0xdd
    &undefinedCreation, // 0xde
    &undefinedCreation, // 0xdf
    &undefinedCreation, // 0xe0
    &undefinedCreation, // 0xe1
    &undefinedCreation, // 0xe2
    &undefinedCreation, // 0xe3
    &undefinedCreation, // 0xe4
    &undefinedCreation, // 0xe5
    &undefinedCreation, // 0xe6
    &undefinedCreation, // 0xe7
    &undefinedCreation, // 0xe8
    &undefinedCreation, // 0xe9
    &undefinedCreation, // 0xea
    &undefinedCreation, // 0xeb
    &undefinedCreation, // 0xec
    &undefinedCreation, // 0xed
    &undefinedCreation, // 0xee
    &undefinedCreation, // 0xef
    &undefinedCreation, // 0xf0
    &undefinedCreation, // 0xf1
    &undefinedCreation, // 0xf2
    &undefinedCreation, // 0xf3
    &undefinedCreation, // 0xf4
    &undefinedCreation, // 0xf5
    &undefinedCreation, // 0xf6
    &undefinedCreation, // 0xf7
    &undefinedCreation, // 0xf8
    &undefinedCreation, // 0xf9
    &undefinedCreation, // 0xfa
    &undefinedCreation, // 0xfb
    &undefinedCreation, // 0xfc
    &undefinedCreation, // 0xfd
    &undefinedCreation, // 0xfe
    &undefinedCreation // 0xff
};
//=============================================================================
auto createPacket(Client *client, packetid_t packetid) -> Packet {
        return CREATIONMAPPING.at(packetid)(client) ;
}

