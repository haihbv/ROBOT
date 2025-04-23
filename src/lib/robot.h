#ifndef __ROBOT__
#define __ROBOT__
#include <Arduino.h>
#include "Stepper.h"
#include "Servo.h"
#include "float_math.h"

#define BUTTON_PIN0             A0
#define BUTTON_PIN1             A1
#define BUTTON_PIN2             A2
#define BUTTON_PIN3             A3

#define   RIGHT_STEPPER_PIN1    2
#define   RIGHT_STEPPER_PIN2    3
#define   RIGHT_STEPPER_PIN3    4
#define   RIGHT_STEPPER_PIN4    5

#define   LEFT_STEPPER_PIN1     6
#define   LEFT_STEPPER_PIN2     7
#define   LEFT_STEPPER_PIN3     8
#define   LEFT_STEPPER_PIN4     9

#define   LEFT_SERVO_PIN        10
#define   RIGHT_SERVO_PIN       11

#define TRIG 12
#define ECHO 13 

#define speed 2000
class Button_Class
{
  private:
    uint8_t pin;
    uint8_t pre_press_status;
    uint8_t pre_hold_status;
    uint32_t pre_time;

  public:
    void Init(uint8_t pin);
    uint8_t Read(void);
    uint8_t IsPressed(void);
    uint8_t Hold(uint16_t hold_time);
};

class IR_Class

{
  private:
    uint8_t pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8;    
    uint8_t data = 0;

  public:
    void Init(uint8_t L3_pin, uint8_t L2_pin, uint8_t L1_pin, uint8_t L0_pin, uint8_t R0_pin, uint8_t R1_pin, uint8_t R2_pin, uint8_t R3_pin);

    uint8_t ReadDigitalValue(int16_t threshold);
    uint16_t ReadAnalogValue(uint8_t index);
};

class Motion_Class
{
  private:
    float left_speed = 0;
    float right_speed = 0;

  public:
    Stepper_Class  Right_Stepper;
    Stepper_Class  Left_Stepper;
  
    void RunLR(float vL, float vR);
    void Stop(void);
    void WaitDistance(uint32_t distance_step);
    void WaitRotation(uint32_t rotation_step);
    void MoveForward(uint32_t distance_step);
    void MoveBackward(uint32_t distance_step);
    int  GetEncoder(void);
};

class Gripper_Class
{
  public:
    Servo  Right_Servo;
    Servo  Left_Servo;
  
    void Open(void);
    void Close(void);
    void MoveTo(int16_t angle);
};

class Robot_Class
{
  public:
    void Init(void);
    Button_Class   Button[4];
    IR_Class       IRSensor;
    Motion_Class   Motion;
    Gripper_Class  Gripper;
};

extern Robot_Class Robot;

void Robot_Init(void);

#endif