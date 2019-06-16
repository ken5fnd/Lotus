#ifndef __interface_H
#define __interface_H

#include <stdint.h>

enum LED_COLOR {
    OFF = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 4,
    YELLOW = 3,  // R+G
    CYAN = 6,    // B+G
    MAGENTA = 5, // R+B
    WHITE = 7
};

enum SE_TYPE { OK1, OK2, NG, SELECT };

void interface_LED(uint8_t _LED_R, uint8_t _LED_L);
void Speaker_ON();
void Speaker_Hz(unsigned short _Hz);
void Speaker_OFF();
void wakeup();
void error_battlowvoltage();
void mode_SE(enum SE_TYPE _SE);
#endif