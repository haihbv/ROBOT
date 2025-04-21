#include <Arduino.h>
#include "lib/robot.h"

#define LAZER 0 // 0: khong co laze, 1: co laze
void setup()
{
  Robot.Init();
}
/***********************************************************
 * @task: Leanbot xuất phát từ vị trí “Hành quân”,
 * đi qua con đường an toàn, lấy lần lượt 2 thanh gỗ và
 * đặt chúng vào các vị trí trống tại vị trí “Căn cứ”.
 * Sau đó di chuyển tới "Vị trí Trung Tâm".
 ************************************************************/
void task1(void)
{
}

/***********************************************************
 * @task: Leanbot xuất phát từ trung tâm, hướng về vi trí
 * “Giải phóng” và sắp xếp lại các thanh gỗ tượng trưng
 * cho quân địch - quân ta
 ************************************************************/
void task2(void)
{
}

/***********************************************************
 * @task: Leanbot đứng tại "Vị trí Trung Tâm", hướng về
 * cung tròn chứa 3 Quân địch.
 * Sau đó Ngắm và Bắn, tiêu diệt các mục tiêu này.
 ************************************************************/
void task3(void)
{
  // tia lazer giua
  Robot.Motion.RunLR(-2000, 2000);
  Robot.Motion.WaitRotation(2117); // huong ve phia cung tron
  Robot.Motion.Stop();
#if (LAZER == 0)
  {
    Robot.Gripper.Open();
    delay(500);
    Robot.Gripper.Close();
    delay(500);
  }
#endif
  delay(500);
  // ban tia lazer ben trai
  Robot.Motion.RunLR(-2000, 2000);
  Robot.Motion.WaitRotation(706);
  Robot.Motion.Stop();
#if (LAZER == 0)
  {
    Robot.Gripper.Open();
    delay(500);
    Robot.Gripper.Close();
    delay(500);
  }
#endif
  delay(500);
  // ban tia lazer ben phai
  Robot.Motion.RunLR(2000, -2000);
  Robot.Motion.WaitRotation(706 + 706);
  Robot.Motion.Stop();
#if (LAZER == 0)
  {
    Robot.Gripper.Open();
    delay(500);
    Robot.Gripper.Close();
    delay(500);
  }
#endif
  delay(500);
  // quay ve huong trung tam
  Robot.Motion.RunLR(-2000, 2000);
  Robot.Motion.WaitRotation(706);
  Robot.Motion.Stop();
#if (LAZER == 0)
  {
    Robot.Gripper.Open();
    delay(500);
    Robot.Gripper.Close();
    delay(500);
  }
#endif
  delay(500);
}

/***********************************************************
 * @task: Leanbot xuất phát từ vị trí ngắm bắn, tới gắp
 * khối gỗ tượng trưng cho lá cờ tại khu vực quy định,
 * di chuyển qua mê cung và đặt khối gỗ này vào vị trí
 * “Giải phóng” và kết thúc nhiệm vụ.
 ************************************************************/
void task4(void)
{
}

void loop()
{
  if (Robot.Button[0].IsPressed())
  {
    task1();
  }
  if (Robot.Button[1].IsPressed())
  {
    task2();
  }
  if (Robot.Button[2].IsPressed() == 0)
  {
    task3();
  }
  if (Robot.Button[3].IsPressed())
  {
    task4();
  }
}
