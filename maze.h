#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <Arduino.h>
#include "setup.h"

//#include <iostream>
//#include <vector>
//#include <string.h>
#include <queue>

using namespace std;



struct Coord
{
    int x, y;
};

class Cell {
	public:
		boolean north;
		boolean south;
		boolean west;
		boolean east;
		boolean traversed;
                
                boolean floodfill_visited;
		int dist;

		//functions
		Cell();
};

class Maze {
	public:
		Cell maze[16][16];
		int index_x; //x position
		int index_y; //y position
		int mouse_direction;
                int floodfill_next_x;
                int floodfill_next_y;

	public:
		Maze();
		void print_maze();
		void print_maze_position();
		void print_maze_traversed();
                void print_cell(int x, int y);
                void print_maze_walls_cur_cell();
                void print_cur_cell();
                
                //functions to return whether or not there is a wall in each direction relative to the current mouse direction and cell position
                boolean is_cur_wall_right();
                boolean is_cur_wall_left();
                boolean is_cur_wall_front();
                boolean is_cur_wall_back();

                //position updates
		void update_forwardonecell_position();
                void update_turn90left_direction();
                void update_turn90right_direction();
                
                //updating walls
                void maze_update_wall_sides();
                void maze_update_wall_front();
                void maze_update_wall_middle();
                void maze_reset_cur_cell_walls();
                
                //Maze Solving
//                void BFShelper( int nmaze[16][16], int x, int y, int v, queue<Coord>& c );
//                Coord nextCellRecurse( int x, int y );
//                Coord nextCell( );
//                void BFS();
//                void print_nice_maze();
};

#endif

