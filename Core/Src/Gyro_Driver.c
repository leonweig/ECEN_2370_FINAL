#include "Gyro_Driver.h"

static HAL_StatusTypeDef gyroHALStatus;
static SPI_HandleTypeDef hspi5;

void GYRO_INIT(void){

	//GPIO F pin 7 from the circuit schematic
	// set equal to zero (told by TA) otherwise it is used uninitilized
	GPIO_InitTypeDef GPIO_PINCONFIG_GYRO_SCK_MISO_MOSI;
	GPIO_PINCONFIG_GYRO_SCK_MISO_MOSI.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_PINCONFIG_GYRO_SCK_MISO_MOSI.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_PINCONFIG_GYRO_SCK_MISO_MOSI.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_PINCONFIG_GYRO_SCK_MISO_MOSI.Pull = GPIO_NOPULL;
	GPIO_PINCONFIG_GYRO_SCK_MISO_MOSI.Alternate = GPIO_AF5_SPI5;
	__HAL_RCC_GPIOF_CLK_ENABLE();
	HAL_GPIO_Init(GPIOF, &GPIO_PINCONFIG_GYRO_SCK_MISO_MOSI);



	GPIO_InitTypeDef GPIO_PINCONFIG_GYRO_NCS_MEMS_SPI;
	GPIO_PINCONFIG_GYRO_NCS_MEMS_SPI.Pin = GPIO_PIN_1;
	GPIO_PINCONFIG_GYRO_NCS_MEMS_SPI.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_PINCONFIG_GYRO_NCS_MEMS_SPI.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_PINCONFIG_GYRO_NCS_MEMS_SPI.Pull = GPIO_NOPULL;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(GPIOC, &GPIO_PINCONFIG_GYRO_NCS_MEMS_SPI);





	__HAL_RCC_SPI5_CLK_ENABLE();
	//this is the code from main.c (not allowed to call the function but the TA said to use this)
	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi5.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi5.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi5.Init.NSS = SPI_NSS_SOFT;
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	gyroHALStatus = HAL_SPI_Init(&hspi5);

	GYRO_REGISTER_CONFIG();


}

void GYRO_DEVICEID_PRINT(){
	uint8_t DEVICEID = GYRO_REGISTER_READ(GYRO_WHO_AM_I);

	printf("The Device ID is: 0x%02X\n ", DEVICEID);

}
void GRYO_POWER(void){
	//temp is my shifted enable for PD to be enabled
		uint16_t tempReg1 = ((1 << CTRL_REG1_PD) | (1 << CTRL_REG1_ZEN) | (1 << CTRL_REG1_YEN) | (1 << CTRL_REG1_XEN)) << 8;
		uint16_t package_to_write_Reg1 = (0 << READ_REG_READ) | GYRO_CTRL_REG1;
		uint16_t package_to_write_Reg1_shift = tempReg1 | package_to_write_Reg1;

		GYRO_MANUAL_SLAVE_ENABLE();

		//this is from the lecture slide
		while(HAL_GPIO_ReadPin(CS_PORT_GYRO, CS_PIN_GYRO) != GPIO_PIN_RESET);

		//from lectureslide
		gyroHALStatus = HAL_SPI_Transmit(&hspi5, (uint8_t*) &package_to_write_Reg1_shift, 2, TIMEOUT);

		GYRO_HAL_SPI_CHECK(gyroHALStatus);
		GYRO_MANUAL_SLAVE_DISABLE();
}



void GYRO_TEMPERATURE_PRINT(){
	uint8_t Temperature = GYRO_REGISTER_READ(OUT_TEMP);
	printf("The Temperature is: %u\n", Temperature);
	return;
}



void GYRO_REGISTER_CONFIG(void){



	//now again for Reg 5
	//10.b.2 comes here :)
	uint8_t tempReg5 = ((1 << CTRL_REG5_BOOT) | (1 << CTRL_REG5_FIFO_EN));
	uint16_t temp2Reg5 = (GYRO_CTRL_REG5 << 8);
	uint16_t package_to_write_Reg5 = (temp2Reg5 | tempReg5);

	GYRO_MANUAL_SLAVE_ENABLE();
	//this is from the lecture slide
	while(HAL_GPIO_ReadPin(CS_PORT_GYRO, CS_PIN_GYRO) != GPIO_PIN_RESET);


	gyroHALStatus = HAL_SPI_Transmit(&hspi5, (uint8_t*) &package_to_write_Reg5, 1, TIMEOUT);
	GYRO_HAL_SPI_CHECK(gyroHALStatus);
	GYRO_MANUAL_SLAVE_DISABLE();

}



