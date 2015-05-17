#include "drivesm.h"

extern Motor g_motor;
extern Maze g_maze;

enum drive_right_wall_SM_states {INITDRIVERIGHT, FORWARD, TURN90R, TURN90RFORWARD, TURN90LFORWARD};
static int drive_right_wall_SM_state = INITDRIVERIGHT;

void drive_right_wall_SM() {
	//transition
	switch(drive_right_wall_SM_state) {
	    case INITDRIVERIGHT:
	    	drive_right_wall_SM_state = INITDRIVERIGHT;
	    	break;
	    case FORWARD:
                if (!g_maze.is_cur_wall_left() && (millis()%2==0)) drive_right_wall_SM_state=TURN90LFORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=TURN90R;
                else if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=FORWARD;
                else drive_right_wall_SM_state=TURN90RFORWARD;
	    	break;
	    case TURN90R:
                if (!g_maze.is_cur_wall_left() && (millis()%2==0)) drive_right_wall_SM_state=TURN90LFORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=TURN90R;
                else if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=FORWARD;
                else drive_right_wall_SM_state=TURN90RFORWARD;
	    	break;
	    case TURN90RFORWARD:
                if (!g_maze.is_cur_wall_left() && (millis()%2==0)) drive_right_wall_SM_state=TURN90LFORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=TURN90R;
                else if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=FORWARD;
                else drive_right_wall_SM_state=TURN90RFORWARD;
	    	break;
	    case TURN90LFORWARD:
                if (!g_maze.is_cur_wall_left() && (millis()%2==0)) drive_right_wall_SM_state=TURN90LFORWARD;
	    	else if (g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=TURN90R;
                else if (!g_maze.is_cur_wall_front() && g_maze.is_cur_wall_right()) drive_right_wall_SM_state=FORWARD;
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
                drive_right_wall_SM_state=FORWARD;
                delay(500);
	    	break;
	    case FORWARD:
	    	g_motor.ForwardOneCell();
                debugger();
                delay(500);
	    	break;
	    case TURN90R:
                g_motor.Turn90Right();
                debugger();
                delay(500);
	    	break;
	    case TURN90RFORWARD:
                g_motor.Turn90Right();
                g_motor.ForwardOneCell();
                debugger();
                delay(500);
	    	break;
	    case TURN90LFORWARD:
                g_motor.Turn90Left();
                g_motor.ForwardOneCell();
                debugger();
                delay(500);
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
//                g_motor.Turn90Left();
//                g_motor.Turn90Left();
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

