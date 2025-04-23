#ifndef __ULTRASONIC__
#define __ULTRASONIC__
#include "robot.h"

class  Ultrasonic_Class
{
  public:
  void Init(void);
  uint16_t GetDistance(void);
  int Look_Around[4] = {0};
  void Check(void);
};
extern Ultrasonic_Class Ultrasonic;
#endif