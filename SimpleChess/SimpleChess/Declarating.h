#pragma once
#include <vector>
using namespace std;

struct King {
	char name;
	int x;
	int y;
};

struct Rook {
	char name;
	int x;
	int y;
};

int generateBoardSize();
bool isForbidden(int ind, vector<int>& vect);
bool isPossibleRookReplace(char board[100][100], int replace_X, int replace_Y, Rook currentRook, Rook secondRook, King enemyKing, King playerKing);
void printBoard(char board[100][100],const int size);
void playerKingInit(char board[100][100], const int size, int x_BOT, int y_BOT);
void playerROOK1Init(char board[100][100], const int size, int x_BOT, int y_BOT);
void playerROOK2Init(char board[100][100], const int size, int x_bot, int y_bot);
void playerROOKMove(char board[100][100],int replace_X, int replace_Y, Rook currentRook);