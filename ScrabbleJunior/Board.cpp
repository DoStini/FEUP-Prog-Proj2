#include <iostream>
#include <fstream>
#include <sstream>
#include "Board.h"
#include "Word.h"

using std::ifstream, std::stringstream;

Board::Board() = default;

Board::Board(string fileName){

}

Board::~Board() {
    free(letters);
}

void Board::readBoard(string fileName) {
    ifstream f_in;
    f_in.open(fileName);

    if (!f_in.is_open()){
        std::cerr << "File not found!";
    }

    char sep;
    char position[2];
    string word;

    f_in >> vSize >> sep >> hSize;

    initWordVectors();

    unsigned short int verticalIdx;
    unsigned short int horizontalIdx;

    while (f_in){
        f_in >> position >> sep >> word;

        verticalIdx = (int) position[0] - (int) 'A';
        horizontalIdx = (int) position[1] - (int) 'a';

        writeOnArray(word, sep == 'V', verticalIdx, horizontalIdx);

        if (sep == 'V'){
            vWords[verticalIdx].push_back(Word(word, horizontalIdx));
        }
        else{
            vWords[horizontalIdx].push_back(Word(word, verticalIdx));
        }
    }
}

void Board::initArray() {
    letters = (char **) malloc(vSize * sizeof(char *));
    for (int v = 0; v < vSize; ++v) {
        letters[v] = (char *) malloc(hSize * sizeof(char));
        for (int h = 0; h < hSize; ++h) {
            letters[v][h] = 0;
        }
    }
}

void Board::writeOnArray(string word, bool vertical, unsigned short int vIdx, unsigned short int hIdx){
    for (int i = 0; i < word.length(); ++i) {
        letters[vIdx + i*vertical][hIdx + !vertical*(!vertical)] = word[i];                         // If vertical, changes vIdx, otherwise changes hIdx
    }
}

void Board::initWordVectors() {
    for (int i = 0; i < vSize; ++i) {
        vector<Word> vec = {};
        vWords.push_back(vec);
    }
    for (int j = 0; j < hSize; ++j) {
        vector<Word> vec = {};
        hWords.push_back(vec);
    }
}

char Board::readLetter(unsigned short int pos[2]) {
    return letters[pos[0]][pos[1]];
}