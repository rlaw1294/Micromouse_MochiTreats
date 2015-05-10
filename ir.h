#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include <TimerOne.h>

class IRSensorReading {
  public:
    //variables
    int left;
    int mid;
    int right;
    
    int control_left;
    int control_mid;
    int control_right;

    //functions
    void ir_pulse();
    void print_values();
    void print_control_values();
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


