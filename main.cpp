#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>
#include <fstream>

/*

    EVERYTHING NEEDS TO BE TESTED
    SEE JAVA FILE FOR EXPECTED BEHAVIOR

    ->CURRENTLY THE NAME VECTOR UPDATES DO NOT WORK!<-
        NEEDS POINTERS?

 */

// Transition from .txt database to SQL
// Create a GUI (Can just be a window that says the same thing as the
// prompts and has input fields that allow the user to enter the same
// info. Process the input strings in the same manner)

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

// Forward Declarations
std::vector<std::string> readNameFile();
std::string getStrInput(std::string prompt);
std::vector<std::string> readGearFile(std::string fileName);
std::vector<std::string> splitString(std::string line, char seperator_char);
void writeGearFile(std::vector<std::string> als, std::string name);
void writeNameFile(std::vector<std::string> als, std::string name);
void printUsersCurr(std::vector<std::string> currUsers);
void checkIn(std::vector<std::string> &users);
void checkOut(std::vector<std::string> &users);
void view(std::vector<std::string> &a);
void printMenu();

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
*@brief write the list of gear for a user to a txt file
*@params als: a list of all the users names
*@params name: the name of the file sans .txt
*/
void writeGearFile(std::vector<std::string> als, std::string name){
    name += ".txt";
    try {
        std::ofstream outfile (name);
        for(auto i : als){
            outfile << i << std::endl;
        }
        outfile.close();
    } catch (std::exception& e) {
        std::cout << "*****Gear File Write failed!******\nSeems the program "<< 
        "isn't working at this time." << std::endl;
    }
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/**
*@brief write the list of names to a txt file
*@params als: a list of all the users names
*@params name: the name of the file sans .txt
*/
void writeNameFile(std::vector<std::string> als, std::string name){
    name += ".txt";
    try {
        std::ofstream outfile (name);
        for(auto i : als){
            outfile << i << std::endl;
        }
        outfile.close();
    } catch (std::exception& e) {
        std::cout << "*****Name File Write failed!******\nSeems"<< 
        "the program isn't working at this time." << std::endl;
    }
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

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

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

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

// Functioning as expected
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
        std::string userPrompt = "\033[7;1mIf you would like to view a users ";
        userPrompt += "list enter the name.              \nOtherwise hit 'b' ";
        userPrompt += "to go back                ";
        userPrompt += "                        \033[0m";
		std::string user = getStrInput(userPrompt);

		//std::transform(user.begin(), user.end(), user.begin(), ::tolower);

		/*std::locale loc;
		for (std::string::size_type i=0; i<user.length(); ++i)
			std::cout << std::tolower(user[i], loc);
		*/
		user = user + ".txt";
		if ( std::find(a.begin(), a.end(), user) != a.end()){
            std::cout<<"\n"
                    <<"_______________________________"
                    <<"____________________________________"
                    <<"\n"
                    <<std::endl;
			testUser = true;
			// Print the users gear file
			std::vector<std::string> gear;
            std::cout<<"\033[7;1mGear, Quantity, ....,  Expected Return Date"
            		<<"                         \033[0m"
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
		}else if( user == "b.txt"){
			testUser = true;
			hitB = true;
		}else{
			std::cout<<"\033[1;31mThat user was not found!\033[0m"<<std::endl;
		}
	}while(!testUser || !hitB);
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/**
*@brief helper to convert to lower. Had problems with tolower.
*@params input char to convert
*/
char easytolower(char in){
    if(in<='Z' && in>='A')
        return in-('Z'-'z');
    return in;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/**
 * @brief Allows users to return gear and remove their gear file and listing
 * @param users a vector of all people using gear
 */
void checkIn(std::vector<std::string> &users) {

    bool hitB = false;

    std::vector<std::string> checkOutGear;

    bool returning_all = true;
    bool check = false;

    do {
        printUsersCurr(users);
        std::string userPrompt = "\033[7;1mPlease enter the user id from this ";
        userPrompt+="list for the person returning    \ngear or hit 'b' to go";
        userPrompt+=" back.                                         \033[0m";
        std::string user = getStrInput(userPrompt);

        // Replace with C++ contains equiv
        //std::any_of(foo.begin(), foo.end(), [](int i){return i<0;})
        if ((std::find(users.begin(), users.end(), user+".txt")!=users.end()) 
            && user !="b"){
            //if (a.contains(user+".txt") && (user !="b"){
            do {
            	std::string all_prompt="\033[7;1m\nAre you returning all ";
            	all_prompt += "items? (y/n)            \033[0m";
                std::string all = getStrInput(all_prompt);

                std::transform(all.begin(),all.end(),all.begin(),easytolower);
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
                std::regex_token_iterator <std::string::iterator> i(s.begin(), 
                    s.end(), e, -1);
                std::regex_token_iterator <std::string::iterator> end;
                while (i != end){
                    outstanding.push_back(*i++);
                }

                        //.split("\\s*\\/\\s*");

                // Add to an arraylist
                for (auto tempSplit : outstanding) {
                    checkOutGear.push_back(tempSplit);
                }

                std::cout << "Updating File....." << std::endl;
                writeGearFile(checkOutGear, user);
                std::cout << "  Done.\nThanks!" << std::endl;
                hitB = true;

            } else {
                try {
                    std::cout << "Updating Files....." << std::endl;
                    hitB = true;
                    // Remove Erase
                    users.erase(std::remove(users.begin(), users.end(), 
                        user+".txt"), users.end());

                    std::string fileToRemove = user+".txt";
                    remove(fileToRemove.c_str());

                    std::ofstream outputFile;
                    outputFile.open(user+".txt");

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

            if(easytolower(tripLeader[0]) != 'b'){
            	std::string temp = "\033[7;1m\nPlease enter the trip leader's";
                temp += " first initial.                       \033[0m";
                temp = getStrInput(temp);
                std::string userName = temp + tripLeader; 
                // First_initialLastname
                
                std::transform(userName.begin(), userName.end(), 
                    userName.begin(), easytolower);


                std::string returnDate = "\033[7;1m\nPlease enter the expected";
                returnDate += " date for returning the gear. (mm/dd/yy)   ";
                returnDate += "\033[0m";
                returnDate = getStrInput(returnDate);

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
                items += "(no space needed).		    \033[0m\n";
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
                writeGearFile(checkOutGear, userName);
                std::cout << "\033[32;1mDone.\033[0m" << std::endl;
                // Add to the list of names
                users.push_back(userName + ".txt");
                std::cout << "Items Recorded! Have Fun!" << std::endl;

                hitB = true;
            } else {
                hitB = true;
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
        if(s.length() == 1){
            s = easytolower(s[0]);
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
