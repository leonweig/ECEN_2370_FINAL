#ifndef TOUCH_H_
#define TOUCH_H_

#include "LCD_Driver.h"
#include "stmpe811.h"

#define TRUE 1
#define FALSE 0

// want to return more than true or false so do it with enum (0,1,2,..) instead of normal bool
typedef enum{
	NONE_TOUCH_Vertical,
    LEFT_TOUCH,
    RIGHT_TOUCH,
} Touch_Side_Left_Right;

Touch_Side_Left_Right GetTouchedSide(void);


typedef enum{
	NONE_TOUCH_Horizontal,
    TOP_TOUCH,
    BUTTON_TOUCH,
} Touch_Side_Top_Button;

Touch_Side_Top_Button GetTouchedSideHorizontal(void);



#endif
