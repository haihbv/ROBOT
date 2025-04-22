#include "robot.h"

//khoi tao nut nhan
void Button_Class::Init(uint8_t pin)
{
  //pinMode(pin, INPUT);
  pinMode(pin, INPUT_PULLUP); 
  Button_Class::pin = pin;
}

// doc trang thai logic 
uint8_t Button_Class::Read(void)
{
  return digitalRead(pin);
}

// kiem tra nut nhan duoc bam hay khong
uint8_t Button_Class::IsPressed(void)
{
  uint8_t ispressed = 0;
  uint8_t status = Read();

  //if(status && (status != pre_press_status))
  if(!status && (status != pre_press_status))
  {
    ispressed = 1;
  }
  pre_press_status = status;
  return ispressed;
}


// kiem tra nut nhan duoc bam va giu trong 1 khoan thoi gian
uint8_t Button_Class::Hold(uint16_t hold_time)
{
  uint8_t ispressed = 0;
  uint8_t status = Read();

  if( ! status) 
  {
    pre_time = millis();
    pre_hold_status = status;
  }
  
  //if(status && (status != pre_hold_status) && (millis() - pre_time > hold_time))
  if(!status && (status != pre_hold_status) && (millis() - pre_time > hold_time))
  {
    ispressed = 1;
    pre_hold_status = status;
  }
  return ispressed;
}