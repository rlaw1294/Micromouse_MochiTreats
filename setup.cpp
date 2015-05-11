#include "setup.h"

/* --- GLOBALS ---- */
IRSensorReading g_ir;
Motor g_motor;
Maze g_maze;

//DEBUGGER + TIMER INTERRUPT
void timer_interrupt() {
  g_ir.ir_pulse();
}

const long DEBUGGER_PERIOD_MS = 500;
long debugger_timer_time = 0;
int timer_times_checked = 0;
void debugger() {
  timer_times_checked += 1;
  long time_elapsed_ms = millis() - debugger_timer_time;
  if (time_elapsed_ms > DEBUGGER_PERIOD_MS) { //times 1000 because timer is in microsenconds
    boolean time_elapsed = false;
    boolean ir = false;
    boolean ir_control = false;
    boolean ir_wall_threshold = false;
    boolean motor_speed = true;
    boolean motor_encoders = false;
    boolean maze = false;
    boolean maze_traversed = false;
    boolean maze_position = false;

    if (time_elapsed) {
      Serial1.print("Time Elapsed (ms):");
      Serial1.print(time_elapsed_ms/timer_times_checked);
      Serial1.println();
    }
    if (ir_control) g_ir.print_control_values();
    if (ir_wall_threshold) g_ir.print_wall_threshold_values();
    if (ir) g_ir.print_values();
    if (motor_encoders) print_encoder_values();
    if (motor_speed) g_motor.print_motor_values();
    if (maze) g_maze.print_maze();
    if (maze_traversed) g_maze.print_maze_traversed();
    if (maze_position) g_maze.print_maze_position();
    
    timer_times_checked = 0;
    debugger_timer_time = millis();
  }
}

//IR
extern const int IR_PULSE_RATE = 500;

//Motor
extern unsigned long motor_velocity_timer_time_ms = 0;

//Encoders
volatile double g_ticks_left = 0;
volatile double g_ticks_right = 0;
extern const double TICKS_ONE_CELL = 2000;
extern const double TICKS_90_TURN = 450;

//Maze


/* --- PINOUTS --- */
//motor driver logic pins
extern const int g_motor_left_cw = 22; 
extern const int g_motor_left_ccw = 23;
extern const int g_motor_right_cw = 20; 
extern const int g_motor_right_ccw = 21;

//teensy LED
extern const int g_teensy_led = 13;

//ir pins
extern const int g_ir_led_l = 12;
extern const int g_ir_led_m = 10;
extern const int g_ir_led_r = 11;

//ir phototransistor pins
extern const int g_ir_sensor_l = 17;
extern const int g_ir_sensor_m = 16;
extern const int g_ir_sensor_r = 15;

//encoders
extern const int g_encoderLeftA = 8;
extern const int g_encoderLeftB = 7;
extern const int g_encoderRightA = 5;
extern const int g_encoderRightB = 6;


//LED
extern const int g_left_led = 4;
extern const int g_right_led = 3;


void set_pinmodes() {  
  
  //teensy LED
  pinMode(g_teensy_led, OUTPUT);
  digitalWrite(g_teensy_led, HIGH);
  
  //motor
  pinMode(g_motor_left_cw, OUTPUT);
  pinMode(g_motor_left_ccw, OUTPUT);
  pinMode(g_motor_right_cw, OUTPUT);
  pinMode(g_motor_right_ccw, OUTPUT);
  
  analogWrite(g_motor_left_cw, 0);
  analogWrite(g_motor_left_ccw, 0);
  analogWrite(g_motor_right_cw, 0);
  analogWrite(g_motor_right_ccw, 0);
  
  //ir led
  pinMode(g_ir_led_l,OUTPUT);
  pinMode(g_ir_led_m,OUTPUT);
  pinMode(g_ir_led_r,OUTPUT);
  
  Timer1.initialize(IR_PULSE_RATE); //500 microseconds.... 1000microseconds per milisecond
  Timer1.start();  
  Timer1.attachInterrupt(timer_interrupt); //lul so cheap! ><"!... i hate this
  delay(1500);
  g_ir.reset_control_values();
  
  //ir phototransistors
  pinMode(g_ir_sensor_l,INPUT);
  pinMode(g_ir_sensor_m,INPUT);    
  pinMode(g_ir_sensor_r,INPUT);
 
 //encoders
  pinMode(g_encoderLeftA, INPUT);
  pinMode(g_encoderLeftB, INPUT);
  pinMode(g_encoderRightA, INPUT);
  pinMode(g_encoderRightB, INPUT);
  attachInterrupt(g_encoderLeftA, encoder_left_SM, CHANGE);
  attachInterrupt(g_encoderLeftB, encoder_left_SM, CHANGE);
  attachInterrupt(g_encoderRightA, encoder_right_SM, CHANGE);
  attachInterrupt(g_encoderRightB, encoder_right_SM, CHANGE);

  //LED
  pinMode(g_left_led, OUTPUT);
  pinMode(g_right_led, OUTPUT);
  digitalWrite(g_left_led, HIGH);
  digitalWrite(g_right_led, HIGH);

//  delay(3000);
  //Serial
  Serial.begin(9600);
  Serial1.begin(9600);
}

