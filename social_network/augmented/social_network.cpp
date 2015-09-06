#include "network.h"
#include "user.h"
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	// create an object that is of the class type 'network'
	network socialnetwork;

	// read users in from a file that is specified as a command line argument
	socialnetwork.read_friends(argv[1]);

	int option;

// do-while loop that runs until a menu option that is not within range is inputed
	do {

		cout << "Option 1: add user\nOption 2: add friend connection\nOption 3: remove friend connection\nOption 4: print users\nOption 5: list friends\nOption 6: write to file\nOption 7: shortest relational distance\nOption 8: disjoint groups\nOption 9: friend suggestions" << endl;
		cout << "Please input menu option (enter number) and appropriate parameters: " << endl;
		cin >> option;

		//declaration of all variables used in options
		string firstname;
		string lastname;
		string firstname2;
		string lastname2;
		char* file = new char;
		int year;
		int zip;
		int id;
		int id2;
		int e; // used for error checking
		stringstream ss;
		stringstream ss2;
		string name;
		string name2;
		user a;
		vector<int> empty; // friends vector for newly added user


	switch (option) {

	case 1:

		// receive input from user and store in proper format
		cin >> firstname >> lastname >> year >> zip;
		ss << firstname << " " << lastname;
		name = ss.str();

		// use size of vector of users to determine the ID of the new user
		id = socialnetwork.return_vector_size();


		// create an object of class type 'user' by supplying variables
		a = user(id, name, year, zip, empty);

		// add newly created user to the social network
		e = socialnetwork.add_user(a);

		if (e == -1) {
			cout << "Error: too many users" << endl;
		}

		ss.str("");
		
		break;
	case 2:
		// receive input from user and store in proper format
		cin >> firstname >> lastname >> firstname2 >> lastname2;
		ss << firstname << " " << lastname;
		name = ss.str();
		ss2 << firstname2 << " " << lastname2;
		name2 = ss2.str();

		// use function in 'network' to find the IDs in the network of the 2 usernames
		id = socialnetwork.get_id(name);
		id2 = socialnetwork.get_id(name2);


		// user function in 'network' to add a connection using the previously determined user IDs (and also check for errors)
		e = socialnetwork.add_connection(id, id2);

		if (e == -2) {
			cout << "Error: ID does not exist in network" << endl;
		}
		else if (e == -1) {
			cout << "Error: users are already friends" << endl;
		}
			

		// clear stringstreams
		ss.str("");
		ss2.str("");

		break;
	case 3:
		// receive input from user and store in proper format
		cin >> firstname >> lastname >> firstname2 >> lastname2;
		ss << firstname << " " << lastname;
		name = ss.str();
		ss2 << firstname2 << " " << lastname2;
		name2 = ss2.str();


		// use function in 'network' to find the IDs in the network of the 2 usernames
		id = socialnetwork.get_id(name);
		id2 = socialnetwork.get_id(name2);

		// user function in 'network' to remove a connection using the previously determined user IDs (and also check for errors)
		e = socialnetwork.remove_connection(id, id2);

		if (e == -1) {
			cout << "Error: ID does not exist in network" << endl;
		}

		ss.str("");
		ss2.str("");
		break;
	case 4:
		// call 'network' function to print user info for every user in the network
		socialnetwork.print_user_info();
		break;
	case 5:
		// receive input from user and store in proper format
		cin >> firstname >> lastname;
		ss << firstname << " " << lastname;
		name = ss.str();


	// use function in 'network' to find the ID in the network of the username
	id = socialnetwork.get_id(name);

		// check and take proper action if get_id function returns an error value
		if (id == -1) {
			cout << "Error: ID does not exist in network" << endl;
			break;
		}


	// use function in 'network' to print the friends of the user with the previously determined ID
	socialnetwork.print_friends(id);

	ss.str("");

		break;
	case 6:
		// receive input from user
		cin.ignore(100, ' ');
		cin >> file;

		// use function in 'network' to write the current users in the social network to the user-specified file
		e = socialnetwork.write_friends(file);

		if (e == -1) {
			cout << "Error: failed to open file" << endl;
		}
		break;
	case 7:
		// receive input from user and store in proper format
		cin >> firstname >> lastname >> firstname2 >> lastname2;
		ss << firstname << " " << lastname;
		name = ss.str();
		ss2 << firstname2 << " " << lastname2;
		name2 = ss2.str();

		id = socialnetwork.get_id(name);
		id2 = socialnetwork.get_id(name2);

		// run bfs function to find distance between users
		socialnetwork.bfs_depth_of_friend(id, id2);

		ss.str("");
		ss2.str("");
		break;
	case 8:
		//run disjoint groups function
		socialnetwork.disjoint_groups();
		break;
	case 9:
		// receive input from user and store in proper format
		cin >> firstname >> lastname;
		ss << firstname << " " << lastname;
		name = ss.str();

		id = socialnetwork.get_id(name);

		// run friend suggestions function
		socialnetwork.friend_suggestions(id);

		ss.str("");
		break;
	default:
		break;

	}
	delete file;

	} while ((option > 0) && (option < 10));



  return 0;
}
