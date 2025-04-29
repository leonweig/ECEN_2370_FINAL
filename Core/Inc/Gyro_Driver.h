#ifndef GYRO_DRIVER_H_
#define GYRO_DRIVER_H_
#include <stm32f4xx_hal.h>
#include <stdio.h>
#include "Screen2.h"


#define CS_PORT_GYRO GPIOC
#define CS_PIN_GYRO GPIO_PIN_1

//p.28 on i3g.. document
#define GYRO_WHO_AM_I 0x0F
#define GYRO_CTRL_REG1 0x20
#define GYRO_CTRL_REG2 0x21
#define GYRO_CTRL_REG3 0x22
#define GYRO_CTRL_REG4 0x23
#define GYRO_CTRL_REG5 0x24
#define REFERENCE_DATACAPTURE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_THS_XH 0x32
#define INT1_THS_XL 0x33
#define INT1_THS_YH 0x34
#define INT1_THS_YL 0x35
#define INT1_THS_ZH 0x36
#define INT1_THS_ZL 0x37
#define INT1_DURATION 0x38

//for ctrl_reg1
#define CTRL_REG1_PD 3
#define CTRL_REG1_ZEN 2
#define CTRL_REG1_YEN 1
#define CTRL_REG1_XEN 0

#define READ_REG_READ 7

#define DATA_SHIFT_8 8

#define TIMEOUT 25000

#define CTRL_REG5_BOOT 7
#define CTRL_REG5_FIFO_EN 6
#define CTRL_REG5_HPen 4
#define CTRL_REG5_INT1_Sel1 3
#define CTRL_REG5_INT1_Sel2 2
#define CTRL_REG5_Out_Sel1 1
#define CTRL_REG5_Out_Sel0 0


#define READ_REG_NUM_0 0









//GPIOF 7

#define PIN7 7


//p.8 on i3g.. document
#define Vdd_IO 1
#define SCL_SPC 2
#define SDA_SDI_SDO 3
#define SDO_SA0 4
#define CS 5
#define DRDY_INT2 6
#define INT1 7
#define GND 13
#define PLLFILT 14
#define Vdd 16



void GYRO_INIT(void);
void GYRO_DEVICEID_PRINT(void);
void GRYO_POWER(void);
void GYRO_TEMPERATURE_PRINT(void);
void GYRO_REGISTER_CONFIG(void);
uint8_t GYRO_REGISTER_READ(uint16_t Register);
void GYRO_HAL_SPI_CHECK(HAL_StatusTypeDef Status);
void GYRO_MANUAL_SLAVE_ENABLE(void);
void GYRO_MANUAL_SLAVE_DISABLE(void);

typedef enum{
	NONE_TURN,
    LEFT_TURN,
    RIGHT_TURN,
} Turn_Side_Left_Right;

Turn_Side_Left_Right GetTurnedSide(void);


//gyro has an offset of -419 (testing data)
#define GyroOffsetY -425

void DeactivateTurnFlag(void);

#endif
