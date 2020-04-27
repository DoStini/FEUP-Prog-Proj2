#ifndef SCRABBLEJUNIOR_GAME_H
#define SCRABBLEJUNIOR_GAME_H

#include <iostream>
#include "Board.h"
#include "Player.h"

class Game{
public:
    Game(unsigned short int numPlayers, Board board);
    ~Game();
    void initPlayers(unsigned short int numPlayers);
    void initPot();
    char getTile();
    bool playerMove(Player &player);

private:
    vector<char> pot;                     // The bag of tiles
    unsigned short int numPlayers;
    vector<Player> players;
    Board board;
};


#endif
