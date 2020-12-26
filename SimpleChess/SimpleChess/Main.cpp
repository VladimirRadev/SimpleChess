#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <string>
#include "Declarating.h"
using namespace std;

const int BOARD_SIZE = generateBoardSize();
const char EMPTY = '-';
const char BOT = 'B';
const char ROOK1 = 'R';
const char ROOK2 = 'r';
const char KING = 'K';
const int FIGURE_COUNT = 4;
const string NEW_LINE_CHARS = "<< \n";
const string IMPUT_USER_CHARS = ">> ";
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
int main()
{
	char board[100][100] = { 0 };
	srand((unsigned)time(0));
	short action = 0;
	King enemyKing = { BOT,0,0 };
	King playerKing = { KING,0,0 };
	Rook playerRook1 = { ROOK1,0,0 };
	Rook playerRook2 = { ROOK2,0,0 };
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = EMPTY;

		}
	}
	cout << setw(30) << "GAME OPTIONS: \n";
	cout << "1.NEW GAME" << endl;
	cout << "2.CHANGE BOARD SIZE" << endl;
	cout << "3.EXIT" << endl << endl;
	cout << "TYPE THE NUMBER OF WISH ACTION:  ";
	do {
		cin >> action;

	} while (action < 1 || action>3);

	if (action == 1) {
		int x_BOT = (int)(rand() % (BOARD_SIZE - 1));
		int y_BOT = (int)(rand() % (BOARD_SIZE - 1));
		board[x_BOT][y_BOT] = BOT;
		if (x_BOT - 1 >= 0) {
			board[x_BOT - 1][y_BOT] = BOT;
			if (y_BOT - 1 >= 0) {
				board[x_BOT - 1][y_BOT - 1] = BOT;
			}
			if (y_BOT + 1 <= BOARD_SIZE - 1) {
				board[x_BOT - 1][y_BOT + 1] = BOT;
			}
		}
		if (x_BOT + 1 <= BOARD_SIZE - 1) {
			board[x_BOT + 1][y_BOT] = BOT;
			if (y_BOT - 1 >= 0) {
				board[x_BOT + 1][y_BOT - 1] = BOT;
			}
			if (y_BOT + 1 <= BOARD_SIZE - 1) {
				board[x_BOT + 1][y_BOT + 1] = BOT;
			}
		}
		if (y_BOT - 1 >= 0) {
			board[x_BOT][y_BOT - 1] = BOT;
		}
		if (y_BOT + 1 <= BOARD_SIZE - 1) {
			board[x_BOT][y_BOT + 1] = BOT;
		}

		cout << NEW_LINE_CHARS;
		playerKingInit(board, BOARD_SIZE, x_BOT, y_BOT);
		playerROOK1Init(board, BOARD_SIZE, x_BOT, y_BOT);
		playerROOK2Init(board, BOARD_SIZE, x_BOT, y_BOT);
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j] == BOT && (i != x_BOT || j != y_BOT)) {
					board[i][j] = EMPTY;
				}

			}
		}
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j] == enemyKing.name) {
					enemyKing.x = i;
					enemyKing.y = j;
				}
				else if (board[i][j] == playerKing.name) {
					playerKing.x = i;
					playerKing.y = j;
				}
				else if (board[i][j] == playerRook1.name) {
					playerRook1.x = i;
					playerRook1.y = j;
				}
				else if (board[i][j] == playerRook2.name) {
					playerRook2.x = i;
					playerRook2.y = j;
				}
			}
		}
		//string line;
		string playerPiece;
		int player_X = 0;
		int player_Y = 0;
		bool checkMateBOT = false;
		int counterMoves = 0;
		//getline(cin, line, '\n');
		while (!checkMateBOT) {
			printBoard(board, BOARD_SIZE);
			bool flag = false;
			while (!flag) {
				cout << IMPUT_USER_CHARS;
				cin >> playerPiece >> player_X >> player_Y;
				bool flag = true;
				if (playerPiece[0] == KING || playerPiece[0] == ROOK1 || playerPiece[0] == ROOK2) {
					if (player_X >= 0 && player_X <= BOARD_SIZE - 1) {
						if (player_Y >= 0 && player_Y <= BOARD_SIZE - 1) {
							if (board[player_X][player_Y] == EMPTY) {
								if (playerPiece[0] == playerRook1.name) {
									if (isPossibleRookReplace(board,player_X, player_Y,playerRook1.x, playerRook1.y)) {
										board[playerRook1.x][playerRook1.y] = EMPTY;
										board[player_X][player_Y] = playerRook1.name;
										playerRook1.x = player_X;
										playerRook1.y = player_Y;
									}
									else {
										continue;
									}
								}
								else if (playerPiece[0] == playerRook2.name) {
									if (isPossibleRookReplace(board, player_X, player_Y, playerRook2.x, playerRook2.y)) {
										board[playerRook2.x][playerRook2.y] = EMPTY;
										board[player_X][player_Y] = playerRook2.name;
										playerRook2.x = player_X;
										playerRook2.y = player_Y;
									}
									else {
										continue;
									}
								}
								else if (playerPiece[0] == playerKing.name) {
									if ((player_X == playerKing.x && playerKing.y != player_Y) || (player_X != playerKing.x && playerKing.y == player_Y)) {
										if (abs(abs(player_X - playerKing.x) + abs(player_Y - playerKing.y)) <= 1) {
											board[playerKing.x][playerKing.y] = EMPTY;
											board[player_X][player_Y] = playerKing.name;
											playerKing.x = player_X;
											playerKing.y = player_Y;
											break;
										}
										continue;
									}
									else if (abs(abs(player_X-playerKing.x)+abs(player_Y-playerKing.y))<=2) {
										board[playerKing.x][playerKing.y] = EMPTY;
										board[player_X][player_Y] = playerKing.name;
										playerKing.x = player_X;
										playerKing.y = player_Y;
										break;
									}
									else {
										continue;
									}

								}
								flag = true;
								break;
							}
						}
					}

				}
			}
			/*if (playerPiece[0] == playerRook1.name) {
				if ((player_X == playerRook1.x && player_Y != playerRook1.y) || (player_X != playerRook1.x && player_Y == playerRook1.y)) {
					board[playerRook1.x][playerRook1.y] = EMPTY;
					board[player_X][player_Y] = playerRook1.name;
					playerRook1.x = player_X;
					playerRook1.y = player_Y;
				}
				else {
					continue;
				}
			}
			else if (playerPiece[0] == playerRook2.name) {
				if ((player_X == playerRook2.x && player_Y != playerRook2.y) || (player_X != playerRook2.x && player_Y == playerRook2.y)) {
					board[playerRook2.x][playerRook2.y] = EMPTY;
					board[player_X][player_Y] = playerRook2.name;
					playerRook2.x = player_X;
					playerRook2.y = player_Y;
				}
				else {
					continue;
				}
			}
			else if (playerPiece[0] == playerKing.name) {

			}*/



		}

	}
	else if (action == 2) {
		//todo change line in file
		return 0;
	}
	else if (action == 3) {
		cout << "Goodbye" << endl;
		return 0;

	}

}