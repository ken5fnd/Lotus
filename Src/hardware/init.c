#include "adc.h"
#include "tim.h"
#include "stm32f4xx_hal_def.h"
#include "hardware/global.h"
#include "hardware/parameters.h"
#include "hardware/sensors.h"

void init_val() {
   
}

void start_peripherals(){
    /*Gyro*/
    init_gyro();
    /*ADC*/
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_Buffer, ADC_BUFFER_NUM);
    /*TIM*/
    HAL_TIM_Base_Start_IT(&htim6);
}