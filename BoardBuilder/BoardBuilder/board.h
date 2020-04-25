#pragma once

#include "word.h"
#include<utility>
#include<vector>


class Board {
public:
	bool setHeight(int height);
	bool setWidth(int width);
	bool addWord(Word word);
	std::pair<int, int> getHeightLimits() {
		return heightLimits;
	}
	std::pair<int, int> getWidthLimits() {
		return widthLimits;
	}
private:
	std::pair<int, int> heightLimits = std::make_pair(2,20);
	std::pair<int, int> widthLimits = std::make_pair(2, 20);
	std::pair<int, int> size;
	std::vector<Word> words;
};