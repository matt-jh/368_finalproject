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
 * @brief Given a name of a file read it in. Return nothing if not found/opened
 * @params the name of the gear file
 * @return the vector of gear in the file
 **/
std::vector<std::string> readGearFile(std::string fileName){
    std::vector<std::string> gear;
    gear.clear();
    std::ifstream infile(fileName);
    // If the file open worked read and add contents to a vector
    if(infile){
        for( std::string line; getline(infile, line ); ){
            if(line[0] != '#'){
                gear.push_back(line);
            }
        }
    }
    // Checking if the file was opened improperly
    else {
        std::cout << "Couldn't open " << fileName << " for reading\n"
        << std::endl;
        return gear;
    }
    return gear;
}

/**
*@brief write the list of gear for a user to a txt file
*@params als: a list of all the users names
*@params name: the name of the file sans .txt
*/
void writeGearFile(std::vector<std::string> als, std::string name){
    name += ".csv";
    try {
        std::ofstream outfile (name);
        outfile << "#Item Name, Quantity" << std::endl;
        for(auto i : als){
            outfile << i << std::endl;
        }
        outfile.close();
    } catch (std::exception& e) {
        std::cout << "*****Gear File Write failed!******\nSeems the program "<<
        "isn't working at this time." << std::endl;
    }
}

/**
*@brief write the list of names to a txt file
*@params als: a list of all the users names
*@params name: the name of the file sans .txt
*/
void writeNameFile(std::vector<std::string> als, std::string name){
    name += ".csv";
    try {
        std::ofstream outfile (name);
        outfile << "#User Names" << std::endl;
        for(auto i : als){
            outfile << i << std::endl;
        }
        outfile.close();
    } catch (std::exception& e) {
        std::cout << "*****Name File Write failed!******\nSeems"<<
        "the program isn't working at this time." << std::endl;
    }
}

/**
 * @brief Given a name of a file read it in. Return nothing if not found/opened
 * @returns the vector containing the names of people using gear
 **/
std::vector<std::string> readNameFile(){
    std::vector<std::string> input;
    input.clear();
    std::ifstream infile("names.csv");
    // If the file open worked read and add contents to a vector
    if(infile){
        for( std::string line; getline( infile, line ); ){
            if(line[0] != '#'){
                input.push_back(line);
            }
        }
    }else{
        std::fstream file;
        file.open("names.csv", std::fstream::out);
    }
    std::ifstream infile2("names.csv");
    // Checking if the file was opened improperly
    if(!infile2){
        std::cout
                << "Couldn't open names.csv for reading\n"
                << std::endl;
        throw std::exception();
    }
    return input;
}