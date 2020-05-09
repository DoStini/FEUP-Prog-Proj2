#pragma once

#include "word.h"
#include<utility>
#include<vector>

typedef struct {
	std::vector<Word>::iterator iterator;
	bool invalid = false;
} WordsIterator;

class Board {
public:
	Board();
	~Board();

	std::string showBoard(bool color = true);
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
private:
	bool checkFit(Word word, unsigned short max);
	bool checkLegalDelete(std::pair<unsigned short, unsigned short> limits, unsigned position, bool vertical);
	WordsIterator checkWordOnBoard(Word word, Coordinate position, bool vertical);
	WordsIterator checkIfLegal(Word word, Coordinate position, bool vertical);
	void checkIntersections(Word word, Coordinate position, bool vertical, WordsIterator& result);
	void checkEdges(Word word, Coordinate position, bool vertical, WordsIterator& result);
	void writeOnArray(Word word, bool vertical, unsigned short position);
	void deleteOnArray(Word word, bool vertical, unsigned short position);
	void rewriteOnArray(bool vertical, std::pair<unsigned short, unsigned short> limits);
	char** copyLetters();

	std::pair<unsigned short, unsigned short> heightLimits;
	std::pair<unsigned short, unsigned short> widthLimits;
	std::pair<unsigned short, unsigned short> size;
	std::vector<Word> *hWords;
	std::vector<Word> *vWords;
	char** letters;
	int minLetters;
	int minSquares;
};