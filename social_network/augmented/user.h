#ifndef user_H
#define user_H

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class user {
	public:
		user();
		user(int id, string name, int year, int zip, vector<int> friends);
		~user();
		void add_friend(int _id);
		void delete_friend(int _id);
		int return_id();
		string return_name();
		int return_year();
		int return_zip();
		vector<int> return_friends();
		int depth;
		int predecessor;
		int suggestion_score;
		int set_member;
	private:
		int _id;
		string _name;
		int _year;
		int _zip;
		vector<int> _friends;
};

#endif
