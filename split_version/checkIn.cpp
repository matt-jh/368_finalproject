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
 * @brief Allows users to return gear and remove their gear file and listing
 * @param users a vector of all people using gear
 */
void checkIn(std::vector<std::string> &users) {

    bool hitB = false;

    std::vector<std::string> checkOutGear;

    bool returning_all = true;
    bool check = false;
	try{
	    do {
	        printUsersCurr(users);
	        std::string userPrompt = "\033[7;1mPlease enter the user id ";
	        userPrompt+= "from this list for the person returning    \n";
	        userPrompt+="gear or hit 'b' to go back.                    ";
	        userPrompt+="                     \033[0m";
	        std::string user = getStrInput(userPrompt);

	        // Replace with C++ contains equiv
	        //std::any_of(foo.begin(), foo.end(), [](int i){return i<0;})
	        if ((std::find(users.begin(),users.end(), user+".csv")
	        		!=users.end()) && user !="b"){
	            //if (a.contains(user+".csv") && (user !="b"){
	            do {
	            	std::string all_prompt="\033[7;1m\nAre you returning ";
	            	all_prompt += "all items? (y/n)\t\t\t\t    \033[0m";
	                std::string all = getStrInput(all_prompt);

	                std::transform(all.begin(),all.end(),all.begin(),etl);
	                if (all == "y" || all == "n") {
	                    if (all == "y") {
	                        returning_all = true;
	                        check = true;
	                    } else if (all == "n") {
	                        returning_all = false;
	                        check = true;
	                    }
	                } else {
	                    std::cout
	                    		<< "\033[31;1mInvalid input. Try again."
	                    		<< "\033[0m"
	                    		<< std::endl;
	                }
	            } while (!check);

	            if (!returning_all) {
	                std::cout << "\033[7;1m\nHere is a list of the gear you"
	                		<< " checked out :\t\t\t   "
	                		<< "\033[0m\n"
	                		<< std::endl;

	                // Print the users gear file
	                std::vector<std::string> gear=readGearFile(user+".csv");
	                for (auto item : gear) {
	                    std::cout << item << " " << std::endl;
	                }
	                // Find equiv of regexp
	                std::string prompt="\033[7;1m\nPlease enter the items "
	                		"that you are not yet returning in the        "
	                		"\nfollowing form: Please put '/' between items"
	                        " (no space needed) and  \n',' between the item"
	                        " name and the quantity (no space needed).\t    "
	                        "\033[0m\nFor Example: sleeping pad,2/tent,1";

	                std::vector <std::string> outstanding;
	                //= getStrInput(prompt).split("\\s*\\/\\s*");

	                std::string s = getStrInput(prompt);
	                std::regex e("\\s*\\/\\s*");
	                std::regex_token_iterator<std::string::iterator> i(
	                		s.begin(), s.end(), e, -1);
	                std::regex_token_iterator <std::string::iterator> end;
	                while (i != end){
	                    outstanding.push_back(*i++);
	                }

	                        //.split("\\s*\\/\\s*");

	               outstanding.erase(remove_if(outstanding.begin(),
	               			outstanding.end(),[](std::string s){
	               			return s.empty();} ),outstanding.end() );

	                // Add to an arraylist
	                for (auto tempSplit : outstanding) {
	                    	checkOutGear.push_back(tempSplit);
	                }
	                // Add the expected date so it can be seen how overdue
	                // items are
	                int last_ind = gear.size()-1;
	                checkOutGear.push_back(gear[last_ind]);

	                if(checkOutGear.size() == 0){
	                	try {
		                    std::cout << "Updating Files....." << std::endl;
		                    hitB = true;
		                    // Remove Erase
		                    users.erase(std::remove(users.begin(), users.end(),
		                        user+".csv"), users.end());

                            std::sort(users.begin(), users.end());

		                    std::ofstream outputFile;
		                    outputFile.open(user + ".csv");

		                    std::string fileToRemove = user+".csv";
		                    remove(fileToRemove.c_str());

	                	} catch (std::exception& e) {
	                		std::cout<<"Error in file update!" << std::endl;
	                	}
	                	std::cout << "  Done.\nThanks!" <<  std::endl;
	                }else{
		                std::cout << "Updating File....." << std::endl;
		                writeGearFile(checkOutGear, user);
		                std::cout << "\033[32;1m    Done.\033[0m" << std::endl;
		                hitB = true;
	            	}

	            } else {
	                try {
	                    std::cout << "Updating Files....." << std::endl;
	                    hitB = true;
	                    // Remove Erase
	                    users.erase(std::remove(users.begin(), users.end(),
	                        user+".csv"), users.end());

	                    std::ofstream outputFile;
	                    outputFile.open(user+".csv");

	                    std::string fileToRemove = user + ".csv";
	                    std::cout << fileToRemove << std::endl;
	                    remove(fileToRemove.c_str());

	                } catch (std::exception& e) {
	                    std::cout<<"Error in file update! Return the hear "
	                    		<<"normally and if\nany one asks tell them"
	                    		<< "you got this error.\nIts possible your"
	                    		<< " gear was already marked returned"
	                    		<< std::endl;
	                }
	                std::cout << "\033[32;1mDone.\nThanks!\033[0m" << std::endl;
	            }
	        }else if(user == "b"){
	            hitB = true;
	        }else{
	            std::cout << "Invalid user name please try again"
	            		<< std::endl;
	        }

		}while(!hitB);
	}catch(std::exception& e){
			std::cout << "No users found" << std::endl;
	}
}