#include "pid.h"

extern IRSensorReading g_ir;
extern Motor g_motor;

extern boolean use_ir_pid;
extern boolean use_velocity_pid;

extern const int g_left_led;
extern const int g_right_led;

extern volatile double g_ticks_left;
extern volatile double g_ticks_right;

static const double pid_timer_dt = 3; //polling interval in ms
static double cur_pid_timer_ms = 0;
static double prev_pid_timer_ms = 0;

//FOR IR CONTROL
static const double Kp_ir = .15;
static const double Ki_ir = 0;
static const double Kd_ir = 0;

int prev_ir_error = 0;
float integ_ir_error = 0;

//FOR VELOCITY CONTROL - 13, 1, 0
static const double Kp_v = 8; //get to sp without too much oscillation asap
static const double Ki_v = 0; //<1, super small
static const double Kd_v = 0; //*5 to 20
static const double SETPOINT_V = 5000/1000*pid_timer_dt; //Ticks per ms = ticks/sec * (sec/1000ms)

static int cur_encoder_left_ticks = 0;
static int cur_encoder_right_ticks = 0;
static int prev_encoder_left_ticks = 0;
static int prev_encoder_right_ticks = 0;
static double prev_v_error_left = 0;
static double prev_v_error_right = 0;
static double integ_v_error_left = 0;
static double integ_v_error_right = 0;

void PID() {
    /* IR PID */
    /**
    *   IRSensorError = sensorError();
    *   IRSensorErrorInteg += IRSensorError;
    */
//    cur_pid_timer_ms = (double)micros()/(double)1000;
    while (((double)micros()/(double)1000 - prev_pid_timer_ms) < pid_timer_dt) {
      //do nothing!!! waiting until correct time slice has passed
//      Serial1.println("GOOD PID IS WAITING\n");
//        Serial1.println((double)micros()/(double)1000 - prev_pid_timer_ms);
//        Serial1.print("AT+BAUD8"); //rex says to look into this :3
    }
    prev_pid_timer_ms = (double)micros()/(double)1000;
    //take in values now so i work with values from same exact time as possible
    double ir_error = 0;
    int cur_ir_left = g_ir.left;
    int cur_ir_right = g_ir.right;
    
    cur_encoder_left_ticks = g_ticks_left;
    cur_encoder_right_ticks = g_ticks_right;


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
    double deriv_ir_error = (double)(ir_error - prev_ir_error)/(double)pid_timer_dt;
    
    int total_ir_error = Kp_ir*ir_error + Ki_ir*integ_ir_error + Kd_ir*deriv_ir_error;
    
    
    //Velocity PID
    /** velocity is the derivative of position...
    *   position -> velocity -> acceleration
    *   target velocity is our base speed on our motor class
    */
    double cur_vel_left = (cur_encoder_left_ticks - prev_encoder_left_ticks);// /pid_timer_dt;
    double cur_vel_right = (cur_encoder_right_ticks - prev_encoder_right_ticks);// /pid_timer_dt;
    prev_encoder_left_ticks = g_ticks_left;
    prev_encoder_right_ticks = g_ticks_right;    
//    Serial1.println(cur_vel_left); //use to debug, make sure it matches setpoint well
    
    //get error
    double v_error_left = cur_vel_left - SETPOINT_V;
    double v_error_right = cur_vel_right - SETPOINT_V;
    
    
    //integral and derivative error
    integ_v_error_left += v_error_left;
    integ_v_error_right += v_error_right;
    double deriv_v_error_left = v_error_left - prev_v_error_left;
    double deriv_v_error_right = v_error_right - prev_v_error_right;
    prev_v_error_left = v_error_left;
    prev_v_error_right = v_error_right;
    
    //total error
    double total_v_error_left = Kp_v*v_error_left + Ki_v*integ_v_error_left + Kd_v*deriv_v_error_left;
    double total_v_error_right = Kp_v*v_error_right + Ki_v*integ_v_error_right + Kd_v*deriv_v_error_right;


//    if (use_ir_pid == false) total_ir_error = 0;
//    if (use_velocity_pid == false) { total_v_error_left = 0; total_v_error_right = 0; }
    g_motor.SetLeftPWM(total_ir_error - total_v_error_left);
    g_motor.SetRightPWM(-1*total_ir_error - total_v_error_right);
}



