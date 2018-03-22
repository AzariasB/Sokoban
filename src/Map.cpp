//
// Created by Raphaël Haltz on 21/03/2018.
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

const int &Map::at(const Point &p) const
{
    return map[p.y][p.x];
}

void Map::reset()
{
    for(int y = 0; y < map.size(); ++y){
        for(int x = 0; x < map[y].size(); ++x){
            if( (map[y][x] & Box) == Box )
                map[y][x] ^= Box;
            else if( (map[y][x] & Player) == Player)
                map[y][x] ^= Player;
        }
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
    return  ( hasWall(p+left)  && hasWall(p+top)  ) ||
            ( hasWall(p+left)  && hasWall(p+down) ) ||
            ( hasWall(p+right) && hasWall(p+top)  ) ||
            ( hasWall(p+right) && hasWall(p+down) ) ||
            ( hasBlocking(p+left) && hasBlocking(p+topLeft) && hasBlocking(p+top) ) ||
            ( hasBlocking(p+left) && hasBlocking(p+downLeft) && hasBlocking(p+down) ) ||
            ( hasBlocking(p+right) && hasBlocking(p+downRight) && hasBlocking(p+down) ) ||
            ( hasBlocking(p+right) && hasBlocking(p+topRight) && hasBlocking(p+top) );

}

bool Map::isUseless() const
{
    for(int y = 0; y < map.size(); ++y){
        for(int x = 0; x < map[y].size(); ++x){
            Point p(x,y);
            if(hasBox(p) && !hasTarget(p) && isStuck(p))return true;
        }
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

    return isValid(nxtPos) && map[nxtPos.y][nxtPos.x] == Empty || map[nxtPos.y][nxtPos.x] == Target;
}
