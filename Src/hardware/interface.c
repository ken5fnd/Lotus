#include "hardware/interface.h"
#include "gpio.h"
#include "hardware/interface.h"
#include "software/state.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

void interface_LED(uint8_t _LED_L, uint8_t _LED_R) {
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
        Speaker_Hz(2093);
        for(i = 0; i < 2; i++) {
            Speaker_ON();
            HAL_Delay(100);
            Speaker_OFF();
            HAL_Delay(100);
        }
        break;
    case OK3:
        Speaker_Hz(2093);
        for(i = 0; i < 3; i++) {
            Speaker_ON();
            HAL_Delay(70);
            Speaker_OFF();
            HAL_Delay(70);
        }
        break;
    case NG:
        Speaker_Hz(523);
        for(i = 0; i < 3; i++) {
            Speaker_ON();
            HAL_Delay(70);
            Speaker_OFF();
            HAL_Delay(70);
        }
        break;
    case SELECT1:
        Speaker_ON();
        Speaker_Hz(1047);
        HAL_Delay(70);
        Speaker_OFF();
        break;
    case SELECT2:
        Speaker_ON();
        Speaker_Hz(988);
        HAL_Delay(70);
        Speaker_OFF();
        break;
    }
    HAL_Delay(50);
}

uint8_t mode_inputcommand() {
    volatile uint8_t dummy;
    while(1) {
        if(fabs(real_state.ang_vel[0]) > 800.0) {
            while(fabs(real_state.ang_vel[0]) > 600.0) {
                dummy++;
            }
            return 0; //決定
        } else if(real_state.ang_vel[1] > 1100.0) {
            while(fabs(real_state.ang_vel[1]) > 800.0) {
                dummy++;
            }
            return 1; //++
        } else if(real_state.ang_vel[1] < -1100.0) {
            while(fabs(real_state.ang_vel[1]) > 800.0) {
                dummy++;
            }
            return 2; //--
        } else if(fabs(real_state.ang_vel[2]) > 900.0) {
            while(fabs(real_state.ang_vel[2]) > 700.0) {
                dummy++;
            }
            return 3; //キャンセル
        }
    }
}

uint8_t mode_select() {
    uint8_t mode_buff = 0x00;
    uint8_t mode_return = 0x00;
    uint8_t color_buff;
    uint8_t color_L = OFF;
    uint8_t color_R = OFF;
    bool seq = false;
    while(1) {
        switch(mode_buff & 0x03) {
        case 0:
            color_buff = GREEN;
            break;
        case 1:
            color_buff = RED;
            break;
        case 2:
            color_buff = BLUE;
            break;
        case 3:
            color_buff = YELLOW;
            break;
        }
        if(seq) {
            color_R = color_buff;
        } else {
            color_L = color_buff;
        }
        color_buff = OFF;
        interface_LED(color_L, color_R);
        switch(mode_inputcommand()) {
        case 0: //決定
            if(seq == false) {
                mode_SE(OK2);
                seq = true;
                mode_return = mode_buff & 0x03;
                mode_buff = 0x00;
            } else {
                mode_SE(OK3);
                mode_return += (mode_buff & 0x03) << 2;
                return mode_return;
            }
            break;
        case 1: //++
            mode_SE(SELECT1);
            mode_buff++;
            break;
        case 2: //--
            mode_SE(SELECT2);
            mode_buff--;
            break;
        case 3: //キャンセル
            if(seq == true) {
                interface_LED(OFF, OFF);
                mode_SE(NG);
                color_L = OFF;
                color_R = OFF;
                mode_buff = 0x00;
                mode_return = 0x00;
                seq = false;
            }
            break;
        }
    }
}
