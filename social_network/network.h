#ifndef network_H
#define network_H

#include <iostream>
#include <sstream>
#include <vector>
#include "user.h"
using namespace std;

class network {
	public:
		network();
		~network();
		int read_friends(char *fname);
		int write_friends(char *fname);
		int add_user(user user);
		int add_connection(int id, int id2);
		int remove_connection(int id, int id2);
		int get_id(string name);
		void print_user_info();
		void print_friends(int id);
		vector<user> return_users();
		int return_vector_size(); // created new function to return size of network object (for use in determination of id in social_network.cpp)
	private:
		vector<user> users;
};

#endif
