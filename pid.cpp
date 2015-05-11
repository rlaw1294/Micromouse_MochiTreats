#include "pid.h"

extern IRSensorReading g_ir;
extern Motor g_motor;

extern const int g_left_led;
extern const int g_right_led;

static const int Kp_ir = 1;
static const int Ki_ir = 1;
static const int Kd_ir = 1;

static const int Kp_v = 1;
static const int Ki_v = 1;
static const int Kd_v = 1;


unsigned long pid_ir_timer_time = 0;
int prev_ir_error = 0;

void PID() {
/* IR PI */
/**
*   IRSensorError = sensorError();
*   IRSensorErrorInteg += IRSensorError; 
*/
    //take in values now so i work with values from same exact time as possible
    int ir_error = 0;
    int cur_ir_left = g_ir.left;
    int cur_ir_mid = g_ir.mid;
    int cur_ir_right = g_ir.right;

    //IR PID
    if (cur_ir_left > g_ir.left_wall_threshold && cur_ir_right < g_ir.right_wall_threshold) { //both walls
        ir_error = cur_ir_left - cur_ir_right; //left - right
        /* so left is positive error, right is negative error */
    }
    else if (cur_ir_left > g_ir.left_wall_threshold) { //left wall only: increase spd left, decrease spd right
        ir_error = 2*(g_ir.control_left - cur_ir_left);
    }
    else if (cur_ir_right > g_ir.right_wall_threshold) { //right wall only: decrease spd left, increase spd right
        ir_error = 2*(g_ir.control_right - cur_ir_right);
    }
    else { //no walls, can't use IR
        ir_error = 0;
    }

    SetLeftPWM(g_motor.BASEPWM + ir_error);
    SetRightPWM(g_motor.BASEPWM - ir_error);

}

