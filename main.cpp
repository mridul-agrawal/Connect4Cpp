#include <iostream>
#include <stdlib.h>
#include "printAscii.hpp"
using namespace std;

#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define WHITE   "\033[37m"      /* White */
#define YELLOW  "\033[33m"      /* Yellow */


void WelcomeScreen() {
  cout<<BLUE;
  printAscii("WelcomeTitle.txt");
  cout<<WHITE<<"\n\n\nRules:\n1. Two Player Game (Red {"<<RED<<"R"<<WHITE<<"} & Blue {"<<BLUE<<"B"<<WHITE<<"})\n2. Board Size is 6 rows x 7 Columns.\n3. A player wins if he/she is able to connect 4 dots horizontally, vertically or diagonally.\n4. Its a Draw if the board is fully filled.\n\n\nHow To Play:\n1. Game will always start with player-1 i.e. Red(R)\n2. In each turn choose the column number in which you want to drop the ball.\n3. rows will be filled from bottom to top in every column.\n\n\n";
  cout<<GREEN;
  printAscii("GameStarts.txt");
  cout << WHITE << "\n\n";
};

void InitializeBoard(char board[8][7]) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<7; j++) {
      if(i<6) board[i][j] = 'O';
      else if(i==6) board[i][j] = '-';
      else if(i==7) board[i][j] = '0'+(j+1);
    }
  }
};

void PrintBoard(char board[8][7]) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<7; j++) {
      if(board[i][j] == 'R') {
        cout << RED << board[i][j] << "\t";
      } else if(board[i][j] == 'B') {
        cout << BLUE << board[i][j] << "\t";
      } else {
        cout << WHITE << board[i][j] << "\t";
      }
    }
    cout << "\n";
  }
  cout << WHITE << "\n\n";
}

bool EnterRedToken(int col, char board[8][7]) {
  col--;
  if(board[0][col] != 'O') {
    cout << "this column is full. Please select another.\n";
    return true;
  } else {
    for(int i=5; i>=0; i--) {
      if(board[i][col] == 'O') {
        board[i][col] = 'R';
        break;
      }
    }
    return false;
  }
};

bool EnterBlueToken(int col, char board[8][7]) {
  col--;
  if(board[0][col] != 'O') {
    cout << "this column is full. Please select another.\n";
    return true;
  } else {
    for(int i=5; i>=0; i--) {
      if(board[i][col] == 'O') {
        board[i][col] = 'B';
        break;
      }
    }
    return false;
  }
};

bool StartGame() {
  cout << YELLOW << "START THE GAME? (Y/N) : \t";
  char input;
  cin >> input;
  if(input == 'N') {
    cout << "Thanks for Playing\n\n";
    return false;
  } else if (input != 'Y') {
    cout << "Please enter correct input \n\n";
    StartGame();
  }  else {
    return true;
  }
};

bool CheckForWin(char Player, char board[8][7]) {
  bool win = false;

  for(int i=5; i>=0; i--) {
    for(int j=6; j>=0; j--) {
      if(board[i][j] == Player    &&
				board[i-1][j-1] == Player &&
				board[i-2][j-2] == Player &&
				board[i-3][j-3] == Player ) {
				win = true;
			}
			
			if( board[i][j] == Player   &&
				board[i][j-1] == Player &&
				board[i][j-2] == Player &&
				board[i][j-3] == Player ) {
				win = true;
			}
					
			if( board[i][j] == Player   &&
				board[i-1][j] == Player &&
				board[i-2][j] == Player &&
				board[i-3][j] == Player ) {	
				win = true;
			}
					
			if( board[i][j] == Player     &&
				board[i-1][j+1] == Player &&
				board[i-2][j+2] == Player &&
				board[i-3][j+3] == Player ) {
				win = true;
			}
						
			if ( board[i][j] == Player   &&
				 board[i][j+1] == Player &&
				 board[i][j+2] == Player &&
				 board[i][j+3] == Player ) {
				win = true;
			}
    }
  }

  return win;

};



int main() {
  WelcomeScreen();
  char board[8][7];
  InitializeBoard(board);
  // PrintBoard(board);
  bool GameEnds = false;
  bool RedTurn = true;
  bool BlueTurn = false; 

  if(!StartGame()) {
    return 0;
  }

  while(!GameEnds) {
    // CLEAR SCREEN
    cout << WHITE << "\033[2J\033[0;0H";

    if(RedTurn) {
      PrintBoard(board);
      cout << RED << "Player - 1 (RED)\n";
      cout << WHITE << "Enter the column number in which you wish to drop your token \t";
      int r;
      cin >> r;
      RedTurn = EnterRedToken(r,board);
      bool won = CheckForWin('R',board);
      if(won) {
        GameEnds = true;
        cout << RED << "\nPlayer - 1 (Red) Won the Game!!!\n\n";
        PrintBoard(board);
        continue;
      }
      BlueTurn = !RedTurn;
      if(RedTurn) continue;
    }
    
    if(BlueTurn) {
      PrintBoard(board);
      cout << BLUE << "Player - 2 (BLUE)\n";
      cout << WHITE << "Enter the column number in which you wish to drop your token \t";
      int b;
      cin >> b;
      BlueTurn = EnterBlueToken(b,board);
      bool won = CheckForWin('B',board);
      if(won) {
        GameEnds = true;
        cout << BLUE << "\nPlayer - 2 (Blue) Won the Game!!!\n\n";
        PrintBoard(board);
        continue;
      }
      RedTurn = !BlueTurn;
      if(BlueTurn) continue;
    }

  }
} 