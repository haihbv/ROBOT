#include "robot.h"
#include "_Task.h"
#include <Arduino.h>

/***********************************************************
 * @task: Leanbot xuất phát từ vị trí “Hành quân”,
 * đi qua con đường an toàn, lấy lần lượt 2 thanh gỗ và
 * đặt chúng vào các vị trí trống tại vị trí “Căn cứ”.
 * Sau đó di chuyển tới "Vị trí Trung Tâm".
 ************************************************************/
void task1(void)
{   
    // di thang
    Robot.Motion.RunLR(speed, speed);
    Robot.Motion.WaitDistance(2117);
    Robot.Motion.Stop();
    delay(500);
}

/***********************************************************
 * @task: Leanbot xuất phát từ trung tâm, hướng về vi trí
 * “Giải phóng” và sắp xếp lại các thanh gỗ tượng trưng
 * cho quân địch - quân ta
 ************************************************************/
void task2(void)
{
    // di lui
    Robot.Motion.RunLR(-speed, -speed);
    Robot.Motion.WaitDistance(2117);
    Robot.Motion.Stop();
    delay(500);
}

/***********************************************************
 * @task: Leanbot đứng tại "Vị trí Trung Tâm", hướng về
 * cung tròn chứa 3 Quân địch.
 * Sau đó Ngắm và Bắn, tiêu diệt các mục tiêu này.
 ************************************************************/
void task3(void)
{
    // tia lazer giua
    Robot.Motion.RunLR(-speed, speed);
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
    Robot.Motion.RunLR(-speed, speed);
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
    Robot.Motion.RunLR(speed, -speed);
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
    Robot.Motion.RunLR(-speed, speed);
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
    // quay goc 90 do
    Robot.Motion.RunLR(-speed, +speed);
    Robot.Motion.WaitRotation(8466);
    Robot.Motion.Stop();
    delay(500);
}
