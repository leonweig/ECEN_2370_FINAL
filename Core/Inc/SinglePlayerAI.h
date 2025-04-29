#ifndef SINGLEPLAYERAI_H_
#define SINGLEPLAYERAI_H_


#include <stdint.h>
#include <stdbool.h>
#include "Screen2.h"

//the AI is player two and RED

#define NoPlayer 0
#define PlayerOneWin 1
#define PlayerTwoWin 2

#define PlayerOne 1
#define PlayerTwo 2 

#define BoardColums 7
#define BoardRows 6
extern int BoardStatus[BoardColums][BoardRows];

int CheckWinnerSimulation(int BoardStatus[BoardColums][BoardRows]);
int CheckRowWinnerSimulation(int BoardStatus[BoardColums][BoardRows]);
int CheckColumnWinnerSimulation(int BoardStatus[BoardColums][BoardRows]);
int CheckDiagonalWinnerSimulation(int BoardStatus[BoardColums][BoardRows]);


int AIMove(int BoardStatus[BoardColums][BoardRows]);
int FindEmptyRow(int BoardStatus[BoardColums][BoardRows], int column);
int CheckWinMove(int BoardStatus[BoardColums][BoardRows]);
int CheckBlockMove(int BoardStatus[BoardColums][BoardRows]);
int CheckBoard(int BoardStatus[BoardColums][BoardRows]);
int CheckPlayer(int BoardStatus[BoardColums][BoardRows], int player);
int CheckBoard(int BoardStatus[BoardColums][BoardRows]);
int Probcount(int prob);



#endif
