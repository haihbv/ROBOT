#include "robot.h"

// Motor Run and setup left wheel speed | right wheel speed
void Motion_Class::RunLR(float vL, float vR)
{
  left_speed = vL;
  right_speed = vR;
  Left_Stepper.Run(vL);
  Right_Stepper.Run(vR);
}
// Motor Stop
void Motion_Class::Stop(void)
{
  RunLR(0, 0);
}

// Robot chạy theo số bước
// void Motion_Class::WaitDistance(uint32_t distance_step)
// {
//   int pre_encoder = ((Abs(left_speed) > Abs(right_speed)) ? Left_Stepper.encoder : Right_Stepper.encoder);

//   while(Abs(((Abs(left_speed) > Abs(right_speed)) ? Left_Stepper.encoder : Right_Stepper.encoder) - pre_encoder) < distance_step)
//   {
//     RunLR(left_speed, right_speed);
//   }
// }

// Robot quay theo số bước
// void Motion_Class::WaitRotation(uint32_t rotation_step)
// {
//   int pre_encoder = (Abs(left_speed) > Abs(right_speed)) ? Left_Stepper.encoder : Right_Stepper.encoder;

//   while(Abs(((Abs(left_speed) > Abs(right_speed)) ? Left_Stepper.encoder : Right_Stepper.encoder) - pre_encoder) < rotation_step)
//   {
//     RunLR(left_speed, right_speed);
//   }
// }

// motor goes straight
void Motion_Class::WaitDistance(uint32_t distance_step)
{
  int pre_encoder_left = Left_Stepper.encoder;
  int pre_encoder_right = Right_Stepper.encoder;

  while (Abs(Left_Stepper.encoder - pre_encoder_left) < distance_step &&
         Abs(Right_Stepper.encoder - pre_encoder_right) < distance_step)
  {
    // Điều chỉnh tốc độ để giữ cho robot đi thẳng
    int error = (Left_Stepper.encoder - pre_encoder_left) - (Right_Stepper.encoder - pre_encoder_right);

    float adjusted_left_speed = left_speed - (error * 0.1); // Hệ số 0.1 có thể điều chỉnh
    float adjusted_right_speed = right_speed + (error * 0.1);

    RunLR(adjusted_left_speed, adjusted_right_speed);
  }

  Stop(); // Dừng robot sau khi hoàn thành
}

// motor rotation
void Motion_Class::WaitRotation(uint32_t rotation_step)
{
  int pre_encoder_left = Left_Stepper.encoder;
  int pre_encoder_right = Right_Stepper.encoder;

  while (Abs(Left_Stepper.encoder - pre_encoder_left) < rotation_step &&
         Abs(Right_Stepper.encoder - pre_encoder_right) < rotation_step)
  {
    // Chạy động cơ với tốc độ cố định để quay
    RunLR(left_speed, right_speed);
  }

  Stop(); // Dừng robot sau khi hoàn thành
}
void Motion_Class::MoveForward(uint32_t distance_step)
{
  Robot.Motion.RunLR(speed, speed);
  Robot.Motion.WaitDistance(distance_step);
  Robot.Motion.Stop();
}

// Hàm lùi 'distance_step' buoc voi toc do speed
void Motion_Class::MoveBackward(uint32_t distance_step)
{
  Robot.Motion.RunLR(-speed, -speed);
  Robot.Motion.WaitDistance(distance_step);
  Robot.Motion.Stop();
}

int Motion_Class::GetEncoder(void)
{
  return Left_Stepper.encoder;
}