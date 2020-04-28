#ifndef SCRABBLEJUNIOR_PLAYER_H
#define SCRABBLEJUNIOR_PLAYER_H

#include <iostream>
#include <string>
#include "Board.h"

class Player{
public:
    Player();
    Player(vector<char> &pot);
    unsigned short int checkTiles(char letter);
    void initTiles(vector<char> &pot);
    void showTiles();
    void setTile(char letter, unsigned short int pos);
private:
    char tiles[7];
    unsigned short int score = 0;
    std::string name = "";
};

#endif
