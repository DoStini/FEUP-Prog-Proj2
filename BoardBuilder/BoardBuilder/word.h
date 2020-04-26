#pragma once

#include<string>
#include<vector>

class Word {
public:
	bool setText(const std::vector<std::string> &dictionary, std::string _text);
	bool setOrientation(char _orientation);
	void setPosition(std::pair<unsigned short, unsigned short> _startPos);
	std::string getText() { return text; }
	std::pair<unsigned short, unsigned short> getStartPos() { return startPos; }
	char getOrientation() { return orientation; }
private:
	std::string text;
	std::pair<unsigned short, unsigned short> startPos;
	char orientation = '\0';
};