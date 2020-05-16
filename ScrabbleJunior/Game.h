#ifndef SCRABBLEJUNIOR_GAME_H
#define SCRABBLEJUNIOR_GAME_H

#include <iostream>
#include <algorithm>
#include "IO.h"
#include "Board.h"
#include "Player.h"
#include "Color.h"
#include "TopScores.h"
#include "Graphical.h"

class Game{
public:
    Game(unsigned short int numPlayers,std::vector<std::string> playerNames, Board *boardPtr);
    void initPlayers(unsigned short int numPlayers, std::vector<std::string> playerNames);
    void initPot();
    char getRandomTile();
    int inputMove(unsigned short int intPosition[2], Player &player);
    bool playerMove(Player &player);
    void gotValidMove(Player &player, unsigned short int pos[2], char letter, Word *hWordPtr, Word *vWordPtr);
    bool gameManager();
    void changeTile(Player &player);
    void checkWinner();
    void getNameScore(std::vector<Player> &players, std::vector<Winner> &out);


private:
    enum state {Playing, End};
    state currState;
    std::vector<char> pot; // The bag of tiles
    std::vector<std::vector<int>> playerPositions;
    std::vector<ConsoleColors> playerNameColors;
    unsigned short int limit;
    unsigned short int numTiles = 0;
    unsigned short int numPlayers;
    std::vector<Player> players;
    Board *boardPtr;
};


#endif
