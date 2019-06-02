#include <stdint.h>

#ifndef __parameters_H
#define __parameters_H

typedef struct robot_parameter_{
    float weight;//重量(g)
    float gear_rathio;//ギア比
    float moment;//回転モーメント
    float motor_kt; //モータートルク定数()
    float motor_ke; //モーター電圧定数()
    uint8_t size; //ハーフ(0)orクラシック(1)
}robot_parameters;

typedef struct pidgain_{
    float kp;//Pゲイン
    float ki;//Iゲイン
    float kd;//Dゲイン
}pidgain;

typedef struct turn_parameter_{
    float vel;//速度(mm/s)
    float lf;//前距離(mm)
    float lb;//後ろ距離(mm)
    float ang_acc;//角加速度(deg/ss)
    float radius;//旋回半径(mm)
}turn_parameter;

typedef struct attack_parameters_{
    float max_vel;//最高速度(mm/s)
    float max_acc;//最大加速度(mm/ss)
    turn_parameter turn_90;//90度ターン
    turn_parameter turn_180;//180度ターン
    turn_parameter turn_45_I;//入口45度ターン
    turn_parameter turn_135_I;//入口135度ターン
    turn_parameter turn_45_O;//出口45度ターン
    turn_parameter turn_135_O;//出口135度ターン
    turn_parameter turn_v90;//斜め90度ターン
}attack_parameters;

#endif