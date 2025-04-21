#include "robot.h"


void IR_Class::Init(uint8_t L3_pin, uint8_t L2_pin, uint8_t L1_pin, uint8_t L0_pin, uint8_t R0_pin, uint8_t R1_pin, uint8_t R2_pin, uint8_t R3_pin)
{
  pin1 = L3_pin;
  pin2 = L2_pin;
  pin3 = L1_pin;
  pin4 = L0_pin;
  pin5 = R0_pin;
  pin6 = R1_pin;
  pin7 = R2_pin;
  pin8 = R3_pin;

  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);
  pinMode(pin6, INPUT);
  pinMode(pin7, INPUT);
  pinMode(pin8, INPUT);
}

/* Đọc giá trị digital */
uint8_t IR_Class::ReadDigitalValue(int16_t threshold)
{
  data = 0;
  data |= (analogRead(pin1) < threshold ? 0 : 1) << 7;
  data |= (analogRead(pin2) < threshold ? 0 : 1) << 6;
  data |= (analogRead(pin3) < threshold ? 0 : 1) << 5;
  data |= (analogRead(pin4) < threshold ? 0 : 1) << 4;
  data |= (analogRead(pin5) < threshold ? 0 : 1) << 3; 
  data |= (analogRead(pin6) < threshold ? 0 : 1) << 2;
  data |= (analogRead(pin7) < threshold ? 0 : 1) << 1;
  data |= (analogRead(pin8) < threshold ? 0 : 1) << 0;

  return data;
}

/* Đọc giá trị analog  */
uint16_t IR_Class::ReadAnalogValue(uint8_t index)
{
  switch (index)
  {
    case 1:
      return analogRead(pin1);
      break;
    
    case 2:
      return analogRead(pin2);
      break;
    
    case 3:
      return analogRead(pin3);
      break;
    
    case 4:
      return analogRead(pin4);
      break;
    
    case 5:
      return analogRead(pin5);
      break;
    
    case 6:
      return analogRead(pin6);
      break;
    
    case 7:
      return analogRead(pin7);
      break;
    
    case 8:
      return analogRead(pin8);
      break;
    
    default:
      return 0;
      break;
  }
}