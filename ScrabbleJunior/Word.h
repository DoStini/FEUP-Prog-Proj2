#ifndef SCRABBLEJUNIOR_WORD_H
#define SCRABBLEJUNIOR_WORD_H

#include <iostream>
#include <vector>



typedef struct Letter{
    char letter = 0;
    bool covered = false;
};


class Word{
public:
    Word();
    Word(std::string word, unsigned short int start);
    bool inWord(unsigned short int pos);
    bool validMove(unsigned short int pos);
    void coverLetter(unsigned short int pos);

private:
    std::string word;
    std::vector<Letter> letters;
    unsigned short int start;                   // First letter position
    unsigned short int end;                     // Last letter position
};


#endif
