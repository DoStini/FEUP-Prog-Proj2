#include <iostream>
#include "Game.h"
#include "IO.h"
#include "Board.h"
#include "Player.h"


Game::Game(unsigned short int numPlayers, Board board){
    this -> numPlayers = numPlayers;
    this -> board = board;
    initPot();
    initPlayers(numPlayers);
}

Game::~Game() {

}

void Game::initPlayers(unsigned short numPlayers) {
    players.reserve(numPlayers);
    Player player;
    for (int i = 0; i < numPlayers; ++i) {
        player = Player(pot);
        players.push_back(player);
    }
}

void Game::initPot() {
    char temp;
    int temp2;
    unsigned short int pos[2];
    for (int i = 0; i < board.getVSize(); ++i) {
        pos[0] = i;
        for (int j = 0; j < board.getHSize(); ++j) {
            pos[1] = j;
            temp = board.getTile(pos);
            if (temp != ' '){
                pot.push_back(temp);
                temp2++;
            }
        }
    }
    std::cout << temp2;
}

char Game::getTile() {
    unsigned short int index = rand()%pot.size();
    char tile = pot[index];
    pot.erase(pot.begin() + index);
    return tile;
}

bool Game::playerMove(Player &player) {
    printMessage("Enter the position on the board in the format 'Aa': ");
    char position[2];
    while(!checkInput(position, '\n')){
        printMessage("Your input was invalid.");
        printMessage("Re-enter the position on the board in the format 'Aa': ");
    }

    unsigned short int intPosition[2];
    intPosition[0] = position[0] - 'A';
    intPosition[1] = position[1] - 'a';
    unsigned short int playerTileIndex = player.checkTiles(board.getTile(intPosition));
    if (!playerTileIndex){
        printMessage("You don't own that tile!");
        return false;
    }
    else{
        Word hWord;
        Word vWord;
    }
    return true;
}