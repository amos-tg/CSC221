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

  int guess;
  do {
    cout << guess_msg;
    cout.flush();

    cin >> guess;

    // compares the numbers and prints out 
    // the appropriate message.
    if (guess < rand_num) {
      cout << higher_msg << endl; 
    } else if (guess > rand_num) {
      cout << lower_msg << endl;
    }
  } while (guess != rand_num);

  cout << '\n' << "YOU GOT IT!!! " << u8"\u2713" << endl;
  
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
