/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>


#include <stdio.h>

#include "Button_Driver.h"
#include "Screen1.h"
#include "Screen2.h"
#include "Screen3.h"
#include "Gyro_Driver.h"


#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_


void applicationLevelGyroPower(void);
void applicationLevelGyroInit(void);



int CalculatePlayTime(void);

void applicationLevelButtonInterruptInit(void);

void ApplicationInit(void);
void LCD_Visual_Demo(void);
void RunGame(void);


#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_Touch_Polling_Demo(void);
#endif 

#endif 
