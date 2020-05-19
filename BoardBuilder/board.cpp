#include "board.h"
#include "boardIO.h"
#include "color.h"
#include<utility>
#include<vector>
#include<algorithm>
#include<sstream>
#include<fstream>
#include <cassert>

Board::Board() {
	heightLimits = std::make_pair(3, 20);
	widthLimits = std::make_pair(3, 20);
	size = std::make_pair(3, 3);
	minLetters = 14;
	minSquares = 20;
	initializeWords();
}

Board::~Board() {
	for (int l = 0; l < size.first + 2; l++) {
		delete letters[l];
	}
	delete letters;

	delete[] vWords;
	delete[] hWords;
}

/**
* Function to read the board
*
* @param fileName - Name of file to be read.
*
* @returns A boolean indicating if the file was found
*/
bool Board::readBoard(std::string fileName, const std::vector<std::string>& dictionary) {
	std::ifstream f_in;
	std::stringstream file;

	file << fileName << ".txt";
	f_in.open(file.str());

	if (!f_in.is_open()) {
		//f_in.close();
		return false;
	}

	char sep;
	char position[2];
	bool vertical;
	std::vector<Word>* words;
	unsigned short location;
	unsigned short vSize, hSize;
	std::string text;

	f_in >> vSize >> sep >> hSize;
	setWidth(hSize);
	setHeight(vSize);

	unsigned short int verticalIdx;
	unsigned short int horizontalIdx;

	initializeWords();

	while (f_in.peek() != '#' && !f_in.eof() && f_in.peek() != 0) {
		Word word;
		Coordinate positionCoord;

		f_in >> position[0] >> position[1] >> sep >> text;                      // Input is given as "Aa"

		verticalIdx = (int)position[0] - (int)'A';                            // vertical index will be A converted to integer, counting 0 as char A
		horizontalIdx = (int)position[1] - (int)'a';                          // same for horizontal index but with "a"
		vertical = sep == 'V';

		positionCoord.first = verticalIdx;
		positionCoord.second = horizontalIdx;
		word.setText(dictionary, text);
		word.setLimits(positionCoord, vertical);

		if (vertical) {
			words = vWords;
			location = positionCoord.second;
		}
		else {
			words = hWords;
			location = positionCoord.first;
		}

		writeOnArray(word, vertical, location);     // Writing word on graphical board
		words[location].push_back(word);

		f_in.get();
	}
	f_in.close();

	return true;
}

/**
 * Displays the Board object in the console output.
 *
 * @returns a string that can be output to the console, displaying the board.
 */
std::string Board::showBoard() {
	std::stringstream output;

	output << "   ";
	for (unsigned short c = 0; c < size.second; c++) {
		output << (char)(c + 'a');
		if (c != size.second - 1) output << "   ";
	}
	output << std::endl;

	for (unsigned short l = 1; l <= size.first; l++) {
		output << (char)((l - 1) + 'A') << " ";
		output << " ";
		for (unsigned short c = 1; c <= size.second; c++) {
			output << letters[l][c] << " ";
			if (c != size.second) output << "| ";
		}

		output << std::endl;
		if (l != size.first) {
			output << "  ";
			output << "---";
			for (unsigned short c = 1; c < size.second; c++) {
				output << "+---";
			}
			output << std::endl;
		}
	}
	return output.str();
}

/**
 * Displays the Board object in the console output centered.
 *
 * @param xStart, yStart Starting coordinates.
 */
void Board::showCenteredBoard(unsigned short xStart, unsigned short yStart) {
	unsigned short int center = xStart + 14;
	unsigned short start = center - (size.second) * 2;

	gotoxy(start, yStart);
	std::cout << "   ";
	for (unsigned short c = 0; c < size.second; c++) {
		std::cout << (char)(c + 'a');
		if (c != size.second - 1) std::cout << "   ";
	}
	std::cout << std::endl;

	for (unsigned short l = 1; l <= size.first; l++) {
		gotoxy(start, yStart + (l * 2));
		std::cout << (char)((l - 1) + 'A') << " ";
		setColor(BLACK, WHITE);
		std::cout << " ";
		for (unsigned short c = 1; c <= size.second; c++) {
			std::cout << letters[l][c] << " ";
			if (c != size.second) std::cout << "| ";
		}

		gotoxy(start, yStart + (l * 2) + 1);
		if (l != size.first) {
			setColor(WHITE, BLACK);
			std::cout << "  ";
			setColor(BLACK, WHITE);
			std::cout << "---";
			for (unsigned short c = 1; c < size.second; c++) {
				std::cout << "+---";
			}
		}

		setColor(WHITE, BLACK);
	}

	gotoxy(0, yStart + ((size.first + 1) * 2));
}

