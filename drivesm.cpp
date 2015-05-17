#include "drivesm.h"

extern Motor g_motor;
extern Maze g_maze;

enum drive_right_wall_SM_states {INITDRIVERIGHT, FORWARD, TURN90L, TURN90RFORWARD};
static int drive_right_wall_SM_state = INITDRIVERIGHT;

void drive_right_wall_SM() {
	//transition
	switch(drive_right_wall_SM_state) {
	    case INITDRIVERIGHT:
	    	drive_right_wall_SM_state = INITDRIVERIGHT;
	    	break;
	    case FORWARD:
                if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right() && g_maze.is_cur_wall_back() && g_maze.is_cur_wall_left()) { g_maze.maze_reset_cur_cell_walls(); }
                if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=FORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=TURN90L;
                else drive_right_wall_SM_state=TURN90RFORWARD;
	    	break;
	    case TURN90L:
                if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right() && g_maze.is_cur_wall_back() && g_maze.is_cur_wall_left()) { g_maze.maze_reset_cur_cell_walls(); }
                if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=FORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=TURN90L;
                else drive_right_wall_SM_state=TURN90RFORWARD;
	    	break;
	    case TURN90RFORWARD:
                if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right() && g_maze.is_cur_wall_back() && g_maze.is_cur_wall_left()) { g_maze.maze_reset_cur_cell_walls(); }
                if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=FORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=TURN90L;
                else drive_right_wall_SM_state=TURN90RFORWARD;
	    	break;
	    default:
	    	break;
	    };

	//action
	switch(drive_right_wall_SM_state) {
	    case INITDRIVERIGHT:
                g_motor.Turn90Left();
                g_motor.Turn90Left();
                g_motor.ForwardOneCell();
                g_maze.maze[15][0].north=1;
                g_maze.maze[15][0].east=1;
                g_maze.maze[15][0].south=1;
                g_maze.maze[15][0].west=1;
                drive_right_wall_SM_state=FORWARD;
	    	break;
	    case FORWARD:
	    	g_motor.ForwardOneCell();
                debugger();
                delay(50);
	    	break;
	    case TURN90L:
                g_motor.Turn90Left();
                debugger();
                delay(50);
	    	break;
	    case TURN90RFORWARD:
                g_motor.Turn90Right();
                g_motor.ForwardOneCell();
                debugger();
                delay(50);
	    	break;
	    default:
	    	break;
	    };
}


enum drive_left_wall_SM_states {LWINITDRIVELEFT, LWFORWARD, LWTURN90R, LWTURN90LFORWARD};
static int drive_left_wall_SM_state = LWINITDRIVELEFT;

void drive_left_wall_SM() {
	//transition
	switch(drive_right_wall_SM_state) {
	    case LWINITDRIVELEFT:
	    	drive_left_wall_SM_state = LWINITDRIVELEFT;
	    	break;
	    case LWFORWARD:
                if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right() && g_maze.is_cur_wall_back() && g_maze.is_cur_wall_left()) { g_maze.maze_reset_cur_cell_walls(); }
                if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_left()) drive_right_wall_SM_state=LWFORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_left()) drive_right_wall_SM_state=LWTURN90R;
                else drive_left_wall_SM_state=LWTURN90LFORWARD;
	    	break;
	    case LWTURN90R:
                if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right() && g_maze.is_cur_wall_back() && g_maze.is_cur_wall_left()) { g_maze.maze_reset_cur_cell_walls(); }
                if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_left()) drive_right_wall_SM_state=LWFORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_left()) drive_right_wall_SM_state=LWTURN90R;
                else drive_left_wall_SM_state=LWTURN90LFORWARD;
	    	break;
	    case LWTURN90LFORWARD:
                if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right() && g_maze.is_cur_wall_back() && g_maze.is_cur_wall_left()) { g_maze.maze_reset_cur_cell_walls(); }
                if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_left()) drive_right_wall_SM_state=LWFORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_left()) drive_right_wall_SM_state=LWTURN90R;
                else drive_left_wall_SM_state=LWTURN90LFORWARD;
	    	break;
	    default:
	    	break;
	    };

	//action
	switch(drive_right_wall_SM_state) {
	    case LWINITDRIVELEFT:
                g_motor.Turn90Left();
                g_motor.Turn90Left();
                g_motor.ForwardOneCell();
                g_maze.maze[15][0].north=1;
                g_maze.maze[15][0].east=1;
                g_maze.maze[15][0].south=1;
                g_maze.maze[15][0].west=1;
                drive_left_wall_SM_state=FORWARD;
	    	break;
	    case LWFORWARD:
	    	g_motor.ForwardOneCell();
                debugger();
                delay(50);
	    	break;
	    case LWTURN90R:
                g_motor.Turn90Right();
                debugger();
                delay(50);
	    	break;
	    case LWTURN90LFORWARD:
                g_motor.Turn90Left();
                g_motor.ForwardOneCell();
                debugger();
                delay(50);
	    	break;
	    default:
	    	break;
	    };
}



