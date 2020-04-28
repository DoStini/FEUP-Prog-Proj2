#include "board.h"
#include "boardIO.h"
#include<utility>
#include<vector>

Board::Board() {
	heightLimits = std::make_pair(2, 20);
	widthLimits = std::make_pair(2, 20);
	size = std::make_pair(0, 0);
}

Board::~Board() {
	for (int l = 0; l < size.first; l++) {
		free(letters[l]);
	}
	free(letters);

	free(vWords);
	free(hWords);
}

void Board::showBoard() {
	for (unsigned short l = 0; l < size.first; l++) {
		for (unsigned short c = 0; c < size.second; c++) {
			std::cout << letters[l][c] << "t";
		}
		std::cout << std::endl;
	}
}

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

bool Board::initializeWords() {
	if (size.first == 0 || size.second == 0) return false;

	vWords = new std::vector<Word>[size.second];
	hWords = new std::vector<Word>[size.first];

	letters = (char**)calloc(size.first, sizeof(char*));
	for (unsigned short l = 0; l < size.first; l++) {
		letters[l] = (char*)calloc(size.second, sizeof(char));
		for (unsigned short c = 0; c < size.second; c++) {
			letters[l][c] = ' ';
		}
	}

	return true;
}

bool Board::checkFit(Word word, unsigned short max) {
	std::pair<unsigned short, unsigned short> location = word.getLocation();

	return !(location.second >= max || location.first < 0);
}

// TODO
bool Board::checkIntersections(Word word, std::vector<Word> orientationWords) {
	bool intersects = false;
	WordsIterator insertIterator;

	for (insertIterator = orientationWords.begin(); insertIterator != orientationWords.end(); insertIterator++) {

	}

	return false;
}

void Board::writeOnArray(Word word, bool vertical, unsigned short position) {
	unsigned short first = word.getLocation().first;
	unsigned short line = first, col = position;
	std::string text = word.getText();

	if(!vertical) {
		line = position;
		col = first;
	}

	for (unsigned short i = 0; i < text.size(); i++) {
		letters[line][col] = text[i];                         // If vertical, changes vIdx, otherwise changes hIdx

		line += vertical;
		col += !vertical;
	}
}


bool Board::addHWord(Word word, unsigned short position) {
	if (checkFit(word, size.second)) {
		writeOnArray(word, false, position);
		hWords[position].push_back(word);

		return true;
	}

	return false;
}

bool Board::addVWord(Word word, unsigned short position) {
	if (checkFit(word, size.first)) {
		writeOnArray(word, true, position);
		vWords[position].push_back(word);

		return true;
	}

	return false;
}

