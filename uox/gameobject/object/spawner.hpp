//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef spawner_hpp
#define spawner_hpp

#include <cstdint>
#include <iostream>
#include <string>

#include "baseobject.hpp"
class SpawnerFactory ;
//======================================================================
class Spawner : public BaseObject {
    friend class SpawnerFactory ;
protected:
    auto saveData(std::ostream &output) const -> void final ;
public:
    auto setKeyValue(const std::string &key, const std::string &value) ->bool final ;

    Spawner();
    Spawner(serial_t serial);
    ~Spawner() = default ;
};

#endif /* spawner_hpp */
