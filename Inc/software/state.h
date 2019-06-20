#ifndef __state_H
#define __state_H

#include <stdint.h>

/*車体状態*/
typedef struct {
    volatile float dis;   //距離
    volatile float vel_R; //右タイヤ速度
    volatile float vel_L; //左タイヤ速度
    volatile float vel;   //重心速度

    volatile float acc;  //加速度
    volatile float jerk; //速度ジャーク

    volatile float deg[3];      //角度
    volatile float ang_vel[3];  //角速度
    volatile float ang_acc[3];  //角加速度
    volatile float ang_jerk[3]; //角度ジャーク
} __State;

extern __State ideal_state;
extern __State real_state;

/*センサー値*/
typedef struct { //センサー生値
    volatile uint16_t LF, LS, RS, RF;
} __IRSensors_Raw;

typedef struct { //センサー値
    volatile float LF, LS, RS, RF;
} __IRSensors;

extern __IRSensors_Raw IR_sen_raw;
extern __IRSensors IR_sen;

extern volatile float V_Batt; //電源電圧

/*エンコーダ角度*/
typedef struct {
    volatile float R;
    volatile float L;
} __Enc_Deg;

extern __Enc_Deg enc_deg;

#endif