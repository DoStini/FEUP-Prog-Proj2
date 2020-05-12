#include <iostream>
#include <cstring>
#include "Game.h"


Game::Game(unsigned short int numPlayers, std::vector<std::string> playerNames, Board *boardPtr){
    this -> numPlayers = numPlayers;
    this -> boardPtr = boardPtr;
    playerPositions = {
            {XBEGMENU, YBEG - 4},
            {XBEGMENU, YBEG + 5 + boardPtr->getVSize() * YSPACING},
            {boardPtr->getStart() - 40, YBEG + (boardPtr->getVSize() * YSPACING)/2},
            {boardPtr->getStart() + boardPtr->getHSize() * XSPACING + 10, YBEG + (boardPtr->getVSize() * YSPACING)/2}
    };
    initPot();
    limit = pot.size();

    if (numPlayers * 7 > limit){
        clearScreen(XBEGMENU - 15, YBEG - 4);
        std::cout << "Number of players is excessive over number of tiles in the board.";
        gotoxy(XBEGMENU, YBEG - 3);
        waitForKey();
    }
    else{
        initPlayers(numPlayers, playerNames);

        gameManager();
        checkWinner();
    }
}

bool Game::gameManager() {
    while (1){                                          // If number of players exceed nuber of tiles
        for (int i = 0; i < numPlayers; ++i) {
            for (int j = 0; j < 2; ++j) {

                if (numTiles == limit) return true;

                if (boardPtr->analyseMoves(players[i])){
                    bool valid = true;
                    while (valid){
                        valid = !playerMove(players[i]);
                    }
                }
                else{
                    changeTile(players[i]);
                    waitForKey();
                    break;
                }
            }
        }
    }
}

void Game::checkWinner(){

    std::sort(players.begin(), players.end(), [](Player p1, Player p2){ return p1.getScore() < p2.getScore();});

    short int max = players[0].getScore();
    bool tie = false;

    for (int i = 1; i < players.size(); ++i) {
        if (players[i].getScore() == max){
            tie = true;
        }
        else{
            players.resize((i+1) * sizeof(Player)); // deleting
            break;
        }
    }

    clearScreen(XBEGMENU - 20, YBEG - 4);

    if (!tie){
        std::cout << "The winner of the game is " << players[0].getName() << " with " << players[0].getScore() << " points!" << std::endl;
    }
    else{
        std::cout << "The winners of the game are ";
        for (int i = 0; i < players.size(); ++i) {
            std::cout << players[i].getName();
            if (i != players.size() - 1){
                std::cout << ", ";
            }
        }
        std::cout << " with " << players[0].getScore() << " points!" << std::endl;
    }

    std::vector<Winner> winners;
    getNameScore(players, winners);

    checkScores(winners, "scoreboard.win");
}

void Game::getNameScore(std::vector<Player> &players, std::vector<Winner> &out){
    for (int i = 0; i < players.size(); ++i) {
        Winner p;
        std::strncpy(p.name, players[i].getName().c_str(), sizeof(p.name));
        p.score = players[i].getScore();
        out.push_back(p);
    }
}

void Game::initPlayers(unsigned short numPlayers, std::vector<std::string> playerNames) {
    players.reserve(numPlayers);
    Player player;
    for (int i = 0; i < numPlayers; ++i) {
        player = Player(pot, playerNames[i]);
        players.push_back(player);
        players[i].setX(playerPositions[i][0]);
        players[i].setY(playerPositions[i][1]);
        placePlayer(players[i]);
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
    clearScreen(XBEGMENU + 5, YBEG + boardPtr->getVSize() * YSPACING + 10);
    std::cout << player.getName() << ", you're up!";
    gotoxy(XBEGMENU-10, YBEG + boardPtr->getVSize() * YSPACING + 11);
    std::cout << "Enter the position on the board in the format 'Aa': ";

    std::string position;
    while(1){
        if (checkInput(position, '\n') && position.length() == 2) {
            if (position[0] >= 'A' && position[0] <= ('A' + boardPtr->getVSize() ) &&
                position[1] >= 'a' && position[1] <= ('a' + boardPtr->getHSize())) {
                break;
            }
        }
        clearScreen(XBEGMENU, YBEG + boardPtr->getVSize() * YSPACING + 11);
        std::cout << "Your input was invalid.";
        gotoxy(XBEGMENU - 15, YBEG + boardPtr->getVSize() * YSPACING + 12);
        std::cout << "Re-enter the position on the board in the format 'Aa': ";
    }

    intPosition[0] = position[0] - 'A';
    intPosition[1] = position[1] - 'a';

    short int playerTileIndex = player.checkTiles(boardPtr->getTile(intPosition));
    if (playerTileIndex == -1){
        clearScreen(XBEGMENU + 5, YBEG + boardPtr->getVSize() * YSPACING + 11);
        std::cout << "You don't own that tile!";
        gotoxy(XBEGMENU-15, YBEG + boardPtr->getVSize() * YSPACING + 12);
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
    numTiles++;
    if(hWordPtr != NULL){
        hWordPtr->coverLetter(pos[1]);
        player.addPoints(hWordPtr->completedWord());
    }
    if(vWordPtr != NULL){
        vWordPtr->coverLetter(pos[0]);
        player.addPoints(vWordPtr->completedWord());
    }

    player.removeTile(letter);

    replaceVisualChar(boardPtr->getStart() + XSPACING * (pos[1] + 1), YBEG + YSPACING * (pos[0] + 1), letter, RED, BROWN);


    if (pot.size() > 0) {
        char newTile = getRandomTile();
        player.addTile(newTile);
    }

    placePlayer(player);

}

void Game::changeTile(Player &player){
    std:: cout << "You have no moves left..." << std::endl;
    std::cout << "Choose one of your tiles to trade." << std::endl;
    player.showTiles();
    char in;
    getChar(in);
    while (1){
        if (player.checkTiles(toupper(in))){
            player.removeTile(toupper(in));
            player.addTile(getRandomTile());
            waitForKey();
            break;
        }
        else{
            std::cout << "You don't have that tile, re-enter." << std::endl;
        }
    }
}