/**
 * Sets the height of the board if the value is in the limits defined.
 *
 * @param height Value of the height to be stored.
 *
 * @returns a boolean that indicates if the value was stored with success.
 */
bool Board::setHeight(unsigned short height) {
	if (height > heightLimits.second || height < heightLimits.first) {
		return false;
	}

	this->size.first = height;
	return true;
}


/**
 * Sets the width of the board if the value is in the limits defined.
 *
 * @param width Value of the width to be stored.
 *
 * @returns a boolean that indicates if the value was stored with success.
 */
bool Board::setWidth(unsigned short width) {
	if (width > widthLimits.second || width < widthLimits.first) {
		return false;
	}

	this->size.second = width;
	return true;
}


/**
 * Initializes the vWords and hWords arrays and the letters matrix if the height and width has been set.
 *
 * @returns a boolean that indicates if the board was able to be initialized.
 */
bool Board::initializeWords() {
	vWords = new std::vector<Word>[size.second];
	hWords = new std::vector<Word>[size.first];

	letters = new char* [(size_t)size.first + 2];
	for (unsigned short l = 0; l < size.first + 2; l++) {
		letters[l] = new char[(size_t)size.second + 2];
		for (unsigned short c = 0; c < size.second + 2; c++) {
			letters[l][c] = ' ';
		}
	}

	return true;
}

/**
 * Makes a copy of the letters matrix.
 *
 * @returns a copy of the letters matrix.
 */
char** Board::copyLetters() {
	char** copy;

	copy = new char* [(size_t)size.first + 2];
	for (unsigned short l = 0; l < size.first + 2; l++) {
		copy[l] = new char[(size_t)size.second + 2];
		for (unsigned short c = 0; c < size.second + 2; c++) {
			copy[l][c] = letters[l][c];
		}
	}

	return copy;
}

/**
 * Gets the number of letters in the letters matrix.
 *
 * @returns the number of letters.
 */
int Board::getNumberOfLetters() {
	int sum = 0;

	for (unsigned short l = 1; l < size.first + 1; l++) {
		for (unsigned short c = 1; c < size.second + 1; c++) {
			if (letters[l][c] != ' ') sum++;
		}
	}

	return sum;
}

/**
 * Checks if the board has the minimum number of letters defined.
 *
 * @returns a boolean that indicates if the board has the minimum of letters
 */
bool Board::hasMinimumOfLetters() {
	return getNumberOfLetters() >= minLetters;
}

/**
 * Checks if the board has the minimum number of squares defined.
 *
 * @returns a boolean that indicates if the board has the minimum of squares
 */
bool Board::hasMinimumOfSquares() {
	return size.first * size.second >= minSquares;
}

/**
 * Checks if a word can fit in the board.
 * In other words, it checks if the word does not go out of the board's bounds.
 *
 * @param word Word object to add.
 * @param max The board limit that the word can't break.
 *		This is the max column if the word is horizontal.
 *		This is the max row if the word is vertical.
 *
 * @returns a boolean that indicates if the words fits on the board.
 */
bool Board::checkFit(Word word, unsigned short max) {
	std::pair<unsigned short, unsigned short> limits = word.getLimits();

	return !(limits.second >= max || limits.first < 0);
}

/**
 * Checks if the word intersects other words on the same row for horizontal words, or on the same column for vertical words.
 * Also gets an iterator of a vector in vWords or hWords where the word should be inserted so that all words are in order.
 *
 * @param word Word object to add.
 * @param position Starting coordinates of the word.
 * @param vertical Boolean indicating if the word is vertical.
 *
 * @returns a WordsIterator, with invalid True if the word intersects with another and iterator set to where the word should be inserted.
 */
WordsIterator Board::checkIntersections(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	// Orientation words stores the pointer to a vector in either vWords or hWords.
	// position.second is the column of the word, position.first is the line of the word
	std::vector<Word>* orientationWords = vertical ? &vWords[position.second] : &hWords[position.first];
	result.invalid = false;

	// We iterate through each word in orientation words and check if the word to be added to the board is after them.
	// The loop breaks when we find a word that is after the word to be added.
	// As such, result.iterator will always be such that allows the word to be inserted in order.
	for (result.iterator = (*orientationWords).begin(); result.iterator != (*orientationWords).end(); result.iterator++) {
		if (!(word > (*result.iterator))) break;
	}

	if (result.iterator != (*orientationWords).end()) result.invalid = word.intersects(*result.iterator);

	return result;
}

