#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/*
 - Not Finished, + Working

 + readNameFile
 + readGearFile
 - writeGearFile
 - writeNameFile
 - checkOut
 + checkIn
 + getStrInput
 + printUsersCurr
 + view
 + printMenu
 + main
 */

// Add Forward declarations for all methods
// Continue to translate Java into C++
// Transition from .txt database to SQL
// Create a GUI (Can just be a window that says the same thing as the
// prompts and has input fields that allow the user to enter the same
// info. Process the input strings in the same manner)

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

// Forward Declarations
std::vector<std::string> readGearFile(std::string fileName);
std::vector<std::string> readNameFile();
std::vector<std::string> splitString(std::string line, char seperator_char);
void printUsersCurr(std::vector<std::string> currUsers);
std::std::string getStrInput(std::string prompt);
void view(std::vector<std::string> &a);
void printMenu();
std::string getStrInput(std::string prompt);
void checkIn(std::vector<std::string> users);


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

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
            gear.push_back(line);
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

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/**
 * @brief Given a name of a file read it in. Return nothing if not found/opened
 * @returns the vector containing the names of people using gear
 **/
std::vector<std::string> readNameFile(){
    std::vector<std::string> input;
    input.clear();
    std::ifstream infile("names.txt");
    // If the file open worked read and add contents to a vector
    if(infile){
        for( std::string line; getline( infile, line ); ){
            input.push_back(line);
        }
    }
    // Checking if the file was opened improperly
    else {
        std::cout << "Couldn't open names.txt for reading\n"
        << std::endl;
        return input;
    }
    return input;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

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

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/**
 * @brief Print users with gear checked out
 * @params A vector containing the users
 **/
// Functions
void printUsersCurr(std::vector<std::string> currUsers){
    std::sort(currUsers.begin(), currUsers.end());
    std::cout <<"\nThe people with gear checked out are: "<< std::endl;
    for(int i = 0 ; i < currUsers.size() ; i++){
        std::cout << currUsers[i] << "\t";
    }
    // Done for cleaner looking interface
    std::cout << std::endl;
    std::cout << std::endl;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/**
 * @brief Given a string prompt gets a string
 * @params A prompt for input from the user
 * @returns A string of the user's response
 **/
// Functions
std::std::string getStrInput(std::string prompt){
    std::cout << prompt << std::endl;
    std::getline (std::cin, prompt);
    return prompt;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/**
 * @brief Shows the user's gear
 * @params The vector of the user's gear
 **/
void view(std::vector<std::string> &a){
    bool testUser = false;
    bool hitB = false;
    
    do{
        printUsersCurr(a);
        std::string user = getStrInput("If you would like to view a users list enter the name. Otherwise hit 'b' to go back ");
        
        std::tolower(user);
        user = user + ".txt";
        
        if(a.contains(user)) {
            testUser = true;
            // Print the users gear file
            std::vector<string> gear;
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

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

// Functioning as expected
/**
 * @brief Print the main menu for the program
 */
void printMenu(){
    std::cout << " -----------------------------------" <<
    "-------------------------------" << std::endl;
    std::cout << "\n| Check [O]ut Gear | Check [I]n Gear | " <<
    "[V]iew Gear in Use | [Q]uit |\n" << std::endl;
    std::cout << " ------------------------------------" <<
    "------------------------------" << std::endl;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/**
 * @brief Allows the user to see who is using gear and what items they are using
 * @params The vector that contains all users with gear checked out
 */
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

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/**
 * @brief Given a specified prompt return the user's input
 * @param prompt
 * @return the user's response
 */
std::string getStrInput(std::string prompt){
	//std::string stringIn;
	std::cout << prompt << std::endl;
	std::getline (std::cin, prompt);
	return prompt;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/**
 * @brief Allows users to return gear and remove their gear file and listing
 * @param users a vector of all people using gear
 */
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

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/**
 * @brief Runs the database reads, calls the print menu and validates commands
 * @brief Calls the writes when editing is done
 **/
int main() {
    
    std::vector<std::string> nameList;
    
    bool valid_bool = false;
    bool hitQ = false;
    
    std::vector<std::string> input_vector;
    input_vector = readNameFile();
    if(input_vector.size() == 0){
        std::cout << "Error Reading Gear! Quitting..." << std::endl;
        return 0;
    }
    
    do {
        printMenu();
        std::string s = getStrInput("");
        if(s.size() != 1){
            std::tolower(s[0]);
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
            "Please try again." << std::endl;
        }
    }while(!valid_bool || !hitQ);
    
    std::cout << "Quitting.....";
    writeNameFile(input_vector, "names");
    std::cout << "\nDone." << std::endl;
    
    return 0;
}
