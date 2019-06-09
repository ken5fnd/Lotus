void init_val() {
    /*ADC*/
    if(HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_Buffer, ADC_BUFFER_LENGTH) !=
       HAL_OK) {
        _Error_Handler(__FILE__, __LINE__);
    }
}