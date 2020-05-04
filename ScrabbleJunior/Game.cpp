#include <iostream>
#include "Game.h"

short int XBEG = 2;
short int YBEG = 1;



Game::Game(unsigned short int numPlayers, Board *boardPtr){
    this -> numPlayers = numPlayers;
    this -> boardPtr = boardPtr;
    initPot();
    initPlayers(numPlayers);
    std::cout << std::endl << std::endl;

    gameManager();

}

void Game::gameManager() {
    while (1){
        for (int i = 0; i < numPlayers; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (boardPtr->analyseMoves(players[i])){
                    bool valid = true;
                    while (valid){
                        valid = !playerMove(players[i]);
                    }
                }
                else{
                    std:: cout << "You have no moves left..." << std::endl;
                    waitForKey();
                    break;
                }
            }
        }
    }
}


void Game::initPlayers(unsigned short numPlayers) {
    players.reserve(numPlayers);
    Player player;
    string name;
    for (int i = 0; i < numPlayers; ++i) {
        printMessage("Please insert player's name: ", "");
        while (!checkInput(name)){
            printMessage("Invalid, re-enter: ", "");
        }
        player = Player(pot, name);
        players.push_back(player);
    }
}

void Game::initPot() {
    char temp;
    int temp2;
    unsigned short int pos[2];
    for (int i = 0; i < boardPtr->getVSize(); ++i) {
        pos[0] = i;
        for (int j = 0; j < boardPtr->getHSize(); ++j) {
            pos[1] = j;
            temp = boardPtr->getTile(pos);
            if (temp != ' '){
                pot.push_back(temp);
            }
        }
    }
}

char Game::getRandomTile() {
    unsigned short int index = rand()%pot.size();
    char tile = pot[index];
    pot.erase(pot.begin() + index);
    return tile;
}

//void Game::inputMove(int &intPosition){

//}

bool Game::inputMove(unsigned short int intPosition[2], Player &player){
    clearScreen(0, YBEG + boardPtr->getVSize() + 2);
    std::cout << player.getName() << "'s score: " << player.getScore() << std::endl << "This is your board: ";
    player.showTiles();
    std::cout << "Enter the position on the boardPtr in the format 'Aa': ";

    string position;
    while(1){
        if (checkInput(position, '\n') && position.length() == 2) {
            if (position[0] >= 'A' && position[0] <= ('A' + boardPtr->getVSize() ) &&
                position[1] >= 'a' && position[1] <= ('a' + boardPtr->getHSize())) {
                break;
            }
        }
        printMessage("Your input was invalid.");
        printMessage("Re-enter the position on the board in the format 'Aa': ");
    }

    intPosition[0] = position[0] - 'A';
    intPosition[1] = position[1] - 'a';

    short int playerTileIndex = player.checkTiles(boardPtr->getTile(intPosition));
    if (playerTileIndex == -1){
        printMessage("You don't own that tile!");
        waitForKey();
        return false;
    }
    else{
        return true;
    }
}

bool Game::playerMove(Player &player) {                     // Maybe change later to short int (we have array of players)
    unsigned short int pos[2];
    if (!inputMove(pos, player)){
        return false;
    }
    else{
        Word *hWordPtr = boardPtr->findWord(pos[0], pos[1], false);
        Word *vWordPtr = boardPtr->findWord(pos[1], pos[0], true);


        bool valid = false;

        valid = (hWordPtr != NULL && hWordPtr->validMove(pos[1])) || (vWordPtr != NULL && vWordPtr->validMove(pos[0]));

        if (valid){
            gotValidMove(player, pos, boardPtr->getTile(pos), hWordPtr, vWordPtr);
        }
        else{
            std::cout << "That move is illegal!" << std::endl;
            waitForKey();
            return false;
        }
    }
    return true;
}

void Game::gotValidMove(Player &player, unsigned short int pos[2], char letter, Word *hWordPtr, Word *vWordPtr){
    if(hWordPtr != NULL){
        hWordPtr->coverLetter(pos[1]);
        player.addPoints(hWordPtr->completedWord());
    }
    if(vWordPtr != NULL){
        vWordPtr->coverLetter(pos[0]);
        player.addPoints(vWordPtr->completedWord());
    }
    char newTile = getRandomTile();
    player.removeTile(letter);
    player.addTile(newTile);
    replaceVisualChar((XBEG + 2*pos[1]), (YBEG + pos[0]), letter, RED, BROWN);
}


