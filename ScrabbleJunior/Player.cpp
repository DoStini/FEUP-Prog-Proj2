#include <iostream>
#include <algorithm>
#include "Player.h"


Player::Player() = default;

Player::Player(std::vector<char> &pot, std::string name, std::vector<int> pos, ConsoleColors color){
    initTiles(pot);
    setName(name);
    setX(pos[0]);               // Graphical position in console
    setY(pos[1]);
    setColor(color);                // Graphical color
}


/**
 * Function to initialize player's pot
 * Couldn't use the class game to use game.getRandomTile() because Game.h already uses Player.h
 *
 * @param pot - game's pot
 */
void Player::initTiles(std::vector<char> &pot){
    unsigned short int index;

    for (int i = 0; i < 7; ++i) {
        index = rand()%pot.size();
        tiles.push_back(pot[index]);
        pot.erase(pot.begin() + index);
    }
}


/**
 * Function to show player's pot
 */
void Player::showTiles() {
    for (int i = 0; i < tiles.size(); ++i) {
        std::cout << tiles[i] << ' ';
    }
}


/**
 * Function to check if a player has a certain tile
 *
 * @param letter - the tile being searched for
 * @reutn short int - the index of that tile. Returns -1 if not found
 */
short int Player::checkTiles(char letter){
    auto it = std::find(tiles.begin(), tiles.end(), letter);

    return it != tiles.end() ? it - tiles.begin() : -1;
}

/**
 * @param letter - Adding letter to the player's pot
 */
void Player::addTile(char letter){
    tiles.push_back(letter);
}

/**
* @param letter - Removing letter from the player's pot
*/
void Player::removeTile(char letter){
    tiles.erase(std::find(tiles.begin(), tiles.end(), letter));
}

/**
 * @return unsigned short int - Returns the score of the player
 */
unsigned short int Player::getScore(){
    return score;
}

/**
 * @param points - Add x points to the player's score
 */
void Player::addPoints(unsigned short int points){
    score += points;
}

/**
 * @return string - Returns player's name
 */
std::string Player::getName() {
    return name;
}

/**
 * @param name - Setting player's name with param name
 */
void Player::setName(std::string name) {
    this->name = name;
}

/**
 * @return int - Returns X Graphical position
 */
int Player::getX(){
    return pos.first;
}

/**
* @return int - Returns Y Graphical position
*/
int Player::getY(){
    return pos.second;
}

/**
 * @param val - Set X Graphical position with val
 */
void Player::setX(int val){
    pos.first = val;
}

/**
* @param val - Set Y Graphical position with val
*/
void Player::setY(int val){
    pos.second = val;
}

/**
 * Set graphical name's color of player
 *
 * @param color
 */
void Player::setColor(ConsoleColors color) {
    this->color = color;
}
/**
 * Get graphical name's color of player
 */
ConsoleColors Player::getColor() {
    return color;
}