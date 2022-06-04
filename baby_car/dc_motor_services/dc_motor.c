/*
 * dc_motor.c
 *
 * Created: 5/12/2022 7:31:41 PM
 *  Author: Florida
 */ 

#include "dc_motor.h"

void DC_MOTOR_init(DC_MOTOR_t motor){
	IO_set_pin_direction(motor.motor_pins.EN_pin_group,motor.motor_pins.EN_pin_number,OUTPUT); //EN - PWM pin
	IO_set_pin_direction(motor.motor_pins.IN1_pin_group,motor.motor_pins.IN1_pin_number,OUTPUT); //IN1 - PWM pin
	IO_set_pin_direction(motor.motor_pins.IN2_pin_group,motor.motor_pins.IN2_pin_number,OUTPUT); //IN1 - PWM pin	
	

	
	
}

void DC_MOTOR_set_duty(DC_MOTOR_t motor,u8_t duty){
	
	(*(motor.wg_reg)) = ((u16_t)duty*((u16_t)((*(motor.top_reg))*2)-2))/(2*100);  
	  
	
	
}
void DC_MOTOR_set_direction(DC_MOTOR_t motor ,DC_MOTOR_direction_t dir){
	
	switch(dir){
			
		case forward:
			IO_set_pin_data(motor.motor_pins.IN1_pin_group,motor.motor_pins.IN1_pin_number,HIGH);
			IO_set_pin_data(motor.motor_pins.IN2_pin_group,motor.motor_pins.IN2_pin_number,LOW);
		break;
		
		case backward:
			IO_set_pin_data(motor.motor_pins.IN1_pin_group,motor.motor_pins.IN1_pin_number,LOW);
			IO_set_pin_data(motor.motor_pins.IN2_pin_group,motor.motor_pins.IN2_pin_number,HIGH);
		break;
				

		case off:
		default:
			IO_set_pin_data(motor.motor_pins.IN1_pin_group,motor.motor_pins.IN1_pin_number,LOW);
			IO_set_pin_data(motor.motor_pins.IN2_pin_group,motor.motor_pins.IN2_pin_number,LOW);
		break;

	}
	
}