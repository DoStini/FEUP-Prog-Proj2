#include "color.h"
#include "IO.h"
#include <string>



/**
 * Function to put the program on hold
 */
void waitForKey() {
    std::cout <<"Press any key to continue...";
    std::cin.get();
}

/**
 * Function to convert a string into a lowered case one
 *
 * @param str - original string
 * @return - converted string
 */
std::string stringToLower(std::string str) {
    std::string::iterator it;
    std::string newCopy = str;

    for (it = newCopy.begin(); it != newCopy.end(); it++) {
        (*it) = tolower((*it));
    }

    return newCopy;
}


