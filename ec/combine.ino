#include <Leanbot.h>
#include <Arduino_APDS9960.h>


//*******************************************************
class cLbColorDetector {
  public:
    void detect();
    void printRGB();

  private:
    int objRed, objGreen, objBlue;
};

void cLbColorDetector::detect() {
  int originalBrightness = LbRGB.getBrightness();
  LbRGB.setBrightness(255);

  int rr, gg, bb;

  LbRGB.fillColor(0xFF00FF);
  LbRGB.show();

  while (APDS.colorAvailable() == 0);
  APDS.readColor(rr, gg, bb);
  int r1 = rr;
  int b1 = bb;

  LbRGB.fillColor(0x00FF00);
  LbRGB.show();

  while (APDS.colorAvailable() == 0);
  APDS.readColor(rr, gg, bb);
  int g1 = gg;

  LbRGB.fillColor(0x000000);
  LbRGB.show();

  while (APDS.colorAvailable() == 0);
  APDS.readColor(rr, gg, bb);

  objRed   = (r1 - rr) * 2;
  objGreen = (g1 - gg) * 2;
  objBlue  = (b1 - bb) * 1;

  red = objRed;
  green = objGreen;

  LbRGB.setBrightness(originalBrightness);
}

void cLbColorDetector::printRGB() {
  Serial.print("RGB: ");
  Serial.print(objRed);
  Serial.print(" ");
  Serial.print(objGreen);
  Serial.println();
}

cLbColorDetector LbColorDetector;
//********************************************************


int chonBai = 0;
int threshold = 60;
int speed = 1100, stop = 0;
int robot_arm_range = 60;
int speeda = 600;

int angle = 28;
int distanceMm = 270;
int red = 0, green = 0;

#define speed_nv4 1700
#define DISTANCE1 320 // // cách điểm (1) 1 khoảng nhất định
#define DISTANCE2 55 //cách điểm (2) 1 khoảng nhất định
#define DISTANCE3 50 // quãng đường lùi đến điểm (3)
#define DISTANCE4 700 // quãng đường tiến đến điểm (4)
#define DISTANCE5 8 // quãng đường tiến đến điểm (5)
#define DISTANCE6 9 // quãng đường tiến đến điểm (6)
char flag = 1;


void FollowLine_2(int speed){         
    //int speed_4   = 0.8 * speed;
    int speed_3   = 0.6 * speed;
    int speed_2   = 0.4 * speed;
    //int speed_1   = 0.2 * speed;
    int speed_0   = 0 * speed;
    byte line = LbIRLine.read(49); 
    switch (line) {                 // check the location of Leanbot
    case 0b0000:
      LbMotion.runLR(speed_0, speed_0);
      break;
    case 0b0110:
      LbMotion.runLR(speed, speed);
      break;
    case 0b0010:
      LbMotion.runLR(speed, speed_3);
      break;
    case 0b0011:
      LbMotion.runLR(speed, speed_2);
      break;
    case 0b0001:
      LbMotion.runLR(speed, speed_0);
      break;
    case 0b0100:
      LbMotion.runLR(speed_3, speed);
      break;
    case 0b1100:
      LbMotion.runLR(speed_2, speed);
      break;
    case 0b1000:
      LbMotion.runLR(speed_0, speed);
      break;
    case 0b1111:
      LbMotion.runLR(speed_0, speed_0);
      break;
  }
}
//task1
bool junction_1();// hàm phát hiện ngã tư khi chạy 1 line
bool junction_2();// hàm phát hiện ngã tư khi chạy 2 line
void TwoLine(int speed);// chạy theo 2 line
void FollowLine ( int speed);// robot chạy theo 1 line
void Turn_Right(int angle);// hàm rẽ phải
void Turn_Left(int angle);//hàm rẽ trái
void Forward(int speed, int distance);// đi thẳng (tiến, lùi)
void Task_1(void);// hàm thực hiện nvu 1

