//
// Created by Zarma13 on 21-Mar-18.
//

#ifndef SOKOBAN_WINDOW_H
#define SOKOBAN_WINDOW_H

#include "TileMap.h"

class Window {
private:
    TileMap tilemap;

public:

void create_window(std::vector<std::vector<int>> map);

};


#endif //SOKOBAN_WINDOW_H
