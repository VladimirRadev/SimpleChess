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
* Definition of functions listed down below is located in GamePlay.cpp
*
*/
#pragma once
#include <vector>
#include "GameInitializer.h"
bool isBotInCheckByRook(char board[100][100], int bot_X, int bot_Y, int currentRook_X, int currentRook_Y);
bool isBotInCheckByKing(int bot_x, int bot_y, int playerKing_X, int playerKing_Y);
bool isPossibleRookReplace(char board[100][100], int replace_X, int replace_Y, int current_X, int current_Y);
bool isPossibleKingReplace(int replace_X, int replace_Y, King* enemyKing, King* playerKing);
bool canBotTakeRook(char board[100][100], int enemyKingNew_X, int enemyKingNew_Y, Rook* rookToDefend, King* playerKing);
void botMakeValidMove(char board[100][100], const int boardSize, King* enemyKing, King* playerKing, Rook* playerRook1, Rook* playerRook2, bool& checkMateBOT, bool& isDraw);