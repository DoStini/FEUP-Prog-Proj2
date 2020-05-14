#include <algorithm>
#include "Word.h"


Word::Word() = default;

Word::Word(std::string word, unsigned short int start){
    this->start = start;
    this->end = start + word.length() - 1;
    this -> word = word;

    for (int i = 0; i < word.length() ; ++i) {
        char letter;
        letter = word[i];
        letters.push_back(letter);
        covered.push_back(false);
    }
}

/**
 * Function to check if a tile is within a word
 *
 * @param position - Position of the corresponding tile
 * @return bool
 */
bool Word::inWord(unsigned short int position){
    return position >= start && position <= end;
}

/**
 * Checks if a move is valid
 *
 * @param position - Position in the board of the tile being played
 * @return bool
 */
bool Word::validMove(unsigned short int position){
    if (covered[position - start]){                         // Position is refering to the tile in the whole vertical axis
        return false;                                       // Is the position already occupied?
    }
	std::cout << "deededededede";
    // Checks if there is no uncovered letter before the current tile
    return std::find(covered.begin(), covered.begin() + (position - start), false) == covered.begin() + (position - start);
}

/**
 * Function to find a playable tile
 *
 * @return int - Index of the playable tile
 */
short int Word::findPlayable(){
    auto it = std::find(covered.begin(), covered.end(), false);
    return it != covered.end() ?  it - covered.begin() : -1;
}

/**
 * Return the letter in the specified position
 *
 * @param pos - position of the tile
 * @return
 */
char Word::getLetter(unsigned short int pos){
    return letters[pos];
}

/**
 * Checks if a word is completed by finding uncovered letters
 *
 * @return bool
 */
bool Word::completedWord(){
    return std::find(covered.begin(), covered.end(), false) == covered.end();
}

/**
 * Function to cover a letter (setting true to the covered vector in the corresponding position)
 *
 * @param position - Position of the tile in the board
 */
void Word::coverLetter(unsigned short int position){
    covered[position - start] = true;
}

/**
 * Check if a certain position corresponds to the first letter
 * Will be used to detect if we should paint the horizontal tile before that or not
 *
 * @param position
 * @return
 */
bool Word::isFirstLetter(unsigned short int position){
    return position - start == 0;
}