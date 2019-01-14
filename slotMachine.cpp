#include "slotMachine.h"

//=========reel methods================================

//---------------------------\
// reel.spin()                \
//----------------------------------------------------------------
// Simulates the reel spinning by returning a character at random.
// Precondition: A reel object must have been declared.
// Postcondition: Character displayed on reel returned.
//----------------------------------------------------------------
string reel::spin() {
    // Rarest to least rare
    // ✪ - rarest
    // ❆
    // ❤
    // ✤
    // ✔
    // ✖ - least rare
    int randomNumber = (rand() % UPPER_BOUND);      // generate a random number from 0 to 100
    int index;                                      // which index from the string will be returned

    // ✖ returned if 0 to 60
    if (randomNumber <= X_UPPER){
        index = X_INDEX;
    }

    // ✔ returned if 61 to 71
    else if (randomNumber > X_UPPER and randomNumber <= CHECK_UPPER) {
        index = CHECK_INDEX;
    }

    // ✤ returned if 72 to 81
    else if (randomNumber > CHECK_UPPER and randomNumber <= SPOKE_UPPER) {
        index = SPOKE_INDEX;
    }

    // ❤ returned if 82 to 91
    else if (randomNumber > SPOKE_UPPER and randomNumber <= HEART_UPPER) {
        index = HEART_INDEX;
    }

    // ❆ returned if 92 to 98
    else if (randomNumber > HEART_UPPER  and randomNumber <= SNOWFLAKE_UPPER) {
        index = SNOWFLAKE_INDEX;
    }

    // ✪ returned if 99 to 100
    else if (randomNumber > SNOWFLAKE_UPPER and randomNumber <= STAR_UPPER) {
        index = STAR_INDEX;
    }

    string displayChar = rollOptions[index];   // the character that will be displayed/returned

    return displayChar;
}
//=======================================================


//================slot_machine methods===================

//-----------------------------------------------------\
// Default Constructor                                  \
//------------------------------------------------------------------------------
// Creates the slot_machine object.
// Postcondition: slot_machine object created and initial coins stored in money.
//------------------------------------------------------------------------------
slot_machine::slot_machine() {
    // get initial balance
    cout << "Enter Initial Amount of Coins: ";
    cin >> this->money;

    // if illegal amount keep asking..
    while (this->money <= 0) {
        cout << "Not Legal Initial Amount." << endl;
        cout << "Enter Initial Amount of Coins: ";
        cin >> this->money;
    }

    // print balance to console
    cout << this->money << " Coins Entered" << endl;
}

//----------------------------------------------------------------\
// slot_machine.checkLegalBet()                                    \
//-------------------------------------------------------------------------------
// Checks if the bet made by the player is more than balance.
// Parameters: questionableBet - an int tested if more than current balance.
// Precondition: questionableBet must be an int. money must hold current balance.
// Postcondition: Bool returned on whether the bet is higher than balance or not.
//-------------------------------------------------------------------------------
bool slot_machine::checkLegalBet(int questionableBet) {
    // check if bet too high
    if (questionableBet > this->money) {
        cout << "Bet Higher Than Balance." << endl;

        return true;
    }

    // check if bet too low
    else if (questionableBet < 0) {
        cout << "Can't Enter Negative Bet... " << endl;

        return true;
    }

    // at this point: bet is legal
    else {

        return false;
    }
}

//------------------------------------------------------\
// slot_machine.play()                                   \
//-----------------------------------------------------------------------
// Simulates the game. Recieves bet and spins specified number of reels.
// Parameters: numberOfReels - an int: how many reels on this machine.
// Precondition: numberOfReels must be an int > 2 and < 6.
// Postcondition: Game is played out. Bets recieved. -1 sentinel value.
//-----------------------------------------------------------------------
void slot_machine::play(int numberOfReels) {
    string result;              // stores the current char from each spin
    bool notLegalBet = true;    // decides if bet is legal or not
    bool playAgain = true;      // decides if user wants to play again

    // continue to play until out of money or until -1 for bet
    while (playAgain) {
        // return based on no money
        if (this->money <= 0) {
            cout << "You Have No More Money... See Yah." << endl;

            return;
        }
        // keep prompting for bet until its valid or if it is -1 to quit
        while (notLegalBet) {
            // get bet
            cout << "Please Enter Your Bet (-1 to quit): ";
            cin >> this->bet;

            // quit game
            if (this->bet == SENTINEL_VALUE) {
                cout << "\nThanks For Playing!" << endl;
                cout << "Your Payout: " << this->money << " Coins"<< endl;

                return;
            }

            // just some friendly banter
            else if (this->bet == 0) {
                cout << "You Won't Win Anything. But Go For It." << endl;
            }

            // check if bet is a legal one
            notLegalBet = this->checkLegalBet(this->bet);
        }

        // deduct bet from money
        this->money -= this->bet;

        // spin the reel
        cout << endl << "---SPINNING!---" << endl;
        cout << setw(WIDTH) <<" ";
        for (int i = 0; i < numberOfReels; ++i) {
            result = reel::spin();                  // store result
            cout << result << " ";                  // print resole to console
            this->reelResults.push_back(result);    // store result in vector
        }

        cout << endl;
        this->checkForWin(reelResults);             // go and see if they won and how much they won.

        // reset slot reels
        notLegalBet = true;
        reelResults.clear();                        // empty vector
    }
}

//------------------------------------------\
// slot_machine.winnings()                   \
//---------------------------------------------------------------------------------
// Calculates winnings based on character producing the win.
// Parameters: lastBet - int holding most recent bet entered,
//             winningChar - str holding image that appeared 3 or more times,
//             howMany - int holding how many in a row.
// Precondition: User must have won. lastBet >= 0 && < balance, how many > 2 && < 6
// Postcondition: Winnings calculated and returned based on winningChar and howMany.
//---------------------------------------------------------------------------------
int slot_machine::winnings(int lastBet, string winningChar, int howMany) {
    // Rarest to least rare
    // Winning base numbers x bet
    // ✪ three: 500.. four: 1000.. five: 10000
    // ❆ three: 100.. four: 300.. five: 400
    // ❤ three: 50.. four: 100.. five: 300
    // ✤ three: 20.. four: 40.. five: 80
    // ✔ three: 15.. four: 30.. five: 60
    // ✖ three: 10.. four: 20.. five: 40

    int winMoney = 0;           // how much money user wins
    int baseNumber = 0;         // number to be multiplied by bet

    //----------WINNING AMOUNTS-----------------------
    if (winningChar == "✖") {
        baseNumber = xWin[howMany-INITIAL_INDEX];
    }

    else if (winningChar == "✔") {
        baseNumber = checkWin[howMany-INITIAL_INDEX];
    }

    else if (winningChar == "✤") {
        baseNumber = spokeWin[howMany-INITIAL_INDEX];
    }

    else if (winningChar == "❤") {
        baseNumber = heartWin[howMany-INITIAL_INDEX];
    }

    else if (winningChar == "❆") {
        baseNumber = snowflakeWin[howMany-INITIAL_INDEX];
    }

    else if (winningChar == "✪") {
        baseNumber = starWin[howMany-INITIAL_INDEX];
        cout << "JACKPOT!!!" << endl;
    }
    //--------------------------------------------------

    winMoney = baseNumber * lastBet;    // calculate how much money was won.

    return winMoney;
}

//----------------------------------\
// slot_machine.checkForWin()        \
//---------------------------------------------------------------------------
// Checks all the scenarios a user could have won.
// Parameters: slotResults - vector of strings representing each reel.
// Precondition: slotResults have to be generated from spin or play function.
// Postcondition: If won.. coins added to current balance.
//                If loss.. message displayed to screen.
//                Current balance displayed.
//---------------------------------------------------------------------------
void slot_machine::checkForWin(vector<string> slotResults) {
    int coinsWon = 0;           // stores how many coins won

    //----User Wins---------------------------------------------------------------

    // five in a row
    if (slotResults[0] == slotResults[1] && slotResults[0] == slotResults[2]
        && slotResults[0] == slotResults[3] && slotResults[0] == slotResults[4]) {
        coinsWon = winnings(this->bet, slotResults[0], 5);
    }

    // four in a row (first four)
    else if (slotResults[0] == slotResults[1] && slotResults[0] == slotResults[2] && slotResults[0] == slotResults[3]) {
        coinsWon = winnings(this->bet, slotResults[0], 4);
    }

    // four in a row (second four)
    else if (slotResults[1] == slotResults[2] && slotResults[1] == slotResults[3] && slotResults[1] == slotResults[4]) {
        coinsWon = winnings(this->bet, slotResults[1], 4);
    }

    // three in a row (first three)
    else if (slotResults[0] == slotResults[1] && slotResults[0] == slotResults[2]) {
        coinsWon = winnings(this->bet, slotResults[0], 3);
    }

    // three in a row (second group of three)
    else if (slotResults[1] == slotResults[2] && slotResults[1] == slotResults[3]) {
        coinsWon = winnings(this->bet, slotResults[1], 3);
    }

    // three in a row (third group of three)
    else if (slotResults[2] == slotResults[3] && slotResults[2] == slotResults[4]) {
        coinsWon = winnings(this->bet, slotResults[2], 3);
    }
    //-------------------------------------------------------------------------------

    // if user loses
    else {
        cout << "Sorry, Try Again" << endl;
        cout << "Lost " << this->bet <<" Coins.." << endl;
        cout << "Current Balance: " << money << endl;

        return;             // if user loses exit function
    }

    // show winnings
    cout << "YOU WIN" << endl;
    cout << "You Won: " << coinsWon << " Coins!" << endl;

    // add winnings to current balance
    this->money += coinsWon;
    cout << "Current Balance: " << money << endl;
}

//=======================================================

//================three_reel methods=====================

//------------------------------\
// three_reel.spin()             \
//-----------------------------------------------------------
// Simulates spinning a three reel machine.
// Precondition: Three reel machine must be constructed.
// Postcondition: Game is played out on a three reel machine.
//-----------------------------------------------------------
void three_reel::spin() {
    slot_machine::play(this->reels);
}
//=======================================================

//================four_reel methods======================

//--------------------------------\
// four_reel.spin()                \
//-----------------------------------------------------------
// Simulates spinning a four reel machine.
// Precondition: Four reel machine must be constructed.
// Postcondition: Game is played out on a four reel machine.
//-----------------------------------------------------------
void four_reel::spin() {
    slot_machine::play(this->reels);
}
//=======================================================

//================five_reel methods======================

//--------------------------------\
// five_reel.spin()                \
//------------------------------------------------------------
// Simulates spinning a five reel machine.
// Precondition: Five reel machine must be constructed.
// Postcondition: Game is played out on a five reel machine.
//------------------------------------------------------------
void five_reel::spin() {
    slot_machine::play(this->reels);
}
//=======================================================