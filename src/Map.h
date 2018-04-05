//
// Created by
// - Azarias Boutin
// - Raphaël Haltz
// - Quentin Journet
//

#ifndef SOKOBAN_MAP_H
#define SOKOBAN_MAP_H

#include <vector>
#include <queue>
#include <string>
#include "State.hpp"

/**
 * @brief toChar a char for every type of cell in the sokoban board
 * @param code the code of the cell
 * @return the corresponding char
 */
char toChar(int code);

/**
 * @brief The Map class contains a 2 dimensionnal
 * vector, with all the data about the basic map
 * (the walls, the empty spaces, and the targets)
 * States can be applied to the map, in order
 * to put the player and the boxes, to calculate
 * the next states
 */
class Map {
public:
    /**
     * @brief Map default empty constructor
     */
    Map();

    /**
     * @brief Map constructor with the width and height,
     * to initiliaze the space of the grid
     * @param width width of the map
     * @param height height of the map
     */
    Map(int width, int height);

    /**
     * @brief isAccessible if the cell in the given direction
     * is accessible, starting from the given origin point
     * @param origin the point to move from
     * @param dir the direction to follow
     * @return if the cell is accessible (if it's empty,
     * or there is a box in it, and this box can be pushed)
     */
    bool isAccessible(const Point &origin, const Point &dir) const;

    /**
     * @brief isValid if the given point is within the boundaries of the map
     * @param p point to check
     * @return wether the point is within the boundaries of the map
     */
    bool isValid(const Point &p) const;

    /**
     * @brief toString string version of the map
     * @return
     */
    std::string toString() const;

    /**
     * @brief at reference to the value of the cell at
     * the given position
     * @param p position to search for
     * @return reference to the value of the cell
     */
    int &at(const Point &p);

    /**
     * @brief reset removes all the boxes
     * and the player of the map,
     * only the target, the empty places
     * and the target are left afterward
     */
    void reset();

    /**
     * @brief isUseless if the map can not be solved,
     * given its current state (if there is a box stuck
     * against a wall or in a corner)
     * @return if the map can't be solved
     */
    bool isUseless() const;

    /**
     * @brief at const version of the 'at' method
     * @param p
     * @return
     */
    const int &at(const Point &p) const;

    /**
     * @brief detectViablePositions
     */
    void detectViablePositions();

    /**
    * @brief getViablePositions all the positions
    * where the player can move
     * @return
     */
    const std::vector<Point> &getViablePositions() const;

private:
    /**
     * @brief left (-1,0)
     */
    static const Point left;

    /**
     * @brief top (0,-1)
     */
    static const Point top;

    /**
     * @brief right (1,0)
     */
    static const Point right;

    /**
     * @brief down (0, 1)
     */
    static const Point down;

    /**
     * @brief topLeft (-1, -1)
     */
    static const Point topLeft;

    /**
     * @brief topRight (1, -1)
     */
    static const Point topRight;

    /**
     * @brief downLeft (-1, 1)
     */
    static const Point downLeft;

    /**
     * @brief downRight (1, 1)
     */
    static const Point downRight;

    /**
     * @brief isStuck if the box located at
     * the given position is stuck (agains a wall
     * or in a corner)
     * @param p
     * @return
     */
    inline bool isStuck(const Point &p) const;

    /**
     * @brief againstWall if the box at the position p, is agains the wall
     * in the direction test
     * @param p the box position
     * @param test the side of the box to test has a wall
     * @param d1 the direction where the wall can move
     * @return if the box is agains a wall and there is no target against this wall
     */
    inline bool  againstWall(const Point &p, const Point &test, const Point &d1) const;

    /**
     * @brief hasWall the given position in the map contains a wall
     * @param p position to test
     * @return
     */
    inline bool hasWall(const Point &p) const;

    /**
     * @brief hasTarget wether the given position in the map contains a target
     * @param p
     * @return
     */
    inline bool hasTarget(const Point &p) const;

    /**
     * @brief hasBox wether the given position in the map contains a box
     * @param p
     * @return
     */
    inline bool hasBox(const Point &p) const;

    /**
     * @brief hasBlocking wether the given position in the map contains a box or a wall
     * @param p
     * @return
     */
    inline bool hasBlocking(const Point &p) const;

    /**
     * @brief map the map itself
     */
    std::vector<std::vector<int>> map;

    /**
     * @brief viablePositions list of all the positions
     * where the player can move (ignoring the box position)
     */
    std::vector<Point> viablePositions;
};


#endif //SOKOBAN_MAP_H
