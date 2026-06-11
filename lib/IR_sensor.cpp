#include "IR_sensor.h"
#include "pins.h"

uint16_t sensorRaw[NUM_SENSORS];
uint16_t sensorMapped[NUM_SENSORS];
uint8_t  sensorBinary;
uint16_t sensorSum;

static uint16_t blackVal[NUM_SENSORS];
static uint16_t whiteVal[NUM_SENSORS];
static uint16_t threshold[NUM_SENSORS];
static bool     calibrated = false;

void IR_init() {
    pinMode(EN_SENSOR, OUTPUT);
}

void IR_enable() {
    digitalWrite(EN_SENSOR, HIGH);
}

void IR_disable() {
    digitalWrite(EN_SENSOR, LOW);
}

void IR_read() {
    sensorSum = 0;
    sensorBinary = 0;

    sensorRaw[0] = analogRead(SENSOR_0);
    sensorRaw[1] = analogRead(SENSOR_1);
    sensorRaw[2] = analogRead(SENSOR_2);
    sensorRaw[3] = analogRead(SENSOR_3);
    sensorRaw[4] = analogRead(SENSOR_4);
    sensorRaw[5] = analogRead(SENSOR_5);
    sensorRaw[6] = analogRead(SENSOR_6);
    sensorRaw[7] = analogRead(SENSOR_7);

    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        uint16_t val = sensorRaw[i];

        if (calibrated) {
            if (val < blackVal[i]) val = blackVal[i];
            if (val > whiteVal[i]) val = whiteVal[i];
            sensorMapped[i] = map(val, blackVal[i], whiteVal[i], 0, 1000);
        } else {
            sensorMapped[i] = val;
        }

        if (calibrated && val > threshold[i]) {
            sensorBinary |= 0x01;
        }
        sensorBinary <<= 1;

        sensorSum += sensorMapped[i];
    }
}

void IR_calibrate() {
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        if (blackVal[i] == 0) blackVal[i] = 1023;
        if (sensorRaw[i] < blackVal[i]) blackVal[i] = sensorRaw[i];
        if (sensorRaw[i] > whiteVal[i]) whiteVal[i] = sensorRaw[i];
        threshold[i] = (blackVal[i] + whiteVal[i]) / 2;
    }
    calibrated = true;
}

void IR_print() {
    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        Serial.print(sensorRaw[i]);
        Serial.write('\t');
    }
    Serial.println();
}
