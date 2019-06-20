#include "hardware/global.h"
#include "hardware/parameters.h"
#include <stdint.h>

/* */
volatile float offset_ang_vel[3];//ジャイロオフセット 

/*システム変数*/
uint16_t ADC_Buffer[ADC_BUFFER_NUM];//ADCバッファ