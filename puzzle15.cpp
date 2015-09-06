//******************************************************
// File: puzzle15.cpp
// Description:  15-Tile Puzzle Game
// Author: CS 103 
// Notes: To move a tile you should just type the number
//        of the tile.  Also the blank tile is represented
//        by the value 0
//******************************************************

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Prototypes
void shuffle(int [], int);
bool isSolved(int []);
void printBoard(int []);
bool checkAndMove(int [], int);

const int DIM = 4;

int main()
{
  int tiles[DIM*DIM];
  int tileToMove;
  int numMoves;

  // Seed random number generator
  srand(time(0));

  // Initialize the board then permute it
  for(int i=0; i < DIM*DIM; i++){
    tiles[i] = i;
  }

  // Ask user for number of scrambling moves
  cout << "How many scrambling moves should be attempted: " << endl;
  cin >> numMoves;

  // Scramble the tiles
  shuffle(tiles, numMoves);

  // Primary gameplay loop
  while ( !isSolved(tiles) ){
    printBoard(tiles);

    // Get a selection from the user
    cout << "\n\nEnter a tile to move: ";
    cin >> tileToMove;
    cout << endl;
    
    if( ! checkAndMove(tiles, tileToMove) ){
      cout << "Invalid tile to move" << endl;
    }
  }
  cout << "You win!!" << endl;
  return 0;
}

// Permute the tiles -- this is a really bad
//  way of initializing because we'll just
//  randomly guess a tile and try to move it
//  but if it's not next to the blank tile
//  it will not do anything

void shuffle(int tiles[], int numMoves )
{
  for(int i=0; i < numMoves; i++){
    // what range of values could be produced
    //  by 1 + rand()%(DIM*DIM-1)
    int tileToMove = 1+rand()%(DIM*DIM-1);
    checkAndMove(tiles, tileToMove);
  }
}

// Check if the game is solved
bool isSolved(int tiles[])
{




int a = 0;

for (int i = 0; i <= 15; i++) {
	if (i == tiles[i]) {
	a++;
	}
}

if (a == 16) {
	return true;
}
else {
	return false;
}
}




// Print the tile values in a DIMxDIM grid 
//  with 3-spaces per column
void printBoard(int tiles[])
{

int a = 1;
cout << "|";
for (int i = 0; i <= 15; i++) {
	
	if (tiles[i] == 0) {
	cout << "   |";
	a++;
	}
	else{

	cout << setw(3) << tiles[i] << "|";
	if ((a % 4) == 0) {
	
	cout << "\n----------------\n";
	if (i != 15) {
	cout << "|";
	}
	}
	a++;
	}
}
}


// returns true is move was able to be completed
// successfully, false otherwise
bool checkAndMove(int tiles[], int tileVal)
{
  int tileIdx = -1;
  int blankIdx = -1;
  bool valid = false;

  // Do sanity check
  if(tileVal >= DIM*DIM || tileVal < 0){
    return false;
  }

  // Find the given index of the given tile value 
  //  and blank tile
  for(int i=0; i < DIM*DIM; i++){
    if(tiles[i] == tileVal){
      tileIdx = i;
    }
    if(tiles[i] == 0){
      blankIdx = i;
    }
  }

  // Check if the blank and specified tile are
  //  next to each other
  // Check up
  if(tileIdx - DIM >= 0 && (tileIdx - DIM) == blankIdx){
    valid = true;
  }
  // Check down
  else if(tileIdx + DIM < (DIM*DIM) && (tileIdx + DIM) == blankIdx){
    valid = true;
  }
  // Check right
  else if( (tileIdx % DIM) != (DIM-1)  && (tileIdx + 1) == blankIdx){
    valid = true;
  }
  // Check left
  else if( (tileIdx % DIM) != 0  && (tileIdx - 1) == blankIdx){
    valid = true;
  }

  // Move the tile if valid
  if(valid){
    tiles[tileIdx] = tiles[blankIdx];
    tiles[blankIdx] = tileVal;
  }
  // Return our status
  return valid;
}

