#pragma once

#include "word.h"
#include<utility>
#include<vector>

/**
 * Stores an iterator for a vector words, like a column of vWords or a row from hWords
 *		and a boolean indicating if that iterator is valid.
 */
typedef struct {
	std::vector<Word>::iterator iterator;
	bool invalid = false;
} WordsIterator;


/**
 * The Board class is a storage of rows and columns.
 * Each row/column is a storage of words.
 * Allows defining a minimum of letters and a minimum of squares (rows * columns)
 */
class Board {
public:
	Board();
	~Board();

	std::string showBoard(bool color = true);
	void showCenteredBoard(unsigned short xStart, unsigned short yStart);
	bool setHeight(unsigned short height);
	bool setWidth(unsigned short width);
	bool hasMinimumOfSquares();
	bool hasMinimumOfLetters();
	bool initializeWords();
	bool addWord(Word word, Coordinate position, bool vertical);
	short deleteWord(Word word, Coordinate position, bool vertical);
	int getNumberOfLetters();
	void saveBoard(std::string fileName);

	std::pair<unsigned short, unsigned short> getHeightLimits() { return heightLimits; }
	std::pair<unsigned short, unsigned short> getWidthLimits() { return widthLimits; }
	std::pair<unsigned short, unsigned short> getSize() { return size; }
	int getMinLetters() { return minLetters; }
	int getMinSquares() { return minSquares; }
private:
	bool checkFit(Word word, unsigned short max);
	bool checkLegalDelete(std::pair<unsigned short, unsigned short> limits, unsigned location, bool vertical);
	WordsIterator checkWordOnBoard(Word word, Coordinate position, bool vertical);
	WordsIterator checkIfLegal(Word word, Coordinate position, bool vertical);
	WordsIterator checkIntersections(Word word, Coordinate position, bool vertical);
	bool checkEdges(Word word, Coordinate position, bool vertical);
	void writeOnArray(Word word, bool vertical, unsigned short location);
	void deleteOnArray(Word word, bool vertical, unsigned short location);
	void rewriteOnArray(bool vertical, std::pair<unsigned short, unsigned short> limits);
	char** copyLetters();

	std::pair<unsigned short, unsigned short> heightLimits;
	std::pair<unsigned short, unsigned short> widthLimits;
	std::pair<unsigned short, unsigned short> size;

	/**
	 * Either hWords or vWords are arrays (1) of vectors (2) of words (3).
	 *
	 * Each array (1) contains N vectors (2), N representing the number of columns/rows.
	 * Each vector (2) contains M words, M representing the number of words in that specific column/row.
	 * This way, we can quickly access/find a specified word given a position [location, index]
	 *                              location -> Identifies a column if the word is vertical.
	 *										   Identifies a row if the word is horizontal.
	 *                              index ->	   Identifies the order of that word.
	 *
	 * Each word (3) contains valuable information about valid moves.
	*/
	std::vector<Word> *hWords, *vWords;
	char** letters;
	int minLetters;
	int minSquares;
};