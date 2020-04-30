#include <algorithm>
#include "Word.h"


Word::Word() = default;

Word::Word(std::string word, unsigned short int start){
    this->start = start;
    this->end = start + word.length() - 1;
    this -> word = word;

    for (int i = 0; i < word.length() ; ++i) {

        covered.push_back(false);
    }
}

bool Word::inWord(unsigned short int position){
    if (position >= start && position <= end){
        return validMove(position);
    }
    else{
        return false;
    }
}

bool Word::validMove(unsigned short int position){
    if (covered[position]){
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

bool Word::completedWord(){
    return std::find(covered.begin(), covered.end(), false) == covered.end();
}


void Word::coverLetter(unsigned short int position){
    covered[position - start] = true;
}

