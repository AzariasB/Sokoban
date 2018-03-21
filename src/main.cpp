
#include <iostream>
#include <fstream>
#include "Map.h"

Map parseFile(const std::string &mapName)
{
    std::ifstream mapF;
    mapF.open(mapName);
    if(!mapF.is_open()){
        std::cerr << "File not found " << std::endl;
        return Map(0, 0);//;//empty map
    }

    int width = 0;
    int height = 0;
    mapF >> width;
    mapF.ignore();// comma
    mapF >> height;
    mapF.ignore();// \n

    std::cout << "Width = " << width << " - height = " << height << std::endl;

    Map mMap;//(width, height);
    for(int y = 0; y < height; ++y){//read all columns
        for(int x = 0; x < width; ++x){// read all lines
            int value;
            mapF >> value;
            mapF.ignore();// comma or \n
            CellsTypes ct = Map::toCellType(value);
            mMap.SetXY(x, y, ct);
        }
        std::cout << std::endl;
    }
    return mMap;
}

int main() {
    parseFile("../data/soko1.txt");
    return 0;
}
