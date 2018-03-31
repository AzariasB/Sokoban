/*
 * The MIT License
 *
 * Copyright 2017 azarias.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * File:   State.hpp
 * Author: azarias
 *
 * Created on 21/3/2018
 */
#ifndef STATE_HPP
#define STATE_HPP

#include <list>
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <array>

typedef signed char int8;

class Map;
class State;

enum CellsTypes {
    Empty  = 0,
    Box    = 1 << 0,
    Player = 1 << 1,
    Target = 1 << 2,
    Wall   = 1 << 3
};

struct Point{
    Point():x(0),y(0){}

    Point(int8 _x, int8 _y) : x(_x), y(_y){}

    Point operator -(const Point &other) const{
        return Point(x - other.x, y - other.y);
    }

    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }

    Point &operator -=(const Point &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Point &operator +=(const Point &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    int64_t toInt6() const
    {
        return 0x3F & (((x-1) & 0x07) |  ( ((y-1) & 0x07) << 3));
    }

    bool operator==(const Point & other) const
    {
        return x == other.x && y == other.y;
    }

    int8 x,y;
};


class State
{
public:
    State();

    bool isSolutionOf(const Map &m);

    void applyTo(Map &m);

    void applyMove(const Point & move, Map &map);

    void computeNextStates(Map &map, int pred, std::vector<State> &stateQueue, std::unordered_map<int,int> &anc);

    void extractFrom(Map &map);

    int64_t toInt64() const;

    bool operator==(const State & other) const;


private:
    static std::unordered_map<int64_t, bool> knownStates;

    static const std::array<Point, 4> CARDINALS;

    bool stateExists(const State &origin);

    void setPlayerPosition(int8 x, int8 y);

    void addBoxPosition(int8 x, int8 y);

    Point m_ppos;

    std::vector<Point> m_boxes;

};

#endif // STATE_HPP
