#include "color.h"
#include <iostream>
#include <string>

void getString(std::string &string) {
	std::getline(std::cin, string);
}

/**
 * Function that prompts the user for the input of a single char.
 * Reads only the first char input to the buffer, all else is deleted from the buffer.
 * Allows the EOF character.
 *
 * @param[out] delimiter The last char must be at the end of the buffer
 */
void getChar(char& input) {
	input = getchar();
	if(input != '\n' && input != EOF) std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void printMessage(std::string message, std::string end) {
	std::cout << message << end;
}

void printMessage(std::string message, int bgColor, int fgColor, std::string end) {
	std::cout << "\033[" << COLOR[bgColor].first << ";" << COLOR[fgColor].second << "m" << message << "\033[0m" << end;
}

bool checkStop() {
	return std::cin.eof();
}

void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void waitForKey() {
	printMessage("Press any key to continue...", WHITE, BLACK, "");
	std::cin.get();
}

std::string stringToLower(std::string str) {
	std::string::iterator it;
	std::string newCopy = str;

	for (it = newCopy.begin(); it != newCopy.end(); it++) {
		(*it) = tolower((*it));
	}

	return newCopy;
}

std::string stringToUpper(std::string str) {
	std::string::iterator it;
	std::string newCopy = str;

	for (it = newCopy.begin(); it != newCopy.end(); it++) {
		(*it) = toupper((*it));
	}

	return newCopy;
}

void gotoxy(int x, int y) {
	std::cout << "\033[" << y << ";" << x << "f";
}