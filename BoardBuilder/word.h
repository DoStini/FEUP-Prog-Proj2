#pragma once

#include<string>
#include<vector>

class Word {
public:
	bool setText(const std::vector<std::string> &dictionary, std::string _text);
	bool setLocation(std::pair<unsigned short, unsigned short> _location, char orientation);
	std::string getText() { return text; }
	std::pair<unsigned short, unsigned short> getLocation() { return location; }
private:
	std::string text;
	std::pair<unsigned short, unsigned short> location;
};