uint8_t GYRO_REGISTER_READ(uint16_t Register_num){
	uint8_t CommandToSend = (1 << READ_REG_READ) | Register_num;

	uint16_t ReceivedData = 0x00;


	GYRO_MANUAL_SLAVE_ENABLE();
	//called  CS_PORT_GYRO, CS_PIN_GYRO from lecture
	while(HAL_GPIO_ReadPin(CS_PORT_GYRO, CS_PIN_GYRO) != GPIO_PIN_RESET);

	gyroHALStatus = HAL_SPI_TransmitReceive(&hspi5, &CommandToSend, (uint8_t*) &ReceivedData, 2, TIMEOUT);

	GYRO_HAL_SPI_CHECK(gyroHALStatus);

	uint8_t DataReturned = (0xFF00 & ReceivedData) >> 8;
	GYRO_MANUAL_SLAVE_DISABLE();
	return DataReturned;
}



void GYRO_HAL_SPI_CHECK(HAL_StatusTypeDef Status){

	if(gyroHALStatus != HAL_OK)
		{
			for(;;);
		}
}
void GYRO_MANUAL_SLAVE_ENABLE(void){
	//pull this down to 0
	//this function was given by TA
	HAL_GPIO_WritePin(CS_PORT_GYRO, CS_PIN_GYRO, DISABLE); //disable and enable are flipped

}
void GYRO_MANUAL_SLAVE_DISABLE(void){
	HAL_GPIO_WritePin(CS_PORT_GYRO, CS_PIN_GYRO, ENABLE); //disable and enable are flipped
}




//we have to read the y-axis of the gyro p.20 on datasheet for reference
//we have to read both registers (high and low) and combine them (output is 2s compliment data)


float TurnValueAngle;

float TurnDistance = 0;

uint32_t TimeOne = 0;

uint32_t TimeTwo = 0;

uint32_t LastTurn;

int TurnFlag;




//This function detects the acceleration and integrates it over time to get the angle, The angle resets after a certain time OR inbetween a certain angle.
Turn_Side_Left_Right GetTurnedSide(){

	if(TimeOne == 0)
	{
		TimeOne = HAL_GetTick();
	}



	while(1)
	{
		// need this for breaking out of double loop in 2 files
		if(GetTurnActive() == FALSE)
		{
			break;
		}

		TimeTwo = HAL_GetTick();
		//float since we need negatives and small numbers
		float Integration =  (((float)TimeTwo - (float)TimeOne) / (float)1000);
		TimeOne = TimeTwo;



        uint8_t GyroValueLowY = GYRO_REGISTER_READ(OUT_Y_L);
        uint8_t GyroValueHighY = GYRO_REGISTER_READ(OUT_Y_H);

        uint16_t GyroValueHighYShifted = GyroValueHighY << 8;

        //signed int for roation data (positive rotation or negative)
        int16_t ValueYCombined = (int16_t)(GyroValueHighYShifted | GyroValueLowY);

		//245 dps from CTRL_REG4 p.10 for values
        TurnValueAngle = ValueYCombined * (float)0.00875;

        TurnDistance = TurnDistance + (TurnValueAngle * Integration);


        if(TurnFlag == 0)
        {
        	//+- 20 degree for minimu angle
        	if(TurnDistance > 20)
        	{
        		TurnFlag = 1;
        		LastTurn = HAL_GetTick();
        		return RIGHT_TURN;
        	}
        	if(TurnDistance < -20)
        	{
        		LastTurn = HAL_GetTick();
        		TurnFlag = 1;
        		return LEFT_TURN;
        	}
        }
        //this onyl happens when we are between -3 and 3 so we never have a drift of the gyro since it is not working properly and adds random values
        if((TurnFlag == 0) && (TurnValueAngle < 3) && (TurnValueAngle > -3))
        {
        	TurnDistance = 0;
        }
        // we reset when time is too hand we are between -5 and 5
        if((TurnFlag == 1) || ((TimeTwo - LastTurn) > 2000))
        {

        	//if we are between -5 and 5 we reset (values come from testing)
        	if(((TurnDistance > -5) && (TurnDistance < 5)) || ((TimeTwo - LastTurn) > 2000))
        	{
        		LastTurn = HAL_GetTick();
        		TurnFlag = 0;
        		TurnDistance = 0;
        	}
        }
    }
//to not get a warning but will never happen
	return NONE_TURN;
}

//called when coin is dropped by interrupt
void DeactivateTurnFlag(void)
{
	TurnFlag = 0;
}
