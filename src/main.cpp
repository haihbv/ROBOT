#include <Arduino.h>
#include "lib/robot.h"
#include "lib/_Task.h"


void setup()
{
  Robot.Init();
}

void loop()
{
  if (Robot.Button[0].IsPressed()) // A0
  {
    task1();
  }
  else if (Robot.Button[1].IsPressed()) // A4
  {
    task2();
  }
  else if (Robot.Button[2].IsPressed()) // A5
  {
    task3();
  }
  else if (Robot.Button[3].IsPressed()) // A1
  {
    task4();
  }
  else
  {
    Robot.Motion.RunLR(0, 0); // ko bam gi thi dung
  }
}
