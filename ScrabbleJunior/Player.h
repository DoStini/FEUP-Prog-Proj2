#ifndef SCRABBLEJUNIOR_PLAYER_H
#define SCRABBLEJUNIOR_PLAYER_H

#include <iostream>
#include <string>
#include "Board.h"

class Player{
public:
    unsigned short int checkTiles(char letter);
    void initTiles(Board &board);
    void setTile(char letter, unsigned short int pos);
private:
    char tiles[7];
    unsigned short int score;
    std::string name;
};

#endif
