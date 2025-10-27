#include <iomanip>
#include <iostream>
#include <string>
#include "query.cpp"

using namespace std;

int verify_weight(int kilos); 
int verify_miles(int miles);
double get_rate(int kilos);
void get_and_print_cost(int kilos, int miles, double rate);

const char *pkg_weight_query = 
  "What is the package weight in kilograms? : ";
const char *pkg_weight_err = 
  "Error: kilos input > 0 kilos and kilos input <= 20 kilos";
const char *miles_shipped_query = 
  "In miles, how far will the package be shipped? : ";
const char *miles_shipped_err = 
  "Error: miles input >= 10 miles and miles input <= 3,000 miles";

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

  double rate = get_rate(pkg_weight);
  get_and_print_cost(pkg_weight, miles_shipped, rate);

  return 0;
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

// returns the rate based on kilos/package weight
double get_rate(int kilos) {
  double rate; 

	if (kilos <= 2) {
		rate = 1.10;
	} else if (kilos <= 6) {
    rate = 2.20; 
  } else if (kilos <= 10) {
    rate = 3.70;
  } else if (kilos <= 20) {
    rate = 4.80;
  } 
  
  return rate;
}

void get_and_print_cost(int kilos, int miles, double rate) {
  double miles_by_5h = static_cast<double>(miles) / 500.0;
  double cost = miles_by_5h * rate;

  cout << "Total Cost: $" << fixed 
    << setprecision(2) << cost;
}
