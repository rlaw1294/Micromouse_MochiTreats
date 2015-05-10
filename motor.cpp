#include "motor.h"

extern Maze g_maze;
enum direction_facing {NORTH, SOUTH, EAST, WEST};


extern int g_motor_left_cw;
extern int g_motor_left_ccw;
extern int g_motor_right_cw;
extern int g_motor_right_ccw;

extern volatile double g_ticks_left;
extern volatile double g_ticks_right;

extern const double TICKS_ONE_CELL;
extern const double TICKS_90_TURN;

extern unsigned long motor_velocity_timer_time_ms;

/* --- PUBLICS --- */
Motor::Motor()
{
    this->MAXPWM = .30*255;
    this->BASEPWM = .75*(this->MAXPWM);
    this->left_pwm = this->MAXPWM;
    this->right_pwm = this->MAXPWM;
}

void Motor::MoveForward() {
  if (this->left_pwm >= 0) { MoveLeftForward(); }
  else { MoveLeftBackward(); }
  if (this->right_pwm >=0) { MoveRightForward(); }
  else { MoveRightBackward(); }
  IR_PID();
}

void Motor::ForwardOneCell() {
  double end_ticks_left = g_ticks_left + TICKS_ONE_CELL;
  double end_ticks_right = g_ticks_right + TICKS_ONE_CELL;
  while(g_ticks_left < end_ticks_left || g_ticks_right < end_ticks_right) {
    MoveForward(); 
  }
  g_maze.update_forwardonecell_position();
  Off();
//  delay(1000);
}

void Motor::Turn90Left() {
  double end_ticks_left = g_ticks_left - TICKS_90_TURN;
  double end_ticks_right = g_ticks_right + TICKS_90_TURN;
  while(g_ticks_left > end_ticks_left || g_ticks_right < end_ticks_right) {
    SpinLeft(); 
  }
//  Serial1.println("Spun 90 left");
}

void Motor::Turn90Right() {
  double end_ticks_left = g_ticks_left + TICKS_90_TURN;
  double end_ticks_right = g_ticks_right - TICKS_90_TURN;
  while(g_ticks_left < end_ticks_left || g_ticks_right > end_ticks_right) {
    SpinRight();
  }
//  Serial1.println("Spun 90 right");
}

void Motor::Off() {
    LeftOff();
    RightOff();
}

void Motor::test_motor() {
  ForwardOneCell();
//  IR_PID();
  Off();
  delay(2000);
  Turn90Left();
  Off();
  delay(2000);
  Turn90Right();
  Off();
  delay(2000);
  Off();
  delay(1000);
}

void Motor::print_motor_values() {
    Serial1.print("Motor Speed: L: ");
    Serial1.print(this->left_pwm);
    Serial1.print(" R: ");
    Serial1.print(this->right_pwm);
    Serial1.println();
}



/* --- PRIVATES --- */
void Motor::SetLeftPWM(float pwm) {
  if (pwm > MAXPWM) pwm = MAXPWM;
  else if (pwm < -1*MAXPWM) pwm = -1*MAXPWM;
  this->left_pwm = pwm;
}

void Motor::SetRightPWM(float pwm) {
  if (pwm > MAXPWM) pwm = MAXPWM;
  else if (pwm < -1*MAXPWM) pwm = -1*MAXPWM;
  this->right_pwm = pwm;
}




void Motor::MoveLeftForward() {
  if (this->left_pwm < 0) { Serial1.println("negative pwm ... but leftforward called?!"); }
  else {
    analogWrite(g_motor_left_cw, this->left_pwm);
    analogWrite(g_motor_left_ccw, 0); 
  }
}

void Motor::MoveRightForward() {
  if (this->right_pwm < 0) { Serial1.println("negative pwm ... but rightforward called?!"); }
  else {
    analogWrite(g_motor_right_cw, this->right_pwm);
    analogWrite(g_motor_right_ccw, 0);
  }
}

void Motor::MoveLeftBackward() {
  if (this->left_pwm > 0) { Serial1.println("positive pwm ... but leftback called?!"); }
  else {
    analogWrite(g_motor_left_cw, 0); 
    analogWrite(g_motor_left_ccw, abs(this->left_pwm));
  }
}

void Motor::MoveRightBackward() {
  if (this->right_pwm > 0) { Serial1.println("positive pwm ... but rightback called?!"); }
  else {
    analogWrite(g_motor_right_cw, 0);
    analogWrite(g_motor_right_ccw, abs(this->right_pwm));
  }
}




void Motor::SpinLeft() {
  analogWrite(g_motor_left_cw, 0);
  analogWrite(g_motor_left_ccw, this->BASEPWM*.5);
  analogWrite(g_motor_right_cw, this->BASEPWM*.5);
  analogWrite(g_motor_right_ccw, 0);
}

void Motor::SpinRight() {
  analogWrite(g_motor_left_cw, this->BASEPWM*.5);
  analogWrite(g_motor_left_ccw, 0);
  analogWrite(g_motor_right_cw, 0);
  analogWrite(g_motor_right_ccw, this->BASEPWM*.5);
}

void Motor::LeftOff() {
    analogWrite(g_motor_left_cw, 0);
    analogWrite(g_motor_left_ccw, 0);
}

void Motor::RightOff() {
  analogWrite(g_motor_right_cw, 0);
  analogWrite(g_motor_right_ccw, 0);
}


