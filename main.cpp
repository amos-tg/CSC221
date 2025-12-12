#include <exception>
#include <iostream>
using namespace std;

/// clears the screen using ANSI escape codes.
void clearScreen(void);

/// clears a single line using ANSI escape codes.
void clearLine(void);

/// board: 3x3 board array.
///
/// Takes an empty 3x3 array, initializes the board to '*' in all positions.
void initializeBoard(char (&board)[3][3]);

/// board: 3x3 board array.
///
/// Takes a 3x3 board array, the row and column numbers and cell contents of 
/// the array are displayed.
void displayBoard(char (&board)[3][3]);

/// token: the token to be placed.
///
/// board: the 3x3 board array.
///
/// uses getLocation(row, col) to get the position to  
/// place the token at.
void placeToken(char token, char (&board)[3][3]);

/// row: takes the row at which to place the token
///
/// col: takes the column at which to place the token
///
/// gets and validates the row and column at which to place a token
void getLocation(unsigned short &row, unsigned short &column, char token);

/// The options returned by getBoardState which indicate the game state.
enum { PLAY, TIE, X_WIN, O_WIN };

/// token: token checked 
/// 
/// board: 3x3 array of the board state
/// 
/// ouputs PLAY, TIE, X_WIN, or O_WIN based on the board state
unsigned getBoardState(char token, char (&board)[3][3]);

/// The options returned by checkBoard which indicate the board state
enum { SPACE_LEFT, NO_SPACE, WINNER };

/// token: the token to check for winning 3 in a row state
///
/// board: the 3x3 array checked for the various states
///
/// Checks for a row winner, a column winner, or a diagonal winner
/// if no winner is found, checks to see if there are still available 
/// cells in the board array. Returns SPACE_LEFT, NO_SPACE, WINNER.
unsigned checkBoard(char token, char (&board)[3][3]);

int main(void) {
  char board[3][3];

  clearScreen();
  initializeBoard(board);
  displayBoard(board);
  
  char token = 'X';
  for (int i = 1; i < 10; ++i) {
    placeToken(token, board);

    if (token == 'X') {
      token = 'O';   
    } else {
      token = 'X';
    }

    clearScreen();

    auto win_msg = " Won the Game!";
    switch (getBoardState(token, board)) {
      case X_WIN:
        i = 10;
        cout << 'X' << win_msg << endl;
        break;
      case O_WIN:
        i = 10;
        cout << 'O' << win_msg << endl;
        break;
      case TIE:
        i = 10;
        cout << "Nobody" << win_msg << endl;
        break;
      case PLAY:
        break;
    }

    displayBoard(board);
  } 


  return 0;
}

void clearScreen(void) {
  cout << "\033[2J\033[H"; 
  cout.flush();
}

void clearLine(void) {
  cout << "\033[2K";
  cout.flush();
}

void initializeBoard(char (&board)[3][3]) {
  for (char (&row)[3]: board) {
    for (char &square: row) {
      square = '*';
    }
  }
}

void displayBoard(char (&board)[3][3]) {
  cout << '\n' << "   | 1 | 2 | 3 |" 
    << '\n' << "----------------" << '\n';

  for (int row = 0; row < 3; ++row) {
    cout << ' ' << (row+1) << " | ";

    for (char &token: board[row]) {
      cout << token << " | "; 
    }

    cout << '\n' << "----------------" << '\n';
  }  

  cout.flush();
}

void placeToken(char token, char (&board)[3][3]) {
  unsigned short row, column;  
  auto taken_msg = 
    "The location inputted is already taken... (hit enter to try again)";

  for (;;) {
    string enter; 

    getLocation(row, column, token);

    switch (board[row][column]) {
      case 'X':
        cout << taken_msg << endl;
        cin >> enter;
        continue;
        break;
      case 'O':
        cout << taken_msg << endl;
        cin >> enter;
        continue;
        break;
    }

    board[row][column] = token;
    break;
  }
}

void getLocation(unsigned short &row, unsigned short &column, char token) {
  auto input_err = "Error: invalid input";

  cout << "Input the row to place the " << token << " at: ";
  cin >> row;
  if (cin.fail() || row > 3 || row < 1) {
    cerr << input_err << endl; 
    exit(1);
  }

  clearLine();
  cout.flush();

  cout << "Input the column to place the " << token << " at: ";
  cin >> column;
  if (cin.fail() || column > 3 || column < 1) {
    cerr << input_err << endl; 
    exit(1);
  }

  clearLine();
  cout.flush();

  // account for zero based indexing
  --row;
  --column;
}

unsigned getBoardState(char token, char (&board)[3][3]) {
  switch (checkBoard(token, board)) {
    case SPACE_LEFT:
      return PLAY; 
      break;
    case WINNER:
      if (token == 'X') {
        return X_WIN;
      } else if (token == 'O') {
        return O_WIN;
      }

      break;
    case NO_SPACE:
      return TIE;
      break;
  } 

  cerr << "Error: unreachable control flow" << endl;
  exit(1);
}

unsigned checkBoard(char token, char (&board)[3][3]) {
  // check rows
  for (char (&row)[3]: board) {
    for (int i = 0; i < 3; ++i) {
      if (token != row[i]) {
        continue;
      } else if (i == 2) {
        return WINNER;
      }
    }
  }
  
  // check columns
  for (int col = 0; col < 3; ++col) {
    for (int row = 0; row < 3; ++row) {
      if (token != board[row][col]) {
        continue;
      } else if (row == 2) {
        return WINNER;
      }
    }
  }                            
  
  // handles top left to bottom right diagonal 
  //
  // Index Representation:
  // (row:0, col:0) -> (row:1, col:1) -> (row:2, col:2)
  for (int row{}, col{}; row < 3; ++col, ++row) {
    if (token != board[row][col]) {
      break;
    } else if (row == 2) {
      return WINNER;
    }
  } 

  // handles the bottom left to top right diagonal 
  //
  // Index Representation:
  // (row:2, col:0) -> (row 1, col:1) -> (row:0, col:2)
  for (int row = 2, col = 0; col < 3; ++col, --row) {
    if (token != board[row][col]) {
      break;
    } else if (col == 2) {
      return WINNER;
    }
  }

  // nothing matched, so we check for space now
  for (char (&row)[3]: board) {
    for (char &spot: row) {
      if ('*' == spot) {
        return SPACE_LEFT;
      }
    }
  }

  // we didn't find any winners or space so we return NO_SPACE
  return NO_SPACE;
}

