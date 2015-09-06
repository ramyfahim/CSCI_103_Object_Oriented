#include <iostream>
#include <cstdlib>
#include <ctime>
#include "deck.h"
#include "card.h"
#include "warplayer.h"

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cout << "Provide number of games to simulate and 1=debug, 0=no debug " << endl;
    return 1;
  }
  srand(time(0));
  int numSims = atoi(argv[1]);
  bool debug = atoi(argv[2]);
  int numBattles = 0;
  int numWars = 0;
  int p1Wins = 0;
  int p2Wins = 0;
  for(int i=0; i < numSims; i++){

    // Write your single game of War code here (or decompose 
    // the single game into smaller functions that you write)
    // We've started things for you



    // Declare and prepare your deck then print it out to double check
    Deck d;
    d.shuffle();
    d.cut();
    if(debug){
      d.printDeck();
    }

    // Declare the two players and deal the cards to the two players

	WarPlayer player1, player2;


	for (int i = 0; i < 26; i++) {
		player1.addCard(d.getTop());
		player2.addCard(d.getTop());
		}


    // Write a loop that plays one turn at a time, until the game is over
    // Remember each player takes their top card, compares them, and the
    //  player with the greater-valued card gets back both
    // If there is a tie, each player flips one more card (provided they have
    //  one more), with the player with the greater-valued 2nd card getting
    //  all the cards.  If they don't have one more to flip, that player 
    //  immediately loses

    // Be sure to update the statistics variables, numBattles, numWars,
    //  p1Wins, p2Wins, etc.


	Card c1, c2, c3, c4;
	while (player1.sizecheck() && player2.sizecheck()) {

		numBattles++;

     c1 = player1.removeTopCard();
     c2 = player2.removeTopCard();
    

     if (c1.compare(c2) == -1)
     {player2.addCard(c2);
      player2.addCard(c1);
     }

     else if (c1.compare(c2) == 1)
     {player1.addCard(c1);
      player1.addCard(c2);
     }

     else
     {
      if (player1.sizecheck()==0 || player2.sizecheck() == 0)
      break;
			numWars++;

      c3 = player1.removeTopCard();
      c4 = player2.removeTopCard();



      if (c3.compare(c4) == -1){
      player2.addCard(c2);
      player2.addCard(c4);
      player2.addCard(c1);
      player2.addCard(c3);
      }

     else if (c3.compare(c4) == 1){
      player1.addCard(c1);
      player1.addCard(c3);
      player1.addCard(c2);
      player1.addCard(c4);
      }

      else{
      player1.addCard(c2);
      player2.addCard(c4);
      player1.addCard(c1);
      player2.addCard(c3);     
      }
     }

    }

  if (player1.sizecheck() == 0)
  p2Wins++;
  if (player2.sizecheck() == 0)
  p1Wins++;
		}
	 // end for
  // Print statistics
  cout << "Total Battles = " << static_cast<double>(numBattles)/numSims << endl;
  cout << "Total Wars = " << static_cast<double>(numWars)/numSims << endl;
  cout << "P1 wins = " << p1Wins << endl;
  cout << "P2 wins = " << p2Wins << endl;
  return 0;
}
