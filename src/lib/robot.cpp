#include "robot.h"

Robot_Class Robot;

void Robot_Class::Init(void)
{
  Button[0].Init(BUTTON_PIN0); //A0
  Button[1].Init(BUTTON_PIN1); //A1
  Button[2].Init(BUTTON_PIN2); //A2
  Button[3].Init(BUTTON_PIN3); //A3

  Motion.Right_Stepper.Init(RIGHT_STEPPER_PIN1, RIGHT_STEPPER_PIN2, RIGHT_STEPPER_PIN3, RIGHT_STEPPER_PIN4);
  Motion.Left_Stepper.Init(LEFT_STEPPER_PIN1, LEFT_STEPPER_PIN2, LEFT_STEPPER_PIN3, LEFT_STEPPER_PIN4);

  Gripper.Left_Servo.attach(LEFT_SERVO_PIN);
  Gripper.Right_Servo.attach(RIGHT_SERVO_PIN);

  Ultrasonic.Init();

  
}