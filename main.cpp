#include <fstream>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

/// string answerPath = the path of the answer key file
///
/// char (&answerKey)[20]: answerKey = the buf the answer key is loaded into 
///
///
/// Reads the answer key at answerPath into the answerKey buffer.
///
/// Failure to read the answer key from answerPath will terminate the program 
/// with an error.
void getAnswers(string answerPath, char (&answerKey)[20]);

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
/// Checks the students answers against the answer key and returns the number 
/// of incorrect answers. 
///
///
/// Stores the incorrect question numbers in an array, and stores the correct
/// answer and the students answer in a 2-D parallel array.
///
/// The incorrect question numbers and the associated correct answer and 
/// incorrect answer are updated.
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
  return 0;
}

void getAnswers(string answerPath, char (&answerKey)[20]) {
  ifstream keyStream(answerPath); 
  if (!keyStream.is_open()) {
    cerr << "Error: failed to open answer key file" << endl;
    terminate();
  }

  for (char &answer: answerKey) {
    if (!(keyStream >> answer)) {
      cerr << "Error: failed to read from answer key file" << endl;
      terminate();
    }
  }
}
