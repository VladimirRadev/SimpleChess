#pragma once
#include <vector>
using namespace std;
int generateBoardSize();
bool isPossibleRookReplace(char board[100][100],int replace_X, int replace_Y, int current_X,int current_Y);
void printBoard(char board[100][100],const int size);
void playerKingInit(char board[100][100], const int size, int x_BOT, int y_BOT);
void playerROOK1Init(char board[100][100], const int size, int x_BOT, int y_BOT);
void playerROOK2Init(char board[100][100], const int size, int x_bot, int y_bot);
