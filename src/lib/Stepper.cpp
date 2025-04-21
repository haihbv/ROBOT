#include "Stepper.h"
#include "float_math.h"

#define SET_STATE(STATE1, STATE2, STATE3, STATE4)   \
  { digitalWrite(pin1, STATE1);                       \
    digitalWrite(pin2, STATE2);                       \
    digitalWrite(pin3, STATE3);                       \
    digitalWrite(pin4, STATE4);   }


void Stepper_Class::Init(int Pin1, int Pin2, int Pin3, int Pin4)
{
  pin1 = Pin1;
  pin2 = Pin2;
  pin3 = Pin3;
  pin4 = Pin4;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  //Serial.println(String(pin1) + String(pin2) + String(pin3) + String(pin4));
}
void Stepper_Class::Run(float speed)
{

  speed = (speed == 0) ? 0 : (speed > 0 ? Map(speed, 0, 2000, 1e6, 1000) : -Map(speed, 0, -2000, 1e6, 1000));
  speed = Constrain(speed, -2000, 2000);

  if(speed  && ((micros() - cur_time) > (uint32_t)Abs(speed)))
  {
    switch(step)
    {
      case 0:
        SET_STATE(1, 0, 0, 0);
        break;
      case 1:
        SET_STATE(1, 1, 0, 0);
        break;
      case 2:
        SET_STATE(0, 1, 0, 0);
        break;
      case 3:
        SET_STATE(0, 1, 1, 0);
        break;
      case 4:
        SET_STATE(0, 0, 1, 0);
        break;
      case 5:
        SET_STATE(0, 0, 1, 1);
        break;
      case 6:
        SET_STATE(0, 0, 0, 1)
        break;
      case 7:
        SET_STATE(1, 0, 0, 1);
        break;
    }
    //Serial.println(String(pin1) + String(pin2) + String(pin3) + String(pin4));
    step += (speed > 0 ? 1 : -1) * OPTION;
    if(step > 7) step = 0;
    else if(step < 0) step = 7;
    cur_time = micros();

    if(step % 2 == 0) encoder += (speed > 0 ? 1 : -1);
  }
}
