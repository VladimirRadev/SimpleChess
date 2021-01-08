/**
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Vladimir Radev
* @idnumber 62530
* @compiler VC
*
* File to store all definitions of functions declarated in GamePlay.h file
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <map>
#include "GamePlay.h"
#include "GameInitializer.h"
using namespace std;

const char EMPTY = '-';
const char BOT = 'B';
const char ROOK1 = 'R';
const char ROOK2 = 'r';
const char KING = 'K';
bool isBotInCheckByRook(char board[100][100], int bot_X, int bot_Y, int currentRook_X, int currentRook_Y) {
	//if bot tries to take rook
	if (bot_X == currentRook_X && bot_Y == currentRook_Y) {
		return false;
	}
	else if (bot_X == currentRook_X) {
		//if bot has cover by other figure
		if (bot_Y < currentRook_Y) {
			char firstFigureInLine = '\0';
			for (int i = bot_Y + 1; i <= currentRook_Y; i++) {
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
			else if (firstFigureInLine == KING && (bot_Y - currentRook_Y) > 2) {
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
				if (board[i][bot_Y] != EMPTY && board[i][bot_Y] != BOT) {
					firstFigureInLine = board[i][bot_Y];
					break;
				}
			}
			if (firstFigureInLine == ROOK1 || firstFigureInLine == ROOK2) {
				return true;
			}
			else if (firstFigureInLine == KING && (bot_X - currentRook_X) > 2) {
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
			for (int i = bot_X + 1; i <= currentRook_X; i++) {
				if (board[i][bot_Y] != EMPTY && board[i][bot_Y] != BOT) {
					firstFigureInLine = board[i][bot_Y];
					break;
				}
			}
			if (firstFigureInLine == ROOK1 || firstFigureInLine == ROOK2) {
				return true;
			}
			else if (firstFigureInLine == KING && (currentRook_X - bot_X) > 2) {
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
bool isPossibleRookReplace(char board[100][100], int replace_X, int replace_Y, int current_X, int current_Y) {
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
bool isPossibleKingReplace(int replace_X, int replace_Y, King* enemyKing, King* playerKing) {
	if ((replace_X == playerKing->x && playerKing->y != replace_Y) || (replace_X != playerKing->x && playerKing->y == replace_Y)) {
		if (abs(abs(replace_X - playerKing->x) + abs(replace_Y - playerKing->y)) <= 1) {
			//same method is bot in check by king working for is king in check by bot after replace
			if (!isBotInCheckByKing(enemyKing->x, enemyKing->y, replace_X, replace_Y)) {
				return true;
			}
		}
		return false;
	}
	else if (abs(abs(replace_X - playerKing->x) + abs(replace_Y - playerKing->y)) <= 2) {
		if (!isBotInCheckByKing(enemyKing->x, enemyKing->y, replace_X, replace_Y)) {
			return true;
		}
		return false;
	}
	else {
		return false;
	}
}
bool canBotTakeRook(char board[100][100], int enemyKingNew_X, int enemyKingNew_Y, Rook* rookToDefend, King* playerKing) {
	if (rookToDefend->isTaken) {
		if (isBotInCheckByKing(enemyKingNew_X, enemyKingNew_Y, playerKing->x, playerKing->y)) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (isBotInCheckByRook(board, enemyKingNew_X, enemyKingNew_Y, rookToDefend->x, rookToDefend->y) || isBotInCheckByKing(enemyKingNew_X, enemyKingNew_Y, playerKing->x, playerKing->y)) {
		return false;
	}
	else {
		return true;
	}

}
void botMakeValidMove(char board[100][100], const int boardSize, King* enemyKing, King* playerKing, Rook* playerRook1, Rook* playerRook2, bool& checkMateBOT, bool& isDraw) {
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
			else if (board[enemyKing->x - 1][enemyKing->y] == playerRook1->name && canBotTakeRook(board, enemyKing->x - 1, enemyKing->y, playerRook2, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x - 1][enemyKing->y] = enemyKing->name;
				enemyKing->x = enemyKing->x - 1;
				enemyKing->y = enemyKing->y;
				playerRook1->isTaken = true;
				return;
			}
			else if (board[enemyKing->x - 1][enemyKing->y] == playerRook2->name && canBotTakeRook(board, enemyKing->x - 1, enemyKing->y, playerRook1, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x - 1][enemyKing->y] = enemyKing->name;
				enemyKing->x = enemyKing->x - 1;
				enemyKing->y = enemyKing->y;
				playerRook2->isTaken = true;
				return;
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
			else if (board[enemyKing->x - 1][enemyKing->y - 1] == playerRook1->name && canBotTakeRook(board, enemyKing->x - 1, enemyKing->y - 1, playerRook2, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x - 1][enemyKing->y - 1] = enemyKing->name;
				enemyKing->x = enemyKing->x - 1;
				enemyKing->y = enemyKing->y - 1;
				playerRook1->isTaken = true;
				return;
			}
			else if (board[enemyKing->x - 1][enemyKing->y] == playerRook2->name && canBotTakeRook(board, enemyKing->x - 1, enemyKing->y - 1, playerRook1, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x - 1][enemyKing->y - 1] = enemyKing->name;
				enemyKing->x = enemyKing->x - 1;
				enemyKing->y = enemyKing->y - 1;
				playerRook2->isTaken = true;
				return;
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
			else if (board[enemyKing->x - 1][enemyKing->y + 1] == playerRook1->name && canBotTakeRook(board, enemyKing->x - 1, enemyKing->y + 1, playerRook2, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x - 1][enemyKing->y + 1] = enemyKing->name;
				enemyKing->x = enemyKing->x - 1;
				enemyKing->y = enemyKing->y + 1;
				playerRook1->isTaken = true;
				return;
			}
			else if (board[enemyKing->x - 1][enemyKing->y + 1] == playerRook2->name && canBotTakeRook(board, enemyKing->x - 1, enemyKing->y + 1, playerRook1, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x - 1][enemyKing->y + 1] = enemyKing->name;
				enemyKing->x = enemyKing->x - 1;
				enemyKing->y = enemyKing->y + 1;
				playerRook2->isTaken = true;
				return;
			}

		}
	}

	//(x+1) state
	if (enemyKing->x + 1 <= boardSize - 1) {
		//(x+1) y 
		if (enemyKing->y <= boardSize - 1 && enemyKing->y >= 0) {
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
			else if (board[enemyKing->x + 1][enemyKing->y] == playerRook1->name && canBotTakeRook(board, enemyKing->x + 1, enemyKing->y, playerRook2, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x + 1][enemyKing->y] = enemyKing->name;
				enemyKing->x = enemyKing->x + 1;
				enemyKing->y = enemyKing->y;
				playerRook1->isTaken = true;
				return;
			}
			else if (board[enemyKing->x + 1][enemyKing->y] == playerRook2->name && canBotTakeRook(board, enemyKing->x + 1, enemyKing->y, playerRook1, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x + 1][enemyKing->y] = enemyKing->name;
				enemyKing->x = enemyKing->x + 1;
				enemyKing->y = enemyKing->y;
				playerRook2->isTaken = true;
				return;
			}

		}

		//(x+1) (y-1)
		if (enemyKing->y - 1 >= 0) {
			if (board[enemyKing->x + 1][enemyKing->y - 1] == EMPTY) {
				if (isBotInCheckByRook(board, enemyKing->x + 1, enemyKing->y - 1, playerRook1->x, playerRook1->y) ||
					isBotInCheckByRook(board, enemyKing->x + 1, enemyKing->y - 1, playerRook2->x, playerRook2->y) ||
					isBotInCheckByKing(enemyKing->x + 1, enemyKing->y - 1, playerKing->x, playerKing->y)) {
					checkMateMove_X = enemyKing->x + 1;
					checkMateMove_Y = enemyKing->y - 1;
				}
				else {
					possibleMovementsOfBOT[counterOfPossibleMovements][0] = enemyKing->x + 1;
					possibleMovementsOfBOT[counterOfPossibleMovements][1] = enemyKing->y - 1;
					++counterOfPossibleMovements;
				}
			}
			else if (board[enemyKing->x + 1][enemyKing->y - 1] == playerRook1->name && canBotTakeRook(board, enemyKing->x + 1, enemyKing->y - 1, playerRook2, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x + 1][enemyKing->y - 1] = enemyKing->name;
				enemyKing->x = enemyKing->x + 1;
				enemyKing->y = enemyKing->y - 1;
				playerRook1->isTaken = true;
				return;
			}
			else if (board[enemyKing->x + 1][enemyKing->y - 1] == playerRook2->name && canBotTakeRook(board, enemyKing->x + 1, enemyKing->y - 1, playerRook1, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x + 1][enemyKing->y - 1] = enemyKing->name;
				enemyKing->x = enemyKing->x + 1;
				enemyKing->y = enemyKing->y - 1;
				playerRook2->isTaken = true;
				return;
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
			else if (board[enemyKing->x + 1][enemyKing->y + 1] == playerRook1->name && canBotTakeRook(board, enemyKing->x + 1, enemyKing->y + 1, playerRook2, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x + 1][enemyKing->y + 1] = enemyKing->name;
				enemyKing->x = enemyKing->x + 1;
				enemyKing->y = enemyKing->y + 1;
				playerRook1->isTaken = true;
				return;
			}
			else if (board[enemyKing->x + 1][enemyKing->y + 1] == playerRook2->name && canBotTakeRook(board, enemyKing->x + 1, enemyKing->y + 1, playerRook1, playerKing)) {
				board[enemyKing->x][enemyKing->y] = EMPTY;
				board[enemyKing->x + 1][enemyKing->y + 1] = enemyKing->name;
				enemyKing->x = enemyKing->x + 1;
				enemyKing->y = enemyKing->y + 1;
				playerRook2->isTaken = true;
				return;
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
		else if (board[enemyKing->x][enemyKing->y - 1] == playerRook1->name && canBotTakeRook(board, enemyKing->x, enemyKing->y - 1, playerRook2, playerKing)) {
			board[enemyKing->x][enemyKing->y] = EMPTY;
			board[enemyKing->x][enemyKing->y - 1] = enemyKing->name;
			enemyKing->x = enemyKing->x;
			enemyKing->y = enemyKing->y - 1;
			playerRook1->isTaken = true;
			return;
		}
		else if (board[enemyKing->x][enemyKing->y - 1] == playerRook2->name && canBotTakeRook(board, enemyKing->x, enemyKing->y - 1, playerRook1, playerKing)) {
			board[enemyKing->x][enemyKing->y] = EMPTY;
			board[enemyKing->x][enemyKing->y - 1] = enemyKing->name;
			enemyKing->x = enemyKing->x;
			enemyKing->y = enemyKing->y - 1;
			playerRook2->isTaken = true;
			return;
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
		else if (board[enemyKing->x][enemyKing->y + 1] == playerRook1->name && canBotTakeRook(board, enemyKing->x, enemyKing->y + 1, playerRook2, playerKing)) {
			board[enemyKing->x][enemyKing->y] = EMPTY;
			board[enemyKing->x][enemyKing->y + 1] = enemyKing->name;
			enemyKing->x = enemyKing->x;
			enemyKing->y = enemyKing->y + 1;
			playerRook1->isTaken = true;
			return;
		}
		else if (board[enemyKing->x][enemyKing->y + 1] == playerRook2->name && canBotTakeRook(board, enemyKing->x, enemyKing->y + 1, playerRook1, playerKing)) {
			board[enemyKing->x][enemyKing->y] = EMPTY;
			board[enemyKing->x][enemyKing->y + 1] = enemyKing->name;
			enemyKing->x = enemyKing->x;
			enemyKing->y = enemyKing->y + 1;
			playerRook2->isTaken = true;
			return;
		}
	}


	if (possibleMovementsOfBOT.size() == 0 && !(isBotInCheckByRook(board, enemyKing->x, enemyKing->y, playerRook1->x, playerRook1->y) ||
		isBotInCheckByRook(board, enemyKing->x, enemyKing->y, playerRook2->x, playerRook2->y) ||
		isBotInCheckByKing(enemyKing->x, enemyKing->y, playerKing->x, playerKing->y))) {
		isDraw = true;
		return;
	}
	else if (possibleMovementsOfBOT.size() == 0 && (isBotInCheckByRook(board, enemyKing->x, enemyKing->y, playerRook1->x, playerRook1->y) ||
		isBotInCheckByRook(board, enemyKing->x, enemyKing->y, playerRook2->x, playerRook2->y) ||
		isBotInCheckByKing(enemyKing->x, enemyKing->y, playerKing->x, playerKing->y))) {
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