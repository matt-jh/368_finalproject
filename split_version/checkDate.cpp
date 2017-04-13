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

 // #include "printFunctions.h"
/**
 * @brief ensures that the user enters a valid date
 * @params the sting containing the user entered date
 * @return a bool that is true if the date is a valid one
 **/
bool checkDate(std::string longdate){
	std::vector<std::string> words;
    words = splitString(longdate, '/');

   	std::string month = words[0];
   	std::string day = words[1];
   	std::string year = words[2];

   	bool valid = false;

   	int y = atoi(year.c_str());
   	int m = atoi(month.c_str());
   	int d = atoi(day.c_str());

   	if(y >= 17 && words.size() == 3){
	   	int daysinmonth[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	   	
	   	// Leap year checking
	   	if(y % 400 == 0 || (y % 100 != 0 && y % 4 == 0)){
	    	daysinmonth[1] = 29;
		}else{
			daysinmonth[1] = 28;
		}

	   	// days in month checking
	   	if (m < 13){
	    	if( d <= daysinmonth[m - 1] ){
	        	valid = true;
			}
		}
	}

   return valid;
}
