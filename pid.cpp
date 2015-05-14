#include "pid.h"

extern IRSensorReading g_ir;
extern Motor g_motor;

extern boolean use_ir_pid;
extern boolean use_velocity_pid;

extern const int g_left_led;
extern const int g_right_led;

extern volatile double g_ticks_left;
extern volatile double g_ticks_right;

static const float Kp_ir = .15;
static const float Ki_ir = 0;
static const float Kd_ir = 0;

static const float Kp_v = 25;
static const float Ki_v = 0;
static const float Kd_v = 0;

static const float pid_timer_dt = .01; //polling interval in ms
unsigned long pid_timer_ms = 0;

int prev_ir_error = 0;
float integ_ir_error = 0;
int prev_encoder_left_ticks = 0;
int prev_encoder_right_ticks = 0;
float integ_v_error = 0;

void PID() {
    /* IR PID */
    /**
    *   IRSensorError = sensorError();
    *   IRSensorErrorInteg += IRSensorError; 
    */
    while ((micros()/1000)-pid_timer_ms < pid_timer_dt) {
      //do nothing!!! waiting until correct time slice has passed
//      Serial1.println("GOOD PID IS WAITING\n");
    }
    pid_timer_ms = micros()/1000;
    //take in values now so i work with values from same exact time as possible
    int ir_error = 0;
    int cur_ir_left = g_ir.left;
    int cur_ir_right = g_ir.right;
    
    int cur_encoder_left_ticks = g_ticks_left;
    int cur_encoder_right_ticks = g_ticks_right;
    
    
    //IR PID
    if (cur_ir_left > g_ir.left_wall_threshold && cur_ir_right > g_ir.right_wall_threshold) { //both walls
        ir_error = cur_ir_left - cur_ir_right; //left - right
        /* so left is positive error, right is negative error */
    }
    else if (cur_ir_left > g_ir.left_wall_threshold) { //left wall only: increase spd left, decrease spd right
        ir_error = (cur_ir_left - g_ir.control_left);
    }
    else if (cur_ir_right > g_ir.right_wall_threshold) { //right wall only: decrease spd left, increase spd right
        ir_error = -1*(cur_ir_right - g_ir.control_right);
    }
    else if (cur_ir_left < g_ir.left_wall_threshold && cur_ir_right < g_ir.right_wall_threshold) { //no walls, can't use IR
        ir_error = 0;
    }
    prev_ir_error = ir_error;
    
    integ_ir_error += ir_error*pid_timer_dt;
    float deriv_ir_error = (float)(ir_error - prev_ir_error)/pid_timer_dt;
    
    int total_ir_error = Kp_ir*ir_error + Ki_ir*integ_ir_error + Kd_ir*deriv_ir_error;
    
    
    //Velocity PID - DISABLE THIS DURING A TURN?! AND DURING A STOP!!!!
    //if (!NOT TURN)
    /** velocity is the derivative of position...
    *   position -> velocity -> acceleration
    *   target velocity is our base speed on our motor class
    */
    float cur_vel_left = (cur_encoder_left_ticks - prev_encoder_left_ticks);
    float cur_vel_right = (cur_encoder_right_ticks - prev_encoder_right_ticks);
    prev_encoder_left_ticks = cur_encoder_left_ticks;
    prev_encoder_right_ticks = cur_encoder_right_ticks;
    float v_error = cur_vel_left - cur_vel_right; //left is positive error, right is negative error
    
    //set_vel = 400 ticks; //pick a good speed
    //v_error_L = KpL*(set_vel - cur_vel_left)
    //v_error_R = KpR*(set_vel - cur_vel_right)
    //you don't need total 
    float total_v_error = Kp_v*v_error;

    if (use_ir_pid == false) total_ir_error = 0;
    if (use_velocity_pid == false) total_v_error = 0;
    g_motor.SetLeftPWM(g_motor.BASEPWM + total_ir_error - total_v_error);
    //g_motor.SetLeftPWM(total_ir_error - v_error_L);
    //g_motor.SetRightPWM(total_ir_error - v_error_R);
    
    g_motor.SetRightPWM(g_motor.BASEPWM - total_ir_error + total_v_error);
}



