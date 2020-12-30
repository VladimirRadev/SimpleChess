#pragma once
#include <vector>
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
bool isBotInCheckByRook(char board[100][100],int bot_X, int bot_Y, int currentRook_X, int currentRook_Y);
bool isBotInCheckByKing(int bot_x, int bot_y, int playerKing_X, int playerKing_Y);
bool isPossibleRookReplace(char board[100][100],int replace_X, int replace_Y, int current_X,int current_Y);
bool isPossibleKingReplace(int replace_X,int replace_Y, King* enemyKing, King *playerKing);
bool canBotTakeRook(char board[100][100], int enemyKingNew_X, int enemyKingNew_Y, Rook* rookToDefend, King* playerKing);
void botMakeValidMove(char board[100][100], const int boardSize, King* enemyKing, King* playerKing, Rook* playerRook1, Rook* playerRook2, bool& checkMateBOT,bool &isDraw);
void clearBoard(char board[100][100], const int boardSize);
void clearData(King* enemyKing, King* playerKing, Rook* playerRook1, Rook* playerRook2);
void printBoard(char board[100][100],const int size);
void playerKingInit(char board[100][100], const int size, King *enemyKing);
void playerROOK1Init(char board[100][100], const int size, King* enemyKing);
void playerROOK2Init(char board[100][100], const int size, King* enemyKing);
