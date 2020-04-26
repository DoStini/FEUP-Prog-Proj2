#pragma once

#include<string>
#include<vector>

class Word {
public:
	bool setText(const std::vector<std::string> &dictionary, std::string _text);
	bool setOrientation(char _orientation);
	void setPosition(std::pair<int, int> _startPos);
	std::string getText() { return text; }
	std::pair<int, int> getStartPos() { return startPos; }
	char getOrientation() { return orientation; }
private:
	std::string text;
	std::pair<int, int> startPos;
	char orientation = '\0';
};