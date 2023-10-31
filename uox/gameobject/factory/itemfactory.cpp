//Copyright © 2023 Charles Kerr. All rights reserved.

#include "itemfactory.hpp"

#include <algorithm>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
ItemFactory::ItemFactory():serialGenerator(ItemFactory::lowSerial, ItemFactory::highSerial){
}

//======================================================================
auto ItemFactory::exists(serial_t serial) const -> bool {
    return object.find(serial) != object.end() ;
}
//======================================================================
auto ItemFactory::erase(serial_t serial) -> void {
    auto iter = object.find(serial) ;
    if (iter != object.end() ) {
        object.erase(iter) ;
    }
}
//======================================================================
auto ItemFactory::create(serial_t serial ) -> Item* {
    if (serial == INVALIDSERIAL) {
        serial = serialGenerator.next();
    }
    else {
        serialGenerator.used(serial) ;
    }
    auto item = new Item() ;
    item->serialNumber = serial ;
    object.insert_or_assign(serial,std::unique_ptr<Item>(item));

    return item ;
}
//======================================================================
auto ItemFactory::operator[](serial_t serial) const -> const Item* {
    auto iter = object.find(serial) ;
    if (iter != object.end()){
        return iter->second.get() ;
    }
    throw std::out_of_range("Serial not a valid item: "s+util::ntos(serial,16,true,8)) ;
}
//======================================================================
auto ItemFactory::operator[](serial_t serial) -> Item* {
    auto iter = object.find(serial) ;
    if (iter != object.end()){
        return iter->second.get() ;
    }
    throw std::out_of_range("Serial not a valid item: "s+util::ntos(serial,16,true,8)) ;

}

