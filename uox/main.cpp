#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "utility/netutil.hpp"
#include "network/packet.hpp"
#include "utility/strutil.hpp"
using namespace std::string_literals;

int main(int argc, const char * argv[]) {
    auto errorcode = EXIT_SUCCESS;
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
