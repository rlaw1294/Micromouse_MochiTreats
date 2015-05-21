#include "drivesm.h"

extern Motor g_motor;
extern Maze g_maze;
extern IRSensorReading g_ir;

extern int g_settings_decision;
boolean right_wall_randomvar = false; //lol.


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
                if (right_wall_randomvar == true) {
                  unsigned long temp = micros();
                  if(temp%4==0) g_motor.ForwardOneCell(); 
                  if(temp%5==0) g_motor.Turn90Left();
                }
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
                delay(25);
	    	break;
	    case TURN90L:
                g_motor.Turn90Left();
                debugger();
                delay(25);
	    	break;
	    case TURN90RFORWARD:
                g_motor.Turn90Right();
                g_motor.ForwardOneCell();
                debugger();
                delay(25);
	    	break;
	    default:
	    	break;
	    };
}

//!! LEFT WALL DOESN'T WORK RIGHT NOW - DONO WHY, DEBUG LATER, OR DON'T CARE
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
                delay(25);
	    	break;
	    case LWTURN90R:
                g_motor.Turn90Right();
                debugger();
                delay(25);
	    	break;
	    case LWTURN90LFORWARD:
                g_motor.Turn90Left();
                g_motor.ForwardOneCell();
                debugger();
                delay(25);
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
                delay(50);
	    	break;
	    case SOFORWARD:
	    	g_motor.ForwardOneCell();
                debugger();
                delay(50);
	    	break;
	    default:
	    	break;
	    };
}


//wewt maze solving!!
enum drive_floodfill_maybe_SM_states {FFMINIT, FFMFORWARD};
static int drive_floodfill_maybe_SM_state = FFMINIT;

Coord next_cell;
void drive_floodfill_maybe_SM() {

	//transition
	switch(drive_floodfill_maybe_SM_state) {
	    case FFMINIT:
	    	drive_floodfill_maybe_SM_state = FFMINIT;
	    	break;
	    case FFMFORWARD:
                g_maze.BFS();
                next_cell = g_maze.nextCell();
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
//                g_maze.print_nice_maze();
                if (next_cell.x == g_maze.index_x) {
                  if (next_cell.y == g_maze.index_y+1) {
                    g_motor.FaceSouth();
                    g_motor.ForwardOneCell();
                  }
                  else if (next_cell.y == g_maze.index_y-1) {
                    g_motor.FaceNorth();
                    g_motor.ForwardOneCell();
                  }
                }
                else if (next_cell.y == g_maze.index_y) {
                  if (next_cell.x == g_maze.index_x+1) {
                    g_motor.FaceEast();
                    g_motor.ForwardOneCell();
                  }
                  else if (next_cell.x == g_maze.index_x-1) {
                    g_motor.FaceWest();
                    g_motor.ForwardOneCell();
                  }
                }
                else {
                  Serial1.println("STUPID");
                  g_settings_decision = 0;
                  drive_right_wall_SM_state = FORWARD;
                }
//                  Serial1.print("X: ");
//                  Serial1.print(next_cell.x);
//                  Serial1.print("   ");
//                  Serial1.print("Y: ");
//                  Serial1.print(next_cell.y);
//                  Serial1.println();       
                drive_floodfill_maybe_SM_state=FFMFORWARD;
	    	break;
	    default:
	    	break;
	    };
}



//So BM
enum drive_bluetooth_manual_SM_states {BMINIT, BMSETTINGS, BMCOMMANDS};
static int drive_bluetooth_manual_SM_state = BMINIT;

int straight_pwm_modifier = 0;
char bm_command = '0';
void drive_bluetooth_manual_SM() {
    g_ir.left_wall_threshold = 1024-200;
    g_ir.mid_wall_threshold = 1024-400;
    g_ir.right_wall_threshold = 1024-200;
    
	switch(drive_bluetooth_manual_SM_state) {
	    case BMINIT:           
                drive_bluetooth_manual_SM_state = BMCOMMANDS;
	    	break;
	    case BMSETTINGS:
                Serial1.println("Settings Mode");
                while (bm_command != 'q') {
                  if (Serial1.available() > 0) bm_command = Serial1.read();
                  else bm_command = '0';
                  
                  if (bm_command == 'e') {
                    straight_pwm_modifier+=5;
                    Serial1.print("\nPWM: ");
                    Serial1.print(g_motor.BASEPWM+straight_pwm_modifier);
                    Serial1.println();                    
                  }
                  else if (bm_command == 'r') {
                    straight_pwm_modifier-=5;
                    Serial1.print("\nPWM: ");
                    Serial1.print(g_motor.BASEPWM+straight_pwm_modifier);
                    Serial1.println();
                  }
                }
                bm_command = '0';
                drive_bluetooth_manual_SM_state=BMCOMMANDS;
	    	break;
	    case BMCOMMANDS:
                Serial1.println("Command Mode");
                while (bm_command != 'q') {
                  if (Serial1.available() > 0) bm_command = Serial1.read();
                  else bm_command = '0';
                  
                  //cell by cell
                  if (bm_command == 'w') {g_motor.ForwardOneCell();}
                  else if (bm_command == 'a') {g_motor.Turn90Left();}
                  else if (bm_command == 'd') {g_motor.Turn90Right();}
                  
                  //just go
                  else if (bm_command == 'i') {
                    g_motor.SetLeftPWM(g_motor.BASEPWM+straight_pwm_modifier);
                    g_motor.SetRightPWM(g_motor.BASEPWM+straight_pwm_modifier);                    
                    g_motor.MoveForward();
                    delay(50);
                    if (g_ir.mid > g_ir.mid_wall_threshold) { //don't crash please! backup!
                      g_motor.Off();
                      g_motor.SetLeftPWM(-.5*g_motor.BASEPWM); 
                      g_motor.SetRightPWM(-.5*g_motor.BASEPWM);
                      g_motor.MoveLeftBackward();
                      g_motor.MoveRightBackward();  
                      delay(700);
                      g_motor.Off();
                    }
                  }
                  else if (bm_command == 'j') {g_motor.SpinLeft();delay(50);}
                  else if (bm_command == 'l') {g_motor.SpinRight();delay(50);}
                  else g_motor.Off();
                }
                bm_command = '0';
                drive_bluetooth_manual_SM_state=BMSETTINGS;
	    	break;
	    default:
	    	break;
	    };
}

