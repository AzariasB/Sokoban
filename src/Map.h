//
// Created by Raphaël Haltz on 21/03/2018.
//

#ifndef SOKOBAN_MAP_H
#define SOKOBAN_MAP_H

#include <vector>
#include <queue>
#include <string>
#include "State.hpp"

char toChar(int code);

class Map {
public:
    Map();
    Map(int width, int height);

    bool isAccessible(const Point &origin, const Point &dir) const;

    bool isValid(const Point &p) const;

    std::string toString() const;

    int &at(const Point &p);

    const int &at(const Point &p) const;

    std::vector<std::vector<int>> &get(){return map;}

private:
    std::vector<std::vector<int>> map;
};


#endif //SOKOBAN_MAP_H
