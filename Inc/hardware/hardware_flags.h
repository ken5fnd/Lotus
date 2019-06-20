#ifndef __hardware_flags_H
#define __hardware_flags_H

#include <stdbool.h>

typedef struct {
    unsigned char enable_gyro : 3; //ジャイロ有効 MSBからx,y,z
    bool enable_IRLED : 1;         //壁センサLED有効
    bool enable_motor : 1;         //モーター有効
    bool enable_encorder : 1;      //エンコーダ有効
    unsigned char wall_control : 2; //壁制御フラグ 0:無効 1:横壁 2:斜め横 3:前壁
    bool deg_control : 1;           //角度制御フラグ
} __Hardware_Flag;
#endif