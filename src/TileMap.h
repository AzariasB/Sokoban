//
// Created by Zarma13 on 21-Mar-18.
//

#include <SFML/Graphics.hpp>

#ifndef SOKOBAN_TILEMAP_H
#define SOKOBAN_TILEMAP_H



class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<std::vector<int>> tiles, unsigned int width, unsigned int height);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


#endif //SOKOBAN_TILEMAP_H
