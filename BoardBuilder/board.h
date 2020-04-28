#pragma once

#include "word.h"
#include<utility>
#include<vector>


class Board {
public:
	bool setHeight(unsigned short height);
	bool setWidth(unsigned short width);
	bool initializeWords();
	bool addHWord(Word word, unsigned short position);
	bool addVWord(Word word, unsigned short position);
	std::pair<unsigned short, unsigned short> getHeightLimits() { return heightLimits; }
	std::pair<unsigned short, unsigned short> getWidthLimits() { return widthLimits; }
	std::pair<unsigned short, unsigned short> getSize() { return size; }
private:
	bool checkFit(Word word, unsigned short max);
	bool checkIntersections(Word word, std::vector<Word> orientationWords);

	std::pair<unsigned short, unsigned short> heightLimits = std::make_pair(2,20);
	std::pair<unsigned short, unsigned short> widthLimits = std::make_pair(2, 20);
	std::pair<unsigned short, unsigned short> size = std::make_pair(0,0);
	typedef std::vector<Word>::iterator WordsIterator;
	std::vector<Word> *hWords = (std::vector<Word>*) malloc (2 * sizeof(std::vector<Word>));
	std::vector<Word> *vWords = (std::vector<Word>*) malloc (2 * sizeof(std::vector<Word>));
};