/**
 * Checks if the sides of the word touch other words.
 * Also checks if the word intersects correctly with other words.
 * This is, words can only correctly intersect if the letter where they intersect is equal.
 *
 * @param word Word object to add.
 * @param position Starting coordinates of the word.
 * @param vertical Boolean indicating if the word is vertical.
 *
 * @returns a bool that indicates if the word can be placed.
 */
bool Board::checkEdges(Word word, Coordinate position, bool vertical) {
	std::string text = word.getText();
	size_t textSize = text.size();
	int lineStart, lineEnd;
	int columnStart, columnEnd;
	position.first++; position.second++; ///< it is added one to the coordinates because the letter matrix has a border of empty letters

	// Here is checked if the end sides of the word touch the sides of other words.
	if (letters[position.first - vertical][position.second - !vertical] != ' ' ||
		letters[position.first + (vertical * textSize)][position.second + (!vertical * textSize)] != ' ') {

		return false;
	}

	// For each letter in the word we check if it's sides touch other words.
	// If it touches another word, if the intersecting letter is different on both words then they intersect incorrectly, returning false.
	for (int i = 0; i < textSize; i++) {
		lineStart = position.first - !vertical, lineEnd = position.first + !vertical;
		columnStart = position.second - vertical, columnEnd = position.second + vertical;

		if (letters[lineStart][columnStart] != ' ' ||
			letters[lineEnd][columnEnd] != ' ') {
			if (letters[position.first][position.second] != text[i]) {
				return false;
			}
		}

		position.first += vertical; position.second += !vertical;
	}

	return true;
}

/**
 * Checks if the word can be placed in the board
 *
 * @param word Word object to add.
 * @param position Starting coordinates of the word.
 * @param vertical Boolean indicating if the word is vertical.
 *
 * @returns a WordsIterator, with invalid True if the word can't be placed and iterator set to where the word should be inserted.
 */
WordsIterator Board::checkIfLegal(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	unsigned short limit = vertical ? size.first : size.second;

	result.invalid = !checkFit(word, limit);
	if (result.invalid) return result;

	result = checkIntersections(word, position, vertical);
	if (result.invalid) return result;

	result.invalid = !checkEdges(word, position, vertical);

	return result;
}


/**
 * Stores a word's letters in the letters matrix in the board.
 *
 * @param word Word object to add.
 * @param vertical Boolean indicating if the word is vertical.
 * @param location Row or column where the word is placed.
 *		Is a column if the word is vertical
 *		Is a row if the word is horizontal
 */
void Board::writeOnArray(Word word, bool vertical, unsigned short location) {
	unsigned short first = word.getLimits().first;
	unsigned short line = first, col = location;
	std::string text = word.getText();

	if (!vertical) {
		line = location;
		col = first;
	}
	line++; col++;

	for (unsigned short i = 0; i < text.size(); i++) {
		letters[line][col] = text[i];

		line += vertical;
		col += !vertical;
	}
}

/**
 * Adds a word to the appropriate array (hWords or vWords) of the Board if it can be placed.
 *
 * @param word Word object to add.
 * @param position Starting coordinates of the word.
 * @param vertical Boolean indicating if the word is vertical.
 *
 * @returns a boolean, set to True if the word was placed successfully.
 */
bool Board::addWord(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	std::vector<Word>* words;
	unsigned short location;

	// location is the row/column where the word may be placed.
	// Is a column if the word is vertical
	// Is a row if the word is horizontal
	if (vertical) {
		words = vWords;
		location = position.second;
	}
	else {
		words = hWords;
		location = position.first;
	}

	result = checkIfLegal(word, position, vertical);

	if (!result.invalid) {
		writeOnArray(word, vertical, location);
		words[location].insert(result.iterator, word);

		return true;
	}

	return false;
}


/**
 * Replaces a word's letters in the letters matrix in the board with spaces.
 *
 * @param word Word object to delete.
 * @param vertical Boolean indicating if the word is vertical.
 * @param location Row or column where the word is placed.
 *		Is a column if the word is vertical
 *		Is a row if the word is horizontal
 */
void Board::deleteOnArray(Word word, bool vertical, unsigned short location) {
	unsigned short first = word.getLimits().first;
	unsigned short line = first, col = location;
	std::string text = word.getText();

	if (!vertical) {
		line = location;
		col = first;
	}
	line++; col++;

	for (unsigned short i = 0; i < text.size(); i++) {
		letters[line][col] = ' ';

		line += vertical;
		col += !vertical;
	}
}


/**
 * Rewrites all words in the letters matrix of the board, within a limit of rows/columns.
 *
 * @param vertical Boolean indicating if the words are vertical.
 * @param limits Pair with the start and end limits where the words will be rewritten.
 *		Is a Pair of columns if the words are vertical
 *		Is a Pair of rows if the words are horizontal
 */
