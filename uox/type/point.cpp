//Copyright © 2023 Charles Kerr. All rights reserved.

#include "point.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
// Point
//======================================================================

//======================================================================
Point::Point():x(0),y(0){
}
//======================================================================
Point::Point(int x, int y):Point(){
    this->x = x;
    this->y = y ;
}
//======================================================================
Point::Point(const std::string &line):Point() {
    auto [xval,yval] = util::split(line,",") ;
    this->x = std::stoi(xval,nullptr,0) ;
    this->y = std::stoi(yval,nullptr,0);
}
//======================================================================
Point::Point(const Point3 &value):Point() {
    this->x = value.x ;
    this->y = value.y ;
}

//======================================================================
auto Point::describe() const -> std::string {
    return std::to_string(x) + ","s + std::to_string(y) ;
}
//======================================================================
auto Point::operator=(const Point &value) -> Point& {
    this->x = value.x ;
    this->y = value.y ;
    return *this ;
}
//======================================================================
auto Point::operator=(const Point3 &value) -> Point& {
    this->x = value.x ;
    this->y = value.y ;
    return *this ;
}
//======================================================================
auto Point::distance(const Point &value) const -> double {
    return std::sqrt(std::pow(static_cast<double>(std::abs(this->x - value.x)),2.0) + std::pow(static_cast<double>(std::abs(this->y - value.y)),2.0)) ;
}
//======================================================================
auto Point::operator<(const Point &value) const ->bool {
    return this->x < value.x ;
}
//======================================================================
auto Point::operator<(const Point3 &value) const ->bool {
    return this->x < value.x ;
}

//======================================================================
// Point3
//======================================================================
//======================================================================
Point3::Point3():Point(),z(0){
}
//======================================================================
Point3::Point3(int x, int y,int z):Point3(){
    this->x = x ;
    this->y = y ;
    this->z = z ;
}
//======================================================================
Point3::Point3(const std::string &line):Point3(){
    auto values = util::parse(line,",");
    switch (values.size()) {
        default:
        case 3:
            z = std::stoi(values[2],nullptr,0);
            [[fallthrough]];
        case 2:
            y = std::stoi(values[1],nullptr,0);
            [[fallthrough]];
        case 1:
            x = std::stoi(values[0],nullptr,0);
            [[fallthrough]];
        case 0:
            break;
    }
}
//======================================================================
Point3::Point3(const Point &value): Point3() {
    this->x = value.x ;
    this->y = value.y ;
}

//======================================================================
auto Point3::describe() const -> std::string {
    return Point::describe() + ","s + std::to_string(z) ;
}
//======================================================================
auto Point3::operator=(const Point &value) -> Point3& {
    this->x = value.x ;
    this->y = value.y ;
    this->z = 0 ;
    return *this ;
}
//======================================================================
auto Point3::operator=(const Point3 &value) -> Point3& {
    this->x = value.x ;
    this->y = value.y ;
    this->z = value.y ;
    return *this ;
}
//======================================================================
auto Point3::distance(const Point3 &value) const -> double {
    auto dis1 =  std::pow(static_cast<double>(std::abs(this->x - value.x)),2.0) + std::pow(static_cast<double>(std::abs(this->y - value.y)),2.0) ;
    return std::sqrt(dis1 + std::pow(static_cast<double>(std::abs(this->z - value.z)),2.0)) ;
}
//======================================================================
auto Point3::distance(const Point &value) const -> double {
    return std::sqrt(std::pow(static_cast<double>(std::abs(this->x - value.x)),2.0) + std::pow(static_cast<double>(std::abs(this->y - value.y)),2.0)) ;
}
//======================================================================
auto Point3::operator<(const Point &value) const ->bool {
    return this->x < value.x ;
}
//======================================================================
auto Point3::operator<(const Point3 &value) const ->bool {
    return this->x < value.x ;
}
