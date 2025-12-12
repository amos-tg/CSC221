#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// the fact that the world series was not played in 1904 and 1994 has no 
// effect on the program, because the date is not displayed and since no one
// played the world series in those years there will be no additional data to filter.

/// file_path: the name of the file containing the team names.
/// team_names: reference to a vector of string team names.
///
/// Reads the team names from file_path into the team_names 
/// vector. Returns an error if the file open or reading fails.
void getTeams(const string file_path, vector<string> &team_names);

/// team_name: the name of the team to find
/// team_names: the vector of winners from 1903 to 2012 excluding 1904 and 1994
///
/// returns the number of times that team_name occurs in the team_names vector of winners. 
unsigned findWinners(const string query_team_name, const vector<string> &team_names);

int main(void) {
  char team_names_path[] = "./Teams.txt";
  char winner_team_names_path[] = "./WorldSeriesWinners.txt";
  vector<string> team_names{}, winner_team_names{};
  string query_team_name;

  getTeams(team_names_path, team_names); 
  getTeams(winner_team_names_path, winner_team_names);

  cout << "Team Names:" << '\n';
  for (string &team_name: team_names) {
    cout << team_name << '\n';
  }

  cout.flush();

  for (;;) {
    cout << '\n' << "Enter the name of a team (enter quit to end): ";
    cout.flush();
    if (!getline(cin, query_team_name)) {
      cerr << "Error: failed to read invalid team name input" << endl;
      terminate();
    }

    if (query_team_name == "quit") {
      break;
    }

    // if the team isn't in the list of teams tell the user and reset
    if (!findWinners(query_team_name, team_names)) {
      cout << "Team name wasn't on the list, try again..." << endl;
      continue;
    }

    int num_wins = findWinners(query_team_name, winner_team_names);

    cout << '\n' << query_team_name << " won the World Series " 
      << num_wins << " times." << '\n' << endl;
  }

  return 0;
}

void getTeams(string file_path, vector<string> &team_names) {
  ifstream file(file_path);
  string tname;

  if (!file) {
    cerr << "Error: failed to open file" << file_path << endl;
    terminate();
  }

  while (getline(file, tname)) {
    // having an issue where '\r' postfixes every team name.
    if (tname[tname.length() - 1] == '\r') {
      tname.pop_back();
    }
    
    team_names.push_back(tname);
    tname.clear();
  }
}

unsigned findWinners(string query_team_name, const vector<string> &team_names) {
  unsigned counter{};
  for (const string &tname: team_names) {
    if (tname == query_team_name) { 
      ++counter; 
    }
  }

  return counter;
}
