
#include <iostream>
#include <fstream>
#include "Map.h"
#include "TileMap.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
            mapF.ignore();// comma or \n
            if( (value & Player) == Player){
                mMap.SetStart(x,y);
            }
            mMap.SetXY(x, y, value);
        }
    }

    mapF.close();
    return mMap;
}

int main(int argc, char **argv) {



    Map map = parseFile("../data/soko1.txt");

    for(unsigned int i = 0; i< map.getHeight();i++){
        for(unsigned int j = 0; j< map.getWidth();j++){
            std::cout << map.GetXY(j,i);
        }
        std::cout << std::endl;

    }

    sf::RenderWindow window(sf::VideoMode(500, 500), "Sokoban");

    TileMap tilemap;
    if (!tilemap.load("../data/sprites.png", sf::Vector2u(32, 32), map.getMap(), map.getWidth(), map.getHeight()))
        return -1;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on dessine le niveau
        window.clear();
        window.draw(tilemap);
        window.display();
    }

    return 0;
}
