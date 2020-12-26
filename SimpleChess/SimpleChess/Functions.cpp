#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "StructHolder.h"
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
bool isForbidden(int ind, vector<int>& vect) {
	for (int i = 0; i < vect.size(); i++) {
		if (ind == vect[i]) {
			return true;
		}
	}
	return false;

}
bool isPossibleRookReplace(char board[100][100], int replace_X, int replace_Y, Rook currentRook, Rook secondRook, King enemyKing, King playerKing) {
	if ((replace_X == currentRook.x && replace_Y != currentRook.y) || (replace_X != currentRook.x && replace_Y == currentRook.y)) {
	


	}
	else {
		return false;
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
void playerKingInit(char board[100][100], const int size, int x_BOT, int y_BOT) {
	for (int x = 0; x < size; x++) {
		for (int y = size - 1; y >= 0; y--) {
			if (board[x][y] != BOT && board[x][y] == EMPTY) {
				board[x][y] = KING;
				return;
			}
		}
	}
}
void playerROOK1Init(char board[100][100], const int size, int x_BOT, int y_BOT) {
	for (int x = 0; x <= size-1; x++) {
		if (x == x_BOT) {
			continue;
		}
		for (int y = size-1; y >= 0; y--) {
			if (y == y_BOT) {
				continue;
			}
			else if(board[x][y]!=BOT && board[x][y]!=KING && board[x][y]==EMPTY)
			{
				board[x][y] = ROOK1;
				return;
			}
		}
	}
}
void playerROOK2Init(char board[100][100], const int size, int x_BOT, int y_BOT) {
	for (int x = size-1; x >=0; x--) {
		if (x == x_BOT) {
			continue;
		}
		for (int y = 0; y < size; y++) {
			if (y == y_BOT) {
				continue;
			}
			else if (board[x][y] != BOT && board[x][y] != KING && board[x][y] != ROOK1 && board[x][y] == EMPTY)
			{
				board[x][y] = ROOK2;
				return;
			}
		}
	}
}
void playerROOKMove(char board[100][100], int replace_X, int replace_Y, Rook currentRook) {
	board[currentRook.x][currentRook.y] = EMPTY;
	board[replace_X][replace_Y] = currentRook.name;
	currentRook.x = replace_X;
	currentRook.y = replace_Y;
}