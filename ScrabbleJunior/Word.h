#ifndef SCRABBLEJUNIOR_WORD_H
#define SCRABBLEJUNIOR_WORD_H

#include <iostream>
#include <vector>



typedef struct{
    bool covered = false;
}Letter;


class Word{
public:
    Word();
    Word(std::string word, unsigned short int start);
    bool inWord(unsigned short int pos);
    bool validMove(unsigned short int pos);
    void coverLetter(unsigned short int pos);
    bool completedWord();

private:
    std::string word;
    std::vector<bool> covered;
    unsigned short int start;                   // First letter position
    unsigned short int end;                     // Last letter position
};


#endif
