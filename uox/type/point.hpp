//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef point_hpp
#define point_hpp

#include <cstdint>
#include <iostream>
#include <string>


struct Point3;
//======================================================================
// Point
//======================================================================
//======================================================================
struct Point {
    int x;
    int y ;
    Point();
    Point(int x, int y) ;
    Point(const std::string &line);
    Point(const Point3 &value);
    auto describe() const -> std::string ;
    auto operator=(const Point &value) -> Point& ;
    auto operator=(const Point3 &value) -> Point& ;
    auto distance(const Point &value) const -> double ;
    auto operator<(const Point &value) const ->bool ;
    auto operator<(const Point3 &value) const ->bool ;
};
//======================================================================
// Point3
//======================================================================
//======================================================================
struct Point3 : public Point {
    int z;
    Point3();
    Point3(int x, int y,int z) ;
    Point3(const std::string &line);
    Point3(const Point &value) ;
    auto describe() const -> std::string ;
    auto operator=(const Point &value) -> Point3& ;
    auto operator=(const Point3 &value) -> Point3& ;
    auto distance(const Point3 &value) const -> double ;
    auto distance(const Point &value) const -> double ;
    auto operator<(const Point3 &value) const ->bool ;
    auto operator<(const Point &value) const ->bool ;

};

#endif /* point_hpp */
