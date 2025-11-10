#include <fstream>
#include <string>
#include <filesystem>
#include "query.cpp"


using namespace std;


auto const path_query = 
  "What is the name of the data file? : ";

auto const town_name_query = 
  "What is the name of the Town? : ";

auto const chart_header_msg = 
  "Population Growth\n(each * represents 1,000 people)";


int main(void) {
  filesystem::path data_path = query(path_query); 
  ifstream data_ifstream(data_path);
  if (!data_ifstream.is_open()) {
    cerr << "Error: ifstream open method failed" << endl;
    exit(1);
  }

  string town_name = query(town_name_query);

  cout << '\n' << town_name << ' ' 
    << chart_header_msg << endl;

  int pop;
  for (int year = 1900; data_ifstream >> pop; year += 20) {
    string asts;
    int ast_num = pop / 1000;

    for (int i = 0; i < ast_num; ++i) {
      asts = asts + '*';
    }

    cout << year << ' ' << asts << endl; 
  }

  return 0;
} 

