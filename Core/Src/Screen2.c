#include "Screen2.h"




//1 is for player 1, 2 for player 2 and 0 for no player at all
int BoardStatus[BoardColums][BoardRows];
//+34 for the offsets
const int ColumnCirclePosition[7] = {18, 52, 86, 120, 154, 188, 222};
const int RowCirclePosition[6] = {302, 268, 234, 200, 166, 132};

static int PlayerCoinPositionTurn;
static int PlayerTurn;
bool TurnActive;


bool CheckTie(void){
	int BoardRowsFull = 0;
	for(int i = 0; i < BoardColums; i++)
	{
		//we only need to check the top rows (other functions do the rest already
		if(BoardStatus[i][BoardRows - 1] != NoPlayer)
		{
			BoardRowsFull++;
		}
	}
	if(BoardRowsFull == BoardColums)
	{
		return TRUE;
	}
	return FALSE;
}




void DeactivateTurn(void){
	TurnActive = FALSE;
	DeactivateTurnFlag();
}

bool GetTurnActive(void){
	return TurnActive;
}
void InitilizeBoardGame(void){

	for (int i = 0; i < BoardColums; i++){
	    for (int j = 0; j < BoardRows; j++){
	        BoardStatus[i][j] = NoPlayer;
	    }
	}

    LCD_Clear(0, LCD_COLOR_MAGENTA);
    PlayerCoinPositionTurn = 3;
    TurnActive = TRUE;
    PlayerTurn = PlayerOne;
    DisplayCurrentBoardGrid();

}


int PlayGameAgainstAI(void){
	InitilizeBoardGame();
    int Winner = NoPlayer;
    bool Tie = FALSE;
    while(Winner == NoPlayer && Tie == FALSE)
    {
    	//we need this delay for the button such that one can play in a smoother way
        HAL_Delay(200);
        if(PlayerTurn == PlayerOne)
        {
            MakeMove();
        }
        else
        {
            MakeMoveGameAI();
        }
        Tie = CheckTie();
        Winner = CheckWinner();
        DisplayCurrentBoardGrid();

    }
    if(Winner == PlayerOneWin)
    {
        return PlayerOneWin;
    }
    if(Winner == PlayerTwoWin)
    {
        return PlayerTwoWin;
    }
    //same function as PlayGame just with switching moves
	return 0;
}


void MakeMoveGyro(void){

    FullArray:

    TurnActive = TRUE;
    while (TurnActive){
        Turn_Side_Left_Right TurnSide = GetTurnedSide();

        if(TurnSide == LEFT_TURN){
            if(PlayerTurn == PlayerOne)
            {
                MoveCoinLeftPlayerOne();
            }
            else
            {
                MoveCoinLeftPlayerTwo();
            }
        }

        if(TurnSide == RIGHT_TURN){
            if(PlayerTurn == PlayerOne)
            {
                MoveCoinRightPlayerOne();
            }
            else
            {
                MoveCoinRightPlayerTwo();
            }
        }

    }

    if(BoardStatus[PlayerCoinPositionTurn][BoardRows - 1] != NoPlayer)
    {
        //to not place when column is full
        goto FullArray;
    }

    for (uint8_t i = 0; i < BoardRows; i++)
    {
        if(BoardStatus[PlayerCoinPositionTurn][i] == NoPlayer)
        {
            BoardStatus[PlayerCoinPositionTurn][i] = PlayerTurn;
            goto Placed;
        }
    }
Placed:

    ChangePlayer();
	RemoveCurrentPlayerTurnCoin();
    DisplayCurrentBoardGrid();

}



int RunScreen2(bool SinglePlayerTrue)
{
    if(SinglePlayerTrue == TRUE){
        int winner = PlayGameAgainstAI();
        return winner;
    }
    if(SinglePlayerTrue == FALSE){
        int winnerAi = PlayGame();
        return winnerAi;
    }
    return 0;
}



