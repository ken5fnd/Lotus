#include <stdint.h>

#ifndef __parameters_H
#define __parameters_H

#define ADC_BUFFER_NUM (5) // AD変換の個数

#define GYRO_XOUT_H (0x43 | 0x80)
#define GYRO_XOUT_L (0x44 | 0x80)
#define GYRO_YOUT_H (0x45 | 0x80)
#define GYRO_YOUT_L (0x46 | 0x80)
#define GYRO_ZOUT_H (0x47 | 0x80)
#define GYRO_ZOUT_L (0x48 | 0x80)

typedef struct {
    float weight;      //重量(g)
    float gear_rathio; //ギア比
    float moment;      //回転モーメント
    float motor_kt;    //モータートルク定数()
    float motor_ke;    //モーター電圧定数()
    uint8_t size;      //ハーフ(0)orクラシック(1)
} __Robot_Parameters;
extern __Robot_Parameters robot_parameters;

typedef struct {
    float kp; // Pゲイン
    float ki; // Iゲイン
    float kd; // Dゲイン
} __PID_Gain;

extern __PID_Gain gain_vel;
extern __PID_Gain gain_dis;
extern __PID_Gain gain_avel;
extern __PID_Gain gain_deg;
extern __PID_Gain gain_wall_S;
extern __PID_Gain gain_wall_S_d;
extern __PID_Gain gain_wall_F_R;
extern __PID_Gain gain_wall_F_L;

typedef struct {
    float vel;     //速度(mm/s)
    float lf;      //前距離(mm)
    float lb;      //後ろ距離(mm)
    float ang_acc; //角加速度(deg/ss)
    float radius;  //旋回半径(mm)
} __Turn_Parameter;

typedef struct {
    float max_vel;             //最高速度(mm/s)
    float max_acc;             //最大加速度(mm/ss)
    __Turn_Parameter turn_90;    // 90度ターン
    __Turn_Parameter turn_180;   // 180度ターン
    __Turn_Parameter turn_45_I;  //入口45度ターン
    __Turn_Parameter turn_135_I; //入口135度ターン
    __Turn_Parameter turn_45_O;  //出口45度ターン
    __Turn_Parameter turn_135_O; //出口135度ターン
    __Turn_Parameter turn_v90;   //斜め90度ターン
} __Attack_Parameters;

typedef struct{
    volatile float R;
    volatile float L;
} __Coeff_Ang_Vel;

extern __Coeff_Ang_Vel coeff_ang_vel;

#endif