//task2
int check_color();
void Task2(void);
void followline_task2(void);


//task4
int adjustWithIR();
void task4();

void setup() {
  Leanbot.begin();
  //LbIRLine.doManualCalibration(TB1A);
  LbMission.begin(); 
  APDS.begin(); 
  if (APDS.begin()) {
    Serial.println("Init APDS-9960 ok.");
  } else {
    Serial.println("Init APDS-9960 error.");
    while (1);  // Dừng chương trình nếu lỗi
  }
}



void loop() {
  while (chonBai == 0){
        byte touch_sense_1 = LbTouch.read(TB1A);
        byte touch_sense_2 = LbTouch.read(TB1B);
        byte touch_sense_3 = LbTouch.read(TB2A);
        if (touch_sense_1) {
            // Bai 1 2
            chonBai = 1;
        } else if (touch_sense_2) {
            // Bai 4
            chonBai = 2;
        }  else if (touch_sense_3) {
            // Bai 2
            chonBai = 3;
        }
    }

    if (chonBai == 1){ //TB1A
        Task_1();
        Task2();
        chonBai = 2;
    }
    else if (chonBai == 2){ //TB1B
        task4();
    }
    else if(chonBai == 3){ //TB2A
        Task2();
    }
}

bool junction_1(){
    byte line = LbIRLine.read(threshold);
    if (line == 0b0111)return true;
    if (line == 0b1110)return true;
    if (line == 0b1111)return true;
    return false;
}
bool junction_2()
{
    byte line = LbIRLine.read(threshold);
    if (line == 0b0110)return true;
    if (line == 0b0111)return true;
    if (line == 0b1110)return true;
    if (line == 0b1111)return true;
    return false;
}
void TwoLine(int speed){
    int speed_2 = 0.3 * speed ;
    int speed_3 = 0.6 * speed ; 
    int stop   = 0;  // stop 
    byte line = LbIRLine.read(threshold);   
    // LbIRLine.println(line);  
    
    switch (line){
      case 0b0000:
        LbMotion.runLR(speed, speed);
        break;
  
      case 0b0011:
        LbMotion.runLR(speed_2, speed);
        break;
    
      case 0b0001:
        LbMotion.runLR(speed_3, speed);
        break;
    
      case 0b1100:
        LbMotion.runLR(speed, speed_2);
        break;
    
      case 0b1000:
        LbMotion.runLR(speed, speed_3);
        break;
    
      case 0b1111:
        LbMotion.runLR(stop, stop);
        break;
    }
}
void FollowLine ( int speed){         
    //int speed_4   = 0.8 * speed;
    int speed_3   = 0.6 * speed;
    int speed_2   = 0.4 * speed;
    //int speed_1   = 0.2 * speed;
    int speed_0   = 0;
    byte line = LbIRLine.read(threshold); 
    switch (line) {                 // check the location of Leanbot
    case 0b0000:
    case 0b0110:
      LbMotion.runLR(speed, speed);
      break;


    case 0b0010:
      LbMotion.runLR(speed, speed_3);
      break;

    case 0b0011:
      LbMotion.runLR(speed, speed_2);
      break;

    case 0b0001:
      LbMotion.runLR(speed, speed_0);
      break;


    case 0b0100:
      LbMotion.runLR(speed_3, speed);
      break;

    case 0b1100:
      LbMotion.runLR(speed_2, speed);
      break;

    case 0b1000:
      LbMotion.runLR(speed_0, speed);
      break;


    case 0b1111:
      LbMotion.runLR(speed_0, speed_0);
      break;
  }
}
void Turn_Right(int angle)
{
    LbMotion.runLR(500, -500);
    LbMotion.waitRotationDeg(angle);
    LbMotion.stopAndWait();
}
void Turn_Left(int angle)
{
    LbMotion.runLR(-500, 500);
    LbMotion.waitRotationDeg(angle);
    LbMotion.stopAndWait();
}
void Forward(int speed, int distance)                  
{
    LbMotion.runLR(speed, speed);
    LbMotion.waitDistanceMm(distance);
    LbMotion.runLR(0, 0); //?
    LbMotion.stopAndWait();
}
void Task_1(void)
{
  //step1: di chuyển đến vạch kẻ ngang và tiến hành gắp
  while (!junction_2()) // chạy dò line đến vạch kẻ ngang thì dừng lại
  {
    TwoLine(speed);  
  }
  LbMotion.runLR(0, 0);  //?
  LbMotion.stopAndWait() ;
  Forward(speed, 30); // tiến thêm 1 khoảng  //25
  Turn_Left(90 + 4); // quay lại gắp, có thể điều chỉnh tốc độ quay và góc
  LbMotion.stopAndWait(); // stop the robot

  //gắp
  int distanceMm_task1_1 = Leanbot.pingMm(); // đo khoảng cách từ sensor - vật
  LbDelay(100); // wait for 100ms
  int run_1 = distanceMm_task1_1 - robot_arm_range; // tính khoảng cách từ tay đến vật
  Forward(speeda, run_1); 
  LbGripper.close(); // gắp
  LbMotion.stopAndWait();
  Forward(-speeda, run_1); 
  Turn_Right(91); // quay về vị trí ban đầu, có thể điều chỉnh tốc độ quay và góc
  LbMotion.runLR(0,0);
  LbMotion.stopAndWait();

  //step 2: di chuyển đến vị trí căn cứ và kiểm tra vị trí trống và đặt lần đầu
  while (!junction_2()) // di chuyển đến line trước căn cứ
  {
    TwoLine(speed); 
  }
  LbMotion.stopAndWait();
  LbMotion.runLR(0, 0);
  // đọc 2 vị trí đầu tiên 
  int left = LbIRArray.read(ir6L); 
  int right = LbIRArray.read(ir7R); 
  LbDelay(1000);
  int deg_left_1 = 0;
  int deg_right_1 = 0;
  int deg_left_2 = 0;
  int deg_right_2 = 0;

  // nếu không có vật thể gán giá trị ô có vật thể là góc quay
  if (left > 700){
      deg_left_1 = 135; // có thể điều chỉnh góc quay cho phù hợp
  }
  if (right > 700){
      deg_right_1 = 135;
  }
  Forward(speeda, 120);
  while (!junction_2()) // ?? đoạn lên check 2 vị trí c d
  {
    LbMotion.runLR(speeda,speeda);
  }
  LbMotion.stopAndWait();
  LbMotion.runLR(0, 0);
  int left_2 = LbIRArray.read(ir6L);
  int right_2 = LbIRArray.read(ir7R);
  LbDelay(1000);

  if (left_2 > 700){
      deg_left_2 = 45;
  }
  if (right_2 > 700 ){
      deg_right_2 = 45;
  } 
  Forward(-speeda, 65); // lùi về trung tâm của căn cứ

  //đặt lần đầu tiên
  int check = 0;
  if ( deg_left_1 != 0){
    Turn_Left(deg_left_1);
    deg_left_1 = 0;
    check = 1;
  }
  else if ( deg_right_1 != 0){
    Turn_Right(deg_right_1);
    deg_right_1 = 0;
    check = 2;
  }
  else if( deg_left_2 != 0){
    Turn_Left(deg_left_2);
    deg_left_2 = 0;
    check = 3;
  }
  else if ( deg_right_2 != 0){
    Turn_Right(deg_right_2);
    deg_right_2 = 0;
    check = 4;
  }
  Forward(speeda, 113 - robot_arm_range);
  LbGripper.open();
  Forward(-speeda, 113 - robot_arm_range);

  //quay đầu lại
  if (check == 1 || check == 3){
    if (check == 1){
      Turn_Left((180 - 135)+5);
    }
    else{
      Turn_Left((180 - 45)+5);
    }
  }
  else{
    if (check == 2){ 
        Turn_Right((180 - 135)+5);
      }
      else{
        Turn_Right((180 - 45)+5);
      }
  }

  //step3: tiến ngược về đến ngã 4 và gắp
  while (!junction_2()) // di chuyển ra khỏi căn cứ
  {
    LbMotion.runLR(speeda,speeda); 
  }
  LbMotion.runLR(0,0);
  LbMotion.stopAndWait();
  Forward(speeda,55);
  // tiến về đến ngã 4
  while (!junction_2())
  {
    TwoLine(600);
  }
  LbMotion.stopAndWait();
  LbMotion.runLR(0, 0);
  Forward(speed, 55);
  Turn_Left(110);
  LbMotion.stopAndWait();

  //gắp
  int distanceMm_task1_2 = Leanbot.pingMm();
  LbDelay(100);
  int run_2 = distanceMm_task1_2 - robot_arm_range; 
  Forward(speeda, run_2);  
  LbMotion.stopAndWait(); 
  LbGripper.close();
  LbMotion.stopAndWait();
  Forward(-speeda, run_2 + 2); 
  LbMotion.stopAndWait(); 
  LbMotion.runLR(0,0);

  Turn_Left(70);
  LbMotion.runLR(0,0);
  LbMotion.stopAndWait();
  LbDelay(100); 
  

  //step4: di chuyển về căn cứ
  Forward(speeda, 50);
  while (!junction_2()) 
  {
    TwoLine(speed);
  }
  LbMotion.stopAndWait();
  LbMotion.runLR(0, 0);
  Forward(speed, 120);// di chuyển ra trung tâm
  check = 0;
  if ( deg_left_1 != 0){
    Turn_Left(deg_left_1);
    deg_left_1 = 0;
    check = 1;
  }
  else if ( deg_right_1 != 0){
    Turn_Right(deg_right_1);
    deg_right_1 = 0;
    check = 2;

  }
  else if( deg_left_2 != 0){
    Turn_Left(deg_left_2);
    deg_left_2 = 0;
    check = 3;

  }
  else if ( deg_right_2 != 0){
    Turn_Right(deg_right_2);
    deg_right_2 = 0;
    check = 4;

  }
  Forward(speeda, 114 - robot_arm_range);
  LbGripper.open();
  Forward(-speeda, 114 - robot_arm_range);
  if (check == 1 || check == 3){
    if (check == 1){
      Turn_Left((180 - 135)+5);
    }
    else{
      Turn_Left((180 - 45)+5);
    }
  }
  else{
    if (check == 2){ 
        Turn_Right((180 - 135)+5);
      }
      else{
        Turn_Right((180 - 45)+5);
      }
  }

  //step5: di chuyển về vị trí tt
  while (!junction_2()) // di chuyển ra khỏi căn cứ
  {
    LbMotion.runLR(speeda,speeda); // 
  }
  LbMotion.runLR(0,0);
  LbMotion.stopAndWait();
  Forward(speeda,55);
  while (!junction_2()) // tiến về đến ngã 4
  {
    TwoLine(600); 
  }
  LbMotion.runLR(0, 0);
  LbMotion.stopAndWait();
  Forward(speed, 25);
  Turn_Right(91);
  // tiến về trung tâm hoàn thành nvu
  while(!junction_1())
  {
    FollowLine(1500);
  }
  Forward(speed, 30);
  while(!junction_1())
  {
    FollowLine(1500);
  }
  Forward(speed, 27);
  LbMotion.stopAndWait();
  LbMotion.runLR(0, 0);
  Turn_Right(91);
}

