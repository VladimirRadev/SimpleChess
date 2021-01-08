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
* Header file store declaration of functions used in Main.cpp ( where is the game loop)
* Definition of functions listed down below is located in GameInitializer.cpp
*
*/
#pragma once
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>


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
void consoleClear();
void clearBoard(char board[100][100], const int boardSize);
void clearData(King* enemyKing, King* playerKing, Rook* playerRook1, Rook* playerRook2);
void printBoard(char board[100][100], const int size);
void playerKingInit(char board[100][100], const int size, King* enemyKing);
void playerROOK1Init(char board[100][100], const int size, King* enemyKing);
void playerROOK2Init(char board[100][100], const int size, King* enemyKing);