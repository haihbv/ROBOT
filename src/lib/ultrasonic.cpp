#include "ultrasonic.h"

Ultrasonic_Class Ultrasonic;

void Ultrasonic_Class::Init(void)
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

float Ultrasonic_Class::Distance_cm(void)
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
   float time = pulseIn(echo, HIGH);
   
    return (time * 0.0343) / 2.0;// tra ve cm
}
void Ultrasonic_Class::Check(void)
{
    Robot.Motion.RunLR(2000, -2000);
    Robot.Motion.WaitRotation(985);
    delay(50);
    if(Ultrasonic.Distance_cm() < 20){
        checkCircle[0] = 1;
        Robot.Motion.MoveForward(1000, 2000);
        Robot.Motion.MoveBackward(1000, 2000);
    }
    delay(50);
    Robot.Motion.RunLR(2000, -2000);
    Robot.Motion.WaitRotation(2048);
    delay(50);
    if(Ultrasonic.Distance_cm() < 20){
        checkCircle[1] = 1;
        Robot.Motion.MoveForward(1000, 2000);
        Robot.Motion.MoveBackward(1000, 2000);
    }
    delay(50);
    Robot.Motion.RunLR(2000, -2000);
    Robot.Motion.WaitRotation(1970);
    delay(50);
    if(Ultrasonic.Distance_cm() < 20){
        checkCircle[2] = 1;
        Robot.Motion.MoveForward(1000, 2000);
        Robot.Motion.MoveBackward(1000, 2000);
    }
    delay(50);
    Robot.Motion.RunLR(2000, -2000);
    Robot.Motion.WaitRotation(2048);
    delay(50);
    if(Ultrasonic.Distance_cm() < 25){
        checkCircle[3] = 1;
        Robot.Motion.MoveForward(1000, 2000);
        Robot.Motion.MoveBackward(1000, 2000);
    }
    delay(50);
}


