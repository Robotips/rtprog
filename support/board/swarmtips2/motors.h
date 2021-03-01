
#ifndef MOTORS_H
#define MOTORS_H

#include <stdint.h>

void motors_init(void);
void motors_task(void);

// coders
int getC1(void);
int getC2(void);

// motors_init
void motors_start(void);
void motors_stop(void);

typedef enum {
    Motors_State_Stop,
    Motors_State_Linear,
    Motors_State_Rotate
} Motors_State;

void motors_moveForward(int16_t distance); // mm
void motors_rotate(int16_t angle);         // deg

void motors_setSpeed(int16_t speed);
Motors_State motors_state(void);

#endif // MOTORS_H
