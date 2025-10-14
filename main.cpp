#include <iostream>
#include <iomanip>
#include <random>
#include <string>

using namespace std;

typedef struct Equation {
  int answer;
  int num1;
	int num2;
} Equation; 

Equation gen_problem(void);
void print_problem(Equation exp);
void print_answer(Equation exp);

int main(void) {
	string user_input;
	int user_answer;

  Equation exp = gen_problem();
	print_problem(exp);

	getline(cin, user_input);
	user_answer = stoi(user_input);

	if (user_answer == exp.answer) {
    cout << '\n' << "You got it right!" << endl;
	} else {
		print_answer(exp);
	}

  return 0;
}

Equation gen_problem(void) {
	random_device rd;
	Equation exp;

	mt19937 gen(rd());
	uniform_int_distribution<> distrib(100, 999);

  int num1 = distrib(gen);
	int num2 = distrib(gen);
  int answer = num1 + num2; 

	return exp = {
    .answer = answer,
		.num1 = num1,
		.num2 = num2, 
	};
}

void print_problem(Equation exp) {
  cout << setw(4) << exp.num1 << '\n';  
	cout << '+' << exp.num2 << endl;
	cout << "----" << endl;
}

void print_answer(Equation exp) {
  cout << '\n' << "You got it wrong the answer was: " << exp.answer << endl;
}
