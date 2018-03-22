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

    void reset();

    bool isUseless() const;

    const int &at(const Point &p) const;

    std::vector<std::vector<int>> &get(){return map;}

private:
    static const Point left;
    static const Point top;
    static const Point right;
    static const Point down;
    static const Point topLeft;
    static const Point topRight;
    static const Point downLeft;
    static const Point downRight;

    bool isStuck(const Point &p) const;

    bool hasWall(const Point &p) const;

    bool hasTarget(const Point &p) const;

    bool hasBox(const Point &p) const;

    bool hasBlocking(const Point &p) const;

    std::vector<std::vector<int>> map;
};


#endif //SOKOBAN_MAP_H
