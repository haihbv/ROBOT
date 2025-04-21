#include "auto_calib.h"

void Auto_calib::Init_Sensor(int Pin1, int Pin2, int Pin3, int Pin4) {
    sensor_pins[0] = Pin1;
    sensor_pins[1] = Pin2;
    sensor_pins[2] = Pin3;
    sensor_pins[3] = Pin4;
    for (int i = 0; i < NUM_SENSORS; i++){
         pinMode(sensor_pins[i], INPUT);
    }
    pinMode(CALIB_BUTTON, INPUT_PULLUP);
}

bool Auto_calib::waitForButton() {
    static bool lastState = HIGH;
    static unsigned long lastDebounce = 0;
    if (digitalRead(CALIB_BUTTON) == LOW && lastState == HIGH) {
        lastDebounce = millis();
        lastState = LOW;
    }
    if (digitalRead(CALIB_BUTTON) == HIGH && lastState == LOW) {
        lastState = HIGH;
        if (millis() - lastDebounce > 50) return true;
    }
    return false;
}

void Auto_calib::Auto_Calib() {
    while (!waitForButton());
    for (int i = 0; i < NUM_SENSORS; i++) value_min[i] = 1023;

    unsigned long startTime = millis(); 
    while (millis() - startTime < 3000) {   // quét vạch đen 
        for (int i = 0; i < NUM_SENSORS; i++) {
            uint16_t val = analogRead(sensor_pins[i]);
            if (val < value_min[i]) value_min[i] = val;
        }
    }

    while (!waitForButton());
    for (int i = 0; i < NUM_SENSORS; i++) value_max[i] = 0;

    startTime = millis();
    while (millis() - startTime < 3000) {  
        for (int i = 0; i < NUM_SENSORS; i++) { // quét nền trắng 
            int val = analogRead(sensor_pins[i]);
            if (val > value_max[i]) value_max[i] = val;
        }
    }
    for (int i = 0; i < NUM_SENSORS; i++) { // tính thresshold 
        thres_hold[i] = (value_min[i] + value_max[i]) / 2;
    }
}
