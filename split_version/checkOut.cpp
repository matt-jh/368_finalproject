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
*@brief the function that allows a user to check out gear 
*@params a vector of users
*/
void checkOut(std::vector<std::string> &users){

        std::vector<std::string> checkOutGear;
        bool hitB = false;

        do {
            std::string tripLeader = "\033[7;1mPlease enter the trip leader's ";
            tripLeader += "lastname or hit 'b' to go back.      \033[0m";
            tripLeader = getStrInput(tripLeader);
            
            for(auto lower: tripLeader){
                etl(lower);
            }

            if(tripLeader != "b"){
            	std::string temp = "\033[7;1m\nPlease enter the trip leader's";
                temp += " first initial.                       \033[0m";
                temp = getStrInput(temp);
                std::string userName = temp + tripLeader; 
                // First_initialLastname
                
                std::transform(userName.begin(), userName.end(), 
                    userName.begin(), etl);
                remove_if(userName.begin(), userName.end(), isspace);

                // Ensures the user enters a date that is valid
                bool vaild_date = false;
                std::string returnDate;
                do{
                	returnDate = "\033[7;1m\nPlease enter the ";
                	returnDate += "expected date for returning the gear. ";
                	returnDate += "(mm/dd/yy)   \033[0m";
                	returnDate = getStrInput(returnDate);
                	if(checkDate(returnDate)){
                		vaild_date = true;
                	}else{
                		std::cout 
                				<< "\033[33mSeems you entered "
                				<< "an invalid date!\033[0m" 
                				<< std::endl;
                	}
                }while(!vaild_date);
                

                temp = userName + ".txt";
                if(std::find(users.begin(), users.end(), userName + ".txt") 
                    != users.end()){
                    // Include Date
                    std::string pls_ret="\033[33;1mIt looks like you already";
                    pls_ret +=" have gear checked out. You can check out\n";
                    pls_ret += "more, but please emember to return both sets";
                    pls_ret += " of gear.\n\033[0m";
                    std::cout << pls_ret << std::endl;
                }

                std::string items ="\033[7;1m\nPlease enter all the items you";
                items +=" wish to use and the quantity of that \nitem. Please ";
                items += "put '/' between items (no space needed) and ',' ";
                items += "between\nthe item name and the quantity ";
                items += " (no space needed).	 	    \033[0m\n";
                items += "For Example: sleeping pad,2/tent,1\n";
                items = getStrInput(items);
                

                // Add to an arraylist
                std::vector<std::string> tempSplit;
                // = items.split("\\s*/\\s*");
                // Java equiv:
                // String split[] = items.split("\\s*\\/\\s*");
                std::regex e("\\s*\\/\\s*");
                std::regex_token_iterator <std::string::iterator> i(
                    items.begin(), 
                    items.end(),
                     e, -1);
                std::regex_token_iterator <std::string::iterator> end;

                while (i != end){
                    tempSplit.push_back(*i++);
                }

                for(auto i: tempSplit){
                    checkOutGear.push_back(i);
                }

                checkOutGear.push_back(returnDate);

                // Write the file
                std::cout << "Saving File....." << std::endl;

                //std::cout << "\033[31;1mCalled Write Names\033[0m" << std::endl;
                writeGearFile(checkOutGear, userName);
                std::cout << "\033[32;1mDone.\033[0m" << std::endl;
                // Add to the list of names
                users.push_back(userName + ".txt");
                std::sort(users.begin(), users.end()); // <- ADDED SORT
                std::cout << "Items Recorded! Have Fun!" << std::endl;

                hitB = true;
            } else {
                hitB = true;
            }
        }while(!hitB);
}