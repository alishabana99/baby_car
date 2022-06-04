/*
 * dc_motor.h
 *
 * Created: 5/12/2022 7:31:25 PM
 *  Author: Florida
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "timer.h"
#include "IO.h"

typedef enum{
	
	off = 0,
	forward, 
	backward,
	
	}DC_MOTOR_direction_t;

typedef struct {
		IO_pin_group_t IN1_pin_group;
		IO_pin_number_t IN1_pin_number;
		IO_pin_group_t IN2_pin_group;
		IO_pin_number_t IN2_pin_number;
		IO_pin_group_t EN_pin_group;
		IO_pin_number_t EN_pin_number;
		
	}DC_MOTOR_pins_t;
	
typedef struct{
		DC_MOTOR_pins_t motor_pins;
		volatile unsigned short* top_reg;
		volatile unsigned short* wg_reg;
	}DC_MOTOR_t;
	
void DC_MOTOR_init(DC_MOTOR_t motor);
void DC_MOTOR_set_duty(DC_MOTOR_t motor,u8_t duty);
void DC_MOTOR_set_direction(DC_MOTOR_t motor ,DC_MOTOR_direction_t dir);




#endif /* DC_MOTOR_H_ */