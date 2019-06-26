#include <limits>
#include "GamePlay.h"

// initialized function
GamePlay::GamePlay() {
  // set the board to empty
  // column (i)
  for (int i = 0; i < 3; i++) {
    // row (j)
    for (int j = 0; j < 3; j++) {
      board[i][j] = -1;
    }
  }
  winner = -1;
  challenge_count = 0;
}

// function that allows the user to pick which piece they will be represented by
void GamePlay::piecePick() {
    // declare variables
    int choice = -1;
    bool correct = false;

    // while loop that checks if choice is -1
    // allows the question to be asked if the user enters in an invalid number
    while (choice == -1) {
      // output message
      cout << "Would you like to be an 'X' or an 'O'?" << endl;
      cout << "1: X" << endl;
      cout << "2: O" << endl;
      // allow the user to enter in their choice
      cin >> choice;

      // if that checks if the player chose X
      if (choice == 1) {
        // true means player representation is an X
        // sets the user to X and the cpu to O
        user_rep = true;
        cpu_rep = false;
        choice = true;
      }
      // else if that checks if the user chose O
      else if (choice == 2) {
        // false means player chose O
        // sets the user to O and the cpu to O
        user_rep  = false;
        cpu_rep = true;
        choice = true;
      }
      // all else
      else {
        // resets the cin so there are no invalid errors
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid choice." << endl;
      }
    }

    // if that checks if the user_rep is an X
    if (user_rep == true) {
      cout << "You will be represented by a X on the board. The computer will be represented by an O." << endl;
    }
    // all else
    else {
      cout << "You will be represented by a O on the board. The computer will be represented by an X." << endl;
    }
}

// displays the board to the user
void GamePlay::boardDisplay() {
    cout << endl;
    cout << endl;
    // column (i)
    // for loop that runs through the rows and columns of the board and checks if they are empty. X, or O
    for (int i = 0; i < 3; i++) {
      // row (j)
      cout << "|";
      for (int j = 0; j < 3; j++) {
        // if the position on the board is a 1, display X
        if (board[i][j] == 1) {
            cout << " X "<< "|";
        }
        // else if the position on the board is a 0, display O
        else if (board[i][j] == 0) {
            cout << " O "<< "|";
        }
        // all else
        else {
            cout << "   "<< "|";
        }
      }
      cout << endl;
      // if that checks if the row is less than 2 to display boarder
      if (i < 2) {
        cout << "-------------" << endl;
      }
    }
    cout << endl;
    cout << endl;
}

// function that runs the user's turn
void GamePlay::user_turn() {
  // declare variables
    int row = 4;
    int column = 4;
    bool correct = false;

    // while loop that checks if correct id false
    // makes sure that the user does not chose a spot that has a piece there already
    while (correct == false) {
      // output message
      cout << "Where do you want to place your next turn ?" << endl;
      // while loop that checks if row is greater than 3
      while (row > 3) {
          // allow user to input the row that they want
          cout << "Which row: " << endl;
          cin >> row;
          // if that checks if the user entered in a row less than 3
          if (row > 3) {
              // output message
              cout << "Please enter in a valid row." << endl;
          }
      }

      // while that checks if the column is less than 3
      while (column > 3) {
        // output message
        cout << "Which column: " << endl;
        cin >> column;
        // if that checks if the user entered a column less than 3
        if (column > 3) {
            // output message
            cout << "Please enter in a valid column." << endl;
        }
      }

      // subtract 1 fpom the column and row to make up for array starting at 0
      // if that checks if the board already has a piece in the chosen spot
      if (board[row - 1][column - 1] == cpu_rep || board[row - 1][column - 1] == user_rep) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          row = 4; column = 4;
          cout << "There is already a piece there. Please select a new place." << endl;
      }
      // else allows user to put piece there
      else {
        board[row - 1][column - 1] = user_rep;
        correct = true;
      }
    }
}

