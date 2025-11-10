#include <iostream>
#include <string>

using namespace std;


// Pattern (A & B)'s max length patterns are the same
const char *shared_pat = "++++++++++";


void print_pat_a(void);
void print_pat_b(void);


int main(void) {
  cout << '\n' << "Pattern A:" << '\n';
  print_pat_a();

  cout << '\n' << "Pattern B:" << '\n';
  print_pat_b();

  cout << '\n' << "Pattern A and B consecutively: " << '\n';
  print_pat_a();
  print_pat_b();

  return 0;
}

// prints out pattern A from the directions 
void print_pat_a(void) {
  int max_char = string(shared_pat).length();
  string pat;

  // add an extra + to pat for each iteration until 
  // we reach the length of the pattern from the directions
  // I decided not to use substr here because I think it's more clear
  for (int i = 1; i <= max_char; ++i) {
    cout << (pat += '+') << '\n';
  }  

  cout.flush();
}

// prints out pattern B from the directions
void print_pat_b(void) {
  string pat = shared_pat;
  
  // cast the length to size_t so I can use it in substr
  size_t pat_len = static_cast<size_t>(pat.length());

  // take a substr of the start of the pattern string from,
  // 0 to i, where i is the length of the pattern decremented 
  // by one each iteration until the pattern reaches a singular 
  // char, '+'.
  for (int i = pat_len; i >= 1; --i) {
    cout <<  pat.substr(0, i) << '\n'; 
  }

  cout.flush();
}
