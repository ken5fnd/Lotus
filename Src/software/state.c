#include "software/state.h"

/*車体状態*/
__State ideal_state;      //理想状態
__State real_state;       //実際の状態
const __State RESETState; //リセット用

__IRSensors_Raw IR_sen_raw; //センサー生値
__IRSensors IR_sen;         //センサー値

volatile float V_Batt; //電源電圧

__Enc_Deg enc_deg; //エンコーダ角度
