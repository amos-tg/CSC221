#define NUM_REGIONS 5
#include <iostream>
#include <string>


using namespace std;


void getRegionInfo(string& region, int& num_accidents);
bool isLower(int x, int y);
void showLowest(string region, int num_accidents);


int main(void) {
  string region = ""; 
  // comparing against uninitialized int is undefined so
  // I'm marking this for the getRegionInfo function.
  int num_accidents = -1;

  for (int i = 0; i < NUM_REGIONS; ++i) {
    getRegionInfo(region, num_accidents);
  }

  showLowest(region, num_accidents);

  return 0;
}

/// takes a reference to the string:region, and the int:num_accidents
/// takes user input to gather the region name and number of accidents
/// in said region, if the region has the lowest number of accidents so
/// far, it replaces the old region name with the new one as well as the 
/// accident count. If the number of accidents inputed is less than zero
/// the program will return an error.
void getRegionInfo(string& region, int& num_accidents) {
  string region_cmp;
  unsigned int num_accidents_cmp;

  const auto region_query = "What is the name of the region? : ";
  const auto num_accid_query = "What is the number of accidents in the region? : ";

  // handles initialization / first iteration
  // skips over remaining code, goes to the
  // input validation for num_accidents
  if (num_accidents == -1) {
    // gets region
    cout << region_query;
    cout.flush();
    cin >> region; 

    // gets number accidents
    cout << num_accid_query;
    cout.flush();
    cin >> num_accidents;

    // spaces things out
    cout << endl;

    goto validate_input;
  }

  // gets region
  cout << region_query;
  cout.flush();
  cin >> region_cmp;

  // gets number accidents
  cout << num_accid_query;
  cout.flush();
  cin >> num_accidents_cmp;

  // spaces things out
  cout << endl;

  if (isLower(num_accidents_cmp, num_accidents)) {
    num_accidents = num_accidents_cmp;
    region = region_cmp;
  }

  // the infamous goto label
validate_input:
  if (num_accidents < 0) {
    cerr << "Error: (number of accidents) < 0" << endl;
    exit(1);
  } 

  return;
}

// The directions have the function named
// isLower but the definition says <=, I may have 
// typed it by accident or it might be a typo.
// Also this doesn't account for regions with equal
// numbers of accidents. 
/// returns true if x is less than y.
bool isLower(int x, int y) {
  return (x <= y);
}

/// takes the region with the lowest accidents and it's 
/// accompanying number of accidents and prints it out.
void showLowest(string region, int num_accidents) {
  cout << region << " had the lowest number of accidents : " 
    << num_accidents << endl;

  return;  
}
