#pragma once
struct King {
	char name;
	int x;
	int y;
};

struct Rook {
	char name;
	int x;
	int y;
	bool isTaken;
};
int generateBoardSize();
void clearBoard(char board[100][100], const int boardSize);
void clearData(King* enemyKing, King* playerKing, Rook* playerRook1, Rook* playerRook2);
void printBoard(char board[100][100], const int size);
void playerKingInit(char board[100][100], const int size, King* enemyKing);
void playerROOK1Init(char board[100][100], const int size, King* enemyKing);
void playerROOK2Init(char board[100][100], const int size, King* enemyKing);