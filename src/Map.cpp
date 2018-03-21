//
// Created by Raphaël Haltz on 21/03/2018.
//

#include "Map.h"

Map::Map(){};
Map::Map(int width, int height){
    this->width = width;
    this->height = height;
};

void Map::SetWidth(int width){
  this->width = width;
};
void Map::SetHeight(int height){
  this->height = height;
};
int Map::GetWidth(void){
    return this->width;
};
int Map::GetHeight(void){
    return this->height;
};

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
            return CellsTypes::PlayerOnTarget
        case 8:
            return CellsTypes::Wall;
        default:
            return CellsTypes::Wall;
    };
};
//void Map::SetXY(int x, int y, CellsTypes type);
//CellsTypes Map::GetXY(int x, int y);