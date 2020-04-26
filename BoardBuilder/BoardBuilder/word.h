#pragma once

#include<string>
#include<vector>

class Word {
public:
	bool setText(const std::vector<std::string> &dictionary, std::string _text);
	bool setOrientation(char _orientation);
	void setPosition(std::pair<char, char> _startPos);
private:
	std::string text;
	std::pair<char, char> startPos;
	char orientation = '\0';
};