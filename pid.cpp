#include "pid.h"

extern IRSensorReading g_ir;
extern Motor g_motor;

extern const int g_left_led;
extern const int g_right_led;

extern int g_encoderLeftA;
extern int g_encoderLeftB;
extern int g_encoderRightA;
extern int g_encoderRightB;

static const float Kp_ir = .3;
static const float Ki_ir = 0;
static const float Kd_ir = 0;

static const float Kp_v = 0;
static const float Ki_v = 0;
static const float Kd_v = 0;

static const float pid_timer_dt = 0.01; //polling interval
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
//    while ((micros()/1000)+pid_timer_ms < pid_timer_dt) {
      //do nothing!!! waiting until correct time slice has passed
//      Serial.println("GOOD PID IS WAITING\n");
//    }
//    pid_timer_ms = micros()/1000;
    //take in values now so i work with values from same exact time as possible
    int ir_error = 0;
    int cur_ir_left = g_ir.left;
    int cur_ir_right = g_ir.right;
    
    int cur_encoder_left_ticks = g_encoderLeftA;
    int cur_encoder_right_ticks = g_encoderRightA;
    
    
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
    float cur_vel_left = (cur_encoder_left_ticks - prev_encoder_left_ticks)/pid_timer_dt;
    float cur_vel_right = (cur_encoder_right_ticks - prev_encoder_right_ticks)/pid_timer_dt;
    prev_encoder_left_ticks = cur_encoder_left_ticks;
    prev_encoder_right_ticks = cur_encoder_right_ticks;
    float v_error_left = g_motor.BASEPWM - cur_vel_right;
    float v_error_right = g_motor.BASEPWM - cur_vel_right;
    
//    float total_v_error = Kp_v*v_err
    
    g_motor.SetLeftPWM(g_motor.BASEPWM + total_ir_error);
    g_motor.SetRightPWM(g_motor.BASEPWM - total_ir_error);

}


