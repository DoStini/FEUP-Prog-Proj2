#pragma once

#include "word.h"
#include<utility>
#include<vector>


class Board {
public:
	bool setHeight(unsigned short height);
	bool setWidth(unsigned short width);
	bool checkFit(Word word, unsigned short max);
	bool checkIntersections(Word word, std::vector<Word> orientationWords);
	bool addHWord(Word word, unsigned short position);
	bool addVWord(Word word, unsigned short position);
	std::pair<unsigned short, unsigned short> getHeightLimits() { return heightLimits; }
	std::pair<unsigned short, unsigned short> getWidthLimits() { return widthLimits; }
	std::pair<unsigned short, unsigned short> getSize() { return size; }
private:
	std::pair<unsigned short, unsigned short> heightLimits = std::make_pair(2,20);
	std::pair<unsigned short, unsigned short> widthLimits = std::make_pair(2, 20);
	std::pair<unsigned short, unsigned short> size;
	typedef std::vector<Word>::iterator WordsIterator;
	std::vector<std::vector<Word>> hWords;
	std::vector<std::vector<Word>> vWords;

};