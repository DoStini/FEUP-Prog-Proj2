#ifndef SCRABBLEJUNIOR_GAME_H
#define SCRABBLEJUNIOR_GAME_H

#include <iostream>
#include "Board.h"
#include "Player.h"

class Game{
public:
    Game(unsigned short int numPlayers, Board *boardPtr);
    void initPlayers(unsigned short int numPlayers);
    void initPot();
    char getRandomTile();
    bool inputMove(unsigned short int intPosition[2], Player &player);
    bool playerMove(Player &player);
    void gotValidMove(Player &player, unsigned short int pos[2], char letter, Word *hWordPtr, Word *vWordPtr);

private:
    vector<char> pot;                     // The bag of tiles
    unsigned short int numPlayers;
    vector<Player> players;
    Board *boardPtr;
};


#endif
