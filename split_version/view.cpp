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
 * @brief Allows the user to see who is using gear and what items they are using
 * @params The vector that contains all users with gear checked out
 */
void view(std::vector<std::string> &a){
	bool testUser = false;
	bool hitB = false;
	try{
		do{
			printUsersCurr(a);
	        std::string userPrompt = "\033[7;1mIf you would like to view a ";
	        userPrompt += "users fist enter the name.              \nOtherwise";
	        userPrompt += " hit 'b' to go back                                ";
	        userPrompt += "        \033[0m";
			std::string user = getStrInput(userPrompt);

			//std::transform(user.begin(), user.end(), user.begin(), ::tolower);

			/*std::locale loc;
			for (std::string::size_type i=0; i<user.length(); ++i)
				std::cout << std::tolower(user[i], loc);
			*/
			user = user + ".csv";
			if ( std::find(a.begin(), a.end(), user) != a.end()){
	            std::cout<<"\n"
	                    <<"_______________________________"
	                    <<"____________________________________"
	                    <<"\n"
	                    <<std::endl;
				testUser = true;
				// Print the users gear file
				std::vector<std::string> gear;
	            std::cout<<"\033[7;1mGear, Quantity, ...., Expected Return Date"
	            		<<"                          \033[0m"
	            		<<std::endl;
				gear = readGearFile(user);
				for(auto i: gear){
					std::cout << i << " ";
				}
				std::cout << std::endl;
	            std::cout<<"\n"
	                    <<"_______________________________"
	                    <<"____________________________________"
	                    <<"\n"
	                    <<std::endl;
			}else if( user == "b.csv"){
				testUser = true;
				hitB = true;
			}else{
				std::cout
						<< "\033[1;31mThat user was not found!\033[0m"
						<< std::endl;
			}
		}while(!testUser || !hitB);
	}catch(std::exception& e){
		std::cout << "No users found" << std::endl;
	}
}