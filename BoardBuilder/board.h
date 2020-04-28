#pragma once

#include "word.h"
#include<utility>
#include<vector>


class Board {
public:
	Board();
	~Board();

	void showBoard();
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
	void writeOnArray(Word word, bool vertical, unsigned short position);
	void freeData();

	std::pair<unsigned short, unsigned short> heightLimits;
	std::pair<unsigned short, unsigned short> widthLimits;
	std::pair<unsigned short, unsigned short> size;
	typedef std::vector<Word>::iterator WordsIterator;
	std::vector<Word> *hWords;
	std::vector<Word> *vWords;
	char** letters;
};