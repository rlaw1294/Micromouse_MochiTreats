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
float p_error_ir_mid = 0;
float p_error_ir_left = 0;
float p_error_ir_right = 0;
float i_error_ir_mid = 0;
float i_error_ir_left = 0;
float i_error_ir_right = 0;
float prev_error_ir_mid = 0;
float prev_error_ir_left = 0;
float prev_error_ir_right = 0;
float d_error_ir_mid = 0;
float d_error_ir_left = 0;
float d_error_ir_right = 0;

unsigned long pid_v_timer_time = 0;
float p_error_ir_mid = 0;
float p_error_ir_left = 0;
float p_error_ir_right = 0;
float i_error_ir_mid = 0;
float i_error_ir_left = 0;
float i_error_ir_right = 0;
float prev_error_ir_mid = 0;
float prev_error_ir_left = 0;
float prev_error_ir_right = 0;
float d_error_ir_mid = 0;
float d_error_ir_left = 0;
float d_error_ir_right = 0;

void PID() {
/* IR PI */
/**
*   Error: Actual - Excpected)
*   IRSensorError = sensorError() * IRScalingFactor;
*   IRSensorErrorInteg += IRSensorError; 
*/
    // unsigned long ir_dt_ms = (micros()-pid_ir_timer_time)/1000;
    unsigned long ir_dt_ms = 1;
    float irscalingfactor = 1;
    float error_ir_mid = (g_ir.mid - g_ir.control_mid) * irscalingfactor;
    float error_ir_left = (g_ir.left - g_ir.control_left)* irscalingfactor; //( actual - expected)
    float error_ir_right = (g_ir.right - g_ir.control_right)* irscalingfactor;
    p_error_ir_mid = Kp_ir*error_ir_mid;
    p_error_ir_left = Kp_ir*error_left_ir;
    p_error_ir_right = Kp_ir*error_right_ir;
    i_error_ir_mid += Ki_ir*error_ir_mid*ir_dt_ms;
    i_error_ir_left += Ki_ir*error_left_ir*ir_dt_ms;
    i_error_ir_right += Ki_ir*error_right_ir*ir_dt_ms;
    d_error_ir_mid += Kd_ir*(error_ir_mid)/ir_dt_ms;
    d_error_ir_left += Kd_ir*(error_left_ir)/ir_dt_ms;
    d_error_ir_right += Kd_ir*(error_right_ir)/ir_dt_ms;
    float prev_error_ir_mid = error_ir_mid;
    float prev_error_ir_left = error_ir_left;
    float prev_error_ir_right = error_ir_right;

    if(g_ir.mid > g_ir.control_mid) { //too close to front wall
        digitalWrite(g_left_led, HIGH); //LEFT LED ON
        digitalWrite(g_right_led, HIGH); //RIGHT LED ON
    }
    else {
        if (g_ir.left > g_ir.control_left && g_ir.right < g_ir.control_right) { //too close to left so ROTATE RIGHT
          //left +error
          //right -error
            digitalWrite(g_left_led, HIGH); //LEFT LED ON
            digitalWrite(g_right_led, LOW); //too close to right so ROTATE RIGHT
        }
        else if (g_ir.left < g_ir.control_left && g_ir.right > g_ir.control_right) { //too close to right so ROTATE LEFT
            digitalWrite(g_left_led, LOW);
            digitalWrite(g_right_led, HIGH); //RIGHT LED ON
        }
    //        if (g_ir.right < 50) g_motor.Turn90Left();
        else {
            digitalWrite(g_left_led, LOW);
            digitalWrite(g_right_led, LOW);
        }
    }


}

