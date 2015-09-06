

#include <iostream>
#include <sstream>
#include <vector>
#include "user.h"
using namespace std;

user::user()
{
	_id = 0;
	_name = "Ramy Fahim";
	_year = 1995;
	_zip = 90007;


}

user::user(int id, string name, int year, int zip, vector<int> friends) {
	_id = id;
	_name = name;
	_year = year;
	_zip = zip;
	_friends = friends; // added data for friends vector
}


user::~user()
{

}

void user::add_friend(int _id) {
	_friends.push_back(_id); // use vector function to add friend specified in parameter
}

void user::delete_friend(int _id) {
	for (unsigned int i = 0; i <_friends.size(); i++) {
		if (_friends[i] == _id) {
			_friends.erase(_friends.begin() + i); // use vector function to remove friend specific in parameter
			}
	}
}

//below: "get" accessor methods
int user::return_id() {
	return _id;
}

string user::return_name() {
	return _name;
}

int user::return_year() {
	return _year;
}

int user::return_zip() {
	return _zip;
}

vector<int> user::return_friends() {
	return _friends;
}


