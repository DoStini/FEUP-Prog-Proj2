#include "color.h"
#include <iostream>
#include <string>

void getString(std::string &string) {
	std::getline(std::cin, string);
}

void printMessage(std::string message, std::string end) {
	std::cout << message << end;
}

void printMessage(std::string message, int bgColor, int fgColor, std::string end) {
	std::cout << "\033[" << COLOR[bgColor].first << ";" << COLOR[fgColor].second << "m" << message << "\033[0m" << end;
}

bool checkStop(char input) {
	return std::cin.eof() || std::toupper(input) == 'S';
}

void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void waitForKey() {
	printMessage("Press any key to continue...", WHITE, BLACK, "");
	std::cin.get();
}