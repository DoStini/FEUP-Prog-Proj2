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
    playerNameColors = {
            ConsoleColors::RedFore,
            ConsoleColors::YellowFore,
            ConsoleColors::BlueFore,
            ConsoleColors::GreenFore
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


/**
 * This function is used to control the game flow
 */
bool Game::gameManager() {
    while (1){
        for (int i = 0; i < numPlayers; ++i) {
            for (int j = 0; j < 2; ++j) {                           // Two turns per player

                if (numTiles == limit) return true;                 // Reached the end of the game, every piece has been used
                if (boardPtr->analyseMoves(players[i])){        // Checks if the player can play anything
                    bool valid = true;
                    while (valid){
                        valid = !playerMove(players[i]);        // Loop until a valid move has been given
                    }
                }
                else{
                    changeTile(players[i]);
                    break;
                }
            }
        }
    }
}

/**
 * Function to check who is(are) the winner(s), after the game ends
 */
void Game::checkWinner(){
    std::sort(players.begin(), players.end(), [](Player p1, Player p2){ return p1.getScore() > p2.getScore();});
                                                                    // Sorting by score
    short int max = players[0].getScore();                          // First element will be the best player
    bool tie = false;

    for (int i = 1; i < players.size(); ++i) {                      // Loop until you find someone with a lower score
        if (players[i].getScore() == max){
            tie = true;
        }
        else{
        players.resize(i+1);                                // Deleting the loser players
            break;                                                   // New vector will contain only the winner(s)
        }
    }

    clearScreen(XBEGMENU - 20, YBEG - 4);

    if (!tie){
        std::cout << "The winner of the game is " << players[0].getName() << " with " << players[0].getScore() << " points!";
    }
    else{
        std::cout << "The winners of the game are ";
        for (int i = 0; i < players.size(); ++i) {
            std::cout << players[i].getName();
            if (i != players.size() - 1){
                std::cout << ", ";
            }
        }
        std::cout << " with " << players[0].getScore() << " points!";
    }

    gotoxy(XBEGMENU - 20, YBEG - 3);
    waitForKey();

    std::vector<Winner> winners;
    getNameScore(players, winners);                         // Converting class player to struct of name and score

    checkScores(winners, "scoreboard.win");           // Check if the winner enters the scoreboard
}


/**
 * Function to convert player objects in structs of name and score
 *
 * @param players - the vector containg a(the) player object(s)
 * @param out - the vector containing clean Winner struct(s) that will receive player.name and player.score
 */
void Game::getNameScore(std::vector<Player> &players, std::vector<Winner> &out){
    for (int i = 0; i < players.size(); ++i) {
        Winner p;
        std::strncpy(p.name, players[i].getName().c_str(), sizeof(p.name));
        p.score = players[i].getScore();
        out.push_back(p);
    }
}


/**
 * Function to initialize players objects
 *
 * @param numPlayers - The number of players
 * @param playerNames - Vector containing player names
 */
void Game::initPlayers(unsigned short numPlayers, std::vector<std::string> playerNames) {
    players.reserve(numPlayers);
    Player player;
    for (int i = 0; i < numPlayers; ++i) {
        player = Player(pot, playerNames[i], playerPositions[i], playerNameColors[i]);
        players.push_back(player);
        placePlayer(player);                             // Placing player in the screen
    }


}


/**
 * Function to add all the tiles necessary to the game pot
 * Takes every character from the pre-made board Array and adds to a pot vector
 */
void Game::initPot() {
    char temp;

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


/**
 * Function to retrieve a random tile (letter) from the game pot
 *
 * @return char - The tile chosen randomly
 */
char Game::getRandomTile() {
    unsigned short int index = rand()%pot.size();
    char tile = pot[index];
    pot.erase(pot.begin() + index);
    return tile;
}


/**
 * Function to read a position from the player
 *
 * @param intPosition - The position chosen by the player. Will be return through this
 * @param player - Current player
 */
bool Game::inputMove(unsigned short int intPosition[2], Player &player){
    clearScreen(XBEGMENU + 5, YBEG + boardPtr->getVSize() * YSPACING + 10);
    std::cout << player.getName() << ", you're up!";

    gotoxy(XBEGMENU-10, YBEG + boardPtr->getVSize() * YSPACING + 11);
    std::cout << "Enter the position on the board in the format 'Aa': ";

    std::string position;
    while(1){
        if (checkInput(position, '\n') && position.length() == 2) {                 // Checking if string given contains only 2 letters Aa
            if (position[0] >= 'A' && position[0] <= ('A' + boardPtr->getVSize() ) &&            // Checks if is inside the board limits ('A' = 0, 'A' + vSize = maxIndex)
                position[1] >= 'a' && position[1] <= ('a' + boardPtr->getHSize())) {
                break;
            }
        }

        clearScreen(XBEGMENU, YBEG + boardPtr->getVSize() * YSPACING + 12);
        std::cout << "Your input was invalid.";

        gotoxy(XBEGMENU - 15, YBEG + boardPtr->getVSize() * YSPACING + 13);
        std::cout << "Re-enter the position on the board in the format 'Aa': ";
    }

    intPosition[0] = position[0] - 'A';
    intPosition[1] = position[1] - 'a';

    short int playerTileIndex = player.checkTiles(boardPtr->getTile(intPosition));        // Checking if player contains chosen tile
    if (playerTileIndex == -1){
        clearScreen(XBEGMENU + 3, YBEG + boardPtr->getVSize() * YSPACING + 12);
        std::cout << "You don't own that tile!";

        gotoxy(XBEGMENU, YBEG + boardPtr->getVSize() * YSPACING + 13);
        waitForKey();
        return false;
    }
    else{
        return true;
    }
}


/**
 * Function to control a player move
 *
 * @param player - the current player
 * @return if a valid move was made
 */
bool Game::playerMove(Player &player) {
    unsigned short int pos[2];
    if (!inputMove(pos, player)){
        return false;
    }
    else{
        Word *hWordPtr = boardPtr->findWord(pos[0], pos[1], false);         // Finds horizontal word in that position
        Word *vWordPtr = boardPtr->findWord(pos[1], pos[0], true);          // Finds vertical word in that position

        bool valid = false;

        valid = (hWordPtr != NULL && hWordPtr->validMove(pos[1])) || (vWordPtr != NULL && vWordPtr->validMove(pos[0]));

        // Evaluates if in one of the horizontal/vertical word the tile chosen by the player represents a valid move

        if (valid){
            gotValidMove(player, pos, boardPtr->getTile(pos), hWordPtr, vWordPtr);
        }
        else{
            clearScreen(XBEGMENU + 5, YBEG + boardPtr->getVSize() * YSPACING + 12);
            std::cout << "That move is illegal!";

            gotoxy(XBEGMENU + 5, YBEG + boardPtr->getVSize() * YSPACING + 13);
            waitForKey();
            return false;
        }
    }
    return true;
}


/**
 * Function to perform a series of operations that occur when a valid move is made
 * Things done:
 *      - Increasing numTiles (numTiles is the counter of tiles filled)
 *      - Covering the desired letter in both vertical and horizontal words (if exist)
 *      - Add points to player
 *      - Color the tile in the console
 *      - Adding a tile to the player's pot
 *
 * @param player - the current player
 * @param pos - Position in board chosen by the player
 * @param letter - tile chosen
 * @param hWordPtr - Pointer to horizontal word
 * @param vWordPtr - Pointer to vertical word
 * @return if a valid move was made
 */
void Game::gotValidMove(Player &player, unsigned short int pos[2], char letter, Word *hWordPtr, Word *vWordPtr){
    numTiles++;                                                         // Counter to find the end of the game, used in gameManager
    if(hWordPtr != NULL){                                               // Counts the number of tiles played
        hWordPtr->coverLetter(pos[1]);
        player.addPoints(hWordPtr->completedWord());

        if (!hWordPtr->isFirstLetter(pos[1])){
            for (int i = 1; i < XSPACING; ++i) {
                replaceVisualChar(boardPtr->getStart() + XSPACING * (pos[1] + 1) - i, YBEG + YSPACING * (pos[0] + 1), ' ', ConsoleColors::RedFore, ConsoleColors::YellowBack);
            }
            // If it's not the first letter, paints the one behind him aswell, painting XPACING - 1 times
        }
    }
    if(vWordPtr != NULL){
        vWordPtr->coverLetter(pos[0]);                             // Covers the letter in the vertical/horizontal word
        player.addPoints(vWordPtr->completedWord());                    // Checks if the vertical/horizontal word has been completed

        if (!vWordPtr->isFirstLetter(pos[0])){
            for (int i = 1; i < YSPACING; ++i) {
                replaceVisualChar(boardPtr->getStart() + XSPACING * (pos[1] + 1), YBEG + YSPACING * (pos[0] + 1) - i, ' ', ConsoleColors::RedFore, ConsoleColors::YellowBack);
            }
            // If it's not the first letter, paints the one behind him aswell, painting YPACING - 1 times
        }
    }                                                                   // Using once again true and false as 1/0 to add to the score

    player.removeTile(letter);                                          // Removing letter from the player's pot

    replaceVisualChar(boardPtr->getStart() + XSPACING * (pos[1] + 1), YBEG + YSPACING * (pos[0] + 1), letter, ConsoleColors::RedFore, ConsoleColors::YellowBack);
    // Changing color of the chosen tile



    if (pot.size() > 0) {
        char newTile = getRandomTile();
        player.addTile(newTile);
    }

    placePlayer(player);
}


/**
 * When a player has no available moves, this is called to make the player choose a tile to trade for a random one out of the game's pot
 *
 * @param player - The current player
 */
void Game::changeTile(Player &player){
    clearScreen(XBEGMENU, YBEG + boardPtr->getVSize() * YSPACING + 12);
    std::cout << "You have no moves left...";

    if (pot.size() == 0){                                              // If the pot is clean, no trade can be done
        gotoxy(XBEGMENU - 15, YBEG + boardPtr->getVSize() * YSPACING + 13);
        std::cout << "Skipping player";

        gotoxy(XBEGMENU - 15, YBEG + boardPtr->getVSize() * YSPACING + 13);
        waitForKey();
    }
    else{
        gotoxy(XBEGMENU - 15, YBEG + boardPtr->getVSize() * YSPACING + 13);
        std::cout << "Choose one of your tiles to trade: ";
        player.showTiles();

        while (1){
            char in;
            std::cin >> in;
            if (player.checkTiles(toupper(in)) != -1){              // Checks if the given tile is in the player's possession
                player.removeTile(toupper(in));                     // Removes tile from the player's deck
                player.addTile(getRandomTile());              // Adds a new random tile
                pot.push_back(in);                                  // Returns the player's tile to the game's pot
                waitForKey();
                placePlayer(player);                            // Update player's information

                break;
            }
            else{
                gotoxy(XBEGMENU - 15, YBEG + boardPtr->getVSize() * YSPACING + 14);
                std::cout << "You don't have that tile, re-enter.";
            }
        }
    }
}





