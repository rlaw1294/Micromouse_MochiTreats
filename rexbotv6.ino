#include "setup.h"
#include "ir.h"
#include "motor.h"
#include "pid.h"
#include "encoder.h"
#include "maze.h"
#include "drivesm.h"
#include "TimerOne.h"
#include "floodfill.h"

extern IRSensorReading g_ir;
extern Motor g_motor;
extern Maze g_maze;

extern int g_settings_decision;

void setup() {
  set_pinmodes();
}

void loop() {
  if (g_settings_decision==0) {
    drive_right_wall_SM();
    debugger();
  }
  else if (g_settings_decision==1) {
    drive_left_wall_SM();
    debugger();
  }
  else if (g_settings_decision==2) {
    drive_straight_only_SM();  
    debugger();
  }
  else {
//    drive_right_wall_SM();
    debugger();
  }  
//g_motor.MoveForward();
}


