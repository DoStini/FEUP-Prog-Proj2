#include <iostream>
#include <fstream>
#include <sstream>
#include "Board.h"

using std::ifstream;
using std::stringstream;

Board::Board() = default;

Board::Board(string fileName){
    readBoard(fileName);
    showBoard();
}

Board::~Board() {
    for (int i = 0; i < vSize; ++i) {
        free(letters[i]);
    }
    free(letters);
}


void Board::readBoard(string fileName) {
    ifstream f_in;
    f_in.open(fileName);

    if (!f_in.is_open()){
        std::cerr << "File not found!";
        return;
    }

    char sep;
    char position[2];
    string word;

    f_in >> vSize >> sep >> hSize;

    unsigned short int verticalIdx;
    unsigned short int horizontalIdx;

    initArray();
    initWordVectors();
    int counter = 0;
    while (!f_in.eof()){
        f_in >> position >> sep >> word;

        verticalIdx = (int) position[0] - (int) 'A';
        horizontalIdx = (int) position[1] - (int) 'a';

        writeOnArray(word, sep == 'V', verticalIdx, horizontalIdx);
        counter++;
        if (sep == 'V'){
            vWords[horizontalIdx].push_back(Word(word, verticalIdx));
        }
        else{
            hWords[verticalIdx].push_back(Word(word, horizontalIdx));
        }
    }
}

Word *Board::findWord(unsigned short int index, unsigned short int charPos, bool vertical){
    if (vertical){
        for (int i = 0; i < vWords[index].size(); ++i) {
            if (vWords[index][i].inWord(charPos)){
                return &vWords[index][i];
            }
        }
    }
    else{
        for (int i = 0; i < hWords[index].size(); ++i) {
            if (hWords[index][i].inWord(charPos)) {
                return &hWords[index][i];
            }
        }
    }

    return NULL;
}

void Board::showBoard() {

    std::cout << "  ";
    for (unsigned short c = 0; c < hSize; c++) {
        std::cout << (char)(c + 'a') << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < vSize; ++i) {
        std::cout << (char)(i + 'A') << " ";
        for (int j = 0; j < hSize; ++j) {
            std::cout << letters[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Board::initArray() {
    letters = (char **) malloc(vSize * sizeof(char *));



    for (int v = 0; v < vSize; ++v) {
        letters[v] = (char *) malloc(hSize * sizeof(char));
        for (int h = 0; h < hSize; ++h) {
            letters[v][h] = ' ';
        }
    }
}

void Board::writeOnArray(string word, bool vertical, unsigned short int vIdx, unsigned short int hIdx){
    for (int i = 0; i < word.length(); ++i) {
        letters[vIdx + i*vertical][hIdx + i*!vertical] = word[i];                         // If vertical, changes vIdx, otherwise changes hIdx
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

char Board::getTile(unsigned short int pos[2]) {
    return letters[pos[0]][pos[1]];
}

unsigned short int Board::getHSize(){
    return hSize;
}
unsigned short int Board::getVSize(){
    return vSize;
}

bool Board::analyseMoves(Player &player){
    for (int i = 0; i < hSize; ++i) {
        for (int j = 0; j < hWords[i].size(); ++j) {
            Word cWord = hWords[i][j];
            short int idx = cWord.findPlayable();

            if (idx != -1 && player.checkTiles(cWord.getLetter(idx)) != -1){
                return true;
            }
        }
    }

    for (int i = 0; i < vSize; ++i) {
        for (int j = 0; j < vWords[i].size(); ++j) {
            Word cWord = vWords[i][j];
            short int idx = cWord.findPlayable();

            if (idx != -1 && player.checkTiles(cWord.getLetter(idx)) != -1){
                return true;
            }
        }
    }
    return false;
}
