#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include "Declarating.h"
using namespace std;

const int MAX_BOARD_SIZE = 100;
const int BOARD_SIZE = generateBoardSize();
const char EMPTY = '-';
const char BOT = 'B';
const char ROCK1 = 'R';
const char ROCK2 = 'r';
const char KING = 'K';
const int FIGURE_COUNT = 4;
const string NEW_LINE_CHARS = "<< \n";
const string IMPUT_USER_CHARS = ">>   ";
char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

int main()
{
	srand((unsigned)time(0));
	short action = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = EMPTY;

		}
	}
	cout << setw(30)<<"GAME OPTIONS: \n";
	cout << "1.NEW GAME" << endl;
	cout << "2.CHANGE BOARD SIZE" << endl;
	cout << "3.EXIT" << endl<<endl;
	cout << "TYPE THE NUMBER OF WISH ACTION:  ";
	do {
		cin >> action;

	} while (action<1 || action>3);

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
		playerRock1Init(board, BOARD_SIZE, x_BOT, y_BOT);
		playerRock2Init(board, BOARD_SIZE, x_BOT, y_BOT);
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j] == BOT && (i != x_BOT || j != y_BOT)) {
					board[i][j] = EMPTY;
				}

			}

		}
		printBoard(board, BOARD_SIZE);
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