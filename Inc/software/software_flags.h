#ifndef __software_flags_H
#define __software_flags_H

#include <stdbool.h>

typedef struct {
    bool failsafe : 1;       //フェイルセーフ
    bool capture_log : 1;    //ログ取得フラグ
    bool diagnoral_mode : 1; //機体が斜め状態か
    bool explore_done : 1;   //探索終了フラグ
} __software_flag;
#endif