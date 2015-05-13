#include "setup.h"
#include "ir.h"
#include "motor.h"
#include "pid.h"
#include "encoder.h"
#include "maze.h"
#include <TimerOne.h>

extern IRSensorReading g_ir;
extern Motor g_motor;
extern Maze g_maze;

void setup() {
  set_pinmodes();
}

void loop() {
  g_motor.Turn90Left();
  debugger();
  delay(1000);
  g_motor.Turn90Left();  
  debugger();
    delay(1000);
  g_motor.ForwardOneCell();
  debugger();
    delay(1000);
  g_motor.Turn90Right();
  debugger();
    delay(1000);
  g_motor.ForwardOneCell();
  debugger();
    delay(1000);
  g_motor.ForwardOneCell();
  debugger();
  delay(100000);
//g_motor.test_motor();
}


