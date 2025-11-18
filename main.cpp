#define NUM_SCORES 5
#include <iostream>


using namespace std;


void getScore(
   string judge_name, double& min_score,
   double& max_score, double& score_total);

bool isLower(double x, double y);
bool isHigher(double x, double y);

double calcAverage(
    double score_total, int num_scores,
    double min_score, double max_score);

const char *judge_names[5] = {
  "Joody", "Professor Sprague", "Doctor Phil", 
  "Guy Fierri", "Genghis Khan", };

int main(void) {
  double min_score, max_score, score_total, average;

  min_score = 11;
  max_score = -1;

  for (int i = 0; i < 5; ++i) {
    getScore(
      judge_names[i], min_score,
      max_score, score_total);
  }

  average = calcAverage(
    score_total, NUM_SCORES,
    min_score, max_score);

  // the directions don't say we need to print the value 
  // but that is probably what is expected. 
  cout << "The final score is : " << average << endl;

  return 0;
}

// The directions say between 0 and 10, it's not clear if 0 and 10
// are included in the range. Normally you can give someone a 10 so 
// I'm going to assume that it is an inclusive range. Both 0 and 10 
// will be valid inputs to the program.
//
/// judge_name: a string that gets printed out which shows  
///             different judges are being asked for their scores.
///
/// min_score: a reference to a double which represents the minimum 
///            recieved score.
///
/// max_score: a reference to a double which represents the maximum 
///            recieved score.
///
/// score_total: a reference to a double which represents the total 
///              of all the scores recieved so far.
///
/// First, the func. queries the judge for their score, then it adds
/// the score to the score_total parameter, it will set min_score to 
/// score if the score is less than or equal to the min_score param
/// and it will set max_score to score if score is greater than or 
/// to max_score. I know that the equal to part isn't needed but it's  
/// part of the directions so I'm doing it anyway.
///
/// The function will exit the program if there is invalid user input 
void getScore(
    string judge_name, double& min_score,
    double& max_score, double& score_total) 
{
  double score;

  cout << "Judge " << judge_name
    << ", what do you rate the performance between zero and ten? : ";
  cout.flush();
  cin >> score;

  if (score < 0 || score > 10) {
    cerr << "Error: Invalid score, not between 0 and 10" << endl;
    exit(1);
  }

  score_total += score;

  if (isLower(score, min_score)) {
    min_score = score;
  } 

  if (isHigher(score, max_score)) {
    max_score = score;
  }
}

/// If x is less than or equal to y return true, else return false.
///
/// this function makes the code less clear and is too short 
/// to be a function by itself but it is in the directions 
/// so I'll include it anyway.
bool isLower(double x, double y) {
  return (x <= y);
}

/// If x is greater than or equal to y return true, else return false.
///
/// this function makes the code less clear and is too short 
/// to be a function by itself but it is in the directions 
/// so I'll include it anyway.
bool isHigher(double x, double y) {
  return (x >= y); 
}

/// score_total: The sum of all scores
/// num_scores: The number of individual scores which make up score_total
/// min_score: The lowest score value recieved 
/// max_score: The highest score value recieved
///
/// This function returns the average of all the scores with the outliers,   
/// the minimum and maximum scores, removed so the average is not skewed. 
double calcAverage(
    double score_total, int num_scores,
    double min_score, double max_score)
{
  score_total -= (min_score + max_score);
  return (score_total / num_scores); 
}

