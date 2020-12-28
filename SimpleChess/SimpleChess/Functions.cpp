#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <map>
#include "Declarating.h"
using namespace std;

const char EMPTY = '-';
const char BOT = 'B';
const char ROOK1 = 'R';
const char ROOK2 = 'r';
const char KING = 'K';
int generateBoardSize()
{
	string line = "";
	ifstream inFile;
	inFile.open("constSize.txt", ios::in);
	if (!inFile) {
		return -1;
	}
	getline(inFile, line, '\n');
	inFile.close();
	int num = 0;
	for (int i = 0; i < line.length(); i++) {
		bool flag = false;
		if (line[i] == ' ') {
			continue;
		}
		if (isdigit(line[i])) {
			for (int j = i; j < line.length(); j++) {
				num += num * 10 + (line[j] - '0');
			}
			flag = true;
		}
		if (flag == true) {
			break;
		}
	}
	return num;

}
bool isBotInCheckByRook(char board[100][100],int bot_X, int bot_Y, int currentRook_X, int currentRook_Y) {
	if (bot_X == currentRook_X) {
		//if bot has cover by other figure
		if (bot_Y < currentRook_Y) {
			char firstFigureInLine = '\0';
			for (int i = bot_Y + 1; i <= currentRook_Y;i++) {
				if (board[bot_X][i] != EMPTY && board[bot_X][i] != BOT) {
					firstFigureInLine = board[bot_X][i];
					break;
				}
			}
			if (firstFigureInLine == '\0') {
				return false;
			}
			if (firstFigureInLine == ROOK1 || firstFigureInLine == ROOK2) {
				return true;
			}
			else if (firstFigureInLine == KING && (currentRook_Y - bot_Y) > 2) {
				return false;
			}
			else if (firstFigureInLine == KING && (currentRook_Y - bot_Y) <= 2) {
				return true;
			}
			return false;
		}
		if (bot_Y > currentRook_Y) {
			char firstFigureInLine = '\0';
			for (int i = bot_Y - 1; i >= currentRook_Y; i--) {
				if (board[bot_X][i] != EMPTY && board[bot_X][i] != BOT) {
					firstFigureInLine = board[bot_X][i];
					break;
				}
			}
			if (firstFigureInLine == '\0') {
				return false;
			}
			if (firstFigureInLine == ROOK1 || firstFigureInLine == ROOK2) {
				return true;
			}
			else if (firstFigureInLine == KING && (bot_Y-currentRook_Y) > 2) {
				return false;
			}
			else if (firstFigureInLine == KING && (bot_Y - currentRook_Y) <= 2) {
				return true;
			}
			return false;
		}
	}
	else if (bot_Y == currentRook_Y) {
		if (bot_X > currentRook_X) {
			char firstFigureInLine = '\0';
			for (int i = bot_X - 1; i >= currentRook_X; i--) {
				if (board[i][bot_Y] != EMPTY && board[i][bot_Y]!=BOT) {
					firstFigureInLine = board[i][bot_Y];
					break;
				}
			}
			if (firstFigureInLine == ROOK1 || firstFigureInLine == ROOK2) {
				return true;
			}
			else if (firstFigureInLine == KING && (bot_X-currentRook_X) > 2) {
				return false;
			}
			else if (firstFigureInLine == KING && (bot_X - currentRook_X) <= 2) {
				return true;
			}
			else {
				return false;
			}
		}
		if (bot_X < currentRook_X) {
			char firstFigureInLine = '\0';
			for (int i = bot_X+1; i <= currentRook_X; i++) {
				if (board[i][bot_Y] != EMPTY && board[i][bot_Y] != BOT) {
					firstFigureInLine = board[i][bot_Y];
					break;
				}
			}
			if (firstFigureInLine == ROOK1 || firstFigureInLine == ROOK2) {
				return true;
			}
			else if (firstFigureInLine == KING && (currentRook_X-bot_X) > 2) {
				return false;
			}
			else if (firstFigureInLine == KING && (currentRook_X - bot_X) <= 2) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}
bool isBotInCheckByKing(int bot_x, int bot_y, int playerKing_X, int playerKing_Y) {
	if ((bot_x == playerKing_X && playerKing_Y != bot_y) || (bot_x != playerKing_X && playerKing_Y == bot_y)) {
		if (abs(abs(bot_x - playerKing_X) + abs(bot_y - playerKing_Y)) <= 1) {
			return true;
		}
		return false;
	}
	else if (abs(abs(bot_x - playerKing_X) + abs(bot_y - playerKing_Y)) <= 2) {
		return true;
	}
	else {
		return false;
	}
}

bool isPossibleRookReplace(char board[100][100],int replace_X, int replace_Y, int current_X,int current_Y) {
	if ((replace_X == current_X && replace_Y != current_Y) || (replace_X != current_X && replace_Y == current_Y)) {
		//move up or down
		if (replace_Y == current_Y) {
			if (current_X > replace_X) {
				for (int i = current_X - 1; i > replace_X; i--) {
					if (board[i][replace_Y] != EMPTY) {
						return false;
					}
				}
				return true;
			}
			else if (current_X < replace_X) {
				for (int i = current_X + 1; i < replace_X; i++) {
					if (board[i][replace_Y] != EMPTY) {
						return false;
					}
				}
				return true;
			}
		}
		//move left or right
		else if (replace_X == current_X) {
			if (current_Y > replace_Y) {
				for (int i = current_Y - 1; i > replace_Y; i--) {
					if (board[replace_X][i] != EMPTY) {
						return false;
					}
				}
				return true;
			}
			else if (current_Y < replace_Y) {
				for (int i = current_Y + 1; i < replace_Y; i++) {
					if (board[replace_X][i] != EMPTY) {
						return false;
					}
				}
				return true;
			}
		}

	}
	else {
		return false;
	}
}
void botMakeValidMove(char board[100][100], const int boardSize, King* enemyKing, King* playerKing, Rook* playerRook1, Rook* playerRook2 , bool& checkMateBOT) {
	map<int, int[2]>possibleMovementsOfBOT;
	int checkMateMove_X = enemyKing->x, checkMateMove_Y = enemyKing->y, counterOfPossibleMovements = 0;
	//(x-1) state
	if (enemyKing->x - 1 >= 0) {
		//(x-1) y
		if (enemyKing->y >= 0) {
			if (board[enemyKing->x - 1][enemyKing->y] == EMPTY) {
				if (isBotInCheckByRook(board, enemyKing->x - 1, enemyKing->y, playerRook1->x, playerRook1->y) ||
					isBotInCheckByRook(board, enemyKing->x - 1, enemyKing->y, playerRook2->x, playerRook2->y) ||
					isBotInCheckByKing(enemyKing->x - 1, enemyKing->y, playerKing->x, playerKing->y)) {
					checkMateMove_X = enemyKing->x - 1;
					checkMateMove_Y = enemyKing->y;
				}
				else {
					possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x - 1;
					possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y;
					++counterOfPossibleMovements;
				}
			}
		}
		//(x-1)(y-1)
		if (enemyKing->y - 1 >= 0) {
			if (board[enemyKing->x - 1][enemyKing->y - 1] == EMPTY) {
				if (isBotInCheckByRook(board, enemyKing->x - 1, enemyKing->y - 1, playerRook1->x, playerRook1->y) ||
					isBotInCheckByRook(board, enemyKing->x - 1, enemyKing->y - 1, playerRook2->x, playerRook2->y) ||
					isBotInCheckByKing(enemyKing->x - 1, enemyKing->y - 1, playerKing->x, playerKing->y)) {
					checkMateMove_X = enemyKing->x - 1;
					checkMateMove_Y = enemyKing->y - 1;
				}
				else {
					possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x - 1;
					possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y - 1;
					++counterOfPossibleMovements;
				}
			}
		}

		//(x-1)(y+1)
		if (enemyKing->y + 1 <= boardSize - 1) {
			if (board[enemyKing->x - 1][enemyKing->y + 1] == EMPTY) {
				if (isBotInCheckByRook(board, enemyKing->x - 1, enemyKing->y + 1, playerRook1->x, playerRook1->y) ||
					isBotInCheckByRook(board, enemyKing->x - 1, enemyKing->y + 1, playerRook2->x, playerRook2->y) ||
					isBotInCheckByKing(enemyKing->x - 1, enemyKing->y + 1, playerKing->x, playerKing->y)) {
					checkMateMove_X = enemyKing->x - 1;
					checkMateMove_Y = enemyKing->y + 1;
				}
				else {
					possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x - 1;
					possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y + 1;
					++counterOfPossibleMovements;
				}
			}
			
		}
	}

	//(x+1) state
	if (enemyKing->x + 1 <= boardSize - 1) {
		//(x+1) y 
		if (enemyKing->y <= boardSize - 1 && enemyKing->y>=0) {
			if (board[enemyKing->x + 1][enemyKing->y] == EMPTY) {
				if (isBotInCheckByRook(board, enemyKing->x + 1, enemyKing->y, playerRook1->x, playerRook1->y) ||
					isBotInCheckByRook(board, enemyKing->x + 1, enemyKing->y, playerRook2->x, playerRook2->y) ||
					isBotInCheckByKing(enemyKing->x + 1, enemyKing->y, playerKing->x, playerKing->y)) {
					checkMateMove_X = enemyKing->x + 1;
					checkMateMove_Y = enemyKing->y;
				}
				else {
					possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x + 1;
					possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y;
					++counterOfPossibleMovements;
				}
			}

		}
		//(x+1) (y-1)
		if (enemyKing->y - 1 >= 0) {
			if (board[enemyKing->x + 1][enemyKing->y-1] == EMPTY) {
				if (isBotInCheckByRook(board, enemyKing->x + 1, enemyKing->y-1, playerRook1->x, playerRook1->y) ||
					isBotInCheckByRook(board, enemyKing->x + 1, enemyKing->y-1, playerRook2->x, playerRook2->y) ||
					isBotInCheckByKing(enemyKing->x + 1, enemyKing->y-1, playerKing->x, playerKing->y)) {
					checkMateMove_X = enemyKing->x + 1;
					checkMateMove_Y = enemyKing->y-1;
				}
				else {
					possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x + 1;
					possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y-1;
					++counterOfPossibleMovements;
				}
			}
		}
		//(x+1) (y+1)
		if (enemyKing->y + 1 <= boardSize - 1) {
			if (board[enemyKing->x + 1][enemyKing->y + 1] == EMPTY) {
				if (isBotInCheckByRook(board, enemyKing->x + 1, enemyKing->y + 1, playerRook1->x, playerRook1->y) ||
					isBotInCheckByRook(board, enemyKing->x + 1, enemyKing->y + 1, playerRook2->x, playerRook2->y) ||
					isBotInCheckByKing(enemyKing->x + 1, enemyKing->y + 1, playerKing->x, playerKing->y)) {
					checkMateMove_X = enemyKing->x + 1;
					checkMateMove_Y = enemyKing->y + 1;
				}
				else {
					possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x + 1;
					possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y + 1;
					++counterOfPossibleMovements;
				}
			}
		}
	}
	//x (y-1)
	if (enemyKing->y - 1 >= 0) {
		if (board[enemyKing->x][enemyKing->y - 1] == EMPTY) {
			if (isBotInCheckByRook(board, enemyKing->x, enemyKing->y - 1, playerRook1->x, playerRook1->y) ||
				isBotInCheckByRook(board, enemyKing->x, enemyKing->y - 1, playerRook2->x, playerRook2->y) ||
				isBotInCheckByKing(enemyKing->x, enemyKing->y - 1, playerKing->x, playerKing->y)) {
				checkMateMove_X = enemyKing->x;
				checkMateMove_Y = enemyKing->y - 1;
			}
			else {
				possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x;
				possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y - 1;
				++counterOfPossibleMovements;
			}
		}
	}

	//x (y+1)
	if (enemyKing->y + 1 <= boardSize - 1) {
		if (board[enemyKing->x][enemyKing->y + 1] == EMPTY) {
			if (isBotInCheckByRook(board, enemyKing->x, enemyKing->y + 1, playerRook1->x, playerRook1->y) ||
				isBotInCheckByRook(board, enemyKing->x, enemyKing->y + 1, playerRook2->x, playerRook2->y) ||
				isBotInCheckByKing(enemyKing->x, enemyKing->y + 1, playerKing->x, playerKing->y)) {
				checkMateMove_X = enemyKing->x;
				checkMateMove_Y = enemyKing->y + 1;
			}
			else {
				possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x;
				possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y + 1;
				++counterOfPossibleMovements;
			}
		}
	}



	if (possibleMovementsOfBOT.size() == 0) {
		checkMateBOT = true;
		board[enemyKing->x][enemyKing->y] = EMPTY;
		board[checkMateMove_X][checkMateMove_Y] = BOT;
		return;
	}
	else {
		srand((unsigned)time(0));
		int randomPossibleMove = (int)(rand() % possibleMovementsOfBOT.size());
		int botReplaceOn_X = possibleMovementsOfBOT[randomPossibleMove][0];
		int botReplaceOn_Y = possibleMovementsOfBOT[randomPossibleMove][1];
		board[enemyKing->x][enemyKing->y] = EMPTY;
		board[botReplaceOn_X][botReplaceOn_Y] = enemyKing->name;
		enemyKing->x = botReplaceOn_X;
		enemyKing->y = botReplaceOn_Y;
		return;
		

	}
}
void printBoard(char board[100][100], const int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}
void playerKingInit(char board[100][100], const int size, King* enemyKing) {
	for (int x = 0; x < size; x++) {
		for (int y = size - 1; y >= 0; y--) {
			if (board[x][y] != enemyKing->name && board[x][y] == EMPTY && !isBotInCheckByKing(enemyKing->x,enemyKing->y,x,y)) {
				board[x][y] = KING;
				return;
			}
		}
	}
}
void playerROOK1Init(char board[100][100], const int size, King *enemyKing) {
	for (int x = 0; x <= size-1; x++) {
		if (x == enemyKing->x) {
			continue;
		}
		for (int y = size-1; y >= 0; y--) {
			if (y == enemyKing->y) {
				continue;
			}
			else if(board[x][y]!=enemyKing->name && board[x][y]!=KING && board[x][y]==EMPTY)
			{
				board[x][y] = ROOK1;
				return;
			}
		}
	}
}
void playerROOK2Init(char board[100][100], const int size, King* enemyKing) {
	for (int x = size-1; x >=0; x--) {
		if (x == enemyKing->x) {
			continue;
		}
		for (int y = 0; y < size; y++) {
			if (y == enemyKing->y) {
				continue;
			}
			else if (board[x][y] != enemyKing->name && board[x][y] != KING && board[x][y] != ROOK1 && board[x][y] == EMPTY)
			{
				board[x][y] = ROOK2;
				return;
			}
		}
	}
}
