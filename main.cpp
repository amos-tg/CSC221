#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// the fact that the world series was not played in 1904 and 1994 doesn't has no effect on the program because the date is not displayed and since no one played the world series in those years there will be no additional data to filter.

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
unsigned findWinner(string team_name, const vector<string> &team_names);

int main(void) {
  char team_names_path[] = "./Teams.txt";
  char winner_team_names_path[] = "./WorldSeriesWinners.txt";
  vector<string> team_names{}, winner_team_names{};

  getTeams(team_names_path, team_names); 
  getTeams(winner_team_names_path, winner_team_names);

  cout << "Team Names:" << '\n';
  for (string &team_name: team_names) {
    cout << team_name << '\n';
  }

  cout.flush();

  return 0;
}
