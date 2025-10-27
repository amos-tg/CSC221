#include <string>
#include "query.cpp" 

using namespace std;

int month_check(int month_num);
void days_in_month(int month, int year);

const char *month_query = "Enter a month (1-12): ";
const char *month_err = "Error: invalid month input";  
const char *year_query = "Enter a year: ";

int main(void) {
  int month_num = stoi(query(month_query));   
	if (1 == month_check(month_num)) {
    cout << month_err << endl;
    return -1;
	}  

  int year_num = stoi(query(year_query));
	days_in_month(month_num, year_num);

	return 0;
}

// takes a string month number and validates whether or 
// not it is between or equal to 1 and 12.
// returns 0 for a valid month number.
// returns 1 for an invalid month number.
int month_check(int month_num) {
  if (month_num >= 1 && month_num <= 12) {
    return 0;
	} else {
		return 1;
	}
}

void days_in_month(int month, int year) {
	const int leapFebDays = 29;
	const int Feb = 2;
	const int daysInMonth[12] = {
		31, 28, 31,
		30, 31, 30,
	  31, 31, 30,
		31, 30, 31 };

	// leap checker and day num printer
	if (!(year % 100) && !(year % 400) && month == Feb) {
    cout << leapFebDays << " days" << endl;
	} else if (!(year % 4) && month == Feb) {
    cout << leapFebDays << " days" << endl;  
	} else {
    cout << daysInMonth[--month] << " days" << endl;
	}
}
