#include "word.h"
#include <algorithm>
#include<string>
#include<vector>


bool Word::setText(const std::vector<std::string> &dictionary, std::string _text) {
	if (std::binary_search(dictionary.begin(), dictionary.end(), _text)) {
		this->text = _text;

		return true;
	}

	return false;
}

void Word::setPosition(std::pair<unsigned short, unsigned short> _startPos) {
	this->startPos.first = _startPos.first;
	this->startPos.second = _startPos.second;
}

bool Word::setOrientation(char _orientation) {
	_orientation = toupper(_orientation);

	if (_orientation == 'H' || _orientation == 'V') {
		this->orientation = _orientation;

		return true;
	}
	
	return false;
}