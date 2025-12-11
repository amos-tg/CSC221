#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <exception>
#include <iomanip>

using namespace std;

// I use an odd syntax to refer to the arrays so I can maintain 
// the ability to use range based for loops, however I don't use them
// much past the getAnswers function because I need access to the increment.

/// char *answerKeyPath = the path of the answer key file.
///
/// char *answerCheckedPath = the path of the submitted answer files.
///
/// char (&answerKey)[20] = the buf the answer key is loaded into.
///
/// char (&answerChecked)[20] = the buf the submitted answers are loaded into.
///
/// Reads the answer key at answerPath into the answerKey buffer.
///
/// Failure to read the answer key from answerPath will terminate the program 
/// with an error.
void getAnswers(
  char *answerKeyPath, char *answerCheckedPath,
  char (&answerKey)[20], char (&answerChecked)[20]);

/// char (&answerKey)[20] = the answer key buffer.
///
/// char (&answerChecked)[20] = the checked answers buffer.
/// 
/// char (&answer2D)[2][20] = the two dimensional array storing the correct and
/// incorect answers parallel to one another. First dimension stores the correct 
/// answer, second dimension store the incorect answer. 
///
/// char (&answerNumber)[20] = array storing the corresponding question number, 
/// parallel of answer2D. 
///
///
/// Checks the students answers against the answer key and returns the number 
/// of incorrect answers. 
///
/// Stores the incorrect question numbers in an array, and stores the correct
/// answer and the students answer in a 2-D parallel array.
unsigned int gradeExam(
    char (&answerKey)[20], char (&answerChecked)[20], 
    char (&answer2D)[2][20], unsigned int (&answerNumber)[20]);

/// unsigned int (&answerNumber)[20] = parallel question number for the corresponding
/// question answer set within answer2D.
///
/// char (&answer2D)[2][20] = two dimensional array storing the question and answer set
/// of each incorrect answer parallel to the answerNumber array which indicates the 
/// question number. First dimension stores the correct answer, second dimension store
/// the incorect answer.
///
/// unsigned int numWrong = the number of incorect questions
void writeReport(
    unsigned int (&answerNumber)[20], char (&answer2D)[2][20], 
    unsigned int numWrong);

int main(void) {
  char answerKeyPath[] = "./CorrectAnswers.txt";
  char answerCheckedPath[] = "./StudentAnswers.txt";

  char answerKey[20];
  char answerChecked[20];
  char answer2D[2][20];
  unsigned int answerNumber[20];

  getAnswers(
      answerKeyPath, answerCheckedPath,
      answerKey, answerChecked);

  unsigned int numWrong = gradeExam(
      answerKey, answerChecked, answer2D, answerNumber);

  writeReport(answerNumber, answer2D, numWrong);

  return 0;
}

void getAnswers(
  char *answerKeyPath, char *answerCheckedPath,
  char (&answerKey)[20], char (&answerChecked)[20]) 
{
  ifstream stream(answerKeyPath); 
  if (!stream) {
    cerr << "Error: failed to open answer key file" << endl;
    terminate();
  }

  for (char &answer: answerKey) {
    if ( !(stream >> answer) ) {
      cerr << "Error: failed to read from answer key file" << endl;
      terminate();
    }
  }

  stream.close();
  if (stream.fail()) {
    cerr << "Error: failed to close the opened answer key file" << endl;
    terminate();
  }

  stream.open(answerCheckedPath);
  if (!stream) {
    cerr << "Error: failed to open submitted answers file" << endl;
    terminate();
  }

  for (char &answer: answerChecked) {
    if ( !(stream >> answer) ) {
      cerr << "Error: failed to read from answer key file" << endl;
      terminate();
    }
  } 
}

unsigned int gradeExam(
    char (&answerKey)[20], char (&answerChecked)[20], 
    char (&answer2D)[2][20], unsigned int (&answerNumber)[20])
{
  int numWrong{}; 

  for (int i = 0; i < 20; ++i) {
    if (answerKey[i] != answerChecked[i]) {
      // sets the wrong question's number in the parallel answerNumber array
      // index incremented by number of wrong questions so far.
      answerNumber[numWrong] = i + 1;

      // sets the answer key and incorrect answer in the 2D array based on 
      // the index of how many questions have been wrong so far.
      answer2D[0][numWrong] = answerKey[i];
      answer2D[1][numWrong] = answerChecked[i];

      ++numWrong;
    }
  }

  return numWrong;
}

void writeReport(
    unsigned int (&answerNumber)[20], char (&answer2D)[2][20], 
    unsigned int numWrong)
{
  constexpr size_t q_msg_begin = sizeof("Question") / 2;
  constexpr size_t c_a_msg_begin = sizeof("Correct Answer") / 2;
  constexpr size_t y_a_msg_begin = sizeof("Your Answer") / 2;

  string categories = "Question   Correct Answer   Your Answer"; 

  cout << "Exam Report Details" << '\n' 
    << "Number questions missed: " << numWrong << '\n'
    << "Missed questions and correct answers:" << '\n'
    << categories << '\n';
  
  for (int i = 0; i < numWrong; ++i) {
    // I add the previous messages whitespace counter since it is divided
    // by two to put the displayed value close to the middle of its label
    cout << setfill(' ') << right
      << setw(q_msg_begin) << answerNumber[i] << "   "
      << setw(q_msg_begin + c_a_msg_begin) << answer2D[0][i] << "   "
      << setw(c_a_msg_begin + y_a_msg_begin) << answer2D[1][i] << '\n';
  }

  cout.flush();
}
