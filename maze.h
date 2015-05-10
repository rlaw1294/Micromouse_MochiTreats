#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <Arduino.h>


class Cell {
	public:
		boolean north;
		boolean south;
		boolean west;
		boolean east;
		boolean traversed;
		int dist;

		//functions
		Cell();
		void print_cell();
};

class Maze {
	private:
		Cell maze[16][16];
		int index_x; //x position
		int index_y; //y position
		int direction;

	public:
		Maze();
		void print_maze();
		void print_maze_position();
		void print_maze_traversed();

		// void update_maze_position();
		void update_forwardonecell_position();
};

#endif
