#ifndef __STEPPER__
#define __STEPPER__
#include <Arduino.h>

#define STEPPER_HALFSTEP    1
#define STEPPER_FULLSTEP    2

#define OPTION  STEPPER_HALFSTEP

class Stepper_Class
{
  private:
    int pin1;
    int pin2;
    int pin3;
    int pin4;
    int8_t step = 0;
    uint32_t cur_time = 0;
  public:
    int encoder = 0;

    void Init(int Pin1, int Pin2, int Pin3, int Pin4);
    
    void Run(float speed);
};

#endif