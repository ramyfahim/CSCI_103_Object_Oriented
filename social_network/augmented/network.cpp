#include "network.h"
#include <fstream>
#include <iomanip>
#include <deque>

using namespace std;

network::network() {

}

network::~network() {

}

int network::add_user(user user) {
	if (users.size() >= 100) {
		return -1;
	}
	users.push_back(user); // add user to network class (as long as there are not 100 users in the vector)
	return 0;
}

int network::add_connection(int id, int id2) {



	// check if either of the IDs are below zero or above the total size of the user vector
	if ((id < 0) || (id > (static_cast<int>(users.size())))) {
		return -2;
	}
	if ((id2 < 0) || (id2 > (static_cast<int>(users.size())))) {
		return -2;
	}

	// check if the users are already friends (i.e. check if the ID of one user is contained in the friends list of the other user)
	for (unsigned int i = 0; i < (users[id].return_friends()).size(); i++) {
		if (id2 == (users[id].return_friends())[i]) {
			return -1;
		}
	}


	// use functions in 'user' class to add each user as a friend of the other (users are specificed in parameters of function)
	users[id].add_friend(id2);
	users[id2].add_friend(id);




	return 0;
}

int network::remove_connection(int id, int id2) {


	// check if either of the IDs are below zero or above the total size of the user vector
	if ((id < 0) || (id > (static_cast<int>(users.size())))) {
		return -1;
	}
	if ((id2 < 0) || (id2 > (static_cast<int>(users.size())))) {
		return -1;
	}

	// use functions in 'user' class to remove each user as a friend of the other (users are specificed in parameters of function)
	users[id].delete_friend(id2);
	users[id2].delete_friend(id);




	return 0;
}

// function to return ID of a user from a name as an input
int network::get_id(string name) {
	for (unsigned int i = 0; i < users.size(); i++) {
		if (users[i].return_name() == name) {
			return users[i].return_id();
			}
	}
	return 0;
}

// function to read users from a file and add them to the network
int network::read_friends(char *fname) {
	ifstream ifile;
	ifile.open(fname);
	if (ifile.fail()) {
		return -1;
	}
	int numberOfUsers;
	ifile >> numberOfUsers;
	for (int i = 0; i < numberOfUsers; i++) {
		int id;
		ifile >> id;
		string name;
		getline(ifile, name);
		getline(ifile, name);
		name.erase(name.begin());
		int year;
		ifile >> year;
		int zip;
		ifile >> zip;
		vector<int> friends;
		string userfriends;
		getline(ifile, userfriends);
		getline(ifile, userfriends);
		stringstream ss(userfriends);
		int tf;
		//ss << friends;
		while (ss >> tf) {
			friends.push_back(tf);
		}
		user a = user(id, name, year, zip, friends);
		add_user(a);
	}
return 0;
}

// function to write users onto a file in a format that is readable by the read_friends function
int network::write_friends(char *fname) {

	ofstream ofile;
	ofile.open(fname);
	if (ofile.fail()) {
		return -1;
	}

	ofile << users.size() << endl;

	for (unsigned int i = 0; i < users.size(); i++) {
		ofile << users[i].return_id() << endl;
		ofile << "\t" << users[i].return_name() << endl;
		ofile << "\t" << users[i].return_year() << endl;
		ofile << "\t" << users[i].return_zip() << endl;
		vector<int> f = users[i].return_friends();
		for (unsigned int j = 0; j < f.size(); j++) {		
		ofile << "\t" << f[j];
}
		ofile << "\n";
	


}
	return 0;
}

// function to print the user info of every user in the network vector
void network::print_user_info() {
	cout << left;
	cout << setw(6) << "ID";
	cout << setw(20) << "Name";
	cout << setw(9) << "Year";
	cout << setw(12) << "Zip" << endl;
	cout << "==========================================================" << endl;
	for (unsigned int i = 0; i < users.size(); i++) {
	int id = users[i].return_id();
	string n = users[i].return_name();
	int y = users[i].return_year();
	int z = users[i].return_zip();
	cout << setw(6) << id;
	cout << setw(20) << n;
	cout << setw(9) << y;
	cout << setw(12) << z << endl;
	}
}

// function to print the friends of a user whose ID is specified as a parameter
void network::print_friends(int id) {

cout << left;
	cout << setw(6) << "ID";
	cout << setw(20) << "Name";
	cout << setw(9) << "Year";
	cout << setw(12) << "Zip" << endl;
	cout << "==========================================================" << endl;
		for (unsigned int i = 0; i < ((users[id].return_friends()).size()); i++) {
	int id2 = ((users[id]).return_friends())[i];
	string n = (users[(users[id]).return_friends()[i]]).return_name();
	int y = (users[(users[id]).return_friends()[i]]).return_year();
	int z = (users[(users[id]).return_friends()[i]]).return_zip();
	cout << setw(6) << id2;
	cout << setw(20) << n;
	cout << setw(9) << y;
	cout << setw(12) << z << endl;


		}


}

// below: "get" accessor methods
vector<user> network::return_users() {
	return users;
}


int network::return_vector_size() {
	return users.size();
}


void network::bfs_depth_of_friend(int source, int destination) {

deque <int> queue;
deque <int> print_reverse;
bool found = false;

// reset all users' data members to -1
for (unsigned int i = 0; i < users.size(); i++) {
	users[i].depth = -1;
	users[i].predecessor = -1;
}

// set source user's depth to 0, and add source user to deque
users[source].depth = 0;

queue.push_back(users[source].return_id());

// run while loop until deque is empty. begin by checking all friends of source user (and addin them to the deque). then, by deleting elements from the deck, check all friends of next user (who was added to the deque). continue in this way. assign proper depth to each user. 
while (! queue.empty()) {

	int temp = queue.front();
	queue.pop_front();


	for (unsigned int j = 0; j < users[temp].return_friends().size(); j++) {

		if ((users[(users[temp].return_friends())[j]]).depth == -1) {
			users[(users[temp].return_friends())[j]].depth = users[temp].depth + 1;
			users[(users[temp].return_friends())[j]].predecessor = temp;
			queue.push_back((users[temp].return_friends())[j]);
			if ( (users[(users[temp].return_friends())[j]]).return_id() == destination) {
				found = true; // set 'found' boolean to true if destination user is located
				break;
			}

		}
	}


}

if (found) {

int b = destination;
	// reverse order of users from predecessor for printing
	for (int k = 0; k <= users[destination].depth; k++) {

print_reverse.push_front(b);
b = users[b].predecessor;

	}

print_reverse[0] = source;

// print path of users
cout << "Distance: " << users[destination].depth << endl;

	for (int l = 0; l <= users[destination].depth; l++) {

cout << users[print_reverse[l]].return_name();
if (l != users[destination].depth) {
	cout << " -> ";
	}

}
cout << "\n";
}

else {
	cout << "No relationship found." << endl;
}

}


void network::disjoint_groups() {

deque <int> network; // create deque to store predecessors of users
bool users_unchecked = true;


// reset predecessor deque to -1
for (unsigned int i = 0; i < users.size(); i++) {
	network.push_back(-1);
}

// select (arbitrary) first user and make proper initilizations (get the user's ID, and add user to deque)
network[0] = users[0].return_id();
users[0].set_member = 1;
deque <int> group_queue;
int a = users[0].return_id();
group_queue.push_back(users[0].return_id());


int set = 1; // initialize counter for number of sets
// run while loop until all users have been checked (i.e., no user has -1 as their predecessor value)
while (users_unchecked) {


// run while loop until deque is empty. use BFS to traverse through all users who are connected to the first user by some number of relationships
while (!group_queue.empty()) {
a = group_queue.front();
group_queue.pop_front();
users[a].set_member = set;
network[a] = a;

for (unsigned int i = 0; i < (users[a].return_friends()).size(); i++) {
	if (network[(users[a].return_friends())[i]] == -1) {
	users[(users[a].return_friends())[i]].set_member = set;
	network[(users[a].return_friends())[i]] = ((users[a].return_friends())[i]);
	group_queue.push_back((users[a].return_friends())[i]);
	}
}


}


// perform check to see if there are users who are still unchecked
users_unchecked = false;
for (unsigned int i = 0; i < network.size(); i++) {
	if (network[i] == -1) {
		users_unchecked = true;
		group_queue.push_back(users[i].return_id());
		set++;
		break;
		}
	}


}

if (set == 1) {
	cout << "No disjoint groups." << endl;
	}


// print out all sets with their corresponding users
for (int i = 1; i <= set; i++) {
int printcounter = 0;
deque <int> print;
cout << "Set " << i << ": ";
		for (unsigned int k = 0; k < users.size(); k++) {
			if (users[k].set_member == i) {
				print.push_back(k);
			}
		}
	for (unsigned int j = 0; j < users.size(); j++) {

		if (users[j].set_member == i) {
			cout << users[j].return_name();
			printcounter++;
			if (printcounter != (print.size())) {
				cout << ", ";
			}
		}

	}

print.clear();
cout << "\n";

}

}

void network::friend_suggestions(int source) {

deque <int> depth_queue;

// reset all users' depths to -1 and suggestion_scores to 0
for (unsigned int i = 0; i < users.size(); i++) {
	users[i].depth = -1;
	users[i].suggestion_score = 0;
}

users[source].depth = 0;

depth_queue.push_back(users[source].return_id());

// execute breadth-first-search to assign a depth value to every user
while (! depth_queue.empty()) {

	int temp = depth_queue.front();
	depth_queue.pop_front();


	for (unsigned int j = 0; j < users[temp].return_friends().size(); j ++) {

		if ((users[(users[temp].return_friends())[j]]).depth == -1) {
			users[(users[temp].return_friends())[j]].depth = users[temp].depth + 1;
			depth_queue.push_back((users[temp].return_friends())[j]);
		}
	}


}



deque <int> friend_suggestions_deque;


// find and get all users who have a depth of 2
for (unsigned int i = 0; i < users.size(); i++) {
	if (users[i].depth == 2) {
		friend_suggestions_deque.push_back(i);
	}
}



// compare friends of source user to friends of all users who have a depth of 2 (determined and isolated earlier). if a match is found, increment the user's (the one whose friends are being compared to the source user's friends) suggestion score by 1.
for (unsigned int i = 0; i < users[source].return_friends().size(); i++) {
	int sourceFriend = users[source].return_friends()[i];
	for (unsigned int j = 0; j < friend_suggestions_deque.size(); j++) {
		for (unsigned int k = 0; k < users[friend_suggestions_deque[j]].return_friends().size(); k++) {
			if (sourceFriend == ((users[friend_suggestions_deque[j]]).return_friends()[k])) {
				users[friend_suggestions_deque[j]].suggestion_score += 1;
			}
		}
	}	


}



// determine the highest suggestion score present among the users
int highest = 0;
for (unsigned int i = 0; i < users.size(); i++) {

	if (users[i].suggestion_score > highest) {
		highest = users[i].suggestion_score;
	}

}



cout << left;

if (highest == 0) { // special case: no mutual friends
	cout << "No candidates found." << endl;
	}
else {

// print out names of all users who have the highest suggestion score
cout << "The strongest candidate(s) is/are: " << endl;
for (unsigned int i = 0; i < users.size(); i++) {
	if (users[i].suggestion_score == highest) {
		cout <<setw(20) << users[i].return_name() << "Score: " << highest << endl;
	}

}
}

}
