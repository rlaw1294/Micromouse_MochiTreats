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
//    g_motor.Turn90Left();
    g_motor.ForwardOneCell();
    delay(500);
//    debugger();
  }
  else if (g_settings_decision==2) {
    drive_bluetooth_manual_SM();
//    drive_right_wall_SM();
//    right_wall_randomvar = true;
//    debugger();
  }
  else {
    drive_floodfill_maybe_SM();
//    debugger();
  }
}

