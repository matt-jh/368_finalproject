#ifndef READWRITE_H
#define READWRITE_H


/**
 * @brief Given a name of a file read it in. Return nothing if not found/opened
 * @params the name of the gear file
 * @return the vector of gear in the file
 **/
std::vector<std::string> readGearFile(std::string fileName);

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/**
*@brief write the list of gear for a user to a txt file
*@params als: a list of all the users names
*@params name: the name of the file sans .txt
*/
void writeGearFile(std::vector<std::string> als, std::string name);

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/**
*@brief write the list of names to a txt file
*@params als: a list of all the users names
*@params name: the name of the file sans .txt
*/
void writeNameFile(std::vector<std::string> als, std::string name);

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/**
 * @brief Given a name of a file read it in. Return nothing if not found/opened
 * @returns the vector containing the names of people using gear
 **/
std::vector<std::string> readNameFile();

#endif