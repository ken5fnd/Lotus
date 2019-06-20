#include "hardware/global.h"
#include "hardware/parameters.h"
#include "software/state.h"

void interrupt_TIM6() {
    real_state.ang_vel[0] =
        (float)(get_ang_vel(0) / 16.384) - offset_ang_vel[0];
    real_state.ang_vel[1] =
        (float)(get_ang_vel(1) / 16.384) - offset_ang_vel[1];
    real_state.ang_vel[2] =
        (float)(get_ang_vel(2) / 16.384) - offset_ang_vel[2];
}