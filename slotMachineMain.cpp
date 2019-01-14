#include "slotMachine.h"

int main() {
    srand (time(0));            // set seed for rand function
    void howManyReels();        // function declaration
    void printPayTable();

    howManyReels();             // ask user how many reels they want to play.. then play game

    cout << "\nDONE." << endl;

    return 0;
}

//------------------------------\
// printPayTable()               \
//-------------------------------------------------------------------------
// Display pay table information to user.
// Precondition: howManyReels function called.
// Postcondition: Table displayed to stdout
//-------------------------------------------------------------------------
void printPayTable() {
    cout << "-----------PAY TABLE-----------" << endl;
    cout << "\t✖\t✔\t✤\t ❤\t ❆\t  ✪" << endl;
    cout << "5\t40\t60\t80\t300\t400\t10000" << endl;
    cout << "4\t20\t30\t40\t100\t300\t1000" << endl;
    cout << "3\t10\t15\t20\t50\t100\t500" << endl;
    cout << "--------------------------------" << endl;
}

//------------------------------\
// howManyReels                  \
//-------------------------------------------------------------------------
// Determine how many reels player wants and then set up and play the game.
// Postcondition: Game played out based on how many reels entered.
//-------------------------------------------------------------------------
void howManyReels() {
    int numOfReels;             // number of reels player wants

    // Get user input for numOfReels
    cout << "Welcome to Al’s Big Casino and Donut Emporium!" << endl;
    printPayTable();
    cout << "How Many Reels Would You Like to Play (3, 4, or 5): ";
    cin >> numOfReels;

    // Set up three reel game
    if (numOfReels == 3) {
        cout << "Setting Up Three Reel Game..." << endl;
        three_reel machineThreeReel;
        machineThreeReel.spin();

    }

    // Set up four reel game
    else if (numOfReels == 4) {
        cout << "Setting Up Four Reel Game..." << endl;
        four_reel machineFourReel;
        machineFourReel.spin();
    }

    // Set up five reel game
    else if (numOfReels == 5) {
        cout << "Setting Up Five Reel Game..." << endl;
        five_reel machineFiveReel;
        machineFiveReel.spin();
    }

    // Not valid input
    else{
        cout << "That's Not Valid. Don't Wast Al's Time." << endl;
    }
}