/*
 * Description: This program simulates a casino slot machine. Users can choose to play
 *              a three, four, or five reel game. Winnings are calculated based on bet
 *              entered, number in a row, and frequency of the winning image.
 * Input: The number of reels the player wants, the initial amount of coins entered, the bet for
 *        each round (-1 terminates game). All integers that are input from keyboard <stdin>.
 * Output: The pay table (strings), various prompts for user input(number of reels, number of coins, bet)
 *         all as strings, the current balance (integer), the winnings (integer), and the loss (integer).
 */

//=====PREPROCESSORS============
#ifndef slotMachine_H
#define slotMachine_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
//==============================

//====CONSTANTS=================
const int UPPER_BOUND = 101;      // upper bound of random number generator
const int X_UPPER = 55;           // upper bound of percentage x shows
const int CHECK_UPPER = 71;       // upper bound of percentage check shows
const int SPOKE_UPPER = 81;       // upper bound of percentage spoke shows
const int HEART_UPPER = 91;       // upper bound of percentage heart shows
const int SNOWFLAKE_UPPER = 98;   // upper bound of percentage snowflake shows
const int STAR_UPPER = 100;       // upper bound of percentage star shows
const int WIDTH = 3;              // width of slot machine output
const int SENTINEL_VALUE = -1;    // terminates program
const int X_INDEX = 0;            // index for x image
const int CHECK_INDEX = 1;        // index for check image
const int SPOKE_INDEX = 2;        // index for spoke image
const int HEART_INDEX = 3;        // index for heart image
const int SNOWFLAKE_INDEX = 4;    // index for snowflake image
const int STAR_INDEX = 5;         // index for star image
const int INITIAL_INDEX = 3;      // subtracted from how many to correspond to correct winnings

using namespace std;

//==========reel CLASS-(BASE CLASS)=======================================
class reel {
protected:
    vector<string> rollOptions;             // holds character options
public:
    // CTOR
    // I tested these on the computer in the comp sci lab so it should all be good
    reel() {rollOptions = {"✖", "✔", "✤", "❤", "❆", "✪"};}      // initialize roll options to proper characters

    // Method to spin reel
    string spin();
};
//========================================================================

//===================slot_machine CLASS-(DERIVED FROM reel CLASS)=========
class slot_machine:public reel {
protected:
    vector<string> reelResults;                 // holds results of each reel
    int money;                                  // holds the current balance of player
    int bet;                                    // holds the bet made each round
    int reels;                                  // number of reels a machine has.
    vector<int> xWin = {10, 20, 40};            // winning base numbers for x
    vector<int> checkWin = {15, 30, 60};        // winning baes numbers for check
    vector<int> spokeWin = {20, 40, 80};        // winning base numbers for spoke
    vector<int> heartWin = {50, 100, 300};      // winning base numbers for heart
    vector<int> snowflakeWin = {100, 300, 400}; // winning base numbers for snowflake
    vector<int> starWin = {500, 1000, 10000};   // winning base numbers for star
public:
    // CTOR
    slot_machine();

    // Method to check if player won
    void checkForWin(/*in*/ vector<string> slotResults);

    // Method to actually play the game
    void play(/*in*/ int numberOfReels);

    // Method to check if player made a legal bet.
    bool checkLegalBet(/*in*/ int questionableBet);

    // Method to check how much money the player won.
    int winnings(/*in*/ int lastBet, /*in*/ string winningChar, /*in*/ int howMany);
};
//=========================================================================

//=========three_reel CLASS-(DERIVED FROM slot_machine CLASS)==============
class three_reel:public slot_machine {
public:
    // CTOR
    three_reel() {this->reels = 3;};
    // Spin three_reel machine.
    void spin();
};
//=========================================================================

//=========four_reel CLASS-(DERIVED FROM slot_machine CLASS)===============
class four_reel:public slot_machine {
public:
    // CTOR
    four_reel() {this->reels = 4;};
    // Spin four_reel machine.
    void spin();
};
//=========================================================================

//=========five_reel CLASS-(DERIVED FROM slot_machine CLASS)===============
class five_reel:public slot_machine {
public:
    // CTOR
    five_reel() {this->reels = 5;};
    // Spin five_reel machine.
    void spin();
};
//=========================================================================

#endif //slotMachine_H