#include <iostream>
#include "Game.h"
#include "IO.h"
#include "Board.h"


Game::Game(unsigned short int numPlayers, Board board){
    this -> numPlayers = numPlayers;
    this -> board = board;
    initPlayers(numPlayers);
}

Game::~Game() {
    free(players);
}

void Game::initPlayers(unsigned short numPlayers) {
    players = (Player *) malloc(sizeof(Player) * numPlayers);
}
char Game::getTile() {
    unsigned short int index = rand()%tiles.size();
    char tile = tiles[index];
    tiles.erase(tiles.begin() + index);
    return tile;
}

bool Game::playerMove(Player &player, Board &board) {
    printMessage("Enter the position on the board in the format 'Aa': ");
    char position[2];
    while(!checkInput(position, '\n')){
        printMessage("Your input was invalid.");
        printMessage("Re-enter the position on the board in the format 'Aa': ");
    }

    unsigned short int intPosition[2];
    intPosition[0] = position[0] - 'A';
    intPosition[1] = position[1] - 'a';
    unsigned short int playerTileIndex = player.checkTiles(board.readLetter(intPosition));
    if (!playerTileIndex){
        printMessage("You don't own that tile!");
    }
}