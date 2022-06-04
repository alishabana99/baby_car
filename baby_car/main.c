/*
 * test_project.c
 *
 * Created: 3/9/2022 1:17:38 PM
 * Author : Florida
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "IO.h"
#include <util/delay.h>
#include "timer.h"
#include "car_wheels.h"



int main(){
	
	///////////////////////TCRT5000 SENSOR pin configs /////////////////////////////
	IO_set_pin_direction(GROUPA,PIN_0,INPUT); //right
	IO_set_pin_direction(GROUPA,PIN_1,INPUT); //left
	
	
	
		/************** (START)                  RIGHT/LEFT MOTOR Configuration CODE *********************/

	DC_MOTOR_t right_motor;
	DC_MOTOR_t left_motor;
	
	//Defining and configuring my two motors right_motor and left_motor as the car's two wheels
	CAR_WHEELS_init_motors(&right_motor, &left_motor);
	
		/************** (END)                   RIGHT/LEFT MOTOR Configuration CODE *********************/

			/************** (START)            Timer1 Configs : Motor Timer *********************/

	 TIMER1_config_t motor_control_timer;
	 motor_control_timer.clk_mode = PRESCALER_256 ;
	 
	
	 motor_control_timer.output_compare_modeA = NON_INVERTING_PWM; 
	 motor_control_timer.output_compare_modeB = NON_INVERTING_PWM;
	 motor_control_timer.timer_mode = PC_PWM_ICR1;
	 TIMER1_init(motor_control_timer);

			/************** (END)            Timer1 Configs : Motor Timer *********************/


	while(1){
		if((IO_get_pin_data(GROUPA,PIN_0) == 0) && (IO_get_pin_data(GROUPA,PIN_1) == 1) ){  //the right sensor is out of the line
			
			CAR_WHEELS_turn_right(right_motor,left_motor);
			
		}
		else if ((IO_get_pin_data(GROUPA,PIN_0) == 1) && (IO_get_pin_data(GROUPA,PIN_1) == 0) ){ //the left sensor is out of the line
			
			CAR_WHEELS_turn_left(right_motor,left_motor);
			
		}
		else if ((IO_get_pin_data(GROUPA,PIN_0) == 1) && (IO_get_pin_data(GROUPA,PIN_1) == 1) ){  //Both sensors are on the line
			
			CAR_WHEELS_move_forward(right_motor,left_motor);
			
		}
		else if ((IO_get_pin_data(GROUPA,PIN_0) == 0) && (IO_get_pin_data(GROUPA,PIN_1) == 0) ){  //Both sensors are out of the line
			
			CAR_WHEELS_stop(right_motor,left_motor);
			
		}
		else{
			
		}
		
	}
}
