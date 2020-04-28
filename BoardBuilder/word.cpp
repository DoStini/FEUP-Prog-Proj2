#include "word.h"
#include "boardIO.h"
#include <algorithm>
#include<string>
#include<vector>

bool Word::intersects(Word otherWord) {
	std::pair<unsigned short, unsigned short> otherLocation = otherWord.getLocation();

	return (location.first - 1 > otherLocation.second || location.second + 1 < otherLocation.first);
}

bool Word::setText(const std::vector<std::string> &dictionary, std::string _text) {
	if (std::binary_search(dictionary.begin(), dictionary.end(), stringToLower(_text))) {
		this->text = stringToUpper(_text);

		return true;
	}

	return false;
}

bool Word::setLocation(std::pair<unsigned short, unsigned short> _location, char orientation) {
	if (text.empty()) return false;
	orientation = toupper(orientation);

	if (orientation == 'H') {
		this->location.first = _location.second;
		this->location.second = _location.second + (unsigned short) text.size() - 1;
	}
	else if (orientation == 'V') {
		this->location.first = _location.first;
		this->location.second = _location.first + (unsigned short) text.size() - 1;
	}

	return true;
}