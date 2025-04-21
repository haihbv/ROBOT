#ifndef __ULTRASONIC__
#define __ULTRASONIC__
#include <Arduino.h>
#include "lib/robot.h"
#define trig 12
#define echo 13
class  Ultrasonic_Class
{
  public:
  void Init(void);
  float Distance_cm(void);
  int checkCircle[4] = {0};
  void Check(void);
};
extern Ultrasonic_Class Ultrasonic;
#endif