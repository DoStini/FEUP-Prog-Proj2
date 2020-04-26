#ifndef SCRABBLEJUNIOR_GAME_H
#define SCRABBLEJUNIOR_GAME_H

#include <iostream>
#include "Board.h"


class Game{
public:
    Game(unsigned short int numPlayers, Board board);
    char getTile();

private:
    char tiles[101];
    unsigned short int score[4];
};



#endif
