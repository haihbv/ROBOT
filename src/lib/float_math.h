#ifndef __FLOAT_MATH__
#define __FLOAT_MATH__
#include <Arduino.h>

inline float Abs(float num)
{
  return (num > 0) ? (num) : (-num);
}

inline float Constrain(float value, float min, float max)
{
  return (value < min) ? min : ((value > max) ? max : value);
}

inline float Max(float num1, float num2)
{
  return (num1 > num2) ? num1 : num2;
}

inline float Min(float num1, float num2)
{
  return (num1 < num2) ? num1 : num2;
}

inline float Map(float value, float in_min, float in_max, float out_min, float out_max)
{
  return out_min + (value - in_min) * (out_max - out_min) / (in_max - in_min);
}

#endif