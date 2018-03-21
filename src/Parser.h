//
// Created by Raphaël Haltz on 21/03/2018.
//

#ifndef SOKOBAN_PARSER_H
#define SOKOBAN_PARSER_H

#include <string>
#include "Map.h"

class Parser {
public:

    Map parseFile(const std::string &mapName);

private:

};


#endif //SOKOBAN_PARSER_H
