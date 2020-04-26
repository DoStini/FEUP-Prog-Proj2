#include "word.h"
#include<string>
#include<vector>


bool Word::setText(std::vector<std::string> dictionary, std::string _text) {
	return true;
}

void Word::setPosition(std::pair<char, char> _startPos) {
	this->startPos.first = toupper(_startPos.first);
	this->startPos.second = tolower(_startPos.second);
}

bool Word::setOrientation(char _orientation) {
	_orientation = toupper(_orientation);

	if (_orientation == 'H' || _orientation == 'V') {
		this->orientation = _orientation;

		return true;
	}
	
	return false;
}