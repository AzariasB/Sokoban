//
// Created by Raphaël Haltz on 21/03/2018.
//

#include "Map.h"
#include <queue>

Map::Map(){}

Map::Map(int width, int height):
map(height),
width(width),
height(height){
    for(int i = 0; i < height;++i)
        map[i].reserve(width);
}


int Map::CalculateMoves(int xStart, int yStart)
{
    return 0;
}

void Map::SetWidth(int width){
  this->width = width;
}
void Map::SetHeight(int height){
  this->height = height;
}
int Map::GetWidth(void){
    return width;
}
int Map::GetHeight(void){
    return height;
}

void Map::SetXY(int x, int y, CellsTypes type)
{
    map[y][x] = type;
}
CellsTypes Map::GetXY(int x, int y){
    return map.at(x).at(y);
}

CellsTypes Map::GetTypeFromInt(int input){
    switch(input){
        case 0:
            return CellsTypes::Empty;
        case 1:
            return CellsTypes::Box;
        case 2:
            return CellsTypes::Player;
        case 4:
            return CellsTypes::Target;
        case 5:
            return CellsTypes::BoxOnTarget;
        case 6:
            return CellsTypes::PlayerOnTarget;
        case 8:
            return CellsTypes::Wall;
        default:
            return CellsTypes::Wall;
    };
}
