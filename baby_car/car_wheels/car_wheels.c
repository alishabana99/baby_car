/*
 * car_wheels.c
 *
 * Created: 5/13/2022 1:20:37 AM
 *  Author: Florida
 */ 

#include "car_wheels.h"
#define  SPEED 50

void CAR_WHEELS_init_motors(DC_MOTOR_t* r_motor, DC_MOTOR_t* l_motor){
	
		//EN pin
		l_motor->motor_pins.EN_pin_group = GROUPD;
		l_motor->motor_pins.EN_pin_number = PIN_4;
		//IN1 pin
		l_motor->motor_pins.IN1_pin_group = GROUPC;
		l_motor->motor_pins.IN1_pin_number = PIN_2;
		//IN2 pin
		l_motor->motor_pins.IN2_pin_group = GROUPC;
		l_motor->motor_pins.IN2_pin_number = PIN_3;
		//registers
		l_motor->top_reg = &ICR1;
		l_motor->wg_reg = &OCR1B;
		
		DC_MOTOR_init(*l_motor);
		(*(l_motor->top_reg)) = 625;
		DC_MOTOR_set_duty(*l_motor,SPEED);
		
		
		//EN pin
		r_motor->motor_pins.EN_pin_group = GROUPD;
		r_motor->motor_pins.EN_pin_number = PIN_5;
		//IN1 pin
		r_motor->motor_pins.IN1_pin_group = GROUPC;
		r_motor->motor_pins.IN1_pin_number = PIN_0;
		//IN2 pin
		r_motor->motor_pins.IN2_pin_group = GROUPC;
		r_motor->motor_pins.IN2_pin_number = PIN_1;
		//registers
		r_motor->top_reg = &ICR1;
		r_motor->wg_reg = &OCR1A;

		DC_MOTOR_init(*r_motor);
		(*(r_motor->top_reg)) = 625;
		DC_MOTOR_set_duty(*r_motor,SPEED);
}
void CAR_WHEELS_move_forward(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel){
	
		DC_MOTOR_set_duty(right_wheel,SPEED);
		DC_MOTOR_set_duty(left_wheel,SPEED);
		DC_MOTOR_set_direction(right_wheel,forward);
		DC_MOTOR_set_direction(left_wheel,forward);

	
}

void CAR_WHEELS_move_backward(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel){
				DC_MOTOR_set_duty(right_wheel,SPEED);
				DC_MOTOR_set_duty(left_wheel,SPEED);
				DC_MOTOR_set_direction(right_wheel,backward);
				DC_MOTOR_set_direction(left_wheel,backward);

		
}

void CAR_WHEELS_turn_right(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel){
			
				DC_MOTOR_set_duty(right_wheel,100); //application req : in order to make the car turn faster
				DC_MOTOR_set_direction(right_wheel,forward);
				DC_MOTOR_set_direction(left_wheel,off);
}


void CAR_WHEELS_turn_left(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel){

			DC_MOTOR_set_duty(right_wheel,100);  //application req :  in order to make the car turn faster
			DC_MOTOR_set_direction(right_wheel,off);
			DC_MOTOR_set_direction(left_wheel,forward);

}

void CAR_WHEELS_stop(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel){
	
			DC_MOTOR_set_direction(right_wheel,off);
			DC_MOTOR_set_direction(left_wheel,off);

	
}


void CAR_WHEELS_wheel_speed(DC_MOTOR_t right_wheel, DC_MOTOR_t left_wheel, u8_t speed_percentage){
		
		DC_MOTOR_set_duty(right_wheel,speed_percentage);
		DC_MOTOR_set_duty(left_wheel,speed_percentage);
		
}
