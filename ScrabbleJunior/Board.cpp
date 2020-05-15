#include <iostream>
#include <fstream>
#include <sstream>
#include "Board.h"

using std::ifstream;
using std::stringstream;

Board::Board() = default;

Board::Board(std::string fileName){
    readBoard(fileName);
    showBoard();
}

Board::~Board() {
    for (int i = 0; i < vSize; ++i) {
        free(letters[i]);
    }
    free(letters);
}


/**
* Function to read the board
*
* @param fileName - Name of file to be read.
*/
void Board::readBoard(std::string fileName) {

    ifstream f_in;
    f_in.open(fileName);

    if (!f_in.is_open()){
        std::cerr << "File not found!";
        return;
    }

    char sep;
    char position[2];
    std::string word;

    f_in >> vSize >> sep >> hSize;

    unsigned short int verticalIdx;
    unsigned short int horizontalIdx;

    initArray();                                                                // Initializing our board, containing all letters
initWordVectors();                                                              // Initializing our words containers

    int counter = 0;
    while (f_in.peek() != '#'){
        f_in >> position[0] >> position[1] >> sep >> word;                      // Input is given as "Aa"

        verticalIdx = (int) position[0] - (int) 'A';                            // vertical index will be A converted to integer, counting 0 as char A
        horizontalIdx = (int) position[1] - (int) 'a';                          // same for horizontal index but with "a"

        writeOnArray(word, sep == 'V', verticalIdx, horizontalIdx);     // Writing word on graphical board
        counter++;
        if (sep == 'V'){
            Word temp(word, verticalIdx);
            vWords[horizontalIdx].push_back(temp);
        }
        else{
            hWords[verticalIdx].push_back(Word(word, horizontalIdx));
        }
        f_in.get();
    }
    f_in.close();
}


    /**
    * Comment relating to hWords and vWords
    *
    * It is a vector (1) of vectors (2) of words (3).
    *
    * Each vector (1) contains N vectors (2), N representing the number of columns/rows.
    * Each vector (2) contains N words, N representing the number of words in that specific column/row.
    * This way, we can quickly access/find a specified word give a position [v, h]
    *                               v -> Identifies row / position in column
    *                              h -> Identifies position in row / column
    *                Depending on the orientation of the word we're looking for (horizontally / vertically)
    *
    * Each word (3) contains valuable information about valid moves.
    */


/**
* Function to check and return if a chosen position is within any word
*
* @param index - The column/row where the word might be located
* @param charPos - The position given: related to the position of the character inside index's column/row
*
* @return Word * - Returns the pointer to the word if found. Otherwise returns a Null pointer
*/

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


/**
 * Function to show the board
 */
void Board::showBoard() {
    unsigned short int center = XBEGMENU + 13;
    this->start = center - (hSize * XSPACING) / 2;

    clearScreen(start, YBEG);

    setColor(ConsoleColors::BlackFore, ConsoleColors::WhiteBack);
    for(int space = 0; space < XSPACING; space++) std::cout << ' ';

    for (unsigned short c = 0; c < hSize; c++) {
        std::cout << (char)(c + 'a');
        for(int space = 0; space < XSPACING-1; space++) std::cout << ' ';
    }

    for (int i = 0; i < vSize; ++i) {
        gotoxy(start, YBEG + YSPACING * (i + 1));
        std::cout << (char)(i + 'A');
        setColor(ConsoleColors::WhiteFore, ConsoleColors::BlackBack);
        for (int j = 0; j < hSize; ++j) {
            for(int space = 0; space < XSPACING-1; space++) std::cout << ' ';
            std::cout << letters[i][j];
        }
        setColor(ConsoleColors::BlackFore, ConsoleColors::WhiteBack);
        std::cout << (char)(i + 'A');
    }
    gotoxy(start, YBEG + YSPACING * (vSize + 1));
    for(int space = 0; space < XSPACING; space++) std::cout << ' ';
    for (unsigned short c = 0; c < hSize; c++) {
        std::cout << (char)(c + 'a');
        for(int space = 0; space < XSPACING-1; space++) std::cout << ' ';
    }
    setColor(ConsoleColors::WhiteFore, ConsoleColors::BlackBack);       // Normalizing color
}


/**
* Function to initialize our graphical board array
*/
void Board::initArray() {
    letters = (char **) malloc(vSize * sizeof(char *));

    for (int v = 0; v < vSize; ++v) {
        letters[v] = (char *) malloc(hSize * sizeof(char));
        for (int h = 0; h < hSize; ++h) {
            letters[v][h] = ' ';
        }
    }
}


/**
    * Function to write a character on graphical board
    *
    * @param word - The word to be written on the board
    * @param vertical - If the word is going to be written vertically or horizontally
    * @param vIdx - Position to begin writing
    * @param hIdx - Position to begin writing
    */
void Board::writeOnArray(std::string word, bool vertical, unsigned short int vIdx, unsigned short int hIdx){
    for (int i = 0; i < word.length(); ++i) {
        letters[vIdx + i*vertical][hIdx + i*!vertical] = word[i];                 // If vertical, changes vIdx, otherwise changes hIdx
                                                                                  // Using boolean as 0 and 1 integers
    }
}


/**
  * Function to initialize both hWords and vWords with a prefixed size to avoid segmentation errors
*/
void Board::initWordVectors() {
    for (int i = 0; i < hSize; ++i) {
        std::vector<Word> vec = {};
        vWords.push_back(vec);
    }
    for (int j = 0; j < vSize; ++j) {
        std::vector<Word> vec = {};
        hWords.push_back(vec);
    }
}


/**
* Function to get a character from the board
*
* @param word - The word to be written on the board
* @return char - The letter of that position
*/
char Board::getTile(unsigned short int pos[2]) {
    return letters[pos[0]][pos[1]];
}


/**
 * @return hSize - Horizontal Size
 */
unsigned short int Board::getHSize(){
    return hSize;
}


/**
* @return vSize - Vertical Size
 */
unsigned short int Board::getVSize(){
    return vSize;
}


/**
  * A function to analyse if there are any moves available to be played.
  * Checks every possible word, finds a valid letter to be played and checks if player has it.
  * Stops iteration as soon as he finds a valid move
  *
  * @param player - The player being evaluated
  * @return bool - The existence of a valid move
*/
bool Board::analyseMoves(Player &player){
    for (int c = 0; c < 2; ++c) {                                            // Runs 2 times
        for (int i = 0; i < (c == 0 ? vSize : hSize); ++i) {                 // One for finding vertical word (c = 0) and another for finding horizontal word (c = 1)
            for (int j = 0; j < (c == 0 ? hWords[i].size() : vWords[i].size()); ++j) {
                Word *cWord = (c == 0 ? &hWords[i][j] : &vWords[i][j]);      // If c == 1, selects according to the correspending type of word
                short int idx = cWord->findPlayable();                       // Returns -1 if there's no possible move in that word

                if (idx != -1 && player.checkTiles(cWord->getLetter(idx)) != -1){
                    return true;                                             // Checks if the given valid letter is in player's deck
                }
            }
        }
    }
    /*

    for (int i = 0; i < hSize; ++i) {
        for (int j = 0; j < vWords[i].size(); ++j) {
            Word cWord = vWords[i][j];
            short int idx = cWord.findPlayable();

            if (idx != -1 && player.checkTiles(cWord.getLetter(idx)) != -1){
                return true;
            }
        }
    }

     */

    return false;
}

/**
* @return start - Graphical variable indicating the initial horizontal position of the board.
* Used to center text with board.
*/
unsigned short int Board::getStart(){
    return start;
}
