#include "task.h"
#include "robot.h"
/***********************************************************
 * @task: Leanbot xuất phát từ vị trí “Hành quân”,
 * đi qua con đường an toàn, lấy lần lượt 2 thanh gỗ và
 * đặt chúng vào các vị trí trống tại vị trí “Căn cứ”.
 * Sau đó di chuyển tới "Vị trí Trung Tâm".
 ************************************************************/

void tien_len_can_cu(uint16_t distance_step)
{
    Robot.Motion.MoveForward(distance_step); // 95cm (2117 * 10)
}
// lui ve gap vat ben trai (truoc vach den cua vat) va tien len can cu
void lui_ve_gap_vat_ben_trai() // truoc vach den cua vat
{
    Robot.Motion.MoveForward(2117 * 4); // 40cm
    Robot.Motion.Turn_Left_45();
    Robot.Motion.MoveForward(236); // 1cm
    Robot.Motion.Stop();
    Robot.Gripper.Open();
    Robot.Gripper.Close();
    Robot.Motion.MoveBackward(236);
    Robot.Motion.Turn_Left_45(); // quay ve phia can cu
    // tien len can cu
    tien_len_can_cu(2117 * 4); // 40 cm
}
// lui ve gap vat ben phai (truoc vach den cua vat) va tien len can cu
void lui_ve_gap_vat_ben_phai()
{
    Robot.Motion.MoveForward(2117 * 4); // 40cm
    Robot.Motion.Turn_Right_45();
    Robot.Motion.MoveForward(236); // 1cm
    Robot.Motion.Stop();
    Robot.Gripper.Open();
    Robot.Gripper.Close();
    Robot.Motion.MoveBackward(236);
    Robot.Motion.Turn_Right_45(); // quay ve phia can cu
    // tien len can cu
    tien_len_can_cu(2117 * 4); // 40 cm
}
int pos1 = 1058, pos2 = 1058 + 2117, pos3 = 1058 + 2117 * 2, pos4 = 1058 + 2117 * 3;
int Rotation_Save[4] = {pos1, pos2, pos3, pos4};
int Save_Muc_tieu[4] = {1, 1, 1, 1};
void kiem_tra_xung_quanh()
{
    int sl = 2;
    int cnt = 0;
    int idx;
    Robot.Motion.Turn_Left_45();
    delay(50);
    Robot.Motion.MoveForward(236);
    if (Robot.Ultrasonic.pingCm() < 12)
    {
        ++cnt;
        idx = 0;
        Save_Muc_tieu[idx] = 0;
    }
    Robot.Motion.MoveBackward(236);
    if (cnt == sl)
        return;

    Robot.Motion.Turn_Right_90();
    delay(50);
    Robot.Motion.MoveForward(236);
    if (Robot.Ultrasonic.pingCm() < 12)
    {
        ++cnt;
        idx = 1;
        Save_Muc_tieu[idx] = 0;
    }
    Robot.Motion.MoveBackward(236);
    if (cnt == sl)
        return;

    Robot.Motion.Turn_Right_90();
    delay(50);
    Robot.Motion.MoveForward(236);
    if (Robot.Ultrasonic.pingCm() < 12)
    {
        ++cnt;
        idx = 2;
        Save_Muc_tieu[idx] = 0;
    }
    Robot.Motion.MoveBackward(236);
    if (cnt == sl)
        return;

    Robot.Motion.Turn_Right_90();
    delay(50);
    Robot.Motion.MoveForward(236);
    if (Robot.Ultrasonic.pingCm() < 12)
    {
        ++cnt;
        idx = 3;
        Save_Muc_tieu[idx] = 0;
    }
    Robot.Motion.MoveBackward(236);
    if (cnt == sl)
        return;

    // quay ve phia xuat phat
    Robot.Motion.Turn_Left_90();
    Robot.Motion.Turn_Left_45();
}

