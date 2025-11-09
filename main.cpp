#include <iostream>
#include <fstream>
#include <filesystem>


using namespace std;


ifstream get_roster_ifstream(void);


const auto roster_fname = "LineUp.txt";
const auto fexists_err = "Error: file does not exist";
const auto fopen_err = "Error: failed to open file";


int main(void) {
  ifstream roster_ifstream = get_roster_ifstream();

  // pull out the first name so I don't compare 
  // against uninitialized strings in the loop.
  string front, back, current;
  roster_ifstream >> current;
  front = back = current;
  current.clear();

  // counter must be initialized outside of the loop scope
  // counter starts from one to account for the initialization
  int i;
  for (i = 1; roster_ifstream >> current; ++i) { 
    if (current < front) {
      front = current; 
    } 

    if (current > back) {
      back = current;
    }

    /* this is how I tested the program. 
    cout << "current, i: " << i << " : " << current << endl;
    cout << "front, i: " << i << " : " << front << endl;
    cout << "back, i: " << i << " : " << back << '\n' << endl;*/

    current.clear();
  }

  cout << '\n' << "Front of the line: " << front << endl;
  cout << "Back of the line: " << back << endl;
  cout << "Total number of students: " << i << endl; 
}

/// returns the roster_ifstream for the LineUp.txt file
/// which must be present in the current working directory
/// as dictated by filesystem::current_path.
ifstream get_roster_ifstream(void) { 
  ifstream roster_ifstream;

  // gets LineUp.txt from cwd
  filesystem::path name_list_path = 
    filesystem::current_path().append(roster_fname);

  // checks to make sure the file exists
  if (!filesystem::exists(name_list_path)) {
    cerr << fexists_err << endl;
    exit(1); 
  }

  // opens the file and checks if it opened without err.
  roster_ifstream.open(name_list_path);
  if (!roster_ifstream.is_open()) {
    cerr << fopen_err << endl; 
    exit(1);
  }
  
  return roster_ifstream;
}
