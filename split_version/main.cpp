#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>
#include <fstream>
#include <cctype>

#include "readWrite.h"
#include "printFunctions.h"
#include "view.h"
#include "checkDate.h"
#include "checkOut.h"
#include "checkIn.h"

/**
 * @brief Runs the database reads, calls the print menu and validates commands
 * @brief Calls the writes when editing is done
 **/
int main() {
    
    std::vector<std::string> nameList;
    
    bool valid_bool = false;
    bool hitQ = false;
    
    std::vector<std::string> input_vector;
    try{
    	input_vector = readNameFile();
    }catch(std::exception& e){
        std::cout << "Error Reading Gear! Quitting..." << std::endl;
        return 0;
    }
    
    do {
        printMenu();
        std::string s = getStrInput("");
        if(s.length() == 1){
            s = etl(s[0]);
            if ((s == "v") || (s == "o")|| (s == "i") || (s == "q") ) {
                valid_bool = true;
                if(s=="v"){
                    // View the check outs
                    view(input_vector);
                }else if(s=="o"){
                    // Check out gear
                    checkOut(input_vector);
                }else if(s=="i"){
                    checkIn(input_vector);
                    // Check in Gear
                }else if(s=="q"){
                    hitQ = true;
                }
            } else {
                std::cout << "Seems you entered an invalid command. " <<
                        "Please try again." << std::endl;
            }
        } else {
            std::cout << "Seems you entered an invalid command. " <<
                    "Please only enter one command." << std::endl;
        }
    }while(!valid_bool || !hitQ);
    
    std::cout << "Quitting.....";
    writeNameFile(input_vector, "names");
    std::cout << "\nDone." << std::endl;
    
    return 0;
}
