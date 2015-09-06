// hangman.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char *wordBank[] = {"computer","president","trojan","program","coffee",
			  "library","football","popcorn","science","engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char word[80];  
  char guess;

  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank
 
	int w = rand()%10;
	int wl = strlen(wordBank[w]);
	char* targetWord = new char[wl+1];

	strncpy(targetWord, wordBank[w], wl);
	

	for (int m = 0; m < wl; m++) {
		word[m] = '*';
	}

	word[wl] = '\0';

  // More initialization code as needed


int i = 0;
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed

	while ( (!wordGuessed) && (numTurns > 0) ){

		cout << "Current word: " << word << endl;
		cout << numTurns << " turns left ... ";
		cout << "Guess a letter: ";
		cin >> guess;

		processGuess(word, targetWord, guess);

		if (processGuess(word, targetWord, guess) == 0) {
			numTurns--;
		}

		if ( !strcmp(word, wordBank[w]) ) {
		wordGuessed = true;
		}
	}


  // Print out end of game status

  if(wordGuessed){
    cout << "You win!" << endl;
  }
  else {
    cout << "You lose. You took too many turns." << endl;
  }

    
  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{

	int c = 0;
	int wl = strlen(targetWord);

	for (int i = 0; i < wl; i++) {
		if (targetWord[i] == guess) {
			word[i] = guess;
			c++;
		}
	}

	return c;

}

