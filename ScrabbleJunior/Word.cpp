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

bool Word::inWord(unsigned short int position){
    if (position >= start && position <= end){
        return true;
        // probably wrong return validMove(position);
    }
    else{
        return false;
    }
}

bool Word::validMove(unsigned short int position){
    if (covered[position - start]){   // missing - start
        return false;                                       // Is the position already occupied?
    }

    return std::find(covered.begin(), covered.begin() + position - start, false) == covered.begin() + position - start;
    /*
    for (int i = 0; i < position - start; ++i) {
        if (!covered[i]){
            return false;
        }
    }
    return true;
*/
}

int Word::findPlayable(){
    std::vector<bool>::iterator it = std::find(covered.begin(), covered.end(), false);
    return it != covered.end() ? it - covered.begin() : -1;
}

char Word::getLetter(unsigned short int pos){
    return letters[pos];
}

bool Word::completedWord(){
    return std::find(covered.begin(), covered.end(), false) == covered.end();
}


void Word::coverLetter(unsigned short int position){
    covered[position - start] = true;
}