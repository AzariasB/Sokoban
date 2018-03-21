//
// Created by Raphaël Haltz on 21/03/2018.
//

#ifndef SOKOBAN_MAP_H
#define SOKOBAN_MAP_H

#include <vector>

enum CellsTypes {
    Empty = 0,
    Wall,
    Box,
    Target,
    BoxOnTarget,
    Player,
    PlayerOnTarget
};

class Map {
public:
    Map();
    Map(int width, int height);

    void SetWidth(int width);
    void SetHeight(int height);
    int GetWidth(void);
    int GetHeight(void);

    CellsTypes GetTypeFromInt(int input);
    void SetXY(int x, int y, CellsTypes type);
    CellsTypes GetXY(int x, int y);
private:
    int width;
    int height;
    std::vector<std::vector<CellsTypes>> map;
};


#endif //SOKOBAN_MAP_H