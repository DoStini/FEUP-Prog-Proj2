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
		delete letters[l];
	}
	delete letters;

	delete[] vWords;
	delete[] hWords;
}

void Board::showBoard() {
	std::cout << "  ";
	for (unsigned short c = 0; c < size.second; c++) {
		std::cout << (char)(c + 'a') << ' ';
	}
	std::cout << std::endl;

	for (unsigned short l = 0; l < size.first; l++) {
		std::cout << (char)(l + 'A') << " ";
		for (unsigned short c = 0; c < size.second; c++) {
			std::cout << letters[l][c] << " ";
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

	letters = new (char(*[size.first]));
	for (unsigned short l = 0; l < size.first; l++) {
		letters[l] = new char[size.second];
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

WordsIterator Board::checkIntersections(Word word, std::vector<Word>& orientationWords) {
	WordsIterator result;
	result.invalid = false;

	for (result.iterator = orientationWords.begin(); result.iterator != orientationWords.end(); result.iterator++) {
		if (!word.isAfter(*result.iterator)) break;
	}

	if (result.iterator != orientationWords.end()) result.invalid = word.intersects(*result.iterator);
	
	if (result.invalid) return result;


	return result;
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
		letters[line][col] = text[i];

		line += vertical;
		col += !vertical;
	}
}


bool Board::addWord(Word word, unsigned short position, char orientation) {
	WordsIterator result;
	std::vector<Word>* words;
	unsigned short limit;
	bool vertical;

	if (orientation == 'H') {
		vertical = false;
		limit = size.second;
		words = hWords;
	}
	else {
		vertical = true;
		limit = size.first;
		words = vWords;
	}

	if (checkFit(word, limit)) {
		result = checkIntersections(word, words[position]);

		if (!result.invalid) {
			writeOnArray(word, orientation == 'V', position);
			words[position].insert(result.iterator, word);

			return true;
		}
	}

	return false;
}
