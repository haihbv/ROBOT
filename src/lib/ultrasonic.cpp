#include "ultrasonic.h"

Ultrasonic_Class Ultrasonic;

void Ultrasonic_Class::Init(void)
{
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

uint16_t Ultrasonic_Class::GetDistance(void)
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    unsigned long time = pulseIn(ECHO, HIGH); 
    uint16_t distance = (time * 343) / 2000; 

    return (distance <= 2 || distance >= 400) ? 0 : distance; 
}
void Ultrasonic_Class::Check(void)
{
    const int ROTATION_STEPS[4] = {1058, 2117, 2117, 2117}; 
    const int DISTANCE_THRESHOLDS[4] = {20, 20, 20, 20};                       

    for (int i = 0; i < 4; i++)
    {
        // Quay robot
        Robot.Motion.RunLR(speed, -speed);
        Robot.Motion.WaitRotation(ROTATION_STEPS[i]);
        delay(50);

        // Kiểm tra khoảng cách
        uint16_t distance = GetDistance();
        if (distance != 0 && distance < DISTANCE_THRESHOLDS[i])
        {
            Look_Around[i] = 1;
        }
        else
        {
            Look_Around[i] = 0;
        }

        delay(50);
    }
}