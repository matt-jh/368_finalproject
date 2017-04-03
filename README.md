## CS368 FINAL PROJECT
### Hoofers Gear Checkout System
##### The application will be created in three stages:
1) We will develope a command line version of the application that allows for all of the operations needed by the Hoofers Outing Club. This initial version will use .txt files to store the data
2. We will then modify the program to store the data in an SQL database instead of a series of .txt files.
3. We will then create a GUI for the program so that it can be used outside the commandline. The current plan is to create a GUI window that will print the same information and text as the terminal in the windows. The user input will be done by creating a text box and passing the input into the same functions as the commandline. If time permits we may break the tex input down into individual input fields.
##### The Main class will run the entire program and will eventually call the GUI class or be incorporated into a GUI class. It has the functions for the user to interact with the program by adding or removing trips and viewing who is using gear.
##### The GUI is the lowest priority so if time is short we will focus on SQL before the GUI.
##### Currently the main class has 8 of 11 functions built, but testing and debugging will likely be required.
##### TODO:
 - writeGearFile
    * Will take the changes made by the user and write the gear they are using to a .txt file that is their name.
 - writeNameFile
    * Will write the name of the user into the names.txt file so a user can see what gear they are using.
 - checkOut
    * Will allow the user to check out gear by entering their name and the date they plan on returning their gear before listing the gear that they are using.
    