void Task2(void)
{
  // gắp vị trí đầu tiên ra giữa
  Turn_Right(angle);
  Forward(1000, 150);
  while(LbIRLine.read(50)!= 0b0000){
    FollowLine_2(1200);
  }
  LbMotion.stopAndWait();
  int x = check_color(); //ktra màu lưu vào x
  LbGripper.close();
  Forward(-1000, distanceMm);
  Turn_Left(30);
  Forward(1000, 150);
  while(LbIRLine.read(50)!= 0b0000){
    FollowLine_2(1200);
  }
  LbMotion.stopAndWait();
  LbGripper.open();
  Forward(-1000, distanceMm);

  //quay sang check cột bên trái
  Turn_Left(30);
  Forward(1000, 150);
  while(LbIRLine.read(50)!= 0b0000){
    FollowLine_2(1200);
  }
  LbMotion.stopAndWait();
  int y = check_color();//ktra màu lưu vào y
  if(x != y)//Nếu khác màu, thì gặp và đưa về vị trí trống
  {
    LbGripper.close();
    Forward(-1000, distanceMm);
    Turn_Right(60 + 2);
    Forward(1000, 150);
    while(LbIRLine.read(50)!= 0b0000){
       FollowLine_2(1200);
      }
    LbMotion.stopAndWait();
    LbGripper.open();
    Forward(-1000, distanceMm);
    //Gắp vị trí giữa về vị trí còn trống
    Turn_Left(30);
    Forward(1000, 150);
    while(LbIRLine.read(50)!= 0b0000){
       FollowLine_2(1200);
      }
    LbMotion.stopAndWait();
    LbGripper.close();
   Forward(-1000, distanceMm);
    Turn_Left(30);
    Forward(1000, 150);
    while(LbIRLine.read(50)!= 0b0000){
       FollowLine_2(1200);
      }
    LbMotion.stopAndWait();
    LbGripper.open();
   Forward(-1000, distanceMm);
    Turn_Left(56);
  }
  else if(x == y)//Nếu giống màu, thì lùi lại và đưa vị trí bên cạnh vào vị trí trống
  {
    //lùi lại và gắp vị trí bên trái, khác màu với cột mẫu x
    Forward(-1000, distanceMm);
    Turn_Left(28);
    Forward(1000, 150);
    while(LbIRLine.read(50)!= 0b0000){
       FollowLine_2(1200);
      }
    LbMotion.stopAndWait();
    LbGripper.close();
    Forward(-1000, distanceMm);
    //Đưa về vị trí còn trống
    Turn_Right(90);
    Forward(1000, 150);
    while(LbIRLine.read(50)!= 0b0000){
       FollowLine_2(1200);
      }
    LbMotion.stopAndWait();
    LbGripper.open();
    Forward(-1000, distanceMm);
    //Ra cột mẫu x và đưa về vị trí trống
    Turn_Left(30);
    Forward(1000, 150);
    while(LbIRLine.read(50)!= 0b0000){
       FollowLine_2(1200);
      }
    LbMotion.stopAndWait();
    LbGripper.close();
    Forward(-1000, distanceMm);
    Turn_Left(60);
    Forward(1000, 150);
    while(LbIRLine.read(50)!= 0b0000){
       FollowLine_2(1200);
      }
    LbMotion.stopAndWait();
    LbGripper.open();
    Forward(-1000, distanceMm);
    Turn_Left(30);
    //Forward(speed, 8);
  }
}
void followline_task2()
{
  int SPEED_MAX = 1000;             
  //int SPEED_4   = 0.8 * SPEED_MAX;  
  int SPEED_3   = 0.6 * SPEED_MAX;  
  int SPEED_2   = 0.4 * SPEED_MAX;  
  //int SPEED_1   = 0.2 * SPEED_MAX;  
  int SPEED_0   = 0.0 * SPEED_MAX;  

  byte line = LbIRLine.read(60); 
  switch (line) {                 
    case 0b0000:
      LbMotion.runLR(SPEED_0, SPEED_0);
     break;
     
    case 0b0110:
      LbMotion.runLR(SPEED_MAX, SPEED_MAX);
      break;


    case 0b0010:
      LbMotion.runLR(SPEED_MAX, SPEED_3);
      break;

    case 0b0011:
      LbMotion.runLR(SPEED_MAX, SPEED_2);
      break;

    case 0b0001:
      LbMotion.runLR(SPEED_MAX, SPEED_0);
      break;


    case 0b0100:
      LbMotion.runLR(SPEED_3, SPEED_MAX);
      break;

    case 0b1100:
      LbMotion.runLR(SPEED_2, SPEED_MAX);
      break;

    case 0b1000:
      LbMotion.runLR(SPEED_0, SPEED_MAX);
      break;    
  }
}
int check_color() {
    LbColorDetector.detect();
    LbColorDetector.printRGB();
    if (red > green) {
      Serial.println("Red detected!"); return 1;
    } else if (green > red) {
      Serial.println("Green detected!"); return 2;
    } else {
      Serial.println("No color detected!"); return 0;
    }
}

