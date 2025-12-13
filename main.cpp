// WARNING: 
// this may or may not work if you don't have virtual terminal 
// processing enabled on your console. WARNING: because of the
// ANSI escape codes I use which when printed to the screen 
// clear a line or the screen 
//
// https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
#if defined(_WIN64)
  #include <windows.h>
#endif

#include <iostream>

using namespace std;


#if defined(_WIN64)
/// sets virtual terminal mode if the OS is windows
void setVirtTermSeq(void);
#endif

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
  // this is untested so I am hoping it 
  // makes my ANSI escape codes cross platform
  // I think it is safe to guess you are on a 64 bit processor
  #if defined(_WIN64) 
    setVirtTermSeq();
  #endif

  char board[3][3];

  clearScreen();
  initializeBoard(board);
  displayBoard(board);
  
  char token = 'X';
  for (int i = 1; i < 10; ++i) {
    placeToken(token, board);
    clearScreen();

    auto win_msg = " Won the Game!";
    switch (getBoardState(token, board)) {
      case PLAY:
        break;
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
    }

    displayBoard(board);

    if (token == 'X') {
      token = 'O';   
    } else {
      token = 'X';
    }
  } 


  return 0;
}


#if defined(_WIN64)
// allegedly inspired this from megasoft documentation
// this is not a legal admission of lawful or unlawful usage
void setVirtTermSeq(void) {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hOut == INVALID_HANDLE_VALUE)
  {
    cerr << "Error: virtual terminal setting failed" << endl;
    exit(1);
  }
  
  DWORD dwMode = 0;
  if (!GetConsoleMode(hOut, &dwMode))
  {
    cerr << "Error: virtual terminal setting failed" << endl;
    exit(1);
  }
  
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (!SetConsoleMode(hOut, dwMode))
  {
    cerr << "Error: virtual terminal setting failed" << endl;
    exit(1);
  }
}
#endif

// this works on linux but I'm not sure how 
// windows will handle ANSI escape codes.
void clearScreen(void) {
  cout << "\033[2J\033[H"; 
  cout.flush();
}

// this works on linux but I'm not sure how 
// windows will handle ANSI escape codes.
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
  const auto seperator = "----------------";

  // prints out the column labels
  cout << '\n' << "   | 1 | 2 | 3 |" 
    << '\n' << seperator << '\n';

  // prints out the row labels and the row's contents
  for (int row = 0; row < 3; ++row) {
    cout << ' ' << (row+1) << " | ";

    for (char &token: board[row]) {
      cout << token << " | "; 
    }

    cout << '\n' << seperator << '\n';
  }  

  cout.flush();
}


void placeToken(char token, char (&board)[3][3]) {
  unsigned short row, column;  

  auto taken_msg = 
    "The location inputted is already taken... (hit enter to try again)";

  for (;;) {
    getLocation(row, column, token);

    // checks to see if the spot on the board is available
    // and asks for a different one if it's taken
    switch (board[row][column]) {
      case 'X':
        cout << taken_msg << endl;
        continue;
        break;
      case 'O':
        cout << taken_msg << endl;
        continue;
        break;
    }

    board[row][column] = token;
    break;
  }
}

void getLocation(unsigned short &row, unsigned short &column, char token) {
  auto input_err = "Error: invalid input";

  // gets the row and validates it or exits the prog.
  cout << "Input the row to place the " << token << " at: ";
  cin >> row;
  if (cin.fail() || row > 3 || row < 1) {
    cerr << input_err << endl; 
    exit(1);
  }

  clearLine();

  // gets the column and validates it or exits the prog.
  cout << "Input the column to place the " << token << " at: ";
  cin >> column;
  if (cin.fail() || column > 3 || column < 1) {
    cerr << input_err << endl; 
    exit(1);
  }

  clearLine();

  // account for zero based indexing
  --row;
  --column;
}

unsigned getBoardState(char token, char (&board)[3][3]) {
  // parses the game state enum val from checkBoard into more
  // descriptive game state val returned from this function.
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
        break;
      } else if (i == 2) {
        return WINNER;
      }
    }
  }
  
  // check columns
  for (int col = 0; col < 3; ++col) {
    for (int row = 0; row < 3; ++row) {
      if (token != board[row][col]) {
        break;
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

  // nothing matched, checks for space now
  for (char (&row)[3]: board) {
    for (char &spot: row) {
      if ('*' == spot) {
        return SPACE_LEFT;
      }
    }
  }

  // didn't find any winners or space so we return NO_SPACE
  return NO_SPACE;
}

