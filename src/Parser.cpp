//
// Created by Raphaël Haltz on 21/03/2018.
//

#include "Parser.h"
#include <fstream>
#include <iostream>

Map Parser::parseFile(const std::string &mapName)
{
    std::ifstream mapF;
    mapF.open(mapName);
    if(!mapF.is_open()){
        std::cerr << "File not found " << std::endl;
        return Map();//;//empty map
    }

    int width = 0;
    int height = 0;
    mapF >> width;
    mapF.ignore();// comma
    mapF >> height;
    mapF.ignore();// \n

    std::cout << "Width = " << width << " - height = " << height << std::endl;

    Map mMap;//(width, height);
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            int value;
            mapF >> value;
            mapF.ignore();
            std::cout << value << " ";
            //CellsTypes ct = Map::toCellType(value);
            //mMap.setValue(x,y,ct);
        }
        std::cout << std::endl;
    }
    return mMap;
}
