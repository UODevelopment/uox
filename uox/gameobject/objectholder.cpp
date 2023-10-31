//Copyright © 2023 Charles Kerr. All rights reserved.

#include "objectholder.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;

//======================================================================
auto ObjectHolder::add(BaseObject * object) -> void {
    container.insert_or_assign(object->serialNumber,object) ;
}
//======================================================================
auto ObjectHolder::find(serial_t serial) -> BaseObject * {
    auto iter = container.find(serial) ;
    if (iter != container.end()){
        return iter->second;
    }
    return nullptr ;
}
//======================================================================
auto ObjectHolder::remove(serial_t serial) -> void {
    auto iter = container.find(serial) ;
    if (iter != container.end()){
        container.erase(iter) ;
    }
}
//======================================================================
auto ObjectHolder::contains(serial_t serial) const -> bool {
    auto iter = container.find(serial) ;
    if (iter != container.end()){
        return true ;
    }
    return false ;
}
//======================================================================
auto ObjectHolder::size() const -> size_t {
    return container.size();
}
//======================================================================
auto ObjectHolder::empty() const -> bool {
    return container.empty();
}
