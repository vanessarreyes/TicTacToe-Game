#include <iostream>
#include <string>
#include <vector>
using namespace std;

class GamePlay {
    // private variables
    private:
      int board[3][3];
      bool user_rep;
      bool cpu_rep;
      int winner;
      int challenge_count;

    // public variables
    public:
      // initialized function
      GamePlay();
      // function piecePick
      void piecePick();
      // function boardDisplay
      void boardDisplay();
      // function user_turn
      void user_turn();
      // function cpu_turn
      void cpu_turn();
      // function challenge
      bool challenge();
      // function boardCheck
      void boardCheck();
      // function getWinner
      int getWinner();
      // function scoreboard
      void scoreboard();


};
