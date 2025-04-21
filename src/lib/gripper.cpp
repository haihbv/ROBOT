#include "robot.h"

/* Mở */
void Gripper_Class::Open(void)
{
  Left_Servo.write(45);
  Right_Servo.write(135);
}

void Gripper_Class::Close(void)
{
  Left_Servo.write(135);
  Right_Servo.write(45);
}

void Gripper_Class::MoveTo(int16_t angle)
{
  angle += 45;
  Left_Servo.write(angle);
  Right_Servo.write(180 - angle);
}

