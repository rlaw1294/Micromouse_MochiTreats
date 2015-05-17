#include "maze.h"

enum direction_facing {NORTH, SOUTH, EAST, WEST};

extern IRSensorReading g_ir;

Cell::Cell() {
	this->north = 0;	
	this->south = 0;	
	this->east = 0;	
	this->west = 0;
	this->traversed = 0;
	this->dist = -1;
        this->floodfill_visited = false;
}


Maze::Maze() {
	this->index_x = 0;
	this->index_y = 15;
        this->mouse_direction = SOUTH;
        this->maze[index_y][index_x].traversed = 1;
        
        this->maze[15][0].south = 1;
        this->maze[15][0].west = 1;
        this->maze[15][0].east = 1;
        
        floodfill_next_x = 0;
        floodfill_next_y = 13;
}


void Maze::update_forwardonecell_position() { //also updates traversed
	int new_index_x = index_x;
	int new_index_y = index_y;

	if (mouse_direction == NORTH && new_index_y > 0) { 
		new_index_y -= 1; 
	}
	else if(mouse_direction == SOUTH && new_index_y < 15) {
		new_index_y += 1;
	}
	else if(mouse_direction == EAST && new_index_x < 15) {
		new_index_x += 1;
	}
	else if(mouse_direction == WEST && new_index_x > 0) { 
		new_index_x -= 1;
	}

    this->index_x = new_index_x;
    this->index_y = new_index_y;
    maze[index_y][index_x].traversed = true;
}

void Maze::update_turn90left_direction() {
  int temp_mouse_direction = this->mouse_direction;
  if (temp_mouse_direction == NORTH) this->mouse_direction = WEST;
  else if (temp_mouse_direction == WEST) this->mouse_direction = SOUTH;
  else if (temp_mouse_direction == SOUTH) this->mouse_direction = EAST;
  else if (temp_mouse_direction == EAST) this->mouse_direction = NORTH;
}

void Maze::update_turn90right_direction() {
  int temp_mouse_direction = this->mouse_direction;
  if (temp_mouse_direction == NORTH) this->mouse_direction = EAST;
  else if (temp_mouse_direction == EAST) this->mouse_direction = SOUTH;
  else if (temp_mouse_direction == SOUTH) this->mouse_direction = WEST;
  else if (temp_mouse_direction == WEST) this->mouse_direction = NORTH;
}

void Maze::maze_update_wall_sides() {
  float wall_tolerance = 50;
   if (g_ir.left > g_ir.left_wall_threshold - wall_tolerance) { //left wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).west = 1; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).north = 1; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).east = 1; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).south = 1; }
   }
   else { //no left wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).west = 0; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).north = 0; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).east = 0; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).south = 0; }
   }
   
   if (g_ir.right > g_ir.right_wall_threshold - wall_tolerance) { //right wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).east = 1; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).south = 1; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).west = 1; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).north = 1; }
   }
   else { //no right wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).east = 0; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).south = 0; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).west = 0; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).north = 0; }     
   }
}

void Maze::maze_update_wall_front() {
  //this function should only be called if we already know there is a wall in front
   if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).north = 1; }
   else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).east = 1; }
   else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).south = 1; }
   else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).west = 1; }  
}

//don't use this...prone to error
void Maze::maze_update_wall_middle() {
   float wall_tolerance = 50;
   if (g_ir.mid > g_ir.right_wall_threshold - wall_tolerance) { //middle wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).north = 1; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).east = 1; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).south = 1; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).west = 1; }
   }
   else {
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).north = 0; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).east = 0; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).south = 0; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).west = 0; }
   }
}

void Maze::maze_reset_cur_cell_walls() {
  (this->maze[this->index_y][this->index_x]).north = 0;
  (this->maze[this->index_y][this->index_x]).east = 0;
  (this->maze[this->index_y][this->index_x]).south = 0;
  (this->maze[this->index_y][this->index_x]).west = 0;
}

