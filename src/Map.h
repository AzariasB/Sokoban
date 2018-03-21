//
// Created by Raphaël Haltz on 21/03/2018.
//

#ifndef SOKOBAN_MAP_H
#define SOKOBAN_MAP_H

#include <vector>
#include <queue>

enum CellsTypes {
    Empty = 0,
    Box =    1 << 0,
    Player = 1 << 1,
    Target = 1 << 2,
    Wall =   1 << 3
};

struct Move;

class Map {
public:
    Map();
    Map(int width, int height);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int CalculateMoves();

    bool isComplete() const;

    bool isAccessible(int x, int y, int xDir, int yDir) const;

    void performMove(const Move &mv);

    void SetXY(int x, int y, int type);

    void SetStart(int x, int y);

    int GetXY(int x, int y);

    const std::vector<std::vector<int>> &getMap() const;

    void setMap(const std::vector<std::vector<int>> &map);

private:
    bool isValid(int x, int y) const;

    void addMoves(int x, int y, std::queue<Move> &q, int treeDepth) const;

    int width;
    int height;
    std::vector<std::vector<int>> map;

    int xStart, yStart;
};


#endif //SOKOBAN_MAP_H
