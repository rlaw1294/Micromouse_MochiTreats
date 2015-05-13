#include "encoder.h"

extern int g_encoderLeftA;
extern int g_encoderLeftB;
extern int g_encoderRightA;
extern int g_encoderRightB;

static int encoder_left_SM_state;
static int encoder_right_SM_state;

extern double g_ticks_left;
extern double g_ticks_right;

enum encoder_states {ZERO, ONE, TWO, THREE, FOUR};


void print_encoder_values() {
	Serial1.print("Encoders: ");
	Serial1.print(" L:");
	Serial1.print(g_ticks_left);
	Serial1.print(" R:");
	Serial1.print(g_ticks_right);
	Serial1.println();
}


void encoder_left_SM() {
	int next_state;
	if (digitalRead(g_encoderLeftA) == LOW && digitalRead(g_encoderLeftB) == LOW) next_state = ZERO;
	else if (digitalRead(g_encoderLeftA) == LOW && digitalRead(g_encoderLeftB) == HIGH) next_state = ONE;
	else if (digitalRead(g_encoderLeftA) == HIGH && digitalRead(g_encoderLeftB) == LOW) next_state = TWO;
	else if (digitalRead(g_encoderLeftA) == HIGH && digitalRead(g_encoderLeftB) == HIGH) next_state = THREE;
	else next_state = FOUR;

	//transition
	switch(encoder_left_SM_state) {
	    case ZERO:
	    	//find next state
	    	if (next_state == TWO) g_ticks_left++;
	    	if (next_state == ONE) g_ticks_left--;
	    	break;
	    case ONE:
	    	if (next_state == ZERO) g_ticks_left++;
	    	if (next_state == THREE) g_ticks_left--;
	    	break;
	    case TWO:
	    	if (next_state == THREE) g_ticks_left++;
	    	if (next_state == ZERO) g_ticks_left--;
	    	break;
	    case THREE:
	    	if (next_state == ONE) g_ticks_left++;
	    	if (next_state == TWO) g_ticks_left--;
	    	break;
	    default:
	    	break;
	    };

	//action
	switch(next_state) {
	    case ZERO:
	    	encoder_left_SM_state = ZERO;
	    	break;
	    case ONE:
	    	encoder_left_SM_state = ONE;
	    	break;
	    case TWO:
	    	encoder_left_SM_state = TWO;
	    	break;
	    case THREE:
	    	encoder_left_SM_state = THREE;
	    	break;
	    default:
	    	break;
	    };
}



void encoder_right_SM() {
	int next_state;
	if (digitalRead(g_encoderRightA) == LOW && digitalRead(g_encoderRightB) == LOW) next_state = ZERO;
	else if (digitalRead(g_encoderRightA) == LOW && digitalRead(g_encoderRightB) == HIGH) next_state = ONE;
	else if (digitalRead(g_encoderRightA) == HIGH && digitalRead(g_encoderRightB) == LOW) next_state = TWO;
	else if (digitalRead(g_encoderRightA) == HIGH && digitalRead(g_encoderRightB) == HIGH) next_state = THREE;
	else next_state = FOUR;

	//transition
	switch(encoder_right_SM_state) {
	    case ZERO:
	    	//find next state
	    	if (next_state == TWO) g_ticks_right++;
	    	if (next_state == ONE) g_ticks_right--;
	    	break;
	    case ONE:
	    	if (next_state == ZERO) g_ticks_right++;
	    	if (next_state == THREE) g_ticks_right--;
	    	break;
	    case TWO:
	    	if (next_state == THREE) g_ticks_right++;
	    	if (next_state == ZERO) g_ticks_right--;
	    	break;
	    case THREE:
	    	if (next_state == ONE) g_ticks_right++;
	    	if (next_state == TWO) g_ticks_right--;
	    	break;
	    default:
	    	break;
	    };

	//action
	switch(next_state) {
	    case ZERO:
	    	encoder_right_SM_state = ZERO;
	    	break;
	    case ONE:
	    	encoder_right_SM_state = ONE;
	    	break;
	    case TWO:
	    	encoder_right_SM_state = TWO;
	    	break;
	    case THREE:
	    	encoder_right_SM_state = THREE;
	    	break;
	    default:
	    	break;
	    };
}




