//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef allfactory_hpp
#define allfactory_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "itemfactory.hpp"
#include "multifactory.hpp"
#include "playerfactory.hpp"
#include "spawnerfactory.hpp"
//======================================================================

struct AllFactory {
    ItemFactory itemFactory ;
    MultiFactory multiFactory ;
    PlayerFactory playerFactory ;
    SpawnerFactory spawnerFactory ;
    AllFactory() ;

};


#endif /* allfactory_hpp */
