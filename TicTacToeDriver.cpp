// Vanessa Reyes
// Tic Tac Toe

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "GamePlay.h"
using namespace std;

// main function
int main() {
    // allows for more random numbers
    srand(123);
    // Game vector that holds GamePlay class objects
    vector<GamePlay> Games;
    // declare variables
    bool another_game = true;
    int game_num = 0;
    int user_win = 0;
    int cpu_win = 0;

    // ouput message
    cout << "============= Tic Tac Toe =============" << endl;
    // while loop that checks if another game is true to keep playing the game
    while (another_game == true) {
        // declare variables
        int y_or_no = -1;
        GamePlay new_game;
        // create a new addition to variable
        Games.push_back(new_game);
        int winner = -1;
        int turn = 0;
        bool challenge_true = false;

        // call piece pick function from Games class
        Games[game_num].piecePick();

        // while loop that checks if there is any winner yet
        while (winner == -1) {
          // call board display function from Games class
          Games[game_num].boardDisplay();

          // call user turn function from Games class
          Games[game_num].user_turn();

          // call board check function from Game class
          Games[game_num].boardCheck();

          // call get winner function from the Games class and set the return to variable
          winner = Games[game_num].getWinner();

          // if that checks if there is any winner
          if (winner == -1) {
              // if that checks if the turn is greater than 1
              if (turn >= 1) {
                  // call the challenege function and set the return to a variable
                  challenge_true = Games[game_num].challenge();
                  // if that checks if the challenge_true is false
                  if (challenge_true == false) {
                      // call the cpu_turn function from Games class
                      Games[game_num].cpu_turn();
                  }
              }
              // all else
              else {
                  // call cpu_turn from Games function
                  Games[game_num].cpu_turn();
              }

              // call board check function from the Games function
              Games[game_num].boardCheck();

              // call get winner function and set return equal to variable
              winner = Games[game_num].getWinner();
          }
          // add one to the turn
          turn++;

          // if that checks if the winner is 0
          if (winner == 0) {
            // add one to the user win
            user_win++;
          }
          // else if that checks if the winner is 1
          else if (winner == 1) {
            // add one to the cpu win
            cpu_win++;
          }
        }

        // while loop that checks if yes or no is -1
        while(y_or_no == -1) {
          // declare variables
          y_or_no = -2;

          // display message
          cout << endl;
          cout << "Scoreboard" << endl;
          cout << "User score: " << user_win << endl;
          cout << "CPU score: " << cpu_win << endl;
          cout << endl;
          cout << "Do you want to play another game?" << endl;
          cout << "1: Yes" << endl;
          cout << "2: No" << endl;
          cin >> y_or_no;

          // if that checks if yes or no is 1
          if (y_or_no == 1) {
            // set another game to true
            another_game = true;
            // add one to the game number
            game_num++;
          }
          // else if that checks if yes or no is 2
          else if (y_or_no == 2) {
            // set another game to false
            another_game = false;
            // if that checks if the user win is greater than cpu win
            if (user_win > cpu_win) {
              // display message
              cout << "Nice job, you have won the cpu against Tic Tac Toe" << endl;
            }
            else {
              cout << "Better luck next time playing the computer at Tic Tac Toe" << endl;
            }
          }
          // all else
          else {
            // resets the cin so there are no invalid errors
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter in valid choice." << endl;
            y_or_no = -1;
          }
        }
    }
    return 0;
}
