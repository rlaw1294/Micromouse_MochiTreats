//this doesn't work, use the bst() in maze.cpp that eric made :)....fix this later, maybe

#ifndef FLOODFILL_H
#define FLOODFILL_H

//THIS FUNCTIONS MODIFIES MAZE OBJECT!! BEWARE!
//it does?... o-o. i don't know why i made that comment... hm... :D

#include <Arduino.h>
#include "setup.h"
#include "maze.h"

void maze_floodfill(int cheatx, int cheaty, int x, int y, int cur_dist);

#endif



