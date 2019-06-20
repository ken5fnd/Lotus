#ifndef __global_H
#define __global_H

#include "hardware/parameters.h"
#include <stdint.h>

/* */
extern volatile float offset_ang_vel[];

/*システム変数*/
extern uint16_t ADC_Buffer[ADC_BUFFER_NUM];
#endif