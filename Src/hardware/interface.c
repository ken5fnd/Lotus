#include "hardware/interface.h"
#include "gpio.h"
#include "hardware/interface.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include <math.h>
#include <stdlib.h>

void interface_LED(uint8_t _LED_R, uint8_t _LED_L) {
    HAL_GPIO_WritePin(LED_R_R_GPIO_Port, LED_R_R_Pin,
                      !(_LED_R & 0x01)); // LED_R_R
    HAL_GPIO_WritePin(LED_R_G_GPIO_Port, LED_R_G_Pin,
                      !((_LED_R & 0x02) >> 1)); // LED_R_G
    HAL_GPIO_WritePin(LED_R_B_GPIO_Port, LED_R_B_Pin,
                      !((_LED_R & 0x04) >> 2)); // LED_R_B

    HAL_GPIO_WritePin(LED_L_R_GPIO_Port, LED_L_R_Pin,
                      !(_LED_L & 0x01)); // LED_L_R
    HAL_GPIO_WritePin(LED_L_G_GPIO_Port, LED_L_G_Pin,
                      !((_LED_L & 0x02) >> 1)); // LED_R_G
    HAL_GPIO_WritePin(LED_L_B_GPIO_Port, LED_L_B_Pin,
                      !((_LED_L & 0x04) >> 2)); // LED_L_B
}

void Speaker_ON() {
    if(HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
}

void Speaker_Hz(unsigned short _Hz) {
    __HAL_TIM_PRESCALER(&htim11, 1000000 / _Hz);
    __HAL_TIM_SetCompare(&htim11, TIM_CHANNEL_1, 23);
}

void Speaker_OFF() {
    if(HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
}

void Speaker_Scale(uint16_t _Hz, uint8_t _time) {
    Speaker_ON();
    Speaker_Hz(_Hz);
    HAL_Delay(_time);
    Speaker_OFF();
}

void wakeup() {
    Speaker_ON();
    Speaker_Hz(1047);
    HAL_Delay(100);
    Speaker_Hz(2093);
    HAL_Delay(500);
    Speaker_OFF();
    interface_LED(GREEN, GREEN);
    HAL_Delay(500);
    interface_LED(OFF, OFF);
    HAL_Delay(50);
    interface_LED(GREEN, GREEN);
    HAL_Delay(50);
    interface_LED(OFF, OFF);
    HAL_Delay(50);
    interface_LED(GREEN, GREEN);
    HAL_Delay(500);
    interface_LED(OFF, OFF);
    HAL_Delay(500);
}

void error_battlowvoltage() {
    uint8_t i;
    Speaker_Hz(523);
    for(i = 0; i < 3; i++) {
        interface_LED(RED, RED);
        Speaker_ON();
        HAL_Delay(100);
        Speaker_OFF();
        interface_LED(OFF, OFF);
        HAL_Delay(100);
    }
}

void mode_SE(enum SE_TYPE _SE) {
    uint8_t i;
    switch(_SE) {
    case OK1:
        Speaker_ON();
        Speaker_Hz(587);
        HAL_Delay(70);
        Speaker_Hz(2093);
        HAL_Delay(70);
        Speaker_OFF();
        break;
    case OK2:
        Speaker_Hz(1047);
        for(i = 0; i < 2; i++) {
            Speaker_ON();
            HAL_Delay(100);
            Speaker_OFF();
            HAL_Delay(100);
        }
        break;
    case NG:
        Speaker_Hz(523);
        for(i = 0; i < 2; i++) {
            Speaker_ON();
            HAL_Delay(70);
            Speaker_OFF();
            HAL_Delay(70);
        }
        break;
    case SELECT:
        Speaker_ON();
        Speaker_Hz(988);
        HAL_Delay(70);
        Speaker_OFF();
        break;
    }
}
