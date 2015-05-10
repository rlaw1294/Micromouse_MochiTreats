#include "setup.h"
#include "ir.h"
#include "motor.h"
#include "pid.h"
#include "encoder.h"
#include "maze.h"
#include <TimerOne.h>

extern IRSensorReading g_ir;
extern Motor g_motor;
//extern Maze g_maze;

void setup() {
  set_pinmodes();
}

void loop() {
//  g_motor.Turn90Right();
//  g_motor.ForwardOneCell();
g_motor.MoveForward();
  debugger();
//g_motor.test_motor();
}

