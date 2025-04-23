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
  else if (Robot.Button[1].IsPressed()) // A1
  {
    task2();
  }
  else if (Robot.Button[2].IsPressed()) // A2
  {
    task3();
  }
  else if (Robot.Button[3].IsPressed()) // A3
  {
    task4();
  }
  else
  {
    Robot.Motion.Stop();
  }
}
