#ifndef __sensors_H
#define __sensors_H

void gyro_rw(uint8_t *_Data_Input, uint8_t *_Data_Output);
void init_gyro();
int16_t get_avel(uint8_t _axis);
int16_t gyro_get_reference();

#endif