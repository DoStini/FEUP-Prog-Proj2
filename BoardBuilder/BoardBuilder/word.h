#pragma once

#include<string>
#include<vector>

class Word {
public:
	bool setText(std::vector<std::string> dictionary, std::string _text);
	bool setPosition(char _orientation, std::pair<int, int> _startPos);
private:
	std::string text;
	std::pair<int, int> startPos;
	char orientation = '\0';
};