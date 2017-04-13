#ifndef PRINTFUNCTIONS_H
#define PRINTFUNCTIONS_H

/**
 * @brief Print users with gear checked out
 * @params A vector containing the users
 **/
// Functions
void printUsersCurr(std::vector<std::string> currUsers);

/**
 * @brief Print the main menu for the program
 */
void printMenu();

/**
 * @brief Given a string prompt gets a string
 * @params A prompt for input from the user
 * @returns A string of the user's response
 **/
// Functions
std::string getStrInput(std::string prompt);

/**
 * @brief helper to convert to lower. Had problems with tolower.
 * @params input char to convert
 */
char etl(char in);

/**
 * @brief Splits the given line based on the given char
 * @params The line to be edited
 * @params The char to be the divider
 * @returns The vector made from each segment of the line
 **/
// Functions
std::vector<std::string> splitString(std::string line, char seperator_char);

#endif