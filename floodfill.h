#ifndef FLOODFILL_H
#define FLOODFILL_H

//THIS FUNCTIONS MODIFIES MAZE OBJECT!! BEWARE!

#include <Arduino.h>
#include "setup.h"
#include "maze.h"

void maze_floodfill(int cheatx, int cheaty, int x, int y, int cur_dist);

#endif



