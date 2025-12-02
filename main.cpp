#include <iostream>


using namespace std;


void getLengthWidth(double& length, double& width); 
double calcPerimeter(double length, double width);
double calcArea(double length, double width);
void displayProperties(double perimeter, double area);


int main(void) {
  const auto repeat_msg = 
    "Do you want to repeat the process? (y/n) : ";
  const auto repeat_input_err = 
    "Error: invalid choice, use y, Y, n, or N.";

  double length, width; 
  char repeat; 

  do { 
    cout << '\n';

    getLengthWidth(length, width);
    /// cpp passes by value like c, so no need to worry 
    /// about moving the length and width before calcArea
    double perimeter = calcPerimeter(length, width);
    double area = calcArea(length, width);
    displayProperties(perimeter, area);

    cout << repeat_msg;
    cout.flush();
    cin >> repeat;
    switch (repeat) { 
      case 'y':
        break;
      case 'Y':
        break;
      case 'n': 
        repeat = 0;
        break;
      case 'N':
        repeat = 0;
        break;
      default: 
        cerr << repeat_input_err << endl;
        exit(1);
    }
  } while (repeat);

  return 0;
}

/// set double length and width by reference
/// based on user input
void getLengthWidth(double& length, double& width) {
  const auto length_query = "What is the length of the rectangle? ";
  const auto width_query = "What is the width of the rectangle? ";
  const auto double_cin_err = 
    "Error: user input is invalid, x > 0 && no non-integrals";

  cout << length_query;
  cin >> length;  
  if (cin.fail() || !(length > 0)) {
    cerr << double_cin_err << endl;
    exit(1);
  }

  cout << width_query;
  cin >> width;
  if (cin.fail() || !(length > 0)) {
    cerr << double_cin_err << endl;
    exit(1);
  }
}

/// returns the perimeter of the rectangle based on it's 
/// length and width which are passed as double params
double calcPerimeter(double length, double width) {
  return 2 * (length + width);
}
 
/// returns the area of a rectangle based on it's length
/// and width which are passed as double params 
double calcArea(double length, double width) {
  return length * width;
}

/// prints out the perimeter and area of the rectangle
/// the perimeter and area are passed as double params
void displayProperties(double perimeter, double area) {
  cout << "The perimeter = " << perimeter << '\n'
    << "The area = " << area << endl;
}
