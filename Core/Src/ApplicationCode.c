/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"


/* Static variables */
static bool SinglePlayer;
static int WinsPlayerOne;
static int WinsPlayerTwo;
static uint32_t StartTime;
static uint32_t EndTime;






void applicationLevelGyroPower(void){
	GRYO_POWER();
}
void applicationLevelGyroInit(void){
	GYRO_INIT();
}


void applicationLevelButtonInterruptInit(void)
{
	ButtonInitInterrupt();
}


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_1;

	#endif // COMPILE_TOUCH_FUNCTIONS
}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}




void RunGame(void)
{
	ApplicationInit();
	
	while(TRUE)
	{
	int SingePlayerGame = RunScreen1();
	SinglePlayer = SingePlayerGame;
	StartTime = HAL_GetTick();
	int GameWinner = RunScreen2(SinglePlayer);
	EndTime = HAL_GetTick();

	if(GameWinner == PlayerOne)
	{
		WinsPlayerOne++;
	}
	if(GameWinner == PlayerTwo)
	{
		WinsPlayerTwo++;
	}

	int PlayTime = CalculatePlayTime();

	RunScreen3(PlayTime, WinsPlayerOne, WinsPlayerTwo);
	HAL_Delay(200);


	}
}

int CalculatePlayTime(void){
	//tick freq is 1khz
	int seconds = (EndTime-StartTime) / 1000;
	return seconds;
}





void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

//if i dont do this my EXTI handler is stuck
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0)
    {
        DeactivateTurn();

    }
}


#endif // COMPILE_TOUCH_FUNCTIONS

