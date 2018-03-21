
#include <iostream>
#include <fstream>
#include "State.hpp"
#include "Map.h"

Map parseFile(const std::string &mapName, State &rootState)
{
    std::ifstream mapF;
    mapF.open(mapName);
    if(!mapF.is_open()){
        std::cerr << "File not found " << std::endl;
        return Map(0, 0);//;//empty map
    }

    int width = 0;
    int height = 0;
    mapF >> height;
    mapF.ignore();// comma
    mapF >> width;
    mapF.ignore();// \n

    std::cout << "Width = " << width << " - height = " << height << std::endl;

    Map mMap(width, height);
    for(int y = 0; y < height; ++y){//read all columns
        for(int x = 0; x < width; ++x){// read all lines
            int value;
            mapF >> value;
            mapF.ignore();// comma
            mMap.at(Point(x,y)) = value;
        }
        mapF.ignore();// \n
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

    State root;
    Map m = parseFile(argv[1], root);
    root.extractFrom(m);
    std::queue<State> states;
    states.push(root);
    while(!states.empty()){
        State &next = states.front();
        if(next.isSolutionOf(m)){
            std::cout << "Found solution !" << std::endl;
            next.applyTo(m);
            std::cout << m.toString() << "\n";
            break;
        }
        next.computeNextStates(m, states);
        states.pop();
    }

    return 0;
}
