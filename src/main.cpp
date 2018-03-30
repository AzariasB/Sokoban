
#include <iostream>
#include <fstream>
#include <stack>
#include "State.hpp"
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

    std::shared_ptr<State> root = std::make_shared<State>();
    Map m = parseFile(argv[1]);
    root->extractFrom(m);


    std::vector<std::shared_ptr<State>> states;
    int cursor = 0;
    states.reserve(100000000);
    ancestors anc;
    std::shared_ptr<State> finalState = {};

    states.emplace_back(root);
    while(cursor < states.size()){
        auto &next = states[cursor];
        if(next->isSolutionOf(m)){
            finalState = next;
            break;
        }
        next->computeNextStates(m, next, states, anc);
        cursor++;
    }

    std::stack<std::shared_ptr<State>> order;
    if(finalState){
        std::cout << "Found solution !\n";
       while(finalState != root){
            order.emplace(finalState);
            finalState = anc[finalState];
        }
        order.emplace(root);
        std::cout << "In " << order.size() << " moves\n";
        std::cout << "Explored " << states.size() << " states\n";
        //std::cout << "Known states "  << State::knownStates.size() << " states\n";

        /*
        while(!order.empty()){
            auto &st = order.top();
            order.pop();
            st->applyTo(m);
            std::cout << m.toString() << "\n";
            std::cin.ignore();
            m.reset();
        }*/

    }

    return 0;
}
