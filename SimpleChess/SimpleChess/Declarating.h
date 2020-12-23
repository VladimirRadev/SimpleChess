#pragma once
#include <vector>
using namespace std;
int generateBoardSize();
bool isForbidden(int ind, vector<int>& vect);
void printBoard(char board[100][100],const int size);
void playerKingInit(char board[100][100], const int size, int x_BOT, int y_BOT);
void playerRock1Init(char board[100][100], const int size, int x_BOT, int y_BOT);
void playerRock2Init(char board[100][100], const int size, int x_bot, int y_bot);