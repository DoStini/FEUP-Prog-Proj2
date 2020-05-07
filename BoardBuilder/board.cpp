#include "board.h"
#include "boardIO.h"
#include "color.h"
#include<utility>
#include<vector>
#include<algorithm>
#include<sstream>
#include<fstream>
#include <cassert>

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

std::string Board::showBoard(bool color) {
	std::stringstream output;

	output << "   ";
	for (unsigned short c = 0; c < size.second; c++) {
		output << (char)(c + 'a');
		if (c != size.second - 1) output << "   ";
	}
	output << std::endl;

	for (unsigned short l = 1; l <= size.first; l++) {
		output << (char)((l - 1) + 'A') << " ";
		if (color) output << "\033[47;30m";
		output << " ";
		for (unsigned short c = 1; c <= size.second; c++) {
			output << letters[l][c] << " ";
			if (c != size.second) output << "| ";
		}

		output << std::endl;
		if (l != size.first) {
			if (color) output << "\033[0m";
			output << "  ";
			if (color) output << "\033[47;30m";
			output << "---";
			for (unsigned short c = 1; c < size.second; c++) {
				output << "+---";
			}
			output << std::endl;
		}

		if (color) output << "\033[0m";
	}
	return output.str();
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

char** Board::copyLetters() {
	char** copy;

	copy = new (char(*[(size_t)size.first + 2]));
	for (unsigned short l = 0; l < size.first + 2; l++) {
		copy[l] = new char[(size_t)size.second + 2];
		for (unsigned short c = 0; c < size.second + 2; c++) {
			copy[l][c] = letters[l][c];
		}
	}

	return copy;
}

bool Board::checkFit(Word word, unsigned short max) {
	std::pair<unsigned short, unsigned short> location = word.getLocation();

	return !(location.second >= max || location.first < 0);
}

WordsIterator Board::checkIntersections(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	std::string text = word.getText();
	size_t textSize = text.size();
	int lineStart, lineEnd;
	int columnStart, columnEnd;
	
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
		lineStart = position.first - !vertical, lineEnd = position.first + !vertical;
		columnStart = position.second - vertical, columnEnd = position.second + vertical;

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

void Board::deleteOnArray(Word word, bool vertical, unsigned short position) {
	unsigned short first = word.getLocation().first;
	unsigned short line = first, col = position;
	std::string text = word.getText();

	if (!vertical) {
		line = position;
		col = first;
	}
	line++; col++;

	for (unsigned short i = 0; i < text.size(); i++) {
		letters[line][col] = ' ';

		line += vertical;
		col += !vertical;
	}
}

void Board::rewriteOnArray(bool vertical, std::pair<unsigned short, unsigned short> limits) {
	std::vector<Word>* words = vWords;
	unsigned short limit = size.second;

	if (!vertical) {
		words = hWords;
		limit = size.first;
	}

	assert((limits.first >= 0 && limits.second < limit));	

	for (unsigned short i = limits.first; i <= limits.second; i++) {
		for (std::vector<Word>::iterator it = words[i].begin(); it != words[i].end(); it++) {
			writeOnArray(*it, vertical, i);
		}
	}
}

WordsIterator Board::checkWordOnBoard(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	std::string text = word.getText();
	size_t textSize = text.size();

	std::vector<Word>* orientationWords = vertical ? &vWords[position.second] : &hWords[position.first];
	result.invalid = false;

	for (result.iterator = (*orientationWords).begin(); result.iterator != (*orientationWords).end(); result.iterator++) {
		if (!word.isAfter(*result.iterator)) break;
	}

	result.invalid = result.iterator == orientationWords->end() || !(word == (*result.iterator));

	return result;
}

bool Board::checkLegalDelete(std::pair<unsigned short, unsigned short> limits, unsigned position, bool vertical) {
	unsigned short first = limits.first;
	unsigned short line = first, col = position;

	if (!vertical) {
		line = position;
		col = first;
	}
	line++; col++;

	for (unsigned short i = limits.first; i < limits.second; i++) {
		if (letters[line][col] != ' ' && letters[line + vertical][col + !vertical] != ' ') return false;

		line += vertical;
		col += !vertical;
	}

	return true;
}

short Board::deleteWord(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	std::vector<Word>* words;
	unsigned short location;
	std::pair<unsigned short, unsigned short> wordLocation = word.getLocation();
	char** letterCopy;

	if (vertical) {
		words = vWords;
		location = position.second;
	}
	else {
		words = hWords;
		location = position.first;
	}

	result = checkWordOnBoard(word, position, vertical);

	if (result.invalid) return 0;

	letterCopy = copyLetters();

	deleteOnArray(word, vertical, location);
	rewriteOnArray(!vertical, wordLocation);

	if (checkLegalDelete(word.getLocation(), location, vertical)) {
		words[location].erase(result.iterator);

		return 1;
	}

	letters = letterCopy;
	
	return -1;
}

void Board::saveBoard(std::string fileName) {
	std::stringstream path;
	path.str(std::string());
	path << "../Assets/" << fileName << ".TXT";

	std::ofstream saveFile(path.str());
	std::vector<Word>::iterator it;

	saveFile << size.first << 'x' << size.second << std::endl;

	for (int i = 0; i < size.first; i++) {
		for (it = hWords[i].begin(); it != hWords[i].end(); it++) {
			saveFile << (char)(i + 'A') << (char)(it->getLocation().first + 'a') << " H " << it->getText() << std::endl;
		}
	}

	for (int i = 0; i < size.second; i++) {
		for (it = vWords[i].begin(); it != vWords[i].end(); it++) {
			saveFile << (char)(it->getLocation().first + 'A') << (char)(i + 'a') << " V " << it->getText() << std::endl;
		}
	}

	saveFile << "########" << std::endl;
	saveFile << showBoard(false) << std::endl;

	saveFile.close();
}