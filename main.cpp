#include <iostream>
#include <string>
#include "query.cpp"

using namespace std;

int verify_weight(int kilos); 
int verify_miles(int miles);
void get_and_print_cost(int kilos, int miles);

const char *pkg_weight_query = "What is the package weight in kilograms? : ";
const char *pkg_weight_err = "Error: kilos input > 0 kilos and kilos input <= 20 kilos";
const char *miles_shipped_query = "In miles, how far will the package be shipped? : ";
const char *miles_shipped_err = "Error: miles input >= 10 miles and miles input <= 3,000 miles";

int main(void) {
  int pkg_weight = stoi(query(pkg_weight_query));
	if (verify_weight(pkg_weight)) {
		cout << pkg_weight_err << endl;
    return 1;
	} 

	int miles_shipped = stoi(query(miles_shipped_query));
	if (verify_miles(miles_shipped)) {
    cout << miles_shipped_err << endl;
		return 1;
	} 

  get_and_print_cost(pkg_weight, miles_shipped);
} 

// returns 1 for an invalid weight 
// returns 0 for a valid weight
int verify_weight(int kilos) {
	const int floor = 0; 
	const int ceiling = 20;

  if (kilos <= floor || kilos > ceiling) {
    return 1;
	} else {
    return 0;
	}
} 

// returns 1 for an invalid number of miles
// returns 0 for a valid number of miles
int verify_miles(int miles) {
	const int floor = 10;
	const int ceiling = 3000;

	if (miles < floor || miles > ceiling) {
    return 1;
  } else { 
		return 0;
	}
}

void get_and_print_cost(int kilos, int miles) {
  double rate; 
	if (kilos <= 2) {
		rate = 1.10;
	} else if (kilos >= 6)
}
