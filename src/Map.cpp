//
// Created by Raphaël Haltz on 21/03/2018.
//

#include "Map.h"
#include <iostream>

struct Move{
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

    int x,y,dx,dy;/* coordinates from, coordinates to */
    int index;/* depth of tree */
    Map originalMap;

};

Map::Map(){}

Map::Map(int width, int height):
map(height),
width(width),
height(height){
    for(int i = 0; i < height;++i)
        map[i].resize(width);
}

void Map::addMoves(int x, int y, std::queue<Move> &q, int treeDepth) const
{
    //right
    if(isAccessible(x+1,y,1,0)) q.emplace(x,y,1,0, treeDepth, *this);

    //left
    if(isAccessible(x-1,y,-1,0)) q.emplace(x,y,-1,0, treeDepth, *this);

    //up
    if(isAccessible(x,y-1,0,-1))q.emplace(x,y,0,-1, treeDepth, *this);

    //down
    if(isAccessible(x,y+1,0,1))q.emplace(x,y,0,1, treeDepth, *this);
}

void Map::performMove(const Move &mv)
{
    map[mv.y][mv.x] ^= Player;
    int nxtX = mv.x + mv.dx;
    int nxtY = mv.y + mv.dy;

    if(map[nxtY][nxtX] == Box){//Move the box
        int nwBoxPosX = nxtX + mv.dx;
        int nwBoxPosY = nxtY + mv.dy;

        map[nwBoxPosY][nwBoxPosX] |= Box;
        map[nxtY][nxtX] ^= Box;
    }
    map[nxtY][nxtX] |= Player;
}


void Map::SetStart(int x, int y)
{
    xStart = x;
    yStart = y;
}

int Map::CalculateMoves()
{
    std::queue<Move> nxtMoves;
    addMoves(xStart, yStart, nxtMoves, 0);

    while(!nxtMoves.empty()){
        Move m = nxtMoves.front();
        nxtMoves.pop();
        m.performMove();
        if(m.originalMap.isComplete())return m.index;
        m.originalMap.addMoves(m.x + m.dx, m.y + m.dy, nxtMoves, m.index+1);
    }
    return -1;//failed :(
}

void Map::SetXY(int x, int y, int type)
{
    map[y][x] = type;
}


bool Map::isComplete() const
{
    for(auto &vec : map){
        for(auto i : vec){
            if(i == Target)return false;
        }
    }
    return true;
}

bool Map::isValid(int x, int y) const
{
    return x >= 0 && y >= 0 && x < width && y < height;
}

bool Map::isAccessible(int x, int y, int xDir, int yDir) const
{
    if(!isValid(x,y))return false;
    int cellVal = map[y][x];
    if((cellVal & Wall) == Wall)return false;//can't go on wall
    if(cellVal == Empty || cellVal == Target)return true;//can go on empty places, or empty target
    //else => is Box : see if we can push it
    int nxtX = x+xDir;
    int nxtY = y+yDir;

    return isValid(nxtX,nxtY) && map[nxtY][nxtX] == Empty || map[nxtY][nxtX] == Target;
}

int Map::GetXY(int x, int y){
    return this->map.at(x).at(y);
}

int Map::getWidth() const {
    return width;
}

void Map::setWidth(int width) {
    Map::width = width;
}

int Map::getHeight() const {
    return height;
}

void Map::setHeight(int height) {
    Map::height = height;
}

const std::vector<std::vector<int>> &Map::getMap() const {
    return map;
}

void Map::setMap(const std::vector<std::vector<int>> &map) {
    Map::map = map;
}
