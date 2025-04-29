#include "Button_Driver.h"




bool ButtonState(void){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == Button_Pressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void ButtonInitInterrupt(void){
	GPIO_InitTypeDef GPIO_PINCONFIG;
	GPIO_PINCONFIG.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_PINCONFIG.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_PINCONFIG.Pull = GPIO_NOPULL;
	GPIO_PINCONFIG.Pin = GPIO_PIN_0;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &GPIO_PINCONFIG);
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);

	NVIC_EnableIRQ(EXTI0_IRQn);
}
