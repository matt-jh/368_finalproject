#include <iostream>
#include <string>
#include <vector>
#include <sstream>

vector<string> readNameFile(){
    std::vector<string> input;
    input.clear();
    std::ifstream infile("names.txt");
    if(infile){
        for( std::string line; getline( infile, line ); ){
            input.push_back(line);
        }
    }
    else {
        std::cout << "Couldn't open " << filename << " for reading\n" << std::endl;
        return input;
    }
    return input;
}

// Need Split method?
vector<sting> splitString(std:string line, char seperator_char){
    std::vector<std::string> temp;
    for (size_t p = 0, q = 0; p != line.npos; p = q) {
    // Split if the length 1 substring after is a comma
        temp.push_back(line.substr(p + (p != 0),(q = line.find(seperator_char, p + 1)) - p - (p != 0)));
    }
    return temp;
}

// Print users with gear checked out
void printUsersCurr(vector<std:string> currUsers){
    std::cout <<"\nThe people with gear checked out are: "<< std::endl;
    //for (auto i:currUsers){
    for(int i = 0 ; i < currUsers.size() ; i++){
        std:string temp = i;
        splitString(temp, '\\')
        //temp = temp.split("\\.", 2)[0];
        //System.out.print(temp);
        std::cout << temp << "   " << std::endl;
    }
    std::cout << std::endl;
}


// Given a string gets a string
string getStrInput(string prompt){
    std::string stringIn;
    std::cout << prompt << std::endl;
    std::getline (std::cin, stringIn);
    return stringIn;
}

void view(std::vector<string> &a){
    bool testUser = false;
    bool hitB = false;
    
    do{
        printUsersCurr(a);
        string user = getStrInput("If you would like to view a users list enter the name. Otherwise hit 'b' to go back ");
        
        tolower(user);
        user = user + ".txt";
        
        if(a.contains(user)) {
            testUser = true;
            // Print the users gear file
            std::vector<string> gear;
            gear = readGearFile(user);
            for(string item: gear){
                std::cout << item << " ";
            }
            std::cout << std::endl;
            
        }else if( user == "b.txt")){
            testUser = true;
            hitB = true;
        }else{
            std::cout << "That user was not found!" std::endl;
        }
        
    }while(!testUser || !hitB);
    
}

void printMenu(){
        std::cout << " -----------------------------------" <<
                         "-------------------------------" << std::endl;
        std::cout << "\n| Check [O]ut Gear | Check [I]n Gear | " <<
                         "[V]iew Gear in Use | [Q]uit |\n" << std::endl;
        std::cout << " ------------------------------------" <<
                         "------------------------------" << std::endl;
}

int main() {
    
    std::vector<string> nameList;
    
    bool valid_bool = false;
    bool hitQ = false;
    
    std::string<string> input_vector;
    input_vector = readNameFile();
    if(input_vector.size() == 0){
        std::cout << "Error Reading Gear! Quitting..." << std::endl;
        return 0;
    }
    
    do {
        std::cout << "");
        printMenu();
        string string_in = getStrInput("");
        tolower(string_in);
        if ((s == "v") || (s == "o")|| (s == "i") || (s == "q") ) {
            valid_bool = true;
            if(s.equals("v")){
                // View the check outs
                view(a);
            }else if(s.equals("o")){
                // Check out gear
                checkOut(a);
            }else if(s.equals("i")){
                checkIn(a);
                // Check in Gear
            }else if(s.equals("q")){
                hitQ = true;
            }
            
        } else {
            std::cout << "Seems you entered an invalid command. " +
            "Please try again." << std::endl;
        }
        
        // Works Now!
        // System.out.print("Check outs will not appear until the program is restarted.\n");
        
    }while(!valid_bool || !hitQ);
    
    std::cout <<"Quitting.....";
    writeNameFile(a, "names");
    std::cout << "  Done." << std::endl;

    return 0;
}
