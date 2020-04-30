

#include "Word.h"

Word::Word() = default;

Word::Word(std::string word, unsigned short int start){
    this->start = start;
    this->end = start + word.length() - 1;
    this -> word = word;

    for (int i = 0; i < word.length() ; ++i) {
        Letter letter;
        letter.letter = word[i];
        letters.push_back(letter);
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
    if (letters[position].covered){
        return false;                                       // Is the position already occupied?
    }
    for (int i = 0; i < position - start; ++i) {
        if (!letters[i].covered){
            return false;
        }
    }
    return true;
}

void Word::coverLetter(unsigned short int position){
    letters[position - start].covered = true;
}
