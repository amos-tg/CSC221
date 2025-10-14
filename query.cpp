#include <iostream>
#include <string>

// takes a string query and returns a string response
// no endl appended
std::string query(std::string query) {
	using namespace std;
	string ret;
	cout << query;
  cin >> ret;
	return ret;
}
