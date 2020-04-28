#ifndef SCRABBLEJUNIOR_GAME_H
#define SCRABBLEJUNIOR_GAME_H

#include <iostream>
#include "Board.h"
#include "Player.h"

class Game{
public:
    Game(unsigned short int numPlayers, Board *boardPtr);
    ~Game();
    void initPlayers(unsigned short int numPlayers);
    void initPot();
    char getTile();
    bool inputMove(unsigned short int intPosition[2], Player &player);
    bool playerMove(Player &player);

private:
    vector<char> pot;                     // The bag of tiles
    unsigned short int numPlayers;
    vector<Player> players;
    Board *boardPtr;
};


#endif