enum drive_straight_only_SM_states {SOINIT, SOFORWARD};
static int drive_straight_only_SM_state = SOINIT;

void drive_straight_only_SM() {

	//transition
	switch(drive_right_wall_SM_state) {
	    case SOINIT:
	    	drive_straight_only_SM_state = SOINIT;
	    	break;
	    case SOFORWARD:
                drive_straight_only_SM_state=SOFORWARD;
	    	break;
	    default:
	    	break;
	    };

	//action
	switch(drive_right_wall_SM_state) {
	    case SOINIT:
                g_motor.Turn90Left();
                g_motor.Turn90Left();
                drive_right_wall_SM_state=SOFORWARD;
                delay(500);
	    	break;
	    case SOFORWARD:
	    	g_motor.ForwardOneCell();
                debugger();
                delay(500);
	    	break;
	    default:
	    	break;
	    };
}


enum drive_floodfill_maybe_SM_states {FFMINIT, FFMFORWARD};
static int drive_floodfill_maybe_SM_state = FFMINIT;

void drive_floodfill_maybe_SM() {

	//transition
	switch(drive_floodfill_maybe_SM_state) {
	    case FFMINIT:
	    	drive_floodfill_maybe_SM_state = FFMINIT;
	    	break;
	    case FFMFORWARD:
                maze_floodfill(0, 0, g_maze.index_x, g_maze.index_y, 0);
                //clear floodfilled cells
                for (int i=0; i<16; i++) {
                  for (int j=0; j<16; j++) {
                    (g_maze.maze[j][i]).dist = -1;
                  }  
                }                
                drive_floodfill_maybe_SM_state=FFMFORWARD;
	    	break;
	    default:
	    	break;
	    };

	//action
	switch(drive_floodfill_maybe_SM_state) {
	    case FFMINIT:
                g_motor.Turn90Left();
                g_motor.Turn90Left();
                g_motor.ForwardOneCell();
                g_maze.maze[15][0].north=1;
                g_maze.maze[15][0].east=1;
                g_maze.maze[15][0].south=1;
                g_maze.maze[15][0].west=1;
                drive_floodfill_maybe_SM_state=FFMFORWARD;
	    	break;
	    case FFMFORWARD:
                if (g_maze.floodfill_next_x == g_maze.index_x) {
                  if (g_maze.floodfill_next_y == g_maze.index_y+1) {
//                    g_motor.FaceSouth();
//                    g_motor.ForwardOneCell();
                  }
                  else if (g_maze.floodfill_next_y == g_maze.index_y-1) {
//                    g_motor.FaceNorth();
//                    g_motor.ForwardOneCell();
                  }
                }
                else if (g_maze.floodfill_next_y == g_maze.index_y) {
                  if (g_maze.floodfill_next_x == g_maze.index_x+1) {
//                    g_motor.FaceEast();
//                    g_motor.ForwardOneCell();
                  }
                  else if (g_maze.floodfill_next_x == g_maze.index_x-1) {
//                    g_motor.FaceWest();
//                    g_motor.ForwardOneCell();
                  }
                }
                else {
                  Serial1.println("STUPID");
                }
                  Serial1.print("X: ");
                  Serial1.print(g_maze.floodfill_next_y);
                  Serial1.print("   ");
                  Serial1.print("Y: ");
                  Serial1.print(g_maze.floodfill_next_x);
                  Serial1.println();                
                drive_floodfill_maybe_SM_state=FFMFORWARD;
                delay(200);
	    	break;
	    default:
	    	break;
	    };
}