int PlayGame(void){

    InitilizeBoardGame();
    int Winner = NoPlayer;
    int Tie = FALSE;
    while(Winner == NoPlayer && Tie == FALSE)
    {
        HAL_Delay(200);
        MakeMoveGyro();
        Winner = CheckWinner();
        Tie = CheckTie();
        DisplayCurrentBoardGrid();
    }
    if(Winner == PlayerOneWin)
    {
        return PlayerOneWin;
    }
    if(Winner == PlayerTwoWin)
    {
        return PlayerTwoWin;
    }
    //if no win we just return 0 (so nothing added to score in SCREEN 3)
    return 0;
}







void DisplayGrid(void){
	LCD_Draw_Vertical_Line(0, 0, 320, LCD_COLOR_BLACK);
    LCD_Draw_Vertical_Line(34, 0, 320, LCD_COLOR_BLACK);
    LCD_Draw_Vertical_Line(68, 0, 320, LCD_COLOR_BLACK);
    LCD_Draw_Vertical_Line(102, 0, 320, LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(136, 0, 320, LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(170, 0, 320, LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(204, 0, 320, LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(238, 0, 320, LCD_COLOR_BLACK);

	LCD_Draw_Horizontal_Line(0, 115, 240, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(0, 149, 240, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(0, 183, 240, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(0, 217, 240, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(0, 251, 240, LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(0, 285, 240, LCD_COLOR_BLACK);

}





void DisplayCurrentBoardGrid(void){
    DisplayGrid();
    //this populates the board
    for(uint8_t i = 0; i < BoardColums; i++)
    {
        for(uint8_t j = 0; j < BoardRows; j++){
            if(BoardStatus[i][j] == 1){
                DisplayPlayerOneCoinInBoard(i, j);
            }
            if(BoardStatus[i][j] == 2){
                DisplayPlayerTwoCoinInBoard(i, j);
            }
        }
    }

    if(PlayerTurn == PlayerOne){
        DisplayPlayerOneCoinTurn();
    }
    if(PlayerTurn == PlayerTwo){
        DisplayPlayerTwoCoinTurn();
    }
}

void DisplayPlayerOneCoinTurn(void)
{
    for(uint8_t i = 0; i < BoardColums; i++){
        if(PlayerCoinPositionTurn == i){
            int Position_In_X = ColumnCirclePosition[i];
            //16 is radius again
            LCD_Draw_Circle_Fill(Position_In_X, PlayerCoinYPositionTurn, 16, LCD_COLOR_GREEN);
        }
    }
}

void DisplayPlayerTwoCoinTurn(void)
{
    for(uint8_t i = 0; i < BoardColums; i++){
        if(PlayerCoinPositionTurn == i){
            int Position_In_X = ColumnCirclePosition[i];
            //16 is radius again
            LCD_Draw_Circle_Fill(Position_In_X, PlayerCoinYPositionTurn, 16, LCD_COLOR_RED);
        }
    }
}




void DisplayPlayerOneCoinInBoard(uint8_t Column, uint8_t Row)
{
    uint16_t Position_In_X = ColumnCirclePosition[Column];
    uint16_t Position_In_Y = RowCirclePosition[Row];

    //radius is 16 of square
    LCD_Draw_Circle_Fill(Position_In_X, Position_In_Y, 16, LCD_COLOR_GREEN);
}


void DisplayPlayerTwoCoinInBoard(uint8_t Column, uint8_t Row)
{
    uint16_t Position_In_X = ColumnCirclePosition[Column];
    uint16_t Position_In_Y = RowCirclePosition[Row];

    //radius is 16 of square
    LCD_Draw_Circle_Fill(Position_In_X, Position_In_Y, 16, LCD_COLOR_RED);
}


int CheckWinner(void)
{
    int WinnerRow = CheckRowWinner();
    int WinnerColumn = CheckColumnWinner();
    int WinnerDiagonal = CheckDiagonalWinner();

    if((WinnerRow == PlayerOneWin) || (WinnerColumn == PlayerOneWin) || (WinnerDiagonal == PlayerOneWin))
    {
        return PlayerOneWin;
    }
    if((WinnerRow == PlayerTwoWin) || (WinnerColumn == PlayerTwoWin) || (WinnerDiagonal == PlayerTwoWin))
    {
        return PlayerTwoWin;
    }
    return NoPlayer;
}

int CheckColumnWinner(void){
    for(uint8_t i = 0; i < BoardColums; i++)
        {
            //reset four_in_row in every row
            uint8_t four_in_row_player_one = 0;
            uint8_t four_in_row_player_two = 0;

            for(uint8_t j = 0; j < BoardRows; j++)
            {
                if(BoardStatus[i][j] == NoPlayer)
                {
                    four_in_row_player_one = 0;
                    four_in_row_player_two = 0;
                }
                if(BoardStatus[i][j] == PlayerOne)
                {
                    four_in_row_player_one++;
                    four_in_row_player_two = 0;
                }
                if(BoardStatus[i][j] == PlayerTwo)
                {
                    four_in_row_player_one = 0;
                    four_in_row_player_two++;
                }

                //now check for a winner 
                if(four_in_row_player_one == 4)
                {
                    return PlayerOneWin;
                }
                if(four_in_row_player_two == 4){
                    return PlayerTwoWin;
                }
            }
        }
        return NoPlayer;
}

int CheckRowWinner(void){
    for(uint8_t i = 0; i < BoardRows; i++)
        {
            //reset four_in_row in every row
            uint8_t four_in_row_player_one = 0;
            uint8_t four_in_row_player_two = 0;

            for(uint8_t j = 0; j < BoardColums; j++)
            {
                if(BoardStatus[j][i] == NoPlayer)
                {
                    four_in_row_player_one = 0;
                    four_in_row_player_two = 0;
                }
                if(BoardStatus[j][i] == PlayerOne)
                {
                    four_in_row_player_one++;
                    four_in_row_player_two = 0;
                }
                if(BoardStatus[j][i] == PlayerTwo)
                {
                    four_in_row_player_one = 0;
                    four_in_row_player_two++;
                }

                //now check for a winner 
                if(four_in_row_player_one == 4)
                {
                    return PlayerOneWin;
                }
                if(four_in_row_player_two == 4){
                    return PlayerTwoWin;
                }
            }
        }
        return NoPlayer;
}

int CheckDiagonalWinner(void)
{
    //we check both diagonal directions 
    for(uint8_t i = 0; i < BoardRows - 3; i++)
    {
        for(uint8_t j = 0; j < BoardColums - 3; j++)
        {
            uint8_t four_in_diagonal_player_one = 0;
            uint8_t four_in_diagonal_player_two = 0;

            for(uint8_t k = 0; k < 4; k++)
            {
                if(BoardStatus[j+k][i+k] == PlayerOne)
                {
                    four_in_diagonal_player_one++;
                    four_in_diagonal_player_two = 0;
                }
                else if(BoardStatus[j+k][i+k] == PlayerTwo)
                {
                    four_in_diagonal_player_two++;
                    four_in_diagonal_player_one = 0;
                }
                else
                {
                    four_in_diagonal_player_one = 0;
                    four_in_diagonal_player_two = 0;
                }

                if(four_in_diagonal_player_one == 4)
                {
                    return PlayerOneWin;
                }
                if(four_in_diagonal_player_two == 4)
                {
                    return PlayerTwoWin;
                }
            }
        }
    }
    //cannot win under 4 rows (we check left to right top row down)
    for(uint8_t i = 3; i < BoardRows; i++)
    {
        for(uint8_t j = 0; j < BoardColums - 3; j++)
        {
            uint8_t four_in_diagonal_player_one = 0;
            uint8_t four_in_diagonal_player_two = 0;

            for(uint8_t k = 0; k < 4; k++)
            {
                if(BoardStatus[j+k][i-k] == PlayerOne)
                {
                    four_in_diagonal_player_one++;
                    four_in_diagonal_player_two = 0;
                }
                else if(BoardStatus[j+k][i-k] == PlayerTwo)
                {
                    four_in_diagonal_player_two++;
                    four_in_diagonal_player_one = 0;
                }
                else
                {
                    four_in_diagonal_player_one = 0;
                    four_in_diagonal_player_two = 0;
                }

                if(four_in_diagonal_player_one == 4)
                {
                    return PlayerOneWin;
                }
                if(four_in_diagonal_player_two == 4)
                {
                    return PlayerTwoWin;
                }
            }
        }
    }

    return NoPlayer;
}

//this is being used for normal gameplay (touch)
void MakeMove(void){
FullArray:

    TurnActive = TRUE;

    while (TurnActive){

        Touch_Side_Left_Right TouchedSide = GetTouchedSide();

        if(TouchedSide == LEFT_TOUCH){
            if(PlayerTurn == PlayerOne)
            {
                MoveCoinLeftPlayerOne();
                HAL_Delay(200);
                //all these delays are mostly for a smoother gameplay
            }
            else
            {
                MoveCoinLeftPlayerTwo();
                HAL_Delay(200);
            } 
        }

        if(TouchedSide == RIGHT_TOUCH){
            if(PlayerTurn == PlayerOne)
            {
                MoveCoinRightPlayerOne();
                HAL_Delay(200);
            }
            else
            {
                MoveCoinRightPlayerTwo();
                HAL_Delay(200);
            }
        }

    }

    if(BoardStatus[PlayerCoinPositionTurn][BoardRows - 1] != NoPlayer)
    {
        goto FullArray;
    }

    for (uint8_t i = 0; i < BoardRows; i++)
    {
        if(BoardStatus[PlayerCoinPositionTurn][i] == NoPlayer) 
        {
            BoardStatus[PlayerCoinPositionTurn][i] = PlayerTurn;
            goto Placed;
        }
    }
Placed:

    ChangePlayer();
    DisplayCurrentBoardGrid();
}














void MakeMoveGameAI(void) 
{
	RemoveCurrentPlayerTurnCoin();

    int AIMoveColumn = AIMove(BoardStatus);

    //this is for debuggin the AIMove function (if wrong decission happens but not the case)
    if(BoardStatus[AIMoveColumn][BoardRows - 1] != NoPlayer)
    {
        return;
    }
    for(uint8_t i = 0; i < BoardRows; i++)
    {
        if(BoardStatus[AIMoveColumn][i] == NoPlayer)
        {
            BoardStatus[AIMoveColumn][i] = PlayerTurn;
            break; 
        }
    }
    //center position after move
    PlayerCoinPositionTurn = 3;
    ChangePlayer();
    DisplayCurrentBoardGrid();
}
    




void ChangePlayer(void){
    if(PlayerTurn == PlayerOne){
        PlayerTurn = PlayerTwo;
        return;
    }
    else{
        PlayerTurn = PlayerOne;
    }
}


void MoveCoinLeftPlayerOne(void){
    if(PlayerCoinPositionTurn == 0)
    {
        return;
    }
    else
    {
        RemoveCurrentPlayerTurnCoin();
        PlayerCoinPositionTurn = PlayerCoinPositionTurn - 1;
        DisplayPlayerOneCoinTurn();
    }
}

void MoveCoinRightPlayerOne(void){
    if(PlayerCoinPositionTurn == BoardColums-1)
    {
        return;
    }
    else
    {
        RemoveCurrentPlayerTurnCoin();
        PlayerCoinPositionTurn = PlayerCoinPositionTurn + 1;
        DisplayPlayerOneCoinTurn();
    }
}

void MoveCoinLeftPlayerTwo(void){
    if(PlayerCoinPositionTurn == 0)
    {
        return;
    }
    else
    {
        RemoveCurrentPlayerTurnCoin();
        PlayerCoinPositionTurn = PlayerCoinPositionTurn - 1;
        DisplayPlayerTwoCoinTurn();
    }
}

void MoveCoinRightPlayerTwo(void){
    if(PlayerCoinPositionTurn == BoardColums-1)
    {
        return;
    }
    else
    {
        RemoveCurrentPlayerTurnCoin();
        PlayerCoinPositionTurn = PlayerCoinPositionTurn + 1;
        DisplayPlayerTwoCoinTurn();
    }
}

void RemoveCurrentPlayerTurnCoin(void){
    for(uint8_t i = 0; i < BoardColums; i++){
        if(PlayerCoinPositionTurn == i){
            uint16_t Position_In_X = ColumnCirclePosition[i];
            //16 is radius again
            LCD_Draw_Circle_Fill(Position_In_X, PlayerCoinYPositionTurn, 16, LCD_COLOR_MAGENTA);
        }
    }
}
