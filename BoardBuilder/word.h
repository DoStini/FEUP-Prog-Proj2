#pragma once

#include<string>
#include<vector>

typedef std::pair<unsigned short, unsigned short> Coordinate;

class Word {
public:
	bool setText(const std::vector<std::string> &dictionary, std::string _text);
	bool setLocation(Coordinate _location, char orientation);
	bool intersects(Word otherWord);
	bool isAfter(Word otherWord);
	bool operator ==(const Word word);
	std::string getText() { return text; }
	Coordinate getLocation() { return location; }
private:
	std::string text;
	Coordinate location;
};