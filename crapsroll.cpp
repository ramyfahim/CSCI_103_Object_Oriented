// crapsroll.cpp
//  Game generates a random point number: 2-6 or 8-12
//  Then we let the user take turns betting and rolling.
//  If they roll a 7 the game is over and they lose their bet
//  If they roll the point number the game ends but they win their bet
//  Any other roll is a push and the game continues
//
//  Complete the function definitions and calls to get practice
//   using pointers

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


// Takes in and generates die value rolls (each a num. 1-6)
void getDiceRoll(int* die1, int* die2)
{

	*die11 = rand()%6 +1;
	*die11 = rand()%6 +1;



}

// Takes in die value argument by reference, generates them,
//  then returns the bet value
int betAndRoll(int* die1, int* die2)
{
  int bet;
  cout << "Enter a bet: ";
  cin >> bet;
  cout << endl;

  getDiceRoll(die1, die2);
  return bet;
}

int main()
{
  int point, bet, die1, die2;
  srand(time(0));
  // Generate 2,3,4,5,6,8,9,10,11,12
  int myrand = rand() % 10;
  if(myrand >= 5){
    point = 3 + myrand; // Skip 7
  }
  else {
    point = 2 + myrand;
  }
  cout << "The point number is " << point << endl;

  bool doneFlag = false;
  while( !doneFlag ){

    // Complete the call
    int bet = betAndRoll(&die1, &die2);
    
    if(die1 + die2 == 7){
      cout << "Game over!! You lost " << bet << endl;
      doneFlag = true;
    }
    else if(die1 + die2 == point){
      cout << "Game over!! You won " << bet << endl;
      doneFlag = true;
    }
    else {
      cout << "Push...Take back your bet" << endl;
    }
  }

}



