#include <vector>
#include <string>
#include <iostream>
#include <fstream>

/**
 * Reads all the words from the WORDS.TXT file
 *
 * @param[out] words Vector where all the words will be stored.
 */
void readWords(std::vector<std::string> &words) {
	std::ifstream f_in;

	f_in.open("WORDS.TXT");
	if (!f_in.is_open()) {
		std::cerr << "Words file was not found, was it deleted?" << std::endl;
		exit(1);
	}

	std::string line;
	std::getline(f_in, line);
	while (!f_in.eof()) {
		words.push_back(line);
		
		std::getline(f_in, line);
	}

	f_in.close();
}