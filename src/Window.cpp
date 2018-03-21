//
// Created by Zarma13 on 21-Mar-18.
//

#include "Window.h"
#include <iostream>


void Window::create_window(std::vector<std::vector<int>> map){
    sf::RenderWindow window(sf::VideoMode(500, 500), "Sokoban");


    if (!this->tilemap.load("../data/sprites.png", sf::Vector2u(64, 64), map, map.data()->size(), map.size()))
        std::cerr << "File of sprites not found " << std::endl;

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
}