//task4
int adjustWithIR() 
{
  int Kp = 5;
  int V_Goc = 1200;
  int Left = LbIRArray.read(ir6L);
  int Right = LbIRArray.read(ir7R);
  if(Right <= 145){
    return 0;
  }

  int Error = Right - Left;
  
  int VL = V_Goc + Error * Kp;
  int VR = V_Goc - Error * Kp;
  if(Error < 0) Error = Error * (-1);
  LbMotion.runLR(VL,VR);
  return 1;
}
void task4()
{
  if(flag == 1)
  {
    LbMotion.runLR(speed_nv4, speed_nv4);     
    LbMotion.waitDistanceMm(DISTANCE1); 
    LbMotion.runLR(1800, 300);
    LbMotion.waitRotationDeg(70);
    LbMotion.runLR(1700, 1700);
    LbMotion.waitDistanceMm(30);
    flag = 2;
  }

  if(flag == 2)
  {
    adjustWithIR();
    if(Leanbot.pingMm() <= DISTANCE2)
    {
      LbMotion.stopAndWait();
      LbGripper.moveTo(70);
      flag = 3;
    }
  }

  if(flag == 3)
   {
     LbMotion.runLR(-speed_nv4, -speed_nv4);     
     LbMotion.waitDistanceMm(DISTANCE4); 
     LbMotion.runLR(-1800, -300);
     LbMotion.waitRotationDeg(55);
     LbMotion.runLR(speed_nv4, speed_nv4);
     LbMotion.waitDistanceMm(100);
     flag = 4;
   }

   if(flag == 4)
   {
    LbMotion.runLR(1800, 300);
    LbMotion.waitRotationDeg(80);
    LbMotion.stopAndWait();
    flag = 5;
   }

   if(flag == 5)
   {
    LbMotion.runLR(speed_nv4, speed_nv4);
    LbMotion.waitDistanceMm(30);
    flag = 6;
   }
  
   if(flag == 6){
     if(adjustWithIR() == 0){
       flag = 7;
     }
   }

   if(flag==7){
    LbMotion.runLR(speed_nv4, speed_nv4);
    LbMotion.waitDistanceMm(300);
    LbMotion.stopAndWait();
    flag=8;
  }

  if(flag == 8){
    if(adjustWithIR() == 0){
      flag = 9;
    }
  }

  if(flag == 9){
    LbMotion.runLR(speed_nv4, speed_nv4);
    LbMotion.waitDistanceMm(30);
    LbMotion.runLR(1800, 300);
    LbMotion.waitRotationDeg(76);
    LbMotion.stopAndWait();
    LbMotion.runLR(speed_nv4, speed_nv4);
    LbMotion.waitDistanceMm(450);
    LbMotion.stopAndWait();
    LbGripper.open();
    Forward(-1000, 20);
    flag = 0;
  }
}