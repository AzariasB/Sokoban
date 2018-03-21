
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

    Map mMap(width, height);
    for(int y = 0; y < height; ++y){//read all columns
        for(int x = 0; x < width; ++x){// read all lines
            int value;
            mapF >> value;
            std::cout << value << " ";
            mapF.ignore();// comma or \n
            if( (value & Player) == Player){
                mMap.SetStart(x,y);
            }
            mMap.SetXY(x, y, value);
        }
        std::cout << "\n";
    }

    mapF.close();
    return mMap;
}

int main(int argc, char **argv) {
    std::cout << argc << std::endl;

    if(argc < 2){
        std::cerr << "Must pass filename in parameter\n";
        return -1;
    }


    Map m = parseFile(argv[argc]);
    std::cout << m.CalculateMoves() << std::endl;
    return 0;
}