void Board::rewriteOnArray(bool vertical, std::pair<unsigned short, unsigned short> limits) {
	std::vector<Word>* words = vWords;
	unsigned short limit = size.second;

	if (!vertical) {
		words = hWords;
		limit = size.first;
	}

	assert((limits.first >= 0 && limits.second < limit));

	for (unsigned short i = limits.first; i <= limits.second; i++) {
		for (std::vector<Word>::iterator it = words[i].begin(); it != words[i].end(); it++) {
			writeOnArray(*it, vertical, i);
		}
	}
}

/**
 * Checks if a word is on the board.
 *
 * @param word Word object to add.
 * @param position Starting coordinates of the word.
 * @param vertical Boolean indicating if the word is vertical.
 *
 * @returns a WordsIterator, with invalid True if the word is not on the board and iterator set to where the word is.
 */
WordsIterator Board::checkWordOnBoard(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	std::string text = word.getText();
	size_t textSize = text.size();

	std::vector<Word>* orientationWords = vertical ? &vWords[position.second] : &hWords[position.first];

	// A binary search can be used because orientationWords is always ordered.
	result.iterator = std::lower_bound((*orientationWords).begin(), (*orientationWords).end(), word);

	result.invalid = result.iterator == orientationWords->end() || !(word == *(result.iterator));

	return result;
}

/**
 * Checks if deleting a word makes an impossible board configuration.
 *
 * @param limits Start and end positions of the words.
 *		Are columns if the word is horizontal
 *		Are rows if the word is vertical
 * @param location Row or column where the word is placed.
 *		Is a column if the word is vertical
 *		Is a row if the word is horizontal
 * @param vertical Boolean indicating if the word is vertical.
 *
 * @returns a boolean indicating if the board configuration is possible.
 */
bool Board::checkLegalDelete(std::pair<unsigned short, unsigned short> limits, unsigned location, bool vertical) {
	unsigned short first = limits.first;
	unsigned short line = first, col = location;

	if (!vertical) {
		line = location;
		col = first;
	}
	line++; col++;

	for (unsigned short i = limits.first; i < limits.second; i++) {
		if (letters[line][col] != ' ' && letters[line + vertical][col + !vertical] != ' ') return false;

		line += vertical;
		col += !vertical;
	}

	return true;
}

/**
 * Deletes a word from the board if it is possible.
 *
 * @param word Word to be deleted
 * @param position Starting position of the word to be deleted.
 * @param vertical Boolean indicating if the word is vertical.
 *
 * @returns a success value indicating the result of this function
 *		Is 1 if deletion was successfull
 *		Is 0 if word is not on board
 *		Is -1 if deleting the word makes an impossible board configuration
 */
short Board::deleteWord(Word word, Coordinate position, bool vertical) {
	WordsIterator result;
	std::vector<Word>* words;
	unsigned short location;
	std::pair<unsigned short, unsigned short> wordLimits = word.getLimits();
	char** letterCopy;

	if (vertical) {
		words = vWords;
		location = position.second;
	}
	else {
		words = hWords;
		location = position.first;
	}

	result = checkWordOnBoard(word, position, vertical);

	if (result.invalid) return 0;

	letterCopy = copyLetters(); ///< copy the letters to save the current board state.

	deleteOnArray(word, vertical, location);
	rewriteOnArray(!vertical, wordLimits);

	if (checkLegalDelete(word.getLimits(), location, vertical)) {
		words[location].erase(result.iterator);

		return 1;
	}

	letters = letterCopy;

	return -1;
}

/**
 * Saves the Board object to a text file.
 *
 * @param fileName Name of the file where the board will be saved.
 */
void Board::saveBoard(std::string fileName) {
	std::stringstream path;
	path.str(std::string());
	path << fileName << ".TXT";

	std::ofstream saveFile(path.str());
	std::vector<Word>::iterator it;

	saveFile << size.first << 'x' << size.second << std::endl;

	for (int i = 0; i < size.first; i++) {
		for (it = hWords[i].begin(); it != hWords[i].end(); it++) {
			saveFile << (char)(i + 'A') << (char)(it->getLimits().first + 'a') << " H " << it->getText() << std::endl;
		}
	}

	for (int i = 0; i < size.second; i++) {
		for (it = vWords[i].begin(); it != vWords[i].end(); it++) {
			saveFile << (char)(it->getLimits().first + 'A') << (char)(i + 'a') << " V " << it->getText() << std::endl;
		}
	}

	saveFile << "########" << std::endl;
	saveFile << showBoard() << std::endl;

	saveFile.close();
}