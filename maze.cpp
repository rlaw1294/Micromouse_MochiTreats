#include "maze.h"

enum direction_facing {NORTH, SOUTH, EAST, WEST};

Cell::Cell() {
	this->north = 0;	
	this->south = 0;	
	this->east = 0;	
	this->west = 0;
	this->traversed = 0;
	this->dist = -1;
}

void Cell::print_cell(){
	Serial1.print(" N: ");
	Serial1.print(north);
	Serial1.print(" S: ");
	Serial1.print(south);
	Serial1.print(" W: ");
	Serial1.print(west);
	Serial1.print(" E: ");
	Serial1.print(east);
	Serial1.println();
}



Maze::Maze() {
	this->index_x = 0;
	this->index_y = 15;
}

// void Maze::update_position(int index_x, int index_y) {
// 	this->index_x = index_x;
// 	this->index_y = index_y;
// }

void Maze::update_forwardonecell_position() { //also updates traversed
	int new_index_x = index_x;
	int new_index_y = index_y;
	maze[index_y][index_x].traversed = true;


	if (direction == NORTH && this->index_y > 0) { 
		new_index_y = this->index_y - 1; 
	}
	else if(direction == SOUTH && this->index_y < 15) {
		new_index_y = this->index_y + 1;
	}
	else if(direction == EAST && this->index_x < 15) {
		new_index_x = this->index_x + 1;
	}
	else if(direction == WEST && this->index_x > 0) { 
		new_index_x = this->index_x - 1;
	}


    this->index_x = new_index_x;
	this->index_y = new_index_y;
}

void Maze::print_maze_position() {
	Serial1.println("==== POSITION ====");
	for(int y = 0; y < 16; ++y){ //row
		for(int x = 0; x < 16; ++x){ //column
			if (index_x == x && index_y == y) Serial1.print (" 1");
			else Serial1.print(" 0");
		}
		Serial1.println();
	}
	Serial1.println();
}

void Maze::print_maze_traversed() {
	Serial1.println("==== TRAVERSED ====");
	for(int y = 0; y < 16; ++y){ //row
		for(int x = 0; x < 16; ++x){ //column
			if (maze[y][x].traversed == true) Serial1.print (" 1");
			else Serial1.print(" 0");
		}
		Serial1.println();
	}
	Serial1.println();
}

void Maze::print_maze(){
	return;
}


