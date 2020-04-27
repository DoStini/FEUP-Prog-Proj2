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
    void initTiles(Board &board);
    char getTile();
    bool playerMove(Player &player, Board &board);

private:
    vector<char> tiles;
    unsigned short int numPlayers;
    Player *players;
    Board board;
};



#endif
