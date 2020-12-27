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
};
int generateBoardSize();
bool isBotInCheckByRook(char board[100][100],int bot_X, int bot_Y, int currentRook_X, int currentRook_Y);
bool isBotInCheckByKing(int bot_x, int bot_y, int playerKing_X, int playerKing_Y);
bool isPossibleRookReplace(char board[100][100],int replace_X, int replace_Y, int current_X,int current_Y);
void botMakeValidMove(char board[100][100],const int boardSize,King *enemyking,int enemyKing_X,int enemyKing_Y,int playerKing_X,int playerKing_Y,int playerRook1_X, int playerRook1_Y,int playerRook2_X, int playerRook2_Y, bool &checkMateBOT);
void printBoard(char board[100][100],const int size);
void playerKingInit(char board[100][100], const int size, int x_BOT, int y_BOT);
void playerROOK1Init(char board[100][100], const int size, int x_BOT, int y_BOT);
void playerROOK2Init(char board[100][100], const int size, int x_bot, int y_bot);
