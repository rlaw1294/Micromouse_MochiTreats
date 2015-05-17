#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "pid.h"
#include "setup.h"
#include "maze.h"


class Motor {
  public:
      Motor();
      
      void SetLeftPWM(float pwm);
      void SetRightPWM(float pwm);
      
      void MoveForward();
      void ForwardOneCell();
      
      void Turn90Left();
      void Turn90Right();
      
      void FaceNorth();
      void FaceSouth();
      void FaceWest();
      void FaceEast();
      
      void Off();
      
      void RepositionWithFrontMiddleWall();
      
      
      void test_motor();
      void print_motor_values();
      
  public:
      int left_pwm;
      int right_pwm;
      int BASEPWM;
      int MAXPWM; //0-1023 value

      void MoveLeftForward();
      void MoveRightForward();
      void MoveLeftBackward();
      void MoveRightBackward();

      void SpinLeft();
      void SpinRight();
      
      void LeftOff();
      void RightOff();
};

#endif


