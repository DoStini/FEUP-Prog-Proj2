#include "board.h"
#include "boardIO.h"
#include<utility>
#include<vector>
#include<algorithm>

Board::Board() {
	heightLimits = std::make_pair(2, 20);
	widthLimits = std::make_pair(2, 20);
	size = std::make_pair(0, 0);
}

Board::~Board() {
	for (int l = 0; l < size.first + 2; l++) {
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

	for (unsigned short l = 1; l <= size.first; l++) {
		std::cout << (char)((l-1) + 'A') << " ";
		for (unsigned short c = 1; c <= size.second; c++) {
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

	letters = new (char(*[(size_t)size.first+2]));
	for (unsigned short l = 0; l < size.first+2; l++) {
		letters[l] = new char[(size_t)size.second+2];
		for (unsigned short c = 0; c < size.second+2; c++) {
			letters[l][c] = ' ';
		}
	}

	return true;
}

bool Board::checkFit(Word word, unsigned short max) {
	std::pair<unsigned short, unsigned short> location = word.getLocation();

	return !(location.second >= max || location.first < 0);
}

WordsIterator Board::checkIntersections(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	std::string text = word.getText();
	size_t textSize = text.size();
	
	std::vector<Word>* orientationWords = vertical ? &vWords[position.second] : &hWords[position.first];
	position.first++; position.second++;
	result.invalid = false;

	for (result.iterator = (*orientationWords).begin(); result.iterator != (*orientationWords).end(); result.iterator++) {
		if (!word.isAfter(*result.iterator)) break;
	}

	if (result.iterator != (*orientationWords).end()) result.invalid = word.intersects(*result.iterator);
	
	if (result.invalid) return result;

	if (letters[position.first - vertical][position.second - !vertical] != ' ' ||
		letters[position.first + (vertical*textSize)][position.second + (!vertical * textSize)] != ' ') {
		result.invalid = true;

		return result;
	}

	for (int i = 0; i < textSize; i++) {
		int lineStart = position.first - !vertical, lineEnd = position.first + !vertical;
		int columnStart = position.second - vertical, columnEnd = position.second + vertical;

		if (letters[lineStart][columnStart] != ' ' ||
			letters[lineEnd][columnEnd] != ' ') {
			if (letters[position.first][position.second] != text[i]) {
				result.invalid = true;

				return result;
			}
		}

		position.first += vertical; position.second += !vertical;
	}

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
	line++; col++;

	for (unsigned short i = 0; i < text.size(); i++) {
		letters[line][col] = text[i];

		line += vertical;
		col += !vertical;
	}
}


bool Board::addWord(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	std::vector<Word>* words;
	unsigned short limit, location;

	if (vertical) {
		limit = size.first;
		words = vWords;
		location = position.second;
	}
	else {
		limit = size.second;
		words = hWords;
		location = position.first;
	}

	if (checkFit(word, limit)) {
		result = checkIntersections(word, position, vertical);

		if (!result.invalid) {
			writeOnArray(word, vertical, location);
			words[location].insert(result.iterator, word);

			return true;
		}
	}

	return false;
}
