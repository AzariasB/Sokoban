//
// Created by
// - Azarias Boutin
// - Raphaël Haltz
// - Quentin Journet
//


#include "Map.h"
#include <sstream>
#include <iostream>

const Point Map::top = {0,-1};
const Point Map::right = {1,0};
const Point Map::down = {0,1};
const Point Map::left = {-1,0};
const Point Map::topLeft = {-1,-1};
const Point Map::topRight = {1,-1};
const Point Map::downLeft = {-1,1};
const Point Map::downRight = {1,1};


char toChar(int cCode)
{
    if(cCode == Wall){
        return '#';
    }else if(cCode == Player){
        return 'P';
    }else if(cCode == Box){
        return 'o';
    }else if(cCode == Target){
        return 'x';
    }else if(cCode == (Target | Box)) {
        return '+';
    }else if(cCode == (Target | Player)){
        return 'Q';
    }else{
        return ' ';
    }
}

Map::Map(){}

Map::Map(int width, int height):
map(height){
    for(int i = 0; i < height;++i)
        map[i].resize(width);
}

int &Map::at(const Point &p)
{
    return map[p.y][p.x];
}

void Map::detectViablePositions()
{
    viablePositions.reserve(64);
    for(int y = 0; y < map.size(); ++y){
        for(int x = 0; x < map[y].size(); ++x){
            if( (map[y][x] & Wall) != Wall){
                viablePositions.emplace_back(x,y);
            }
        }
    }
}

const std::vector<Point> &Map::getViablePositions() const
{
    return viablePositions;
}

const int &Map::at(const Point &p) const
{
    return map[p.y][p.x];
}

void Map::reset()
{
    for(const Point &p : viablePositions){
        int &v = at(p);
        if((v & Box) == Box)
            v ^= Box;
        else if( (v & Player) == Player)
            v ^= Player;

    }
}

bool Map::hasBlocking(const Point &p) const
{
    return hasWall(p) || hasBox(p);
}

bool Map::hasWall(const Point &p) const
{
    return (map[p.y][p.x] & Wall) == Wall;
}

bool Map::hasTarget(const Point &p) const
{
    return (map[p.y][p.x] & Target) == Target;
}

bool Map::hasBox(const Point &p) const
{
    return (map[p.y][p.x] & Box) == Box;
}

bool Map::isStuck(const Point &p) const
{
    //three blocings
    bool lBlocking = hasBlocking(p+left),
            rBlocking = hasBlocking(p + right),
            tBlocking = hasBlocking(p + top),
            dBlocking = hasBlocking(p + down);

    if(lBlocking && hasBlocking(p + downLeft) && dBlocking ||
            lBlocking && hasBlocking(p+topLeft) && tBlocking ||
            rBlocking && hasBlocking(p + downRight) && dBlocking ||
            rBlocking && hasBlocking(p + topRight) && tBlocking)
        return true;

    //Surrounded by walls
    bool lWall = hasWall(left + p);
    bool rWall = hasWall(right + p);
    bool tWall = hasWall(top + p);
    bool dWall = hasWall(down + p);

    bool surrounded =  ( lWall  && tWall  ) ||
            ( lWall && dWall ) ||
            ( rWall && tWall  ) ||
            ( rWall && dWall );

    if(surrounded)return true;

    //check if against wall and no target
    if(tWall)
        return againstWall(p, top, left);

    if(dWall)
        return againstWall(p, down, left);

    if(rWall)
        return againstWall(p, right, top);

    if(lWall)
        return againstWall(p, left, top);

    return false;
}

bool Map::againstWall(const Point &p, const Point &test, const Point &d1) const
{
    Point cp = (p+d1);
    while(!hasWall(cp)){
        if(!hasWall(cp + test) || hasTarget(cp))return false;
        cp += d1;
    }
    cp = (p-d1);
    while(!hasWall(cp)){
        if(!hasWall(cp + test) || hasTarget(cp))return false;
        cp -= d1;
    }
    return true;
}

bool Map::isUseless() const
{
    for(const Point &p : viablePositions){
        if(hasBox(p) && !hasTarget(p) && isStuck(p))return true;
    }
    return false;
}

std::string Map::toString() const
{
    std::stringstream ss;
    for(int y = 0; y < map.size(); ++y){
        for(int x = 0; x < map[y].size(); ++x){
            ss << toChar(map[y][x]);
        }
        ss << "\n";
    }

    return ss.str();
}


bool Map::isValid(const Point &p) const
{
    return p.x >= 0 && p.y >= 0 && p.x < map[0].size() && p.y < map.size();
}

bool Map::isAccessible(const Point &origin, const Point &dir) const
{
    Point p = origin + dir;
    if(!isValid(p))return false;
    int cellVal = map[p.y][p.x];
    if((cellVal & Wall) == Wall)return false;//can't go on wall
    if(cellVal == Empty || cellVal == Target)return true;//can go on empty places, or empty target
    //else => is Box : see if we can push it
    Point nxtPos = p + dir;

    return isValid(nxtPos) && (map[nxtPos.y][nxtPos.x] == Empty || map[nxtPos.y][nxtPos.x] == Target);
}
