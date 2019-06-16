#ifndef __global_H
#define __global_H

#include "hardware/parameters.h"
#include <stdint.h>

typedef struct { //センサー生値
    volatile uint16_t LF, LS, RS, RF;
} __IRSensors_raw;
typedef struct { //センサー値
    volatile float LF, LS, RS, RF;
} __IRSensors;

typedef struct {          //車体状態
    volatile float dis;   //距離
    volatile float vel_R; //右タイヤ速度
    volatile float vel_L; //左タイヤ速度
    volatile float vel;   //重心速度

    volatile float acc;
    volatile float jerk;
    volatile float ang_jerk;

    volatile float deg;     //角度
    volatile float ang_vel; //角速度
    volatile float ang_acc; //角加速度

    volatile float enc_deg_R; //エンコーダー角度
    volatile float enc_deg_L;

} __Mouse_State;

/*マウス状態変数*/
extern __IRSensors_raw IR_Sen_raw;
extern __IRSensors IR_Sen;

extern __Mouse_State idealState;
extern __Mouse_State realState;
extern const __Mouse_State RESETState;
extern volatile float V_Batt;

/*フラグ系*/
extern uint8_t Flag_gyroEn;

/*システム変数*/
extern uint16_t ADC_Buffer[ADC_BUFFER_NUM];
#endif