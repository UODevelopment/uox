#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "utility/netutil.hpp"
#include "network/packet.hpp"
#include "network/packetinfo.hpp"
#include "utility/strutil.hpp"
using namespace std::string_literals;

int main(int argc, const char * argv[]) {
    auto errorcode = EXIT_SUCCESS;
    auto info = PacketInfo() ;
    info.update(ClientVersion(7,0,98,1));
    for (auto i = 0 ; i < 0xFF; i++){
        auto size = info.sizeFor(i) ;
        if (size >= 0 && size < 3 ){
            std::cout << info.nameFor(i) << " Packet#: " << util::ntos(i,16,true,2) << " Size: "<< size << std::endl;
        }
    }
    try {
        util::net::startup();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        errorcode = EXIT_FAILURE;
    }
    util::net::shutdown();
     return errorcode;
}
