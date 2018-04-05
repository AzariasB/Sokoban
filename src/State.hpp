//
// Created by
// - Azarias Boutin
// - Raphaël Haltz
// - Quentin Journet
//


#ifndef STATE_HPP
#define STATE_HPP

#include <list>
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <array>

typedef signed char int8;

class Map;
class State;

/**
 * @brief The CellsTypes enum
 * all the basic cells type
 */
enum CellsTypes {
    Empty  = 0,
    Box    = 1 << 0,
    Player = 1 << 1,
    Target = 1 << 2,
    Wall   = 1 << 3
};

/**
 * @brief The Point struct
 * usefull class to navigate through
 * the map, has some operators to
 * increment it's x and y value,
 * the two int (x and y) are public
 * and can be modified has the user pleases
 */
struct Point{
    /**
     * @brief Point empty constructor
     */
    Point():x(0),y(0){}

    /**
     * @brief Point constructor with x and y position
     * @param _x x position of the point
     * @param _y y position of the point
     */
    Point(int8 _x, int8 _y) : x(_x), y(_y){}

    /**
     * @brief operator - the difference between this point and the
     * given point
     * @param other point to differ with
     * @return
     */
    Point operator -(const Point &other) const{
        return Point(x - other.x, y - other.y);
    }

    /**
     * @brief operator + the sum of the x and y values of this point
     * and the other
     * @param other the point to sum with
     * @return a new point containing the sum of this point and the given point
     */
    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }

    /**
     * @brief operator -= removes the given point to this point
     * @param other
     * @return the point itself
     */
    Point &operator -=(const Point &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /**
     * @brief operator += adds the given point to this point
     * @param other
     * @return the point itself
     */
    Point &operator +=(const Point &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    /**
     * @brief toInt6 encodes the point into a 6 bits int,
     * used to encode the state in a 64 bits int
     * a 64 bits int is returned in order to be able to do bit shifting
     * and 'or' operators with others 64 bits ints
     * @return the 6 bits encoded point into a 64 bits int
     */
    int64_t toInt6() const
    {
        return 0x3F & (((x-1) & 0x07) |  ( ((y-1) & 0x07) << 3));
    }

    /**
     * @brief operator == if the point is the same as the given point
     * @param other
     * @return wether the x and y coordinates are the same for this point and the other point
     */
    bool operator==(const Point & other) const
    {
        return x == other.x && y == other.y;
    }

    int8 x,y;
};


/**
 * @brief The State class core class of the problem,
 * contains a list of boxes, and the position of the player
 * can be encoded in a 64 bits int to be stored in a map, can apply
 * itself to a map, or generate itself from a map (and clean the map)
 */
class State
{
public:
    /**
     * @brief State empty constructor
     */
    State();

    /**
     * @brief isSolutionOf wether all the boxes of this states
     * are positionned on the targets of the map
     * @param m the map to test on
     * @return
     */
    bool isSolutionOf(const Map &m);

    /**
     * @brief applyTo puts the boxes and the player into the map
     * @param m the map to fill
     */
    void applyTo(Map &m);

    /**
     * @brief applyMove moves the player in the given move direction
     * @param move the direction of the player
     * @param map the map where to apply the move
     */
    void applyMove(const Point & move, Map &map);

    /**
     * @brief computeNextStates calculates the next states of this state,
     * will check in the four cardinal directions if its possible to move,
     * and if it is, adds the new state ins the vector (used as a queue) and
     * declares the new state as the successor of the 'pred' state
     * @param map the map to use to apply the moves and the states
     * @param pred the index of the predecessor state in the stateQueue vector
     * @param stateQueue a vector containing all the visited states and the states to visit, is used as a queue
     * @param anc the map of the ancestors, the key is the successor, the value is the successor
     */
    void computeNextStates(Map &map, int pred, std::vector<State> &stateQueue, std::unordered_map<int,int> &anc);

    /**
     * @brief extractFrom run through the viable positions of the map,
     * to get the player position and the boxes position,
     * cleans the map to remove all the boxes and the player from it
     * @param map the map to clean
     */
    void extractFrom(Map &map);

    /**
     * @brief toInt64 hash function to encode this state to an int 64
     * @return
     */
    int64_t toInt64() const;

private:
    /**
     * @brief knownStates a static map to save all the state that
     * where created, the key is the hash of the state,
     * the value (boolean) is wether the state was visited,
     * by default, this boolean is set to false, and when
     * a new state is created, it will be set to true
     */
    static std::unordered_map<int64_t, bool> knownStates;

    /**
     * @brief CARDINALS the four cardinals directions
     */
    static const std::array<Point, 4> CARDINALS;

    /**
     * @brief stateExists checks if the given state was already created
     * @param origin the state to check for
     * @return wether the given state was already created
     */
    bool stateExists(const State &origin);

    /**
     * @brief setPlayerPosition sets the position of the player for this state
     * @param x the x position of the player
     * @param y the y position of the player
     */
    void setPlayerPosition(int8 x, int8 y);

    /**
     * @brief addBoxPosition adds the position of the box in the boxes vector
     * @param x x position of the box
     * @param y y position of the box
     */
    void addBoxPosition(int8 x, int8 y);

    /**
     * @brief m_ppos position of the player
     */
    Point m_ppos;

    /**
     * @brief m_boxes position of the boxes
     */
    std::vector<Point> m_boxes;

};

#endif // STATE_HPP
