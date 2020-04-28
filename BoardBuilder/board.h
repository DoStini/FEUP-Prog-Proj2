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

	void showBoard();
	bool setHeight(unsigned short height);
	bool setWidth(unsigned short width);
	bool initializeWords();
	bool addWord(Word word, unsigned short position, char orientation);

	std::pair<unsigned short, unsigned short> getHeightLimits() { return heightLimits; }
	std::pair<unsigned short, unsigned short> getWidthLimits() { return widthLimits; }
	std::pair<unsigned short, unsigned short> getSize() { return size; }
private:
	bool checkFit(Word word, unsigned short max);
	WordsIterator checkIntersections(Word word, std::vector<Word>& orientationWords);
	void writeOnArray(Word word, bool vertical, unsigned short position);

	std::pair<unsigned short, unsigned short> heightLimits;
	std::pair<unsigned short, unsigned short> widthLimits;
	std::pair<unsigned short, unsigned short> size;
	std::vector<Word> *hWords;
	std::vector<Word> *vWords;
	char** letters;
};