//Copyright © 2023 Charles Kerr. All rights reserved.

#include "startlocation.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
StartLocation::StartLocation():cli(0){
}
//======================================================================
StartLocation::StartLocation(const std::string &line):StartLocation() {
    auto values = util::parse(line, ";") ;
    if (values.size()>0){
        auto [town,description] = util::split(values[0],",");
        this->town = town;
        this->description = description;
    }
    if (values.size()>1){
        location = Location(values[1]);
    }
    if (values.size()>=2){
        this->cli = std::stoi(values[2],nullptr,0);
    }

 }

