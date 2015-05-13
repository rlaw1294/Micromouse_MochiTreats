#include "ir.h"

extern int IR_PULSE_RATE;

extern int g_ir_led_l;
extern int g_ir_led_m;
extern int g_ir_led_r;

extern int g_ir_sensor_l;
extern int g_ir_sensor_m;
extern int g_ir_sensor_r;

IRSensorReading::IRSensorReading() {
    this->left = 0;
    this->mid = 0;
    this->right = 0;
    this->flag_reading_middle = 0;
    
    this->control_left = 0;
    this->control_mid = 0;
    this->control_right = 0;

    this->left_wall_threshold = 0;
    this->mid_wall_threshold = 0;
    this->right_wall_threshold = 0;

    this->wall_threshold = 0; 
}

void IRSensorReading::ir_pulse() {
    if (this->flag_reading_middle == 0) { this->read_sides(); this->flag_reading_middle=1; }
    else { this->read_mid(); this->flag_reading_middle=0; }
}

void IRSensorReading::reset_control_values() {
  delay(IR_PULSE_RATE*3); //delay so that we get new correct ir readings rather than old ones
  this->control_left = this->left;
  this->control_mid = this->mid;
  this->control_right = this->right;

  this->left_wall_threshold = this->control_left*(1-this->wall_threshold);
  this->mid_wall_threshold = this->control_mid*(1-this->wall_threshold);
  this->right_wall_threshold = this->control_right*(1-this->wall_threshold);
  print_control_values();
}

void IRSensorReading::read_mid() {
    this->mid = analogRead(g_ir_sensor_m);
    digitalWrite(g_ir_led_m, LOW);

    digitalWrite(g_ir_led_l, HIGH);
    digitalWrite(g_ir_led_r, HIGH);
}

void IRSensorReading::read_sides() {
    this->left = analogRead(g_ir_sensor_l);
    this->right = analogRead(g_ir_sensor_r);
    digitalWrite(g_ir_led_l, LOW);
    digitalWrite(g_ir_led_r, LOW);

    digitalWrite(g_ir_led_m, HIGH);
}

void IRSensorReading::print_values() {
    Serial1.print("IR: ");
    Serial1.print(" L:");
    Serial1.print(this->left);
    Serial1.print(" M:");
    Serial1.print(this->mid);
    Serial1.print(" R:");
    Serial1.print(this->right);
    Serial1.println();
}

void IRSensorReading::print_control_values() {
    Serial1.print("Control_IR: ");
    Serial1.print(" L:");
    Serial1.print(this->control_left);
    Serial1.print(" M:");
    Serial1.print(this->control_mid);
    Serial1.print(" R:");
    Serial1.print(this->control_right);
    Serial1.println();  
}

void IRSensorReading::print_wall_threshold_values() {
    Serial1.print("Wall_Threshold_IR: ");
    Serial1.print(" L:");
    Serial1.print(this->left_wall_threshold);
    Serial1.print(" M:");
    Serial1.print(this->mid_wall_threshold);
    Serial1.print(" R:");
    Serial1.print(this->right_wall_threshold);
    Serial1.println();
}




