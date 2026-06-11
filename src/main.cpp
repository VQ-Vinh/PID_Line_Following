#include <Arduino.h>
#include "pins.h"
#include "IR_sensor.h"
#include "PID.h"
#include "motor_control.h"
#include "case_handling.h"

void setup() {
    Serial.begin(9600);
    IR_init();
    IR_enable();
}

void loop() {
    IR_read();
    IR_print();
    delay(200);
}
