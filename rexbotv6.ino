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
extern boolean right_wall_randomvar;

void setup() {
  set_pinmodes();
}

void loop() {
  if (g_settings_decision==0) {
    drive_right_wall_SM();
    right_wall_randomvar = false;
//    debugger();
  }
  else if (g_settings_decision==1) {
    drive_left_wall_SM();
//    debugger();
  }
  else if (g_settings_decision==2) {
    drive_right_wall_SM();
    right_wall_randomvar = true;
    //    drive_straight_only_SM();  
//    debugger();
  }
  else {
    drive_floodfill_maybe_SM();
    delay(25);
//    debugger();
  }  
}


