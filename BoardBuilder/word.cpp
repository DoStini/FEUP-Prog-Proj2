#include "word.h"
#include "boardIO.h"
#include <algorithm>
#include<string>
#include<vector>
#include<set>

/**
 * Gets variations of a word.
 * Deletes, tranposes, inserts and replaces letters in the word
 *
 * @param word Base word.
 *
 * @returns A set of strings with all unique variations of the word.
 */
std::set<std::string> getVariations(std::string word) {
	std::set<std::string> variations;
	std::string mutated;
	mutated = word;

	// Deletes
	for (auto it = mutated.begin(); it != mutated.end(); it++) {
		mutated.erase(it);

		variations.insert(mutated);
		mutated = word;
	}

	// Transposes
	for (size_t i = 0; i < word.size(); i++) {
		for (size_t j = 0; j < word.size(); j++) {
			std::string transposed = word;
			std::swap(transposed[i], transposed[j]);

			variations.insert(transposed);
		}
	}

	// Replaces
	for (auto it = mutated.begin(); it != mutated.end(); it++) {
		for (char alpha = 'a'; alpha <= 'z'; alpha++) {
			(*it) = alpha;

			variations.insert(mutated);
			mutated = word;
		}
	}

	// Inserts
	auto itm = mutated.begin();
	for (; itm != mutated.end(); itm++) {
		for (char alpha = 'a'; alpha <= 'z'; alpha++) {
			mutated.insert(itm, alpha);

			variations.insert(mutated);
			mutated = word;
		}
	}
	for (char alpha = 'a'; alpha <= 'z'; alpha++) {
		mutated.insert(itm, alpha);

		variations.insert(mutated);
		mutated = word;
	}

	return variations;
}


/**
 * Gets similar words of another word.
 *
 * @param dictionary Vector of words that are valid to use.
 * @param word Base word.
 *
 * @returns A vector of similar words.
 */
std::vector<std::string> getSimilarWords(const std::vector<std::string>& dictionary, std::string word) {
	std::vector<std::string> validWords;

	std::set<std::string> variations = getVariations(stringToLower(word));

	for (auto it = variations.begin(); it != variations.end(); it++) {
		if (it->size() > 1 && std::binary_search(dictionary.begin(), dictionary.end(), *it)) {
			validWords.push_back(*it);
		}
	}

	return validWords;
}

/**
 * Checks if word intersects with another word.
 *
 * @param otherWord The word that is compared
 */
bool Word::intersects(const Word& otherWord) const {
	Coordinate otherLimits = otherWord.limits;

	return !(limits.first - 1 > otherLimits.second || limits.second + 1 < otherLimits.first);
}

/**
 * Checks if word is after another word.
 *
 * @param otherWord The word that is compared
 */
bool Word::operator>(const Word& otherWord) const {
	Coordinate otherLimits = otherWord.limits;

	return (limits.first - 1 > otherLimits.second);
}

/**
 * Checks if word is before another word.
 *
 * @param otherWord The word that is compared
 */
bool Word::operator<(const Word& otherWord) const {
	Coordinate otherLimits = otherWord.limits;

	return (limits.second + 1 < otherLimits.first);
}

/**
 * Checks if word is the same as another word.
 * The limits and the text need to be the same.
 *
 * @param otherWord The word that is compared
 */
bool Word::operator==(const Word& otherWord) const{
	return otherWord.text == text && otherWord.limits.first == limits.first; 
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