#include "gpio.h"
#include "hardware/global.h"
#include "hardware/parameters.h"
#include "spi.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>

void gyro_rw(uint8_t *_Data_Input, uint8_t *_Data_Output) {
    volatile uint8_t dummy;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW; // CPOL = 0
    HAL_GPIO_WritePin(CS_GYRO_GPIO_Port, CS_GYRO_Pin, 0);
    for(uint8_t i = 0; i < 5; i++) {
        dummy++;
    }
    HAL_SPI_TransmitReceive(&hspi1, _Data_Input, _Data_Output, 2, 100);
    HAL_GPIO_WritePin(CS_GYRO_GPIO_Port, CS_GYRO_Pin, 1);
}

void init_gyro() {
    uint8_t Data_Input[] = {0x00, 0x00};
    uint8_t Data_Output[2];

	Data_Input[0] = (0x75 | 0x80); //レンジ設定(2000dpi)
    Data_Input[1] = 0x00;
    gyro_rw(Data_Input, Data_Output);
	//printf("%x\n",Data_Output[1]);
    HAL_Delay(10);

	Data_Input[0] = 0x6B;
	Data_Input[1] = 0x00; //Disable Sleep
	gyro_rw(Data_Input, Data_Output);
	HAL_Delay(10);

	Data_Input[0] = 0x6A;
	Data_Input[1] = 0x10; //Reset
	gyro_rw(Data_Input, Data_Output);
	HAL_Delay(10);

    Data_Input[0] = 0x1B; //レンジ設定(2000dpi)
    Data_Input[1] = 0x18;
    gyro_rw(Data_Input, Data_Output);
    HAL_Delay(10);
}

int16_t get_avel(uint8_t _axis) {
    uint8_t Data_Input[] = {0x00, 0x00};
    uint8_t Data_Output[2];
    int16_t gyro_data;

    switch(_axis) {
    case 0: // X
        Data_Input[0] = GYRO_XOUT_H;
        break;
    case 1: // Y
        Data_Input[0] = GYRO_YOUT_H;
        break;
    case 2: // Z
        Data_Input[0] = GYRO_ZOUT_H;
        break;
    }
    gyro_rw(Data_Input, Data_Output);
    //printf("%x", Data_Output[1]);
    gyro_data = Data_Output[1];
    gyro_data = gyro_data << 8;
    switch(_axis) {
    case 0: // X
        Data_Input[0] = GYRO_XOUT_L;
        break;
    case 1: // Y
        Data_Input[0] = GYRO_YOUT_L;
        break;
    case 2: // Z
        Data_Input[0] = GYRO_ZOUT_L;
        break;
    }

    gyro_rw(Data_Input, Data_Output);
	//printf("%x\n", Data_Output[1]);
    gyro_data |= (int16_t)Data_Output[1];

    return gyro_data;
}
int16_t gyro_get_reference() {
    uint8_t Data_Input[] = {0x00, 0x00};
    uint8_t Data_Output[2];
    int16_t gyro_data;
    int32_t sum_data = 0;
    Flag_gyroEn = 0;
    HAL_Delay(100);
    for(uint16_t i = 0; i < 1000; i++) {
        Data_Input[0] = GYRO_ZOUT_H;
        Data_Input[1] = 0x00;
        gyro_rw(Data_Input, Data_Output);
        gyro_data = Data_Output[1];
        gyro_data = gyro_data << 8;

        Data_Input[0] = GYRO_ZOUT_L;
        Data_Input[1] = 0x00;
        gyro_rw(Data_Input, Data_Output);
        gyro_data |= (int16_t)Data_Output[1];
        sum_data += (int32_t)gyro_data;
        HAL_Delay(1);
    }
    return (int16_t)(sum_data / 1000);
}