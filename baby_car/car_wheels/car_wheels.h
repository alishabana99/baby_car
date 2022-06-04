/*
 * car_wheels.h
 *
 * Created: 5/13/2022 1:21:04 AM
 *  Author: Florida
 */ 


#ifndef CAR_WHEELS_H_
#define CAR_WHEELS_H_

#include "dc_motor.h"


void CAR_WHEELS_init_motors(DC_MOTOR_t* r_motor, DC_MOTOR_t* l_motor);

void CAR_WHEELS_move_forward(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel);
void CAR_WHEELS_move_backward(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel);
void CAR_WHEELS_turn_right(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel);
void CAR_WHEELS_turn_left(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel);
void CAR_WHEELS_stop(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel);

void CAR_WHEELS_wheel_speed(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel, u8_t speed_percentage);
#endif /* CAR_WHEELS_H_ */