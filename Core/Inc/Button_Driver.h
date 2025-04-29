#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_


#include <stdbool.h>
#include <stm32f4xx_hal.h>


//pin A0 for the button


#define Button_Port 0
#define Button_Pin 0
#define Button_Pressed 1
#define Button_Released 0


void ButtonInit(void);
bool ButtonState(void);

void ButtonInitInterrupt(void);


#endif

