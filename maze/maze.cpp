#include <iostream>
#include "maze_io.h"
#include <deque>
using namespace std;

// Prototype for maze_search
int maze_search(char *, int, int);

int main(int argc, char *argv[])
{
  int rows, cols, result;
  char *mymaze;

  if(argc < 3){
    cerr << "Usage: ./maze in_filename out_filename" << endl;
    return 1;
  }

  mymaze = read_maze(argv[1], &rows, &cols);


  // For checkpoint 1, just leave maze_search() unedited
  //  and the program should read in the maze, print it
  //  and write it back to the output file
  result = maze_search(mymaze, rows, cols);

  if( result == 1 ){
    cout << "Path successfully found!" << endl;
    print_maze(mymaze,rows,cols);
    write_maze(argv[2],mymaze,rows,cols);
  }
  else if (result == 0) {
    cout << "No path could be found!" << endl;
  }
  else {
    cout << "Error occurred during search!" << endl;
  }

  delete [] mymaze;

  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if an error occurred (no start of finish
 *     cell present in the maze)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char *maze, int rows, int cols)
{

// allocate appropriately sized memory for breadth-first-search-queue array from heap
	//char* bfsq = new char[rows*cols];

	deque<int> dfsq;

// allocate appropriately sized memory for backtrack/predecessor array from heap
	int* backtrack = new int[rows*cols];


// check for how many Start and Finish blocks there are in the maze. create 2 new variables to store amount of instances for each. step through maze and increment the corresponding variable if an 'S' or 'F' block is found
	int scheck = 0;
	int fcheck = 0;
	for (int i = 0; i < (rows*cols); i++) {
		if (maze[i] == 'S') {
			scheck += 1;
		}
		else if (maze[i] == 'F') {
			fcheck += 1;
		}
		else {}
	}



// populate backtrack array. -1 if anything except start block ('S').
	int a = 0;

	for (int i = 0; i < (rows*cols); i++) {
		if (maze[i] != 'S') {
			backtrack[i] = -1;
		}
		else {
			backtrack[i] = -2;
			a = i; // grab position of start
		}
	}


// declare head and tail variable indices for bfsq array
	int front = 0;
	int back = 0;

// assign first entry (start block) in bfsq array an increment tail index (to be ready to store next appended assignment)
	dfsq.push_back(a);
	front++;


	int r;
	int c;


// if one start block and one finish block are found, begin searching for shortest path
if (scheck == 1 && fcheck == 1) {

// perform maze search as long as front does not equal back (this scenario would mean that the entire maze has been searched and no path to the finish block was found).
	while (dfsq[front] != 'F') {

// convert current index to row & column format
		r = a/cols;
		c = a%cols;


// check north block if it is either a movable space or a finish block, and if it has not been visited before
// perform appropriate appendings to arrays
		if (((maze[((r-1)*cols + c)] == '.') || (maze[((r-1)*cols + c)] == 'F')) && backtrack[((r-1)*cols + c)] == -1) {
			dfsq[front] = ((r-1)*cols + c);
			front++;
			backtrack[((r-1)*cols + c)] = a;
		if (maze[((r-1)*cols + c)] == 'F') {
			a = ((r-1)*cols + c);
			break; // break out of while loop if finish block is found
		}
	}
			

// check south block if it is either a movable space or a finish block, and if it has not been visited before
// perform appropriate appendings to arrays
		if (((maze[((r+1)*cols + c)] == '.') || (maze[((r+1)*cols + c)] == 'F')) && backtrack[((r+1)*cols + c)] == -1) {
			dfsq[front] = ((r+1)*cols + c);
			front++;
			backtrack[((r+1)*cols + c)] = a;
		if (maze[((r+1)*cols + c)] == 'F') {
			a = ((r+1)*cols + c);
			break; // break out of while loop if finish block is found
		}
	}


// check south block if it is either a movable space or a finish block, and if it has not been visited before, and it does not require passing through an ede of the maze
// perform appropriate appendings to arrays
		if (((maze[(r*cols + (c-1))] == '.') || (maze[(r*cols + (c-1))] == 'F')) && (((r*cols + c))%cols != 0) && backtrack[(r*cols + (c-1))] == -1) {
			dfsq[front] = (r*cols + (c-1));
			front++;
			backtrack[(r*cols + (c-1))] = a;
		if (maze[(r*cols + (c-1))] == 'F') {
			a = (r*cols + (c-1));
			break; // break out of while loop if finish block is found
		}
	}


// check south block if it is either a movable space or a finish block, and if it has not been visited before, and it does not require passing through an ede of the maze
// perform appropriate appendings to arrays
		if (((maze[(r*cols + (c+1))] == '.') || (maze[(r*cols + (c+1))] == 'F')) && (((r*cols + (c+1)))%cols != 0) && backtrack[(r*cols + (c+1))] == -1) {
			dfsq[front] = (r*cols + (c+1));
			front++;
			backtrack[(r*cols + (c+1))] = a;
		if (maze[(r*cols + (c+1))] == 'F') {
			a = (r*cols + (c+1));
			break; // break out of while loop if finish block is found
		}
	}

		front++;

// assign new value to current index from which the search will continue to be performed
		a = dfsq[front];


}


// use backtrack array to step backwards from finish block and place an * over blocks along the shortest path. stop when path reaches start block (using a break statement).
		int b = a;

		int e;
		while (true) {
			e = backtrack[b];
			if (maze[e] == 'S') {
				break;
			}
			maze[e] = '*';
			b = backtrack[b];
		}
}


// delete memory from heap
	delete [] backtrack;


// return 0 if no shortest path is found in a valid (has 1 S and 1 F) maze.
// return 1 if function successfully finds shortest path of maze.
// return -1 if there is not exactly 1 start block or if there is not exactly 1 finish block. return -1 for any other scenario.
	if (front == back && scheck == 1 && fcheck == 1) {
		return 0;
	}
	else if (front < back && scheck == 1 && fcheck == 1) {
  	return 1;
	}
	else if (scheck != 1 || fcheck != 1) {
		return -1;
	}
	else {
		return -1;
	}
}

