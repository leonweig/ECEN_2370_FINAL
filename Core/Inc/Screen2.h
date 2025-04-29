#ifndef SCREEN2_H_
#define SCREEN2_H_
#include "touch.h"
#include "SinglePlayerAI.h"
#include "Gyro_Driver.h"

//+34 for the offsets

#define PlayerCoinYPositionTurn 64


void DeactivateTurn(void);
int RunScreen2(bool SinglePlayerTrue);
int PlayGameAgainstAI(void);
int PlayGame(void);
void MakeMoveGameAI(void);





void InitilizeBoardGame(void);
void DisplayGrid(void);
void DisplayCurrentBoardGrid(void);
void DisplayPlayerOneCoinTurn(void);
void DisplayPlayerTwoCoinTurn(void);
void DisplayPlayerOneCoinInBoard(uint8_t Column, uint8_t Row);
void DisplayPlayerTwoCoinInBoard(uint8_t Column, uint8_t Row);
void MakeMove(void);
int CheckWinner(void);
int CheckRowWinner(void);
int CheckColumnWinner(void);
int CheckDiagonalWinner(void);
void ChangePlayer(void);
void MoveCoinLeftPlayerOne(void);
void MoveCoinRightPlayerOne(void);
void MoveCoinLeftPlayerTwo(void);
void MoveCoinRightPlayerTwo(void);
void RemoveCurrentPlayerTurnCoin(void);

void MakeMoveGyro(void);


#endif
