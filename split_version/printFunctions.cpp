#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>
#include <fstream>
#include <cctype>
#include <chrono>
#include <ctime>

#include "checkDate.h"
#include "checkOut.h"
#include "checkIn.h"
#include "printFunctions.h"
#include "readWrite.h"
#include "view.h"

/**
 * @brief Print users with gear checked out
 * @params A vector containing the users
 **/
// Functions
void printUsersCurr(std::vector<std::string> currUsers){
	if(currUsers.size() <= 0){
		throw std::exception();
	}
    std::sort(currUsers.begin(), currUsers.end());
    std::cout 
    		<< "\033[7;1m\nThe users with gear checked out are: " 
    		<< "                               \033[0m"
    		<< std::endl;
    for(int i = 0 ; i < currUsers.size() ; i++){
        std::string s = currUsers[i];
        s.erase(s.find_last_of("."), std::string::npos);
        std::cout << s << "\t";
    }
    // Done for cleaner looking interface
    std::cout << std::endl;
    std::cout << std::endl;
}

/**
 * @brief Print the main menu for the program
 */
void printMenu(){
    std::cout << std::endl;
    std::cout << "\033[7;1m -----------------------------------\033[0m" 
            <<"\033[7;1m------------------------------- \033[0m" << std::endl;
    std::cout << "\033[7;1m| Check [O]ut Gear | Check [I]n Gear | \033[0m" 
            <<"\033[7;1m[V]iew Gear in Use | [Q]uit |\033[0m" << std::endl;
    std::cout << "\033[7;1m ------------------------------------\033[0m" 
            <<"\033[7;1m------------------------------ \033[0m" << std::endl;
}

/**
 * @brief Given a string prompt gets a string
 * @params A prompt for input from the user
 * @returns A string of the user's response
 **/
// Functions
std::string getStrInput(std::string prompt){
    std::cout << prompt << std::endl;
    std::getline (std::cin, prompt);
    return prompt;
}

/**
 * @brief Splits the given line based on the given char
 * @params The line to be edited
 * @params The char to be the divider
 * @returns The vector made from each segment of the line
 **/
// Functions
std::vector<std::string> splitString(std::string line, char seperator_char){
    std::vector<std::string> temp;
    for (size_t p = 0, q = 0; p != line.npos; p = q) {
        // Split if the length 1 substring after is the specified char
        temp.push_back(line.substr(p + (p != 0),
                                   (q = line.find(seperator_char, p + 1))
                                   - p - (p != 0)));
    }
    return temp;
}

/**
 * @brief helper to convert to lower. Had problems with tolower.
 * @params input char to convert
 */
char etl(char in){
    if(in<='Z' && in>='A')
        return in-('Z'-'z');
    return in;
}