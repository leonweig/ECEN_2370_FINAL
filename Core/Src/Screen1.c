#include "Screen1.h"

extern uint16_t frameBuffer[LCD_PIXEL_WIDTH * LCD_PIXEL_HEIGHT];


bool RunScreen1(void){
    Display_Screen1();
    return Player_Selection();
}



void Display_Screen1(void){
    //first display the two colors on half of the screen
    //green is player one and red is player two
	for (uint16_t y = 0; y < LCD_PIXEL_HEIGHT; y++){
        for (uint16_t x = 0; x < LCD_PIXEL_WIDTH / 2; x++){
            frameBuffer[y * LCD_PIXEL_WIDTH + x] = LCD_COLOR_GREEN;
        }
        for (uint16_t x = LCD_PIXEL_WIDTH / 2; x < LCD_PIXEL_WIDTH; x++){
            frameBuffer[y * LCD_PIXEL_WIDTH + x] = LCD_COLOR_BLUE2;
        }
    }
    

    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);

    LCD_DisplayChar(30, 100, 'S');
    LCD_DisplayChar(45, 100, 'i');
    LCD_DisplayChar(60, 100, 'n');
    LCD_DisplayChar(75, 100, 'g');
    LCD_DisplayChar(90, 100, 'l');
    LCD_DisplayChar(105, 100, 'e');

    LCD_DisplayChar(30, 124, 'P');
    LCD_DisplayChar(45, 124, 'l');
    LCD_DisplayChar(60, 124, 'a');
    LCD_DisplayChar(75, 124, 'y');
    LCD_DisplayChar(90, 124, 'e');
    LCD_DisplayChar(105, 124, 'r');

    LCD_DisplayChar(130, 100, 'M');
    LCD_DisplayChar(145, 100, 'u');
    LCD_DisplayChar(160, 100, 'l');
    LCD_DisplayChar(175, 100, 't');
    LCD_DisplayChar(190, 100, 'i');

    LCD_DisplayChar(130, 124, 'P');
    LCD_DisplayChar(145, 124, 'l');
    LCD_DisplayChar(160, 124, 'a');
    LCD_DisplayChar(175, 124, 'y');
    LCD_DisplayChar(190, 124, 'e');
    LCD_DisplayChar(205, 124, 'r');



}

//we want to change the flag here after the user input the data
int Player_Selection(void){
    Touch_Side_Left_Right PlayerSelectionState = NONE_TOUCH_Vertical;

    while(PlayerSelectionState == NONE_TOUCH_Vertical)
    {
        PlayerSelectionState = GetTouchedSide();
    }

    if(PlayerSelectionState == LEFT_TOUCH){
        return TRUE;
    }
    if(PlayerSelectionState == RIGHT_TOUCH){
        return FALSE;
    }
    return FALSE;
}

