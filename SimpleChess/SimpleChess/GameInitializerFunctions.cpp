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
* File to store all definitions of functions declarated in GameInitializer.h file
*
*/
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "GameInitializer.h"
#include "GamePlay.h"
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
	inFile.open("CustomSizeBoard.txt", ios::in);
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
void consoleClear()
{
	Sleep(100);
	system("CLS");
	Sleep(100);
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
	srand((unsigned)time(0));
	for (int x = 1 + (int)(rand() % (size - 2)); x >= 0; x--) {
		for (int y = size - 1; y >= 0; y--) {
			if (board[x][y] != enemyKing->name && board[x][y] == EMPTY && !isBotInCheckByKing(enemyKing->x, enemyKing->y, x, y)) {
				board[x][y] = KING;
				return;
			}
		}
	}
}
void playerROOK1Init(char board[100][100], const int size, King* enemyKing) {
	for (int x = 0; x <= size - 1; x++) {
		if (x == enemyKing->x) {
			continue;
		}
		for (int y = size - 1; y >= 0; y--) {
			if (y == enemyKing->y) {
				continue;
			}
			else if (board[x][y] != enemyKing->name && board[x][y] != KING && board[x][y] == EMPTY)
			{
				board[x][y] = ROOK1;
				return;
			}
		}
	}
}
void playerROOK2Init(char board[100][100], const int size, King* enemyKing) {
	for (int x = size - 1; x >= 0; x--) {
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
void clearBoard(char board[100][100], const int boardSize) {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			board[i][j] = EMPTY;
		}
	}
}
void clearData(King* enemyKing, King* playerKing, Rook* playerRook1, Rook* playerRook2) {

	enemyKing->x = 0;
	enemyKing->y = 0;
	playerKing->x = 0;
	playerKing->y = 0;
	playerRook1->x = 0;
	playerRook1->y = 0;
	playerRook1->isTaken = false;
	playerRook2->x = 0;
	playerRook2->y = 0;
	playerRook2->isTaken = false;
}
