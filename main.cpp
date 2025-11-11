#include <iostream>
#include <random>


using namespace std;


int gen_rand_int(void);


const auto guess_msg = 
  "Guess the number: ";
const auto lower_msg = 
  "The number I'm thinking of is lower than that.";
const auto higher_msg = 
  "The number I'm thinking of is higher than that.";


int main(void) {
  int rand_num = gen_rand_int();

  // testing code:
  // cout << rand_num << endl;

  int guess, num_guesses = 0;
  guess = num_guesses = 0;
  do {
    cout << guess_msg;
    cout.flush();

    // gets input, checks that it was valid so the loop 
    // doesn't run infinitely and spam stdout.
    cin >> guess;
    if (cin.fail()) {
      cerr << "Error: You inputted a non-integer value";
      exit(1);
    }

    // compares the numbers and prints out 
    // the appropriate message.
    if (guess < rand_num) {
      cout << higher_msg << '\n' << endl; 
    } else if (guess > rand_num) {
      cout << lower_msg << '\n' << endl;
    }

    ++num_guesses;
  } while (guess != rand_num);


  // makes sure the grammar is correct
  cout << '\n' << "YOU GOT IT!!! " << u8"\u2713" << '\n';
  if (num_guesses == 1) {
    cout << "It took you " << num_guesses << " guess" << endl;
  } else {
    cout << "It took you " << num_guesses << " guesses" << endl;
  }
  
  return 0;
}

/// returns a random integer between 1 and 9999
/// (using the code I wrote for the MathTutor project)
int gen_rand_int(void) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(1, 999);
  int num = distrib(gen);
  return num;
}
