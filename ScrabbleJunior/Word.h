#ifndef SCRABBLEJUNIOR_WORD_H
#define SCRABBLEJUNIOR_WORD_H

#include <iostream>
#include <vector>


/*
typedef struct{
    char letter;
    bool covered = false;
}Letter;
*/

class Word{
public:
    Word();
    Word(std::string word, unsigned short int start);
    bool inWord(unsigned short int pos);
    bool validMove(unsigned short int pos);
    short int findPlayable();
    char getLetter(unsigned short int pos);
    void coverLetter(unsigned short int pos);
    bool completedWord();
    bool isFirstLetter(unsigned short int pos);

private:
    std::string word;
    std::vector<bool> covered;
    std::vector<char> letters;
    unsigned short int start;                   // First letter position
    unsigned short int end;                     // Last letter position
};


#endif
