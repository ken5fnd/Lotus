#include "hardware/global.h"
#include "hardware/parameters.h"
#include <stdint.h>

/*マウス状態変数*/
__IRSensors_raw IR_Sen_raw; //センサー生値
__IRSensors IR_Sen;         //センサー値

__Mouse_State idealState; //理想状態
__Mouse_State realState; //現実状態
const __Mouse_State RESETState; //リセット用
volatile float V_Batt;//電源電圧

/*フラグ系*/
uint8_t Flag_gyroEn;//ジャイロ有効or無効

/*システム変数*/
uint16_t ADC_Buffer[ADC_BUFFER_NUM];