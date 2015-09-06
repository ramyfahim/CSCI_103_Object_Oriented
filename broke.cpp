#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;
int main(int argc, char *argv[])
{

int coins;
double probability;
int games;

int turns = 0;

srand(time(0));

//prompt for and receive appropriate inputs

cout << "Welcome to the GOING BROKE game simulation!" << endl;

cout << "Please enter the number of initial coins for each player: " << endl;
cin >> coins;

cout << "Please enter the coin fairness (probability of heads) with two decimal places (0.00 - 0.99): " << endl;
cin >> probability;

cout << "Please enter the number of total game simulations to perform: " << endl;
cin >> games;



// make array containing number of coins for each player
int playercoins [] = {coins, coins, coins};


// for loop simulating all the different full games
for (int i = 0; i < games; i++) {

// reset number of coins for each player to user-selected amount
playercoins [0] = coins;
playercoins [1] = coins;
playercoins [2] = coins;



// while loop for a single game (until one player goes broke)
// if one player has a number of coins that is not greater than zero (the number would be 0 - a player gone broke), then the while loop's condition evaluates to false and it does not run.
while ((playercoins[0] > 0) && (playercoins[1] > 0) && (playercoins[2] > 0)) {


// make boolean data types for each player's toss (true = heads and false = tails)
bool player1;
bool player2;
bool player3;





// make toss result for first player

// turn randomly generated number into proper format (for comparison with user's probability input)
double outcome = ((double)rand())/RAND_MAX;

// true = heads and false = tails

if (outcome < probability) {
	player1 = true;
}
else {
	player1 = false;
}




// make toss result for second player

outcome = ((double)rand())/RAND_MAX;

// true = heads and false = tails

if (outcome < probability) {
	player2 = true;
}
else {
	player2 = false;
}





// make toss result for third player

outcome = ((double)rand())/RAND_MAX;

// true = heads and false = tails

if (outcome < probability) {
	player3 = true;
}
else {
	player3 = false;
}



// use logical comparisons to determine outcome of turn and consequent exchange of coins

if ((player1 == player2) && (player2 == player3)) {
	turns++;
}
else if ((player1 != player2) && (player1 != player3)) {
	playercoins[0] += 2;
	playercoins[1] -= 1;
	playercoins[2] -= 1;
	turns++;
}
else if ((player2 != player1) && (player2 != player3)) {
	playercoins[0] -= 1;
	playercoins[1] += 2;
	playercoins[2] -= 1;
	turns++;
}
else if ((player3 != player1) && (player3 != player2)) {
	playercoins[0] -= 1;
	playercoins[1] -= 1;
	playercoins[2] += 2;
	turns++;
}



}


}

// calculate average number of turns per game
double averageturns = (double)turns/games;

cout << "Average number of turns per game: " << averageturns << endl;


  return 0;
  
}
