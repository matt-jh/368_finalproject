//import java.awt.*;
package com.company;
import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;



// TODO: TEST EVERYTHING

public class Main {

    public final String fileName = "names.txt";

    // Read in the file containing the list of active accounts
    public static ArrayList<String> readNameFile(){

        ArrayList<String> als = new ArrayList<String>();

        try {
            BufferedReader br = new BufferedReader(new FileReader("names.txt"));
            String s;

            while ((s = br.readLine()) != null) {
                als.add(s);
            }

        }catch(FileNotFoundException e){
            System.out.println("List file is missing!");
        }catch (IOException e){
            System.out.println("Error reading from file.");
        }

        return als;
    }

    // Do the same with that users gear
    public static ArrayList<String> readGearFile(String fileName) {
        ArrayList<String> als = new ArrayList<String>();

        try {
            BufferedReader br = new BufferedReader(new FileReader(fileName));
            String s;

            while ((s = br.readLine()) != null) {
                als.add(s);
            }

        }catch(FileNotFoundException e){
            System.out.println("Gear file is missing!");
        }catch (IOException e){
            System.out.println("Error reading from file.");
        }

        return als;
    }

    // Creates and writes the gear list for a user
    public static void writeGearFile(ArrayList<String> als, String s){
        String name = s;
        name += ".txt";
        try {
            PrintWriter writer = new PrintWriter(name, "UTF-8");
            for(String r: als){
                writer.println(r);
            }
            writer.close();
        } catch (IOException e) {
            System.out.println("*****File Write failed!******\nSeems the program isn't working at this time.");
        }
    }

    // Adds the user to the list
    public static void writeNameFile(ArrayList<String> als, String s){
        String name = s;
        name += ".txt";
        try {
            PrintWriter writer = new PrintWriter(name, "UTF-8");
            for(String r: als){
                writer.println(r);
            }
            writer.close();
        } catch (IOException e) {
            System.out.println("*****File Write failed!******\nSeems the program isn't working at this time.");
        }
    }

    // check out gear
    public static void checkOut(ArrayList<String> a){

        ArrayList<String> checkOutGear = new ArrayList<String>();

        boolean hitB = false;

        do {
            String t = getStrInput("Please enter the trip leader's lastname or hit 'b' to go back.");
            if (!t.toLowerCase().equals("b")) {
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

    // Check in gear
    public static void checkIn(ArrayList<String> a) {

        boolean hitB = false;

        ArrayList<String> checkOutGear = new ArrayList<String>();

        boolean returning_all = true;
        boolean check = false;

        do {
            printUsersCurr(a);
            String user = getStrInput("Please enter the user id from this list for the person returning gear or hit 'b' to o back.");

            if (a.contains(user+".txt") && !user.equals("b")){
                do {
                    String all = getStrInput("Are you returning all items? (y/n)");
                    all.toLowerCase();
                    if (all.equals("y") || all.equals("n")) {
                        if (all.equals("y")) {
                            returning_all = true;
                            check = true;
                        } else if (all.equals("n")) {
                            returning_all = false;
                            check = true;
                        }
                    } else {
                        System.out.print("Invalid input. Try again.");
                    }
                } while (!check);

                if (!returning_all) {
                    System.out.print("\nHere is a list of the gear you checked " +
                            "out and the expected return date\n");

                    // Print the users gear file
                    ArrayList<String> gear = readGearFile(user + ".txt");
                    for (String item : gear) {
                        System.out.println(item + " ");
                    }
                    String outstanding[] = getStrInput("Please enter the items that " +
                            "you are not yet returning in the formPlease put '/' " +
                            "between items (no space needed) and ',' between the " +
                            "item name and the quantity(no space needed)." +
                            "\nFor Example: sleeping pad,2/tent,1").split("\\s*\\/\\s*");

                    // Add to an arraylist
                    for (String tempSplit : outstanding) {
                        checkOutGear.add(tempSplit);
                    }

                    System.out.print("Updating File.....");
                    writeGearFile(checkOutGear, user);
                    System.out.println("  Done.\nThanks!");
                    hitB = true;

                } else {
                    try {
                        System.out.print("Updating Files.....");
                        hitB = true;
                        a.remove(user+".txt");
                        File f = new File(user + ".txt");
                        f.createNewFile();
                        boolean b = f.delete();
                    } catch (Exception e) {
                        System.out.print("Error in file update! Return the hear " +
                                "normally and if\nany one asks tell them you got " +
                                "this error.\nIts possible your gear was already" +
                                " marked returned");
                    }
                    System.out.println("  Done.\nThanks!");
                }
            }else if(user.equals("b")){
                hitB = true;
            }else{
                System.out.print("Invalid user name please try again");
            }

        }while(!hitB);
    }

    // Given a string gets a string
    public static String getStrInput(String s){
        System.out.println(s);
        Scanner scan = new Scanner(System.in);
        String t = scan.nextLine();
        return t;
    }

    // Print users with gear checked out
    public static void printUsersCurr(ArrayList<String> a){
        System.out.println("\nThe people with gear checked out are: ");
        for(int i = 0 ; i < a.size() ; i++){
            String temp = a.get(i);
            temp = temp.split("\\.", 2)[0];
            //System.out.print(temp);
            if(i < a.size()-1){
                System.out.print(temp + ", ");
            }else{
                System.out.print(temp + "\n");
            }
        }
    }

    // check on
    public static void view(ArrayList<String> a){
        boolean testUser = false;
        boolean hitB = false;
        do{

            printUsersCurr(a);
            String user = getStrInput("If you would like to " +
                    "view a users list enter the name. Otherwise " +
                    "hit 'b' to go back ");

            user.toLowerCase();
            user = user + ".txt";

            if(a.contains(user)) {
                testUser = true;
                // Print the users gear file
                ArrayList<String> gear = readGearFile(user);
                for(String item: gear){
                    System.out.println(item + " ");
                }

            }else if(user.equals("b.txt")){
                testUser = true;
                hitB = true;
            }else{
                System.out.print("That user was not found!");
            }
        }while(!testUser || !hitB);

    }

    // Prints the main menu
    public static void printMenu(){
        System.out.print(" -----------------------------------" +
                "-------------------------------");
        System.out.print("\n| Check [O]ut Gear | Check [I]n Gear | " +
                "[V]iew Gear in Use | [Q]uit |\n");
        System.out.print(" ------------------------------------" +
                "------------------------------");
    }

    // Runs it all
    public static void main(String[] args) {

        ArrayList<String> nameList = new ArrayList<String>();

        boolean b = false;
        boolean hitQ = false;

        ArrayList<String> a = readNameFile();

        do {
            System.out.println("");
            printMenu();
            String s = getStrInput("");
            s.toLowerCase();
            if (s.equals("v") || s.equals("o")||s.equals("i") || s.equals("q") ) {
                b = true;
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
                System.out.println("Seems you entered an invalid command. " +
                        "Please try again.");
            }

            // Works Now!
            // System.out.print("Check outs will not appear until the program is restarted.\n");

        }while(!b || !hitQ);
        System.out.print("Quitting.....");

        writeNameFile(a, "names");
        // Write any checkouts to the list
        // Remove any returns to the list
        // Write gear files for checkouts
        // Remove old files?
        System.out.print("  Done.");


    }

}
