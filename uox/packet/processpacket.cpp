//Copyright © 2023 Charles Kerr. All rights reserved.

#include "processpacket.hpp"

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>

#include "network/client.hpp"
#include "utility/strutil.hpp"
#include "packet/process/process0x00.hpp"
#include "packet/process/process0x80.hpp"
#include "packet/process/process0xa0.hpp"
#include "packet/process/process0x91.hpp"
#include "packet/process/process0x83.hpp"
#include "packet/process/process0x5d.hpp"
#include "packet/process/process0xf8.hpp"
using namespace std::string_literals ;

//======================================================================
auto undefinedProcessing(Client *, std::vector<std::uint8_t> &&data) -> void {
    std::cerr <<"Undefined processing for packet: "<<util::ntos(data.at(0),16,true,2)<<std::endl;
}

std::vector<std::function<void(Client*, std::vector<std::uint8_t>&&)>> PROCESSMAPPING{
    &processPacket0x00, // 0x00
    &undefinedProcessing, // 0x01
    &undefinedProcessing, // 0x02
    &undefinedProcessing, // 0x03
    &undefinedProcessing, // 0x04
    &undefinedProcessing, // 0x05
    &undefinedProcessing, // 0x06
    &undefinedProcessing, // 0x07
    &undefinedProcessing, // 0x08
    &undefinedProcessing, // 0x09
    &undefinedProcessing, // 0x0a
    &undefinedProcessing, // 0x0b
    &undefinedProcessing, // 0x0c
    &undefinedProcessing, // 0x0d
    &undefinedProcessing, // 0x0e
    &undefinedProcessing, // 0x0f
    &undefinedProcessing, // 0x10
    &undefinedProcessing, // 0x11
    &undefinedProcessing, // 0x12
    &undefinedProcessing, // 0x13
    &undefinedProcessing, // 0x14
    &undefinedProcessing, // 0x15
    &undefinedProcessing, // 0x16
    &undefinedProcessing, // 0x17
    &undefinedProcessing, // 0x18
    &undefinedProcessing, // 0x19
    &undefinedProcessing, // 0x1a
    &undefinedProcessing, // 0x1b
    &undefinedProcessing, // 0x1c
    &undefinedProcessing, // 0x1d
    &undefinedProcessing, // 0x1e
    &undefinedProcessing, // 0x1f
    &undefinedProcessing, // 0x20
    &undefinedProcessing, // 0x21
    &undefinedProcessing, // 0x22
    &undefinedProcessing, // 0x23
    &undefinedProcessing, // 0x24
    &undefinedProcessing, // 0x25
    &undefinedProcessing, // 0x26
    &undefinedProcessing, // 0x27
    &undefinedProcessing, // 0x28
    &undefinedProcessing, // 0x29
    &undefinedProcessing, // 0x2a
    &undefinedProcessing, // 0x2b
    &undefinedProcessing, // 0x2c
    &undefinedProcessing, // 0x2d
    &undefinedProcessing, // 0x2e
    &undefinedProcessing, // 0x2f
    &undefinedProcessing, // 0x30
    &undefinedProcessing, // 0x31
    &undefinedProcessing, // 0x32
    &undefinedProcessing, // 0x33
    &undefinedProcessing, // 0x34
    &undefinedProcessing, // 0x35
    &undefinedProcessing, // 0x36
    &undefinedProcessing, // 0x37
    &undefinedProcessing, // 0x38
    &undefinedProcessing, // 0x39
    &undefinedProcessing, // 0x3a
    &undefinedProcessing, // 0x3b
    &undefinedProcessing, // 0x3c
    &undefinedProcessing, // 0x3d
    &undefinedProcessing, // 0x3e
    &undefinedProcessing, // 0x3f
    &undefinedProcessing, // 0x40
    &undefinedProcessing, // 0x41
    &undefinedProcessing, // 0x42
    &undefinedProcessing, // 0x43
    &undefinedProcessing, // 0x44
    &undefinedProcessing, // 0x45
    &undefinedProcessing, // 0x46
    &undefinedProcessing, // 0x47
    &undefinedProcessing, // 0x48
    &undefinedProcessing, // 0x49
    &undefinedProcessing, // 0x4a
    &undefinedProcessing, // 0x4b
    &undefinedProcessing, // 0x4c
    &undefinedProcessing, // 0x4d
    &undefinedProcessing, // 0x4e
    &undefinedProcessing, // 0x4f
    &undefinedProcessing, // 0x50
    &undefinedProcessing, // 0x51
    &undefinedProcessing, // 0x52
    &undefinedProcessing, // 0x53
    &undefinedProcessing, // 0x54
    &undefinedProcessing, // 0x55
    &undefinedProcessing, // 0x56
    &undefinedProcessing, // 0x57
    &undefinedProcessing, // 0x58
    &undefinedProcessing, // 0x59
    &undefinedProcessing, // 0x5a
    &undefinedProcessing, // 0x5b
    &undefinedProcessing, // 0x5c
    &processPacket0x5D, // 0x5d
    &undefinedProcessing, // 0x5e
    &undefinedProcessing, // 0x5f
    &undefinedProcessing, // 0x60
    &undefinedProcessing, // 0x61
    &undefinedProcessing, // 0x62
    &undefinedProcessing, // 0x63
    &undefinedProcessing, // 0x64
    &undefinedProcessing, // 0x65
    &undefinedProcessing, // 0x66
    &undefinedProcessing, // 0x67
    &undefinedProcessing, // 0x68
    &undefinedProcessing, // 0x69
    &undefinedProcessing, // 0x6a
    &undefinedProcessing, // 0x6b
    &undefinedProcessing, // 0x6c
    &undefinedProcessing, // 0x6d
    &undefinedProcessing, // 0x6e
    &undefinedProcessing, // 0x6f
    &undefinedProcessing, // 0x70
    &undefinedProcessing, // 0x71
    &undefinedProcessing, // 0x72
    &undefinedProcessing, // 0x73
    &undefinedProcessing, // 0x74
    &undefinedProcessing, // 0x75
    &undefinedProcessing, // 0x76
    &undefinedProcessing, // 0x77
    &undefinedProcessing, // 0x78
    &undefinedProcessing, // 0x79
    &undefinedProcessing, // 0x7a
    &undefinedProcessing, // 0x7b
    &undefinedProcessing, // 0x7c
    &undefinedProcessing, // 0x7d
    &undefinedProcessing, // 0x7e
    &undefinedProcessing, // 0x7f
    &processPacket0x80, // 0x80
    &undefinedProcessing, // 0x81
    &undefinedProcessing, // 0x82
    &processPacket0x80, // 0x83
    &undefinedProcessing, // 0x84
    &undefinedProcessing, // 0x85
    &undefinedProcessing, // 0x86
    &undefinedProcessing, // 0x87
    &undefinedProcessing, // 0x88
    &undefinedProcessing, // 0x89
    &undefinedProcessing, // 0x8a
    &undefinedProcessing, // 0x8b
    &undefinedProcessing, // 0x8c
    &undefinedProcessing, // 0x8d
    &undefinedProcessing, // 0x8e
    &undefinedProcessing, // 0x8f
    &undefinedProcessing, // 0x90
    &processPacket0x91, // 0x91
    &undefinedProcessing, // 0x92
    &undefinedProcessing, // 0x93
    &undefinedProcessing, // 0x94
    &undefinedProcessing, // 0x95
    &undefinedProcessing, // 0x96
    &undefinedProcessing, // 0x97
    &undefinedProcessing, // 0x98
    &undefinedProcessing, // 0x99
    &undefinedProcessing, // 0x9a
    &undefinedProcessing, // 0x9b
    &undefinedProcessing, // 0x9c
    &undefinedProcessing, // 0x9d
    &undefinedProcessing, // 0x9e
    &undefinedProcessing, // 0x9f
    &processPacket0xA0, // 0xa0
    &undefinedProcessing, // 0xa1
    &undefinedProcessing, // 0xa2
    &undefinedProcessing, // 0xa3
    &undefinedProcessing, // 0xa4
    &undefinedProcessing, // 0xa5
    &undefinedProcessing, // 0xa6
    &undefinedProcessing, // 0xa7
    &undefinedProcessing, // 0xa8
    &undefinedProcessing, // 0xa9
    &undefinedProcessing, // 0xaa
    &undefinedProcessing, // 0xab
    &undefinedProcessing, // 0xac
    &undefinedProcessing, // 0xad
    &undefinedProcessing, // 0xae
    &undefinedProcessing, // 0xaf
    &undefinedProcessing, // 0xb0
    &undefinedProcessing, // 0xb1
    &undefinedProcessing, // 0xb2
    &undefinedProcessing, // 0xb3
    &undefinedProcessing, // 0xb4
    &undefinedProcessing, // 0xb5
    &undefinedProcessing, // 0xb6
    &undefinedProcessing, // 0xb7
    &undefinedProcessing, // 0xb8
    &undefinedProcessing, // 0xb9
    &undefinedProcessing, // 0xba
    &undefinedProcessing, // 0xbb
    &undefinedProcessing, // 0xbc
    &undefinedProcessing, // 0xbd
    &undefinedProcessing, // 0xbe
    &undefinedProcessing, // 0xbf
    &undefinedProcessing, // 0xc0
    &undefinedProcessing, // 0xc1
    &undefinedProcessing, // 0xc2
    &undefinedProcessing, // 0xc3
    &undefinedProcessing, // 0xc4
    &undefinedProcessing, // 0xc5
    &undefinedProcessing, // 0xc6
    &undefinedProcessing, // 0xc7
    &undefinedProcessing, // 0xc8
    &undefinedProcessing, // 0xc9
    &undefinedProcessing, // 0xca
    &undefinedProcessing, // 0xcb
    &undefinedProcessing, // 0xcc
    &undefinedProcessing, // 0xcd
    &undefinedProcessing, // 0xce
    &undefinedProcessing, // 0xcf
    &undefinedProcessing, // 0xd0
    &undefinedProcessing, // 0xd1
    &undefinedProcessing, // 0xd2
    &undefinedProcessing, // 0xd3
    &undefinedProcessing, // 0xd4
    &undefinedProcessing, // 0xd5
    &undefinedProcessing, // 0xd6
    &undefinedProcessing, // 0xd7
    &undefinedProcessing, // 0xd8
    &undefinedProcessing, // 0xd9
    &undefinedProcessing, // 0xda
    &undefinedProcessing, // 0xdb
    &undefinedProcessing, // 0xdc
    &undefinedProcessing, // 0xdd
    &undefinedProcessing, // 0xde
    &undefinedProcessing, // 0xdf
    &undefinedProcessing, // 0xe0
    &undefinedProcessing, // 0xe1
    &undefinedProcessing, // 0xe2
    &undefinedProcessing, // 0xe3
    &undefinedProcessing, // 0xe4
    &undefinedProcessing, // 0xe5
    &undefinedProcessing, // 0xe6
    &undefinedProcessing, // 0xe7
    &undefinedProcessing, // 0xe8
    &undefinedProcessing, // 0xe9
    &undefinedProcessing, // 0xea
    &undefinedProcessing, // 0xeb
    &undefinedProcessing, // 0xec
    &undefinedProcessing, // 0xed
    &undefinedProcessing, // 0xee
    &undefinedProcessing, // 0xef
    &undefinedProcessing, // 0xf0
    &undefinedProcessing, // 0xf1
    &undefinedProcessing, // 0xf2
    &undefinedProcessing, // 0xf3
    &undefinedProcessing, // 0xf4
    &undefinedProcessing, // 0xf5
    &undefinedProcessing, // 0xf6
    &undefinedProcessing, // 0xf7
    &processPacket0xF8, // 0xf8
    &undefinedProcessing, // 0xf9
    &undefinedProcessing, // 0xfa
    &undefinedProcessing, // 0xfb
    &undefinedProcessing, // 0xfc
    &undefinedProcessing, // 0xfd
    &undefinedProcessing, // 0xfe
    &undefinedProcessing // 0xff
};
//=============================================================================
auto processPacket(Client *client, std::vector<std::uint8_t> &&data) -> void {
    if (!data.empty()){
        PROCESSMAPPING.at(data.at(0))(client,std::move(data)) ;
    }
}
