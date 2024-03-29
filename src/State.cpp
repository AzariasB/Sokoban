//
// Created by
// - Azarias Boutin
// - Raphaël Haltz
// - Quentin Journet
//


#include "State.hpp"
#include "Map.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <bitset>

const std::array<Point,4> State::CARDINALS = {{
    {0,1},{0,-1},{1,0},{-1,0}
}};

std::unordered_map<int64_t, bool> State::knownStates = {};

State::State()
{
    m_boxes.reserve(16);
}

void State::setPlayerPosition(int8 x, int8 y)
{
    m_ppos = Point(x,y);
}

void State::addBoxPosition(int8 x, int8 y)
{
    m_boxes.emplace_back(x,y);
}


void State::applyTo(Map &m)
{
    m.at(m_ppos) |= Player;

    for(const Point& box : m_boxes){
        m.at(box) |= Box;
    }
}

int64_t State::toInt64() const
{
    int64_t res = 0;
    res |= m_ppos.toInt6();

    int shift = 1;
    for(const Point &p : m_boxes){
        res |= (p.toInt6() << (shift * 6));
        ++shift;
    }

    return res;
}

bool State::isSolutionOf(const Map &m)
{
    for(const Point &p : m_boxes){
        if( (m.at(p) & Target) != Target)return false;
    }
    return true;

}

void State::applyMove(const Point &move, Map &map)
{
    Point nxtPPos = m_ppos + move;

    map.at(m_ppos) ^= Player;
    map.at(nxtPPos) |= Player;

    if((map.at(nxtPPos) & Box) == Box){
        //Move the box
        Point boxPos = nxtPPos + move;
        map.at(nxtPPos) ^= Box;
        map.at(boxPos) |= Box;
    }
}

void State::computeNextStates(Map &map, int pred, std::vector<State> &stateQueue, std::unordered_map<int,int> &anc)
{
    for(const Point &card : CARDINALS){
        applyTo(map);
        if(map.isAccessible(m_ppos, card)){
            applyMove(card, map);
            if(!map.isUseless()){
                State s;
                s.extractFrom(map);
                if(stateExists(s))continue;//state already exists, move on

                s.extractFrom(map);
                stateQueue.push_back(s);
                anc[stateQueue.size() - 1] = pred;
                continue;
            }
        }
        map.reset();
    }
}

bool State::stateExists(const State &origin)
{
    int64_t encoded = origin.toInt64();

    bool &val = knownStates[origin.toInt64()];
    if(val)return true;
    val = true;
    return false;
}

void State::extractFrom(Map &map)
{
    for(const Point &p : map.getViablePositions()){
        int &i = map.at(p);
        if((i & Player) == Player){
            setPlayerPosition(p.x,p.y);
            i ^= Player;
        }else if((i & Box) == Box){
            addBoxPosition(p.x,p.y);
            i ^= Box;
        }
    }
}
