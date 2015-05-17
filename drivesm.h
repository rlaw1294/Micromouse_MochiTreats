#ifndef DRIVESM_H
#define DRIVESM_H

#include <Arduino.h>
#include "setup.h"
#include "ir.h"
#include "motor.h"
#include "maze.h"
#include "floodfill.h"

void drive_right_wall_SM();
void drive_left_wall_SM();
void drive_straight_only_SM();
void drive_floodfill_maybe_SM();

#endif



