#include "board.h"
#include<utility>
#include<vector>

bool Board::setHeight(unsigned short height) {
	if (height > this->heightLimits.second || height < heightLimits.first) {
		return false;
	}

	this->size.first = height;
	return true;
}

bool Board::setWidth(unsigned short width) {
	if (width > this->widthLimits.second || width < widthLimits.first) {
		return false;
	}

	this->size.second = width;
	return true;
}

bool Board::checkFit(Word word, unsigned short max) {
	std::pair<unsigned short, unsigned short> location = word.getLocation();

	return !(location.second >= max || location.first < 0);
}

// TODO
bool Board::checkIntersections(Word word, std::vector<Word> orientationWords) {
	/*bool intersects = false;
	WordsIterator insertIterator = orientationWords.end();

	for (WordsIterator it = orientationWords.begin(); it != orientationWords.end(); it++) {
		if((*it).getLocation().)
	}*/

	return false;
}


bool Board::addHWord(Word word, unsigned short position) {
	if (checkFit(word, size.second)) {
		return true;
	}

	return false;
}

bool Board::addVWord(Word word, unsigned short position) {
	if (checkFit(word, size.first)) {
		return false;
	}

	return false;
}

