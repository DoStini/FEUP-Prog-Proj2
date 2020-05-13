#include <iostream>
#include <algorithm>
#include "Player.h"


Player::Player() = default;

Player::Player(std::vector<char> &pot, std::string name){
    initTiles(pot);
    setName(name);
}

void Player::initTiles(std::vector<char> &pot){

    /**
     * Function to initialize player's pot
     * Couldn't use the class game to use game.getRandomTile() because Game.h already uses Player.h
     *
     * @param pot - game's pot
     */

    unsigned short int index;

    for (int i = 0; i < 7; ++i) {
        index = rand()%pot.size();
        tiles.push_back(pot[index]);
        pot.erase(pot.begin() + index);
    }
}

void Player::showTiles() {

    /**
     * Function to show player's pot
     */

    for (int i = 0; i < tiles.size(); ++i) {
        std::cout << tiles[i] << ' ';
    }
}

short int Player::checkTiles(char letter){

    /**
     * Function to check if a player has a certain tile
     *
     * @param letter - the tile being searched for
     * @reutn short int - the index of that tile. Returns -1 if not found
     */

    auto it = std::find(tiles.begin(), tiles.end(), letter);

    return it != tiles.end() ? it - tiles.begin() : -1;

}

void Player::addTile(char letter){
    /**
     * @param letter - Adding letter to the player's pot
     */
    tiles.push_back(letter);
}
void Player::removeTile(char letter){
    /**
    * @param letter - Removing letter from the player's pot
    */
    tiles.erase(std::find(tiles.begin(), tiles.end(), letter));
}

unsigned short int Player::getScore(){
    /**
     * @return unsigned short int - Returns the score of the player
     */
    return score;
}

void Player::addPoints(unsigned short int points){
    /**
     * @param points - Add x points to the player's score
     */
    score += points;
}

std::string Player::getName() {
    /**
     * @return string - Returns player's name
     */
    return name;
}
void Player::setName(std::string name) {
    /**
     * @param name - Setting player's name with param name
     */
    this->name = name;
}

int Player::getX(){
    /**
     * @return int - Returns X Graphical position
     */
    return pos.first;
}
int Player::getY(){
    /**
    * @return int - Returns Y Graphical position
    */
    return pos.second;
}
void Player::setX(int val){
    /**
     * @param val - Set X Graphical position with val
     */
    pos.first = val;
}
void Player::setY(int val){
    /**
    * @param val - Set Y Graphical position with val
    */
    pos.second = val;
}