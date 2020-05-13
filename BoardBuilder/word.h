#pragma once

#include<string>
#include<vector>

typedef std::pair<unsigned short, unsigned short> Coordinate;


/**
 * A Word class stores text and limits of a word to be placed on a Board.
 * It adds some functions to modify the words and compare limits.
*/
class Word {
public:
	bool setText(const std::vector<std::string> &dictionary, std::string _text);
	bool setLimits(Coordinate position, bool vertical);
	bool intersects(Word otherWord);
	bool operator>(Word otherWord);
	bool operator<(Word otherWord);
	bool operator==(Word otherWord);
	std::string getText() { return text; }
	Coordinate getLimits() { return limits; }
private:
	std::string text;
	Coordinate limits;
};