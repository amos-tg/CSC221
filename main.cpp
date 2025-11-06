#include <iostream>
#include <string>
#include "query.cpp"

using namespace std;


const auto init_pop_query = 
  "What is the initial organism population? : ";
const auto init_pop_err = 
  "Error: initial population cannot be less than 2";

const auto pop_increase_query = 
  "What is the average daily population increase as a percentage? : ";
const auto pop_increase_err = 
  "Error: population increase cannot be negative";

const auto num_days_query = 
  "What is the number of days the population will multiply over? : ";
const auto num_days_err =
  "Error: number of days cannot be less than one";


int main(void) {
  double population = 
    stod(query(init_pop_query)); 

  // input validation, if less than 2 exit with failure code, 1.
  if (population < 2) {
    cerr << init_pop_err << endl;
    exit(1);
  }

  // div 100 produces decimal equivalent of percentage
  double population_increase_percentage = 
    stod(query(pop_increase_query)) / 100; 

  // input validation, cannot be negative 
  if (population_increase_percentage < 0) {
    cerr << pop_increase_err << endl;
    exit(1);
  }

  double number_days_multiplied = 
    stod(query(num_days_query));

  // input validation, do not allow number of 
  // days less than one.
  if (number_days_multiplied < 1) {
    cerr << num_days_err << endl;
    exit(1);
  }

  cout << '\n' << "Population size on day 1" 
    << ": " << population << endl;

  for (int i = 2; i <= number_days_multiplied; ++i) {
    population = population + population_increase_percentage * population; 
    cout << "Population size on day " << i 
      << ": " << population << endl;
  }

  return 0;
}