void dat_vat()
{
    if (Save_Muc_tieu[0] == 0)
    {
        Robot.Motion.RunLR(-speed, speed);
        Robot.Motion.WaitRotation(Rotation_Save[0]);
        Robot.Motion.MoveForward(236);
        Robot.Gripper.Open();
        delay(100);
        Robot.Motion.MoveBackward(236);
        Robot.Motion.RunLR(+speed, -speed);
        Robot.Motion.WaitRotation(Rotation_Save[0]);
        Save_Muc_tieu[0] = 1; // dat xong gan lai bang 1 de lan sau kiem tra ko kiem tra lai nua
    }
    else if (Save_Muc_tieu[1] == 0)
    {
        Robot.Motion.RunLR(-speed, speed);
        Robot.Motion.WaitRotation(Rotation_Save[1]);
        Robot.Motion.MoveForward(236);
        Robot.Gripper.Open();
        delay(100);
        Robot.Motion.MoveBackward(236);
        Robot.Motion.RunLR(+speed, -speed);
        Robot.Motion.WaitRotation(Rotation_Save[1]);
        Save_Muc_tieu[1] = 1;
    }
    else if (Save_Muc_tieu[2] == 0)
    {
        Robot.Motion.RunLR(-speed, speed);
        Robot.Motion.WaitRotation(Rotation_Save[2]);
        Robot.Motion.MoveForward(236);
        Robot.Gripper.Open();
        delay(100);
        Robot.Motion.MoveBackward(236);
        Robot.Motion.RunLR(+speed, -speed);
        Robot.Motion.WaitRotation(Rotation_Save[2]);
        Save_Muc_tieu[2] = 1;
    }
    else if (Save_Muc_tieu[3] == 0)
    {
        Robot.Motion.RunLR(-speed, speed);
        Robot.Motion.WaitRotation(Rotation_Save[3]);
        Robot.Motion.MoveForward(236);
        Robot.Gripper.Open();
        delay(100);
        Robot.Motion.MoveBackward(236);
        Robot.Motion.RunLR(+speed, -speed);
        Robot.Motion.WaitRotation(Rotation_Save[3]);
        Save_Muc_tieu[3] = 1;
    }
}
void task1(void)
{
    tien_len_can_cu(2117 * 10);
    kiem_tra_xung_quanh();
    lui_ve_gap_vat_ben_trai();
    dat_vat();
    lui_ve_gap_vat_ben_phai();
    dat_vat();

    // lui ve va di vao phia trung tam
    Robot.Motion.MoveForward(2117 * 4);
    Robot.Motion.Turn_Right_90();
    Robot.Motion.MoveForward(2117 * 4);
}

/***********************************************************
 * @task: Leanbot xuất phát từ trung tâm, hướng về vi trí
 * “Giải phóng” và sắp xếp lại các thanh gỗ tượng trưng
 * cho quân địch - quân ta
 ************************************************************/
void task2(void)
{
    Robot.Motion.RunLR(-2000, 0);
    Robot.Motion.WaitRotation(4233);
    delay(2000);
    Robot.Motion.RunLR(0, 2000);
    Robot.Motion.WaitRotation(4233);
    delay(2000);
    // Robot.Motion.RunLR(-2000, 2000);
    // Robot.Motion.WaitRotation(2117);
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
        delay(100);
        Robot.Gripper.Close();
        delay(100);
    }
#endif
    // ban tia lazer ben trai
    Robot.Motion.RunLR(-speed, speed);
    Robot.Motion.WaitRotation(706);
    Robot.Motion.Stop();
#if (LAZER == 0)
    {
        Robot.Gripper.Open();
        delay(100);
        Robot.Gripper.Close();
        delay(100);
    }
#endif
    Robot.Motion.RunLR(speed, -speed);
    Robot.Motion.WaitRotation(706*2);
    Robot.Motion.Stop();
    // ban tia lazer ben phai
    Robot.Motion.RunLR(speed, -speed);
    Robot.Motion.WaitRotation(706);
    Robot.Motion.Stop();
#if (LAZER == 0)
    {
        Robot.Gripper.Open();
        delay(100);
        Robot.Gripper.Close();
        delay(100);
    }
#endif
    // quay ve huong trung tam
    Robot.Motion.RunLR(-speed, speed);
    Robot.Motion.WaitRotation(706);
    Robot.Motion.Stop();
}

/***********************************************************
 * @task: Leanbot xuất phát từ vị trí ngắm bắn, tới gắp
 * khối gỗ tượng trưng cho lá cờ tại khu vực quy định,
 * di chuyển qua mê cung và đặt khối gỗ này vào vị trí
 * “Giải phóng” và kết thúc nhiệm vụ.
 ************************************************************/
void task4(void)
{   
    //quay lan 1
    Robot.Motion.RunLR(-2000, 0);
    Robot.Motion.WaitRotation(4233);
    delay(1000);
    Robot.Motion.RunLR(0, 2000);
    Robot.Motion.WaitRotation(4233);
    delay(1000);

    //quay lan 2
    Robot.Motion.RunLR(-2000, 100);
    Robot.Motion.WaitRotation(2177);
    //quay 2 cai cuoi
    Robot.Motion.RunLR(2000, 500);
    Robot.Motion.WaitRotation(3000);
    Robot.Motion.RunLR(2000, -2000);
    Robot.Motion.WaitRotation(706+706);
}
