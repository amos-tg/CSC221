#include <string>
#include <iostream>
#include "query.cpp"

using namespace std;

int check_calc_option(int choice);
void circle_area(void);
void rectangle_area(void);
void triangle_area(void);

const auto geo_type_query = 
R"(Geometry Calculator
    1. Calculate the Area of a Circle
    2. Calculate the Area of a Rectangle
    3. Calculate the Area of a Triangle
    4. Quit
    Enter your choice (1-4): )";
const auto geo_type_err = 
  "Error: the choice was not between (1-4)";

const auto circle_radius_query = 
  "What is the radius of the circle? : ";

const auto rectangle_length_query = 
  "What is the length of the rectangle? : ";
const auto rectangle_width_query = 
  "What is the width of the rectangle? : ";

const auto triangle_base_length_query = 
  "What is the length of the triangle's base? : ";
const auto triangle_height_query = 
  "What is the triangles height? : ";

const double pi = 3.14159;

int main(void) {
  int calc_option = stoi(query(geo_type_query));
  if (check_calc_option(calc_option)) {
    cout << geo_type_err << endl;
    return 1;  
  }

  cout << '\n';

  switch (calc_option) {
    case 1:
      circle_area();
      break;
    case 2:
      rectangle_area();
      break;
    case 3:
      triangle_area();
      break;
  }

  return 0;
}

// returns 1 for an invalid option
// returns 0 for a valid option
int check_calc_option(int choice) {
  if (choice >= 1 && choice <= 4) {
    return 0;
  } else {
    return 1;
  }
}

void circle_area(void) {
  double radius = stod(query(circle_radius_query));    
  double area = pi * (radius * radius); 
  cout << "The Circle's Area is: " << area << endl;
}

void rectangle_area(void) {
  double length = stod(query(rectangle_length_query));
  double width = stod(query(rectangle_width_query));
  double area = length * width;
  cout << "The Rectangle's Area is: " << area << endl;
}

void triangle_area(void) {
  double base_length = stod(query(triangle_base_length_query));
  double height = stod(query(triangle_height_query));
  double area = base_length * height * 0.5; 
  cout << "The Triangle's Area is: " << area << endl;
}
