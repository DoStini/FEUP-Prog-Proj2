#include "board.h"
#include<utility>
#include<vector>

bool Board::setHeight(int height) {
	if (height > this->heightLimits.second || height < heightLimits.first) {
		return false;
	}

	this->size.first = height;
	return true;
}

bool Board::setWidth(int width) {
	if (width > this->widthLimits.second || width < widthLimits.first) {
		return false;
	}

	this->size.second = width;
	return true;
}

bool Board::checkFit(Word word) {
	int textSize = word.getText().size(), location, max;
	char orientation = word.getOrientation();
	std::pair<int, int> startPos = word.getStartPos();

	if (orientation == 'H') {
		location = startPos.second;
		max = this->size.second;
	}
	else {
		location = startPos.first;
		max = this->size.first;
	}

	if (location + textSize > max) return false;
	return true;
}

bool Board::addWord(Word word) {
	if (checkFit(word)) {
		words.push_back(word);

		return true;
	}

	return false;
}