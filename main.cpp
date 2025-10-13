#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// in cups
const double sugar_ratio = 1.5 / 48.0;
const double butter_ratio = 1.0 / 48.0;
const double flour_ratio = 2.75 / 48.0;

typedef struct ingredients{
	double sugar; 
	double butter;
	double flour;
} Ingredients; 

// returns all the ingredients needed with their scaled values
// based on num_cookies
Ingredients get_ingredient_vals(unsigned int num_cookies);

// returns -1 on failure / bad user input
// otherwise, returns num_cookies as double
double parse_to_double(std::string user_input);

int main(void) {
	string user_input;
	double num_cookies;
	Ingredients ing;
	const auto default_precision = cout.precision();

	cout << "How many cookies do you want to bake? : ";
  cout.flush();
	cin >> user_input;

  num_cookies = parse_to_double(user_input);
	if (num_cookies < 0.0) {
    cerr << "Ruh roh Raggy, Invalid user input detected.";
		exit(-1);
	}

  ing = get_ingredient_vals(num_cookies);

	cout << '\n' << endl;

	cout << "Cups of Sugar needed:" << setprecision(3) << ing.sugar << endl;
	cout << setprecision(default_precision);

	cout << "Cups of Butter needed:" << setprecision(3) << ing.butter << endl;
	cout << setprecision(default_precision);

	cout << "Cups of Flour needed:" << setprecision(3) << ing.flour << endl; 
	cout << setprecision(default_precision);

	cout << '\n' << "Get baking pâtissier!" << endl;

	return 0;
}

double parse_to_double(const string user_input) {
	size_t x; 
	double parsed;

	// user_input.contains isn't working for some reason
	// find will not accept non zero prefixed doubles 
  if (user_input.find(".")) {
  	parsed = stod(user_input, &x);
	} else {
  	parsed = static_cast<double>(stoi(user_input, &x));
	}

	if (parsed <= 0.0) {
  	return -1.0;
	}

	return parsed;
}

Ingredients get_ingredient_vals(unsigned int num_cookies) {
  Ingredients ing{
	  .sugar = num_cookies * sugar_ratio,
		.butter = num_cookies * butter_ratio,
		.flour = num_cookies * flour_ratio,
	};

	return ing;
}
