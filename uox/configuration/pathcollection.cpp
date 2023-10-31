//Copyright © 2023 Charles Kerr. All rights reserved.

#include "pathcollection.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std::string_literals ;
//======================================================================
const std::map<std::string, PathCollection::type_t> PathCollection::NAMETYPEMAP{
    {"SERVERPATH"s,SERVERHOME},{"UODATA"s,UODATA},{"ACCOUNTPATH"s,ACCOUNT},
    {"WORLDPATH"s,WORLD},{"LANGUAGEPATH"s,LANGUAGE},{"LOGPATH"s,LOG},
    {"DEFINITIONPATH"s,DEFINITION},{"CONFIGURATION"s,CONFIGURATION}
};
//======================================================================
auto PathCollection::typeForName(const std::string &name) -> type_t {
    auto iter = NAMETYPEMAP.find(name) ;
    if (iter != NAMETYPEMAP.end()){
        return iter->second ;
    }
    throw std::out_of_range("Path name out of range: "s+name);
}
//======================================================================
PathCollection::PathCollection(){
    reset() ;
}
//======================================================================
auto PathCollection::reset() ->void {
    pathValue = std::vector<std::filesystem::path>(COUNT);
}
//======================================================================
// This assumes that the if a directory is relative, it is relative to "SERVERHOME"
// So if relative, it will prepend SERVERHOME to it
auto PathCollection::postLoad(int numworld) ->void {
    // We need to ensure the server data directories are good
    if (pathValue.at(static_cast<size_t>(SERVERHOME)).empty()){
        pathValue.at(static_cast<size_t>(SERVERHOME)) = std::filesystem::current_path();
    }

    if (pathValue.at(static_cast<size_t>(ACCOUNT)).empty()){
        pathValue.at(static_cast<size_t>(ACCOUNT)) = std::filesystem::path("account") ;
    }
    if (pathValue.at(static_cast<size_t>(ACCOUNT)).is_relative()) {
        pathValue.at(static_cast<size_t>(ACCOUNT)) = pathValue.at(static_cast<size_t>(SERVERHOME))/ pathValue.at(static_cast<size_t>(ACCOUNT)) ;
    }
    if (pathValue.at(static_cast<size_t>(WORLD)).empty()){
        pathValue.at(static_cast<size_t>(WORLD)) = std::filesystem::path("world") ;
    }
    if (pathValue.at(static_cast<size_t>(WORLD)).is_relative()) {
        pathValue.at(static_cast<size_t>(WORLD)) = pathValue.at(static_cast<size_t>(SERVERHOME))/ pathValue.at(static_cast<size_t>(WORLD)) ;
    }
    if (pathValue.at(static_cast<size_t>(LANGUAGE)).empty()){
        pathValue.at(static_cast<size_t>(LANGUAGE)) = std::filesystem::path("language") ;
    }
    if (pathValue.at(static_cast<size_t>(LANGUAGE)).is_relative()) {
        pathValue.at(static_cast<size_t>(LANGUAGE)) = pathValue.at(static_cast<size_t>(SERVERHOME))/ pathValue.at(static_cast<size_t>(LANGUAGE)) ;
    }
    if (pathValue.at(static_cast<size_t>(LOG)).empty()){
        pathValue.at(static_cast<size_t>(LOG)) = std::filesystem::path("log") ;
    }
    if (pathValue.at(static_cast<size_t>(LOG)).is_relative()) {
        pathValue.at(static_cast<size_t>(LOG)) = pathValue.at(static_cast<size_t>(SERVERHOME))/ pathValue.at(static_cast<size_t>(LOG)) ;
    }
    if (pathValue.at(static_cast<size_t>(DEFINITION)).empty()){
        pathValue.at(static_cast<size_t>(DEFINITION)) = std::filesystem::path("definition") ;
    }
    if (pathValue.at(static_cast<size_t>(DEFINITION)).is_relative()) {
        pathValue.at(static_cast<size_t>(DEFINITION)) = pathValue.at(static_cast<size_t>(SERVERHOME))/ pathValue.at(static_cast<size_t>(DEFINITION)) ;
    }
    if (pathValue.at(static_cast<size_t>(CONFIGURATION)).empty()){
        pathValue.at(static_cast<size_t>(CONFIGURATION)) = std::filesystem::path("configuration") ;
    }
    if (pathValue.at(static_cast<size_t>(CONFIGURATION)).is_relative()) {
        pathValue.at(static_cast<size_t>(CONFIGURATION)) = pathValue.at(static_cast<size_t>(SERVERHOME))/ pathValue.at(static_cast<size_t>(CONFIGURATION)) ;
    }

    // Now see if they exist
    if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(ACCOUNT)))){
        std::filesystem::create_directories(pathValue.at(static_cast<size_t>(ACCOUNT)));
    }
    if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(WORLD)))){
        std::filesystem::create_directories(pathValue.at(static_cast<size_t>(WORLD)));
    }
    // Now we get to check for each world
    for (auto i = 0 ; i < numworld; i++){
        if (!std::filesystem::exists( pathValue.at(static_cast<size_t>(WORLD))/std::filesystem::path("world"s+std::to_string(i)) )){
            std::filesystem::create_directories(pathValue.at(static_cast<size_t>(WORLD))/std::filesystem::path("world"s+std::to_string(i)));
        }
    }
    if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(LANGUAGE)))){
        std::filesystem::create_directories(pathValue.at(static_cast<size_t>(LANGUAGE)));
    }
    if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(LOG)))){
        std::filesystem::create_directories(pathValue.at(static_cast<size_t>(LOG)));
    }
    if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(DEFINITION)))){
        std::filesystem::create_directories(pathValue.at(static_cast<size_t>(DEFINITION)));
    }
    if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(CONFIGURATION)))){
        std::filesystem::create_directories(pathValue.at(static_cast<size_t>(CONFIGURATION)));
    }

    // Now check uo directory
    
    if (pathValue.at(static_cast<size_t>(UODATA)).empty()){
#if defined(_WIN32)
        pathValue.at(static_cast<size_t>(UODATA)) = std::filesystem::path("C:\\Program Files (x86)\\Electronic Arts\\Ultima Online Classic\\");
        auto potential = std::getenv("UODATA") ;
        if (potential != nullptr){
            pathValue.at(static_cast<size_t>(UODATA)) = std::filesystem::path(potential) ;
        }
#else
        pathValue.at(static_cast<size_t>(UODATA)) = std::filesystem::path("uodata/");
        auto potential = std::getenv("UODATA") ;
        if (potential != nullptr){
            pathValue.at(static_cast<size_t>(UODATA)) = std::filesystem::path(potential) ;
        }
        else {
            potential = std::getenv("HOME") ;
            if (potential != nullptr){
                pathValue.at(static_cast<size_t>(UODATA)) = std::filesystem::path(potential) / std::filesystem::path("uodata/") ;
            }
        }
#endif
    }
    // Now, check if the files are present we need
    if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(UODATA))/std::filesystem::path("tiledata.mul"))){
        throw std::runtime_error("Can not find tiledata.mul at: "s + pathValue.at(static_cast<size_t>(UODATA)).string());
    }
    if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(UODATA))/std::filesystem::path("MultiCollection.uop"))){
        if (!std::filesystem::exists(pathValue.at(static_cast<size_t>(UODATA))/std::filesystem::path("multi.idx")) || !std::filesystem::exists(pathValue.at(static_cast<size_t>(UODATA))/std::filesystem::path("multi.mul"))) {       // see if multi.idx/mul is present
            throw std::runtime_error("Can not find MultiCollection.uop or multi.idx/mul at: "s + pathValue.at(static_cast<size_t>(UODATA)).string());
        }
    }

}
//======================================================================
auto PathCollection::operator[](type_t type) const -> const std::filesystem::path &{
    return pathValue.at(static_cast<size_t>(type));
}
//======================================================================
auto PathCollection::operator[](type_t type)  ->  std::filesystem::path &{
    return pathValue.at(static_cast<size_t>(type));
}
//======================================================================
auto PathCollection::setKeyValue(const std::string &key,const std::string &value) ->bool {
    auto iter = NAMETYPEMAP.find(key) ;
    if (iter == NAMETYPEMAP.end()){
        return false;
    }
    if (!value.empty()){
        pathValue.at(static_cast<size_t>(iter->second)) = std::filesystem::path(value);
    }
    return true ;
}

