#ifndef SETUP_H
#define SETUP_H

#include "ir.h"
#include "motor.h"
#include "encoder.h"
#include "maze.h"
#include <Arduino.h>
#include "TimerOne.h"

void set_pinmodes();
void timer_interrupt();
void debugger();

#endif



