//
// Created by Raphaël Haltz on 21/03/2018.
//

#include "Map.h"
#include <sstream>
#include <iostream>

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
