//
// Created by Raphaël Haltz on 21/03/2018.
//

#ifndef SOKOBAN_MAP_H
#define SOKOBAN_MAP_H

#include <vector>
#include <queue>
#include <string>

enum CellsTypes {
    Empty = 0,
    Box =    1 << 0,
    Player = 1 << 1,
    Target = 1 << 2,
    Wall =   1 << 3
};

struct Move;
char toChar(int code);

class Map {
public:
    Map();
    Map(int width, int height);

    Move CalculateMoves();

    bool isComplete() const;

    bool isAccessible(int x, int y, int xDir, int yDir) const;

    void performMove(const Move &mv);

    void SetXY(int x, int y, int type);

    void SetStart(int x, int y);

    CellsTypes GetXY(int x, int y);

    int width() const
    {
        return m_width;
    }

    std::string toString() const;

private:
    bool isValid(int x, int y) const;

    void addMoves(int x, int y, std::queue<Move> &q, int treeDepth) const;

    int m_width;
    int height;
    std::vector<std::vector<int>> map;

    int xStart, yStart;
};

struct Move{
    Move(){}

    Move(int x, int y, int dirX, int dirY, int idx, const Map &origin):
        x(x),
        y(y),
        dx(dirX),
        dy(dirY),
        index(idx),
        originalMap(origin){

    }

    void performMove(){
        originalMap.performMove(*this);
    }

    int x,y,dx,dy;/* coordinates from, direction*/
    int index;/* depth of tree */
    Map originalMap;

};


#endif //SOKOBAN_MAP_H
