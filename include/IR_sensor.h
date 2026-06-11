#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <Arduino.h>

#define NUM_SENSORS 8

void IR_init();
void IR_read();
void IR_calibrate();
void IR_print();
void IR_enable();
void IR_disable();

extern uint16_t sensorRaw[NUM_SENSORS];
extern uint16_t sensorMapped[NUM_SENSORS];
extern uint8_t  sensorBinary;
extern uint16_t sensorSum;

#endif