// function for the cpu's turn
void GamePlay::cpu_turn() {
    // declare variables
    int row = rand() % 3 + 1;
    int column = rand() % 3 + 1;
    bool correct = false;

    // while loop that checks if the random position chosen is a free spot on board
    while (correct == false) {
      // if that checks if the chosen position is not taken already
      if ((board[row - 1][column - 1] == cpu_rep) || (board[row - 1][column - 1] == user_rep)) {
          // if not open spot, chosen another random location
          row = rand() % 3 + 1;
          column = rand() % 3 + 1;
       }
       // else set that spot to the cpu piece
       else {
         correct = true;
         board[row - 1][column - 1] = cpu_rep;
       }
    }
}

// allows the cpu to stop winner from winning (makes game more challenging)
// checks the board to see if the user has 2 pieces in a row and sets the cpu piece in the area to prevent the user from winning
// only happens if the chance is greater than 30
bool GamePlay::challenge() {
    // declare variables
    // gets a random number out of 100
    int chance = rand() % 100 + 1;
    cout << "Count: " << challenge_count << endl;
    cout << "Chance: " << chance << endl;
    bool place = user_rep;

    // if that checks if the chance is greater than 30 and that the challenge count is not 3
    if (chance > 30 && challenge_count != 3) {
      // Down Column 1 check
      // set the row and column to location to check
      int row = 0; int column = 0;
      // if that checks if the location is a user piece
      if (board[row][column] == place) {
          // if that checks if the location is a user piece
          if (board[1][column] ==  place) {
              // if that checks if the spot to prevent the user from winning is already taken by cpu
              if (board[2][column] != cpu_rep) {
                // set the position to the cpu piece
                board[2][column] = cpu_rep;
                // add one to the challenge count
                challenge_count++;
                // return true
                return true;
              }
              // all else
              else {
                return false;
              }
          }
          // else if that checks if the location is a user piece
          else if (board[2][column] == place) {
              // if that checks if the spot to prevent the user from winning is already taken by cpu
              if (board[1][column] != cpu_rep) {
                // set the position to the cpu piece
                board[1][column] = cpu_rep;
                // add one to the challenge count
                challenge_count++;
                // return true
                return true;
              }
              //  all else
              else {
                return false;
              }
          }
      }

      // Down column 2 check
        // set the row and column to location to check
      row = 0; column = 1;
      // if that checks if the location is a user piece
      if (board[row][column] == place) {
          // if that checks if the location is a user piece
          if (board[1][column] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[2][column] != cpu_rep) {
              // set the position to the cpu piece
              board[2][column] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
          // else if that checks if the location is a user piece
          else if (board[2][column] == place) {
              // if that checks if the spot to prevent the user from winning is already taken by cpu
              if (board[1][column] != cpu_rep) {
                // set the position to the cpu piece
                board[1][column] = cpu_rep;
                // add one to the challenge count
                challenge_count++;
                // return true
                return true;
              }
              // all else
              else {
                return false;
              }
          }
      }

      // Down column 3 check
        // set the row and column to location to check
      row = 0; column = 2;
      // if that checks if the location is a user piece
      if (board[row][column] == place) {
          // if that checks if the location is a user piece
          if (board[1][column] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[2][column] != cpu_rep) {
              // set the position to the cpu piece
              board[2][column] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            else {
              // all else
              return false;
            }
          }
          // else if that checks if the location is a user piece
          else if (board[2][column] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[1][column] != cpu_rep) {
              // set the position to the cpu piece
              board[1][column] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
      }

      // Horizontal row 1 check
        // set the row and column to location to check
      row = 0; column = 0;
      // if that checks if the location is a user piece
      if (board[row][column] == place) {
          // if that checks if the location is a user piece
          if (board[row][1] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[row][2] != cpu_rep) {
              // set the position to the cpu piece
              board[row][2] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
          // else if that checks if the location is a user piece
          else if (board[row][2] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[row][1] != cpu_rep) {
              // set the position to the cpu piece
              board[row][1] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
      }

      // Horizontal row 2 check
        // set the row and column to location to check
      row = 1; column = 0;
      // if that checks if the location is a user piece
      if (board[row][column] == place) {
          // if that checks if the location is a user piece
          if (board[row][1] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[row][2] != cpu_rep) {
              // set the position to the cpu piece
              board[row][2] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
          // else if that checks if the location is a user piece
          else if (board[row][2] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[row][1] != cpu_rep) {
              // set the position to the cpu piece
              board[row][1] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
      }

      // Horizontal row 3 check
        // set the row and column to location to check
      row = 2; column = 0;
      // if that checks if the location is a user piece
      if (board[row][column] == place) {
          // if that checks if the location is a user piece
          if (board[row][1] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[row][2] != cpu_rep) {
              // set the position to the cpu piece
              board[row][2] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
          // else if that checks if the location is a user piece
          else if (board[row][2] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[row][1] != cpu_rep) {
              // set the position to the cpu piece
              board[row][1] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
      }

      // Diagonal check (Left to right)
        // set the row and column to location to check
      row = 0; column = 0;
      // if that checks if the location is a user piece
      if (board[row][column] == place) {
          // if that checks if the location is a user piece
          if (board[1][1] ==  place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[2][2] != cpu_rep) {
              // set the position to the cpu piece
              board[2][2] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
          // else if that checks if the location is a user piece
          else if (board[2][2] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[1][1] != cpu_rep) {
              // set the position to the cpu piece
              board[1][1] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
        }

      // Diagonal check (Right to Left)
        // set the row and column to location to check
      row = 0; column = 2;
      // if that checks if the location is a user piece
      if (board[row][column] == place) {
          // if that checks if the location is a user piece
          if (board[1][1] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[2][0] != cpu_rep) {
              // set the position to the cpu piece
              board[2][0] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
          // else if that checks if the location is a user piece
          else if (board[2][0] == place) {
            // if that checks if the spot to prevent the user from winning is already taken by cpu
            if (board[1][1] != cpu_rep) {
              // set the position to the cpu piece
              board[1][1] = cpu_rep;
              // add one to the challenge count
              challenge_count++;
              // return true
              return true;
            }
            // all else
            else {
              return false;
            }
          }
      }
    }
    return false;
}

// checks if either the user or cpu has won the game by checking the board to see if there are any three in a row
// sets winner to -1 if there is no winner to continue game
void GamePlay::boardCheck() {
  // declare variables
    bool x_or_o;
    int row = -1;
    int column = -1;

    // Down Column 1 check
    // set the row and column to location to check
    row = 0; column = 0;
    // if that checks if the location isn't empty and that there isn't a winner yet
    if (board[row][column] != -1 && winner == -1) {
        // set variable to the piece at that spot
        x_or_o = board[row][column];

        // if that checks if the next location needed to make a three in a row is the same piece
        if (x_or_o == board[1][column]) {
            // if that checks if the next location needed to make a three in a row is the same piece
            if (x_or_o == board[2][column]) {
              // set the winner to the piece that matches the player
              winner = x_or_o;
            }
        }
    }

    // Down column 2 check
    // set the row and column to location to check
    row = 0; column = 1;
    // if that checks if the location isn't empty and that there isn't a winner yet
    if (board[row][column] != -1 && winner == -1) {
        // set variable to the piece at that spot
        x_or_o = board[row][column];

        // if that checks if the next location needed to make a three in a row is the same piece
        if (x_or_o == board[1][column]) {
            // if that checks if the next location needed to make a three in a row is the same piece
            if (x_or_o == board[2][column]) {
              // set the winner to the piece that matches the player
              winner = x_or_o;
            }
        }
    }

    // Down column 3 check
    // set the row and column to location to check
    row = 0; column = 2;
    // if that checks if the location isn't empty and that there isn't a winner yet
    if (board[row][column] != -1 && winner == -1) {
        // set variable to the piece at that spot
        x_or_o = board[row][column];

        // if that checks if the next location needed to make a three in a row is the same piece
        if (x_or_o == board[1][column]) {
            // if that checks if the next location needed to make a three in a row is the same piece
            if (x_or_o == board[2][column]) {
              // set the winner to the piece that matches the player
              winner = x_or_o;
            }
        }
    }

    // Horizontal row 1 check
    // set the row and column to location to check
    row = 0; column = 0;
    // if that checks if the location isn't empty and that there isn't a winner yet
    if (board[row][column] != -1 && winner == -1) {
        // set variable to the piece at that spot
        x_or_o = board[row][column];

        // if that checks if the next location needed to make a three in a row is the same piece
        if (x_or_o == board[row][1]) {
            // if that checks if the next location needed to make a three in a row is the same piece
            if (x_or_o == board[row][2]) {
              // set the winner to the piece that matches the player
              winner = x_or_o;
            }
        }
    }

    // Horizontal row 2 check
    // set the row and column to location to check
    row = 1; column = 0;
    // if that checks if the location isn't empty and that there isn't a winner yet
    if (board[row][column] != -1 && winner == -1) {
        // set variable to the piece at that spot
        x_or_o = board[row][column];

        // if that checks if the next location needed to make a three in a row is the same piece
        if (x_or_o == board[row][1]) {
            // if that checks if the next location needed to make a three in a row is the same piece
            if (x_or_o == board[row][2]) {
              // set the winner to the piece that matches the player
              winner = x_or_o;
            }
        }
    }

    // Horizontal row 3 check
    // set the row and column to location to check
    row = 2; column = 0;
    // if that checks if the location isn't empty and that there isn't a winner yet
    if (board[row][column] != -1 && winner == -1) {
        // set variable to the piece at that spot
        x_or_o = board[row][column];

        // if that checks if the next location needed to make a three in a row is the same piece
        if (x_or_o == board[row][1]) {
            // if that checks if the next location needed to make a three in a row is the same piece
            if (x_or_o == board[row][2]) {
              // set the winner to the piece that matches the player
              winner = x_or_o;
            }
        }
    }

    // Diagonal check (Left to right)
    // set the row and column to location to check
    row = 0; column = 0;
    // if that checks if the location isn't empty and that there isn't a winner yet
    if (board[row][column] != -1 && winner == -1) {
        // set variable to the piece at that spot
        x_or_o = board[row][column];

        // if that checks if the next location needed to make a three in a row is the same piece
        if (x_or_o == board[1][1]) {
            // if that checks if the next location needed to make a three in a row is the same piece
            if (x_or_o == board[2][2]) {
              // set the winner to the piece that matches the player
              winner = x_or_o;
            }
        }
    }

    // Diagonal check (Right to Left)
    // set the row and column to location to check
    row = 0; column = 2;
    // if that checks if the location isn't empty and that there isn't a winner yet
    if (board[row][column] != -1 && winner == -1) {
        // set variable to the piece at that spot
        x_or_o = board[row][column];

        // if that checks if the next location needed to make a three in a row is the same piece
        if (x_or_o == board[1][1]) {
            // if that checks if the next location needed to make a three in a row is the same piece
            if (x_or_o == board[2][0]) {
              // set the winner to the piece that matches the player
              winner = x_or_o;
            }
        }
    }

}

// announces who the winner is
int GamePlay::getWinner() {
    // if the winner is user_rep
    if (winner == user_rep) {
        // display the baord
        boardDisplay();
        // if the user won, return 0
        return 0;
    }
    // else if the winner is the cpu
    else if (winner == cpu_rep) {
        // display the board
        boardDisplay();
        // if the cpu won, return 1;
        return 1;
    }

    // declare variable
    int count = 0;
    // for loop that runs through the board and checks if all the places are not empty to check for draw
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          // if that checks if the board location is not empty
          if (board[i][j] != -1) {
            // add ont to count
            count++;
          }
        }
    }

    // if that checks if the count is 9
    if (count == 9) {
        // display message
        cout << endl;
        cout << "It is a tie." << endl;
        // return -2 for a tie
        return -2;
    }
    // return winner
    return winner;
}
