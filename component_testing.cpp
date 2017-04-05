#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>
#include <fstream>

char easytolower(char in){
	if(in<='Z' && in>='A')
		return in-('Z'-'z');
	return in;
}

std::vector<std::string> readGearFile(std::string fileName){
    
    std::vector<std::string> gear;
    gear.clear();
    
    std::ifstream infile(fileName);

    if(infile){
        for( std::string line; std::getline( infile, line ); ){
            gear.push_back(line);
        }
    }
    else {
        std::cout << "Couldn't open " << fileName << " for reading\n" << std::endl;
        return gear;
    }
    return gear;
}

void printUsersCurr(std::vector<std::string> currUsers){
	std::sort(currUsers.begin(), currUsers.end());
	std::cout <<"\nThe people with gear checked out are: "<< std::endl;
	for(int i = 0 ; i < currUsers.size() ; i++){
		//std::string temp = i;
		//splitString(temp, '\\')
		std::cout << currUsers[i] << "\t";
	}

	std::cout << std::endl;
	std::cout << std::endl;
}

void printMenu(){
    std::cout << " -----------------------------------" <<
    "-------------------------------" << std::endl;
    std::cout << "\n| Check [O]ut Gear | Check [I]n Gear | " <<
    "[V]iew Gear in Use | [Q]uit |\n" << std::endl;
    std::cout << " ------------------------------------" <<
    "------------------------------" << std::endl;
}

std::string getStrInput(std::string prompt){
    //std::string stringIn;
    std::cout << prompt << std::endl;
    std::getline (std::cin, prompt);
    return prompt;
}

std::vector<std::string> splitString(std::string line, char seperator_char){
    std::vector<std::string> temp;
    for (size_t p = 0, q = 0; p != line.npos; p = q) {
        // Split if the length 1 substring after is the specified char
        temp.push_back(line.substr(p + (p != 0),(q = line.find(seperator_char, p + 1)) - p - (p != 0)));
    }
    return temp;
}

void view(std::vector<std::string> &a){
    bool testUser = false;
    bool hitB = false;
    
    do{
        printUsersCurr(a);
        std::string user = getStrInput("If you would like to view a users list enter the name. Otherwise hit 'b' to go back ");


		std::transform(user.begin(), user.end(), user.begin(), easytolower);

		//std::transform(user.begin(), user.end(), user.begin(), ::tolower);

		/*std::locale loc;
		for (std::string::size_type i=0; i<user.length(); ++i)
			std::cout << std::tolower(user[i], loc);
		*/

        user = user + ".txt";
        if ( std::find(a.begin(), a.end(), user) != a.end()){
            testUser = true;
            // Print the users gear file
            std::vector<std::string> gear;
            gear = readGearFile(user);
            for(auto i: gear){
                std::cout << i << " ";
            }
            std::cout << std::endl;
            
        }else if( user == "b.txt"){
            testUser = true;
            hitB = true;
        }else{
            std::cout << "That user was not found!" << std::endl;
        }
        
    }while(!testUser || !hitB);
}

void checkIn(std::vector<std::string> users) {

    bool hitB = false;

    std::vector<std::string> checkOutGear;

    bool returning_all = true;
    bool check = false;

    do {
        printUsersCurr(users);
        std::string user = getStrInput("Please enter the user id from this list for the person returning gear or hit 'b' to o back.");

        // Replace with C++ contains equiv
        //std::any_of(foo.begin(), foo.end(), [](int i){return i<0;})
        if ((std::find(users.begin(), users.end(), user+".txt")!=users.end()) && user !="b"){
            //if (a.contains(user+".txt") && (user !="b"){
            do {
                std::string all = getStrInput("Are you returning all items? (y/n)");

				std::transform(all.begin(), all.end(), all.begin(), easytolower);
                if (all == "y" || all == "n") {
                    if (all == "y") {
                        returning_all = true;
                        check = true;
                    } else if (all == "n") {
                        returning_all = false;
                        check = true;
                    }
                } else {
                    std::cout << "Invalid input. Try again." << std::endl;
                }
            } while (!check);

            if (!returning_all) {
				std::cout << "\nHere is a list of the gear you checked " <<
						  "out and the expected return date\n" << std::endl;

				// Print the users gear file
				std::vector <std::string> gear = readGearFile(user + ".txt");
				for (auto item : gear) {
					std::cout << item << " " << std::endl;
				}
				// Find equiv of regexp
				std::string prompt = "Please enter the items that you are not "
						"yet returning in the formPlease put '/' between items "
						"(no space needed) and ',' between the item name and "
						"the quantity(no space needed).\nFor Example: sleeping "
						"pad,2/tent,1";
				std::vector <std::string> outstanding;
				//= getStrInput(prompt).split("\\s*\\/\\s*");

				std::string s = getStrInput(prompt);
				std::regex e("\\s*\\/\\s*");
				std::regex_token_iterator <std::string::iterator> i(s.begin(), s.end(), e,
														  -1);
				std::regex_token_iterator <std::string::iterator> end;
				while (i != end){
					outstanding.push_back(*i++);
				}

						//.split("\\s*\\/\\s*");
                // C++ Regexp support


                // Add to an arraylist
                for (auto tempSplit : outstanding) {
                    checkOutGear.push_back(tempSplit);
                }

                std::cout << "Updating File....." << std::endl;
                //writeGearFile(checkOutGear, user);
                std::cout << "  Done.\nThanks!" << std::endl;
                hitB = true;

            } else {
                try {
                    std::cout << "Updating Files....." << std::endl;
                    hitB = true;
                    // Remove Erase
                    users.erase(std::remove(users.begin(), users.end(), user+".txt"), users.end());

					std::string fileToRemove = user+".txt";
                    remove(fileToRemove.c_str());

                    // C++ Equivalent
					std::ofstream outputFile;
					outputFile.open(user+".txt");

                    //File f = new File(user + ".txt");
                    //f.createNewFile();
                    // bool b = f.delete();

                } catch (std::exception& e) {
                    std::cout << "Error in file update! Return the hear " <<
                    		"normally and if\nany one asks tell them you got "<<
                    		"this error.\nIts possible your gear was already"<<
                    		" marked returned" << std::endl;
                }
                std::cout << "  Done.\nThanks!" <<  std::endl;
            }
        }else if(user == "b"){
            hitB = true;
        }else{
            std::cout << "Invalid user name please try again" << std::endl;
        }

    }while(!hitB);
}


int main() {
    
    std::vector<std::string> people;
    people.push_back("Tim");
    people.push_back("Bob");
    printUsersCurr(people);

    view(people);
    
    return 0;
}
