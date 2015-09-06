// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype
void permute(char items[], int len);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char *wordBank[] = {"computer","president","trojan","program","coffee",
			  "library","football","popcorn","science","engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // More initialization code


	char* targetWord = new char[targetLen+1];
	strcpy( targetWord, wordBank[target] );
	permute( targetWord, targetLen );
	cout<< "target word: " << targetWord << endl;

  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while ( !wordGuessed && numTurns > 0 ){

	cout << "your scrambled word: " << targetWord << endl;
	cout << "Enter your guess: ";
	cin >> guess;

	if ( !strcmp(guess, wordBank[target]) ) {
	wordGuessed = true;
	}


  }
  if(wordGuessed){
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }

numTurns--;
    
  return 0;
}

// Scramble the letters
void permute(char items[], int len)
{
  for(int i=len-1; i > 0; --i){
    int r =  rand() % i;
    int temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }

}

