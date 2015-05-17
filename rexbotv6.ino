#include "setup.h"
#include "ir.h"
#include "motor.h"
#include "pid.h"
#include "encoder.h"
#include "maze.h"
#include "drivesm.h"
#include "TimerOne.h"

extern IRSensorReading g_ir;
extern Motor g_motor;
extern Maze g_maze;

void setup() {
  set_pinmodes();
}

void loop() {
//  drive_right_wall_SM();
  drive_straight_only_SM();
}


