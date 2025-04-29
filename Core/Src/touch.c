#include "touch.h"

Touch_Side_Left_Right GetTouchedSide()
{
    STMPE811_TouchData touchState;
    touchState.orientation = STMPE811_Orientation_Portrait_1;

    if(STMPE811_ReadTouch(&touchState) == STMPE811_State_Pressed) 
    {
        if(touchState.x > 120)
        {
            return LEFT_TOUCH;
        }
        else
        {
            return RIGHT_TOUCH;
        }
    }
    return NONE_TOUCH_Vertical;
}

Touch_Side_Top_Button GetTouchedSideHorizontal(){
    STMPE811_TouchData touchState;
    touchState.orientation = STMPE811_Orientation_Portrait_1;

    if(STMPE811_ReadTouch(&touchState) == STMPE811_State_Pressed) 
    {
        if(touchState.y < 160)
        {
            return TOP_TOUCH;
        }
        else
        {
            return BUTTON_TOUCH;
        }
    }
    return NONE_TOUCH_Horizontal;
}
