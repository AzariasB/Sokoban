//
// Created by Raphaël Haltz on 21/03/2018.
//

#include "Map.h"

Map::Map(){}

Map::Map(int width, int height):
map(height),
width(width),
height(height){
    for(int i = 0; i < height;++i)
        map.emplace_back(width);
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
    map[y].size();
    //map[y][x] = type;
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
//void Map::SetXY(int x, int y, CellsTypes type);
//CellsTypes Map::GetXY(int x, int y);
