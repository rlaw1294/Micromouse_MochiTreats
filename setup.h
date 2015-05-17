#ifndef SETUP_H
#define SETUP_H

#include "ir.h"
#include "motor.h"
#include "encoder.h"
#include "maze.h"
#include <Arduino.h>
#include "TimerOne.h"
#include "drivesm.h"

void set_pinmodes();
void timer_interrupt();
void settings_SM();
void debugger();

#endif



