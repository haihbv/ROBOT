#include "robot.h"

Ultrasonic_Class Ultrasonic;

void Ultrasonic_Class::Init()
{
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
}

float Ultrasonic_Class::pingCm()
{
    float distance = 0;
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    distance = pulseIn(ECHO, HIGH, 30000) / 58.0;

    return distance;
}