boolean Maze::is_cur_wall_right() {
     if (this->mouse_direction == NORTH && (this->maze[this->index_y][this->index_x]).east == 1) return true;
     else if (this->mouse_direction == EAST && (this->maze[this->index_y][this->index_x]).south == 1) return true;
     else if (this->mouse_direction == SOUTH && (this->maze[this->index_y][this->index_x]).west == 1) return true;
     else if (this->mouse_direction == WEST && (this->maze[this->index_y][this->index_x]).north == 1) return true;
     else return false;
}
boolean Maze::is_cur_wall_left() {
     if (this->mouse_direction == NORTH && (this->maze[this->index_y][this->index_x]).west == 1) return true;
     else if (this->mouse_direction == EAST && (this->maze[this->index_y][this->index_x]).north == 1) return true;
     else if (this->mouse_direction == SOUTH && (this->maze[this->index_y][this->index_x]).east == 1) return true;
     else if (this->mouse_direction == WEST && (this->maze[this->index_y][this->index_x]).south == 1) return true;
     else return false;
}  
boolean Maze::is_cur_wall_front() {
     if (this->mouse_direction == NORTH && (this->maze[this->index_y][this->index_x]).north == 1) return true;
     else if (this->mouse_direction == EAST && (this->maze[this->index_y][this->index_x]).east == 1) return true;
     else if (this->mouse_direction == SOUTH && (this->maze[this->index_y][this->index_x]).south == 1) return true;
     else if (this->mouse_direction == WEST && (this->maze[this->index_y][this->index_x]).west == 1) return true;
     else return false;
}
boolean Maze::is_cur_wall_back() {
     if (this->mouse_direction == NORTH && (this->maze[this->index_y][this->index_x]).south == 1) return true;
     else if (this->mouse_direction == EAST && (this->maze[this->index_y][this->index_x]).west == 1) return true;
     else if (this->mouse_direction == SOUTH && (this->maze[this->index_y][this->index_x]).north == 1) return true;
     else if (this->mouse_direction == WEST && (this->maze[this->index_y][this->index_x]).east == 1) return true;
     else return false;  
}

void Maze::print_maze_position() {
	Serial1.println("==== POSITION ====");
        Serial1.print("Coordinates: ");
        Serial1.print(this->index_x);
        Serial1.print(", ");
        Serial1.print(this->index_y);
        Serial1.println();
        Serial1.print("Direction: ");
        if (this->mouse_direction==WEST) Serial1.print("W");
        else if (this->mouse_direction==NORTH) Serial1.print("N");
        else if (this->mouse_direction==SOUTH) Serial1.print("S");
        else if (this->mouse_direction==EAST) Serial1.print("E");
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

void Maze::print_maze_walls_cur_cell() {
  Serial1.print("WNSE: ");
  if (maze[index_y][index_x].west) Serial1.print("1");
  else Serial1.print("0");
  if (maze[index_y][index_x].north) Serial1.print("1");
  else Serial1.print("0");
  if (maze[index_y][index_x].south) Serial1.print("1");
  else Serial1.print("0");
  if (maze[index_y][index_x].east) Serial1.print("1");
  else Serial1.print("0");  
  Serial1.println();
}

void Maze::print_cell(int x, int y) {
/* 
   WALL    *
   NO WALL `
   NORTH   ^
   WEST    <
   SOUTH   V
   EAST    >
   DIST   ##
   ex)
  ***
 ` > *
 ` 34*
  ```
*/
  if(maze[y][x].north) Serial1.print(" *** \n");
  else Serial1.print(" ``` \n");
  
  if(maze[y][x].west) Serial1.print("*");
  else Serial1.print("'");
  if (this->index_y==y && this->index_x==x) {
    if (this->mouse_direction==NORTH) Serial1.print("^ ");
    else if (this->mouse_direction==EAST) Serial1.print("> ");
    else if (this->mouse_direction==SOUTH) Serial1.print("< ");
    else if (this->mouse_direction==WEST) Serial1.print("V ");
  }
  if(maze[y][x].east) Serial1.print("*\n");
  else Serial1.print("'\n");
  
  if(maze[y][x].west) Serial1.print("*");
  else Serial1.print("'");
  Serial1.print(this->maze[y][x].dist/10);
  Serial1.print(this->maze[y][x].dist%10);
  if(maze[y][x].east) Serial1.print("*\n");
  else Serial1.print("'\n");  
  
  if(maze[y][x].south) Serial1.print(" *** \n");
  else Serial1.print(" ''' \n");  
}

void Maze::print_cur_cell() {
  print_cell(index_x, index_y);
}

void Maze::print_maze(){
	return;
}
