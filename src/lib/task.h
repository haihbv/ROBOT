#ifndef TASK_H
#define TASK_H
#include "robot.h"


/***********************************************************
 * @task: Leanbot xuất phát từ vị trí “Hành quân”,
 * đi qua con đường an toàn, lấy lần lượt 2 thanh gỗ và
 * đặt chúng vào các vị trí trống tại vị trí “Căn cứ”.
 * Sau đó di chuyển tới "Vị trí Trung Tâm".
 ************************************************************/
void tien_len_can_cu(uint16_t distance_step);
void lui_ve_gap_vat_ben_trai();
void lui_ve_gap_vat_ben_phai();
void kiem_tra_xung_quanh();
void dat_vat();
void task1(void);

/***********************************************************
 * @task: Leanbot xuất phát từ trung tâm, hướng về vi trí
 * “Giải phóng” và sắp xếp lại các thanh gỗ tượng trưng
 * cho quân địch - quân ta
 ************************************************************/
void task2(void);

/***********************************************************
 * @task: Leanbot đứng tại "Vị trí Trung Tâm", hướng về
 * cung tròn chứa 3 Quân địch.
 * Sau đó Ngắm và Bắn, tiêu diệt các mục tiêu này.
 ************************************************************/
void task3(void);

/***********************************************************
 * @task: Leanbot xuất phát từ vị trí ngắm bắn, tới gắp
 * khối gỗ tượng trưng cho lá cờ tại khu vực quy định,
 * di chuyển qua mê cung và đặt khối gỗ này vào vị trí
 * “Giải phóng” và kết thúc nhiệm vụ.
 ************************************************************/
void task4(void);

#endif