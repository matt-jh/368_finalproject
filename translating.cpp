#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

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
		if (std::any_of(users.begin(), users.end(), user+".txt") && user !="b"){
		//if (a.contains(user+".txt") && (user !="b"){
			do {
				std::string all = getStrInput("Are you returning all items? (y/n)");
				tolower(all);
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
				std::cout << "\nHere is a list of the gear you checked " +
				"out and the expected return date\n" << std::endl;
				
				// Print the users gear file
				std::vector<std::string> gear = readGearFile(user + ".txt");
				for (auto item : gear) {
					std::cout << item << " " << std::endl;
				}
				// Find equiv of regexp
				string outstanding[]=getStrInput("Please enter the items that "+
						"you are not yet returning in the formPlease put '/' " +
						"between items (no space needed) and ',' between the " +
						"item name and the quantity(no space needed)." +
						"\nFor Example: sleeping pad,2/tent,1").split("\\s*\\/\\s*");
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

					//remove(user+".txt");
					
					// C++ Equivalent
					File f = new File(user + ".txt");
					f.createNewFile();
					// bool b = f.delete();
					
				} catch (std::exception& e) {
					std::cout << "Error in file update! Return the hear " +
									 "normally and if\nany one asks tell them you got " +
									 "this error.\nIts possible your gear was already" +
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

//public static void checkOut(ArrayList<String> a){
void checkOut(std::vector<std::string> users){

        //ArrayList<String> checkOutGear = new ArrayList<String>();
		std::vector<std::string> checkOutGear;

		bool hitB = false;
        //boolean hitB = false;

        do {
            //String t = getStrInput("Please enter the trip leader's lastname or hit 'b' to go back.");
            std::string t = getStrInput("Please enter the trip leader's lastname or hit 'b' to go back.");

            //if (!t.toLowerCase().equals("b")) {
            f (!t.toLowerCase.equals("b")) {
                String temp = getStrInput(
                        "Please enter the trip leader's first initial.");
                String s = temp + t; // First_initialLastname
                s.toLowerCase();
                String r = getStrInput(
                        "Please enter the expected date for returning the gear. " +
                                "(mm/dd/yy)");

                temp = s + ".txt";
                if (a.contains(temp)) {
                    // Include Date
                    s += 2;
                    System.out.println("It looks like you already have gear checked out." +
                            " You can check out more, but please remember to return " +
                            "both sets of gear.\n");
                }

                String items = getStrInput("Please enter all the items you wish " +
                        "to use and the quantity of that item.\nPlease put '/' " +
                        "between items (no space needed) and ',' between the" +
                        "\nitem name and the quantity(no space needed).\n" +
                        "For Example: sleeping pad,2/tent,1");

                // Add to an arraylist
                //String split[] = items.split("\\s*/\\s*");
                String split[] = items.split("\\s*\\/\\s*");
                for(String tempSplit : split){
                    checkOutGear.add(tempSplit);
                }

                checkOutGear.add(r);

                // Write the file
                System.out.print("Saving File.....");
                writeGearFile(checkOutGear, s);
                System.out.println("\nDone.");

                // Add to the list of names
                a.add(s + ".txt");
                // Create a file with the given name (.txt) in the current directory

                System.out.println("Items Recorded! Have Fun!");

                hitB = true;
            } else {
                hitB = true;
            }
        }while(!hitB);

    }

