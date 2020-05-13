#include "word.h"
#include "boardIO.h"
#include <algorithm>
#include<string>
#include<vector>

/**
 * Checks if word intersects with another word.
 *
 * @param otherWord The word that is compared
 */
bool Word::intersects(Word otherWord) {
	Coordinate otherLimits = otherWord.getLimits();

	return !(limits.first - 1 > otherLimits.second || limits.second + 1 < otherLimits.first);
}

/**
 * Checks if word is after another word.
 *
 * @param otherWord The word that is compared
 */
bool Word::operator>(Word otherWord) {
	Coordinate otherLimits = otherWord.getLimits();

	return (limits.first - 1 > otherLimits.second);
}

/**
 * Checks if word is before another word.
 *
 * @param otherWord The word that is compared
 */
bool Word::operator<(Word otherWord) {
	Coordinate otherLimits = otherWord.getLimits();

	return (limits.second + 1 < otherLimits.first);
}

/**
 * Checks if word is the same as another word.
 * The limits and the text need to be the same.
 *
 * @param otherWord The word that is compared
 */
bool Word::operator==(Word otherWord)
{
	return otherWord.getText() == text && otherWord.getLimits().first == limits.first; 
}

/**
 * Sets the text of the word to specified string if it exists in the dictionary given.
 *
 * @param dictionary Vector of words that are valid to use.
 * @param _text String to set the word's text to.
 *
 * @returns a boolean indicating if the text was set successfully.
 */
bool Word::setText(const std::vector<std::string> &dictionary, std::string _text) {
	if (_text.size() > 1 && std::binary_search(dictionary.begin(), dictionary.end(), stringToLower(_text))) {
		this->text = stringToUpper(_text);

		return true;
	}

	return false;
}

/**
 * Sets the word's limits.
 *
 * @param position Coordinates of the first position of the word.
 * @param vertical Boolean that indicates if the word is vertical.
 */
bool Word::setLimits(Coordinate position, bool vertical) {
	if (text.empty()) return false;

	if (!(vertical)) {
		this->limits.first = position.second;
		this->limits.second = position.second + (unsigned short) text.size() - 1;
	}
	else {
		this->limits.first = position.first;
		this->limits.second = position.first + (unsigned short) text.size() - 1;
	}

	return true;
}