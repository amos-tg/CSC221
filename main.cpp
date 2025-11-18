#define CELSIUS_ARR_LEN 20
#define TABLE_LENGTH 38
#define TABLE_MIDDLE 19

#include <string>
#include <iostream>
#include <format>

using namespace std;

double getCelsius(double fahrenheit);
void printTable(double celsius_table[]);

int main(void) {
  // least to greatest celsius vals from 0 to 20.
  double celsius_ltg[CELSIUS_ARR_LEN];

  // loops over the range of requested fahrenheit values and assigns
  // the celsius equivalent in the array at the index fahrenheit value i.e. 
  // celsius_ltg[32] would equal 0 because (32F = 0C)
  for (int fahr = 0; fahr <= 20; ++fahr) {
    // assigns to array from 0 too 20 
    celsius_ltg[fahr] = getCelsius(fahr); 
  }

  // messy messy messy
  printTable(celsius_ltg);

  return 0;
}

/// Takes a double fahrenheit and returns the celsius equivalent.
double getCelsius(double fahrenheit) {
   // might as well get this division done at comp-time
   constexpr double fiveOver9 = 5.0 / 9.0;  

   // returns celsius conversion
   return (fahrenheit - 32) * fiveOver9;
}

/// takes the celsius table which maps to  
/// fahrenheit values by index and formats 
/// the output based on the table before printing
/// the right adjusted graph.
void printTable(double celsius_table[]) {
  int i;

  string table = "\
\n\t|------------------------------------|\
\n\t| Fahrenheit and Celsius Equivalents |\
\n\t|------------------------------------|\
\n\t|       Fahrenheit |         Celsius |\
\n\t|------------------------------------|";

  // generates the seperator which is inserted below each content line.
  string seperator = "\n\t|";
  for (i = 0; i < TABLE_LENGTH - 2; ++i) {
    seperator += '-';
  }
  seperator += '|';

  // generates the formatted content line and adds it to the 
  // table appending the seperator afterward.
  for (i = 0; i <= CELSIUS_ARR_LEN; ++i) {
    int i2, offset;
    string table_item = "|";

    // generates the content line
    for (i2 = 0; i2 < TABLE_LENGTH - 2; ++i2) {
      table_item += ' ';
    }
    table_item += '|';
    table_item[TABLE_MIDDLE] = '|';

    // this sets the fahrenheit value inside the content line right adjusted
    string fahrenheit = to_string(i);
    int fahr_len = fahrenheit.length();
    for (offset = (fahr_len + 1), i2 = 0; i2 < fahr_len; ++i2, --offset) {
      table_item[TABLE_MIDDLE - offset] = fahrenheit[i2];
    }

    // This sets the celsius value inside the content line right adjusted
    string celsius = format("{:.1F}", celsius_table[i]);
    int celsius_len = celsius.length();
    for (offset = (celsius_len + 2), i2 = 0; i2 < celsius_len; ++i2, --offset) {
      table_item[TABLE_LENGTH - offset] = celsius[i2];
    }

    // appends the content line and the premade-seperator line to the table
    // as well as the leading whitespace.
    table += ("\n\t" + table_item + seperator);
  }

  cout << table << endl;
}
