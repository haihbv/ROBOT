#ifndef _AUTO_CALIB_H_
#define _AUTO_CALIB_H_
#include <Arduino.h>
#define NUM_SENSORS 4

#define PIN_SENSOR_1 30
#define PIN_SENSOR_2 31
#define PIN_SENSOR_3 32
#define PIN_SENSOR_4 33

#define CALIB_BUTTON 18
class Auto_calib
{
private:
    uint8_t sensor_pins[NUM_SENSORS];
    bool waitForButton();

public:
    int16_t value_max[NUM_SENSORS];
    uint16_t value_min[NUM_SENSORS];
    uint16_t thres_hold[NUM_SENSORS];
    void Init_Sensor(int Pin1, int Pin2, int Pin3, int Pin4);
    void Auto_Calib();
};
#endif
