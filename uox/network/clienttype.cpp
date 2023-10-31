//Copyright © 2023 Charles Kerr. All rights reserved.

#include "clienttype.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
ClientType:: ClientType(int value) {
    this->type = value ;
}
//======================================================================
auto ClientType::operator==(type_t type) const ->bool {
    return this->type.test(static_cast<int>(type));
}
//======================================================================
auto ClientType::operator!=(type_t type) const ->bool {
    return !operator==(type) ;
}

