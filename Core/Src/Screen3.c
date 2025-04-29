#include "Screen3.h"
extern uint16_t frameBuffer[LCD_PIXEL_WIDTH * LCD_PIXEL_HEIGHT];


void RunScreen3(int Playtime, int WinsPlayerOne, int WinsPlayerTwo){

    DisplayScreen3(Playtime, WinsPlayerOne, WinsPlayerTwo);
    Reset_Selection();
}


void Reset_Selection(void) {
    Touch_Side_Top_Button PlayerSelectionState;

    do {
        PlayerSelectionState = GetTouchedSideHorizontal();
    } while ((PlayerSelectionState == NONE_TOUCH_Horizontal) ||
             (PlayerSelectionState == TOP_TOUCH));

    if (PlayerSelectionState == BUTTON_TOUCH) {
        //reset
    }
}




void DisplayScreen3(int Playtime, int WinsPlayerOne, int WinsPlayerTwo){

    LCD_Clear(0, LCD_COLOR_BLACK);
    
    for (uint16_t y = 0; y < LCD_PIXEL_HEIGHT / 2; y++) {
        for (uint16_t x = 0; x < LCD_PIXEL_WIDTH; x++) {
            frameBuffer[y * LCD_PIXEL_WIDTH + x] = LCD_COLOR_GREEN;
        }
    }
    for (uint16_t y = LCD_PIXEL_HEIGHT / 2; y < LCD_PIXEL_HEIGHT; y++) {
        for (uint16_t x = 0; x < LCD_PIXEL_WIDTH; x++) {
            frameBuffer[y * LCD_PIXEL_WIDTH + x] = LCD_COLOR_GREY;
        }
    }

    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(LCD_COLOR_BLACK);

    // we have to shift the int over for ASCII value
    LCD_DisplayChar(12, 40, 'G');
    LCD_DisplayChar(47, 40, 'R');
    LCD_DisplayChar(82, 40, 'E');
    LCD_DisplayChar(117, 40, 'E');
    LCD_DisplayChar(152, 40, 'N');
    LCD_DisplayChar(187, 40, ':');
    LCD_DisplayChar(222, 40, WinsPlayerOne + '0');

    LCD_DisplayChar(40, 80, 'R');
    LCD_DisplayChar(80, 80, 'E');
    LCD_DisplayChar(120, 80, 'D');
    LCD_DisplayChar(160, 80, ':');
    LCD_DisplayChar(180, 80, WinsPlayerTwo + '0');


    int Playtime100 = (Playtime / 100) % 10;
    int Playtime10 = (Playtime / 10) % 10;
    int Playtime1 = Playtime % 10;


    LCD_DisplayChar(12, 120, 'T');
    LCD_DisplayChar(47, 120, 'I');
    LCD_DisplayChar(82, 120, 'M');
    LCD_DisplayChar(117, 120, 'E');
    LCD_DisplayChar(152, 120, ':');
    LCD_DisplayChar(202, 120, Playtime100 + '0');
    LCD_DisplayChar(212, 120, Playtime10 + '0');
    LCD_DisplayChar(222, 120, Playtime1 + '0');







    LCD_DisplayChar(40, 220, 'R');
    LCD_DisplayChar(80, 220, 'E');
    LCD_DisplayChar(120, 220, 'S');
    LCD_DisplayChar(160, 220, 'E');
    LCD_DisplayChar(200, 220, 'T');
    
    
}
