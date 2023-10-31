//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef factory_hpp
#define factory_hpp

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "type/typedef.hpp"
#include "serialgen.hpp"

//======================================================================
class BaseObject ;
class Factory {
    SerialGenerator serialGenerator ;
    std::unordered_map<serial_t, std::unique_ptr<BaseObject>> object ;

};

#endif /* factory_hpp */
