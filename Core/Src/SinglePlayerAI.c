#include "SinglePlayerAI.h"




//we include these functions as Simluations to not get confused with the single player version
int CheckWinnerSimulation(int BoardStatus[BoardColums][BoardRows])
{
	 int WinnerRow = CheckRowWinnerSimulation(BoardStatus);
	 int WinnerColumn = CheckColumnWinnerSimulation(BoardStatus);
	 int WinnerDiagonal = CheckDiagonalWinnerSimulation(BoardStatus);

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


int CheckRowWinnerSimulation(int BoardStatus[BoardColums][BoardRows]){
    for(uint8_t i = 0; i < BoardColums; i++)
    {
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

int CheckColumnWinnerSimulation(int BoardStatus[BoardColums][BoardRows]){
    for(uint8_t i = 0; i < BoardRows; i++)
    {
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

int CheckDiagonalWinnerSimulation(int BoardStatus[BoardColums][BoardRows])
{
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
                if(BoardStatus[j+k][i+k] == PlayerTwo)
                {
                    four_in_diagonal_player_two++;
                    four_in_diagonal_player_one = 0;
                }
                if(BoardStatus[j+k][i+k] == NoPlayer)
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

    //topleft to bottum right start with i =3
    for(uint8_t i = 3; i < BoardRows ; i++)
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



//all these functions have BoardStatus passed in since we dont have a written the other functions like this before (safer adding a function than changing things)
int AIMove(int BoardStatus[BoardColums][BoardRows])
{

    //the AI first wants to win, then block, then find the best move with prioritizing the center columns
    int WinMove = CheckWinMove(BoardStatus);
    if(WinMove != -1){
        return WinMove;
    }

    int BlockMove = CheckBlockMove(BoardStatus);
    if(BlockMove != -1){
        return BlockMove;
    }

    int BestMove = -1;

    int BestProb = -1000000;
    //in the center we have a better position
    int BestOrder[BoardColums] = {3, 4, 2, 5, 1, 6, 0};

    for(int k = 0; k < BoardColums; k++)
    {
        int Column = BestOrder[k];

        int empty_row = FindEmptyRow(BoardStatus, Column);
        if(empty_row != -1)
        {
            BoardStatus[Column][empty_row] = PlayerTwo;

            int prob_count = CheckBoard(BoardStatus);
            BoardStatus[Column][empty_row] = NoPlayer;

            if(prob_count > BestProb)
            {
                BestProb = prob_count;
                
                BestMove = Column;
            }

        }
    }
    return BestMove;
}


int FindEmptyRow(int BoardStatus[BoardColums][BoardRows], int column){
    for(int j = 0; j < BoardRows; j++){
        if(BoardStatus[column][j] == NoPlayer){
            return j;
        }
    }
    return -1;
}




int CheckWinMove(int BoardStatus[BoardColums][BoardRows])
{
    for(int i = 0; i < BoardColums; i++)
    {
        //we find the first empty row in column
        int empty_row = FindEmptyRow(BoardStatus, i);

        if(empty_row != -1){
            //now we simulate if it would be a win
            BoardStatus[i][empty_row] = PlayerTwo;
            int possible_win = CheckWinner();
            BoardStatus[i][empty_row] = NoPlayer;

            if(possible_win == PlayerTwoWin){
                return i;
            }
        }
    }

    return -1;
}

int CheckBlockMove(int BoardStatus[BoardColums][BoardRows])
{

    for(int i = 0; i < BoardColums; i++)
    {
        //we find the first empty row in column
        int empty_row = FindEmptyRow(BoardStatus, i);

        if(empty_row != -1){
            //now we simulate if it would be a win
            BoardStatus[i][empty_row] = PlayerOne;
            int possible_win = CheckWinner();
            BoardStatus[i][empty_row] = NoPlayer;

            if(possible_win == PlayerOneWin){
                return i;
            }
        }
    }
    return -1;
}




int CheckPlayer(int BoardStatus[BoardColums][BoardRows], int player){

    int prob = 0;

    //we want to count all good formations of player 
    //horizontal check
    for(uint8_t i = 0; i < BoardRows; i++)
    {
        uint8_t numbers_row = 0;
        for(uint8_t j = 0; j < BoardRows; j++)
        {
            if(BoardStatus[i][j] == player)
            {
                numbers_row++;
                if(numbers_row == 4)
                {
                    prob = prob + 100;
                }
                else if(numbers_row == 3)
                {
                    prob = prob + 10;
                }
                else if(numbers_row == 2)
                {
                    prob = prob + 1;
                }
            }
            else 
            {
                numbers_row = 0;
            }
        }
    }

    //vertical check
    for(uint8_t i = 0; i < BoardRows; i++)
    {
        uint8_t numbers_column = 0;
        for(uint8_t j = 0; j < BoardColums; j++)
        {
            if(BoardStatus[j][i] == player)
            {
                numbers_column++;
                if(numbers_column == 4)
                {
                    prob = prob + 100;
                }
                else if(numbers_column == 3)
                {
                    prob = prob + 10;
                }
                else if(numbers_column == 2)
                {
                    prob = prob + 1;
                }
            }
            else
            {
                numbers_column = 0;
            }
        }
    }

    //now split the diagonal 
    for(uint8_t i = 0; i < BoardRows - 3; i++)
    {
        for(uint8_t j = 0; j < BoardColums - 3; j++)
        {
            uint8_t numbers_first_diagonal = 0;
            for(uint8_t k = 0; k < 4; k++)
            {
                if(BoardStatus[j+k][i+k] == player)
                {
                    numbers_first_diagonal++;
                    if(numbers_first_diagonal == 4)
                    {
                        prob = prob + 100;
                    }
                    else if(numbers_first_diagonal == 3)
                    {
                        prob = prob + 10;
                    }
                    else if(numbers_first_diagonal == 2)
                    {
                        prob = prob + 1;
                    }
                }
                else
                {
                    numbers_first_diagonal = 0;
                }
            }
        }
    }

    for(uint8_t i = 0; i < BoardRows - 3; i++)
    {
        for(uint8_t j = 0; j < BoardColums - 3; j++)
        {
            uint8_t numbers_second_diagonal = 0;
            for(uint8_t k = 0; k < 4; k++)
            {
                if(BoardStatus[j+k][i-k] == player)
                {
                    numbers_second_diagonal++;
                    if(numbers_second_diagonal == 4)
                    {
                        prob = prob + 100;
                    }
                    if(numbers_second_diagonal == 3)
                    {
                        prob = prob + 10;
                    }
                    if(numbers_second_diagonal == 2)
                    {
                        prob = prob + 1;
                    }
                }
                else 
                {
                numbers_second_diagonal = 0;
                }
            }
        }
    }   

    return prob;
}


//we want too calculate the probability for the current board
int CheckBoard(int BoardStatus[BoardColums][BoardRows]){
    int prob = 0;

    prob = prob + CheckPlayer(BoardStatus, PlayerTwo);
    prob = prob - CheckPlayer(BoardStatus, PlayerOne);

    return prob;
}


int Probcount(int prob)
{
    if(prob == 4)
    {
        //this is a win so highest
        return 100;
    }
    else if(prob == 3)
    {
        return 10;
    }
    else if(prob == 2)
    {
        return 1;
    }
    return 0;
}
