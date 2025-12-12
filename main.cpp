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
void getTeams(string file_path, vector<string> &team_names);

/// team_name: the name of the team to find
/// team_names: the vector of winners from 1903 to 2012 excluding 1904 and 1994
///
/// returns the number of times that team_name occurs in the team_names vector of winners. 
unsigned findWinners(string team_name, const vector<string> &team_names);

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
    cout << "Enter the name of a team (enter quit to end):" << endl;
    cin >> query_team_name;
    if (cin.fail()) {
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

    cout << query_team_name << "won the World Series " 
      << num_wins << " times." << '\n' << endl;
  }

  return 0;
}
