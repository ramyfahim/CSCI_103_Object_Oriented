#include <iostream>
#include <fstream>
#include "maze_io.h"

using namespace std;

/*************************************************
 * Open the file specified by filename, and read the 
 * maze into a dynamically allocated array.
 * 
 * Return the pointer to that array (don't delete it..
 * we'll do that in main() ).  Return NULL if
 * you are unable to open the file or can't read
 * the dimensions.
 *
 * We also pass in two pointers to integers. Fill 
 *  the integers pointed to by these arguments
 *  with the number of rows and columns 
 *  read by from the file (first two value
 *  in the file)
 *
 *************************************************/

char * read_maze(char *filename, int *rows, int *cols )
{


	ifstream ifile (filename); // open maze from file stated in parameter
	if (ifile.fail()) { //check if file is valid
		cout << "Invalid file" << endl;
		return NULL;
	}


	ifile >> *rows;

	ifile >> *cols;


// allocate appropriately sized memory for array containing maze from heap
	char* maze_array = new char[((*rows) * (*cols))];

// step through file and grab each character, and append it to maze_array
	char ch;
	for (int i = 0; i < (((*rows)*(*cols))); i++) {
		ifile >> ch;
		maze_array[i] = ch;
	}



	return maze_array;


}

/*************************************************
 * Print the maze contents in a 2D format to the
 * screen
 *
 *************************************************/
void print_maze(char *maze, int rows, int cols)
{

// print characters stored in maze array one by one and next to each other. skip to a new line if end of row of maze is reached.
for (int i = 0; i <= ((rows*cols)-1); i++) {
	cout << maze[i];
	if (((i+1) % cols) == 0) {
		cout << "\n";
	}
	
}

}

/*************************************************
 * Write maze should open the file specified by 
 * filename and write the contents of the maze
 * array to the file with the dimensions on the first
 * line.
 *
 *************************************************/
void write_maze(char *filename, char *maze, int rows, int cols)
{

// access file stated in parameter
	ofstream ofile (filename);

// print number of rows and columns into file
	ofile << rows << " " << cols << endl;

// print all characters of maze into file by using the same method that was used in print_maze
for (int i = 0; i <= ((rows*cols)-1); i++) {

	ofile << maze[i];
	if (((i+1) % cols) == 0) {
		ofile << "\n";
	}
	
}



}
