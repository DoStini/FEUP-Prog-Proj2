#include <iostream>
#include <algorithm>
#include "Player.h"


Player::Player() = default;

Player::Player(std::vector<char> &pot, std::string name){
    initTiles(pot);
    this->name = name;
}

void Player::initTiles(std::vector<char> &pot){
    unsigned short int index;

    for (int i = 0; i < 7; ++i) {
        index = rand()%pot.size();
        tiles.push_back(pot[i]);
        pot.erase(pot.begin() + i);
    }
}

void Player::showTiles() {
    for (int i = 0; i < tiles.size(); ++i) {
        std::cout << tiles[i] << ' ';
    }
}

short int Player::checkTiles(char letter){
    std::vector<char>::iterator it = std::find(tiles.begin(), tiles.end(), letter);
    bool temp = it != tiles.end();
    int temp2 = it - tiles.begin();
    return temp ? temp2 : -1;

    /*
    for (int i = 0; i < 7; ++i) {
        if (letter == tiles[i])
            return i;
    }
    return -1;
*/
}

void Player::addTile(char letter){
    tiles.push_back(letter);
}
void Player::removeTile(char letter){
    tiles.erase(std::find(tiles.begin(), tiles.end(), letter));
}

unsigned short int Player::getScore(){
    return score;
}

void Player::addPoints(unsigned short int points){
    score += points;
}

std::string Player::getName() {
    return name;
}
void Player::setName(std::string name) {
    this->name = name;
}

int Player::getX(){
    return pos.first;
}
int Player::getY(){
    return pos.second;
}
void Player::setX(int val){
    pos.first = val;
}
void Player::setY(int val){
    pos.second = val;
}