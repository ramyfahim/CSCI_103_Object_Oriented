#include "network.h"
#include <fstream>
#include <iomanip>

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
