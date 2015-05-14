#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include "setup.h"
#include "TimerOne.h"


class IRSensorReading {
  public:
    //variables
    int left;
    int mid;
    int right;
    
    int control_left;
    int control_mid;
    int control_right;

    int left_wall_threshold;
    int mid_wall_threshold;
    int right_wall_threshold;

    float wall_threshold; //leniency percentage in wall detection

    //functions
    void ir_pulse();
    void print_values();
    void print_control_values();
    void print_wall_threshold_values();
    void reset_control_values();
    
    //Constructor
    IRSensorReading();
        
  private:
    //variables
    bool flag_reading_middle; //1 if currently reading middle. 0 if currently reading sides

    //functions
    void read_mid();
    void read_sides();
};

#endif



