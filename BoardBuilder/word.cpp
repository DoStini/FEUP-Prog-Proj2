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

bool Word::setLocation(std::pair<unsigned short, unsigned short> _location, char orientation) {
	if (text.empty()) return false;
	orientation = toupper(orientation);

	if (orientation == 'H') {
		this->location.first = _location.second;
		this->location.second = _location.second + text.size() - 1;
	}
	else if (orientation == 'V') {
		this->location.first = _location.first;
		this->location.second = _location.first + text.size() - 1;
	}

	return true;
}