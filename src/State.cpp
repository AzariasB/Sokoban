/*
 * The MIT License
 *
 * Copyright 2017 azarias.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * File:   State.cpp
 * Author: azarias
 *
 * Created on 21/3/2018
 */
#include "State.hpp"
#include "Map.h"

#include <algorithm>
#include <iostream>

const std::array<Point,4> State::CARDINALS = {{
    {0,1},{0,-1},{1,0},{-1,0}
}};

std::vector<std::shared_ptr<State>> State::knownStates = []() -> std::vector<std::shared_ptr<State>> {
    std::vector<std::shared_ptr<State>> vec;
    vec.reserve(1 << 20);
    return vec;
}();

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

bool State::operator ==(const State &other) const
{
    return m_ppos == other.m_ppos &&
            m_boxes == other.m_boxes;
}

void State::computeNextStates(Map &map, std::shared_ptr<State> &pred, std::vector<std::shared_ptr<State>> &stateQueue, ancestors &anc)
{
    for(const Point &card : CARDINALS){
        applyTo(map);
        if(map.isAccessible(m_ppos, card)){
            applyMove(card, map);
            if(!map.isUseless()){
                State s;
                s.extractFrom(map);
                std::shared_ptr<State> nwState = {};
                if(!(nwState = getSate(s))){
                    continue;//state already exists, move on
                }
                stateQueue.emplace_back(nwState);
                nwState->extractFrom(map);
                //anc[nwState] = pred;
                continue;
            }
        }
        map.reset();
    }
}

std::shared_ptr<State> State::getSate(const State &origin)
{
    auto found = std::find_if(knownStates.begin(), knownStates.end(), [&origin](const auto &ptr){
        return origin == *ptr;
    });

    if(found == knownStates.end()){
        std::shared_ptr<State> st = std::make_shared<State>(origin);
        knownStates.emplace_back(st);
        return st;
    }

    return {};//already exist => not treating it
}

void State::extractFrom(Map &map)
{
    auto &m = map.get();
    for(int y = 1, s = m.size(); y < s - 1; ++y){
        for(int x = 1, ss = m[y].size(); x < ss - 1; ++x){
            int &i = m[y][x];
            if((i & Player) == Player){
                setPlayerPosition(x,y);
                i ^= Player;
            }else if((i & Box) == Box){
                addBoxPosition(x,y);
                i ^= Box;
            }
        }
    }
}
