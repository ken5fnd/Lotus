#include "tim.h"
#include "gpio.h"
#include "hardware/interface.h"
#include "stm32f4xx_hal.h"
#include <math.h>
#include <stdlib.h>

void interface_LED(uint8_t _LED_R, uint8_t _LED_L)
{
    HAL_GPIO_WritePin(LED_R_R_GPIO_Port, LED_R_R_Pin, !(_LED_R & 0x01));      //LED_R_R
    HAL_GPIO_WritePin(LED_R_G_GPIO_Port, LED_R_G_Pin, !((_LED_R & 0x02) >> 1)); //LED_R_G
    HAL_GPIO_WritePin(LED_R_B_GPIO_Port, LED_R_B_Pin, !((_LED_R & 0x04) >> 2)); //LED_R_B

    HAL_GPIO_WritePin(LED_L_R_GPIO_Port, LED_L_R_Pin, !(_LED_L & 0x01));      //LED_L_R
    HAL_GPIO_WritePin(LED_L_G_GPIO_Port, LED_L_G_Pin, !((_LED_L & 0x02) >> 1)); //LED_R_G
    HAL_GPIO_WritePin(LED_L_B_GPIO_Port, LED_L_B_Pin, !((_LED_L & 0x04) >> 2)); //LED_L_B
}

void Speaker_ON()
{
    if (HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
}

void Speaker_Hz(unsigned short _Hz)
{
    __HAL_TIM_PRESCALER(&htim11, 1000000 / _Hz);
    __HAL_TIM_SetCompare(&htim11, TIM_CHANNEL_1, 23);
}

void Speaker_OFF()
{
    if (HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
}

void Speaker_Scale(uint16_t _Hz, uint8_t _time)
{
    Speaker_ON();
    Speaker_Hz(_Hz);
    HAL_Delay(_time);
    Speaker_OFF();
}