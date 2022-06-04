/*
 * timer.h
 *
 * Created: 11/4/2021 5:09:05 PM
 *  Author: Florida
 */ 


#ifndef TIMER_H_
#define TIMER_H_

//INCLUDES 
#include "../utilities/bit_mask.h"
#include "../utilities/std_types.h"
#include "../interrupt_toolbox.h"

#ifndef F_CPU
#define  F_CPU 1000000UL
#endif

//registers
/* Timer 0 */
#define TCNT0   (*(volatile unsigned char*)0x52)  //Timer counter register 

#define TCCR0   (*(volatile unsigned char*)0x53) //Timer control register
#define FOC0    7		//force output compare
#define WGM00   6		//mode bit 
#define COM01   5		//,,
#define COM00   4		//compare match mode: these bits compare the OC0 pin behavior
#define WGM01   3		//mode bit
#define CS02    2		//,,
#define CS01    1		//,,
#define CS00    0		//CLK select 

#define TWCR    (*(volatile unsigned char*)0x56)
#define SPMCR   (*(volatile unsigned char*)0x57)
#define TIFR    (*(volatile unsigned char*)0x58)

#define TIMSK   (*(volatile unsigned char*)0x59)   //Counter interrupt register
#define TOIE0  0
#define OCIE0  1
#define TOIE1  2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2  6
#define OCIE2  7



#define OCR0    (*(volatile unsigned char*)0x5C)  //Continuously compared with the timer counter, a match can generate an - interrupt     - Wave form on the OC0 pin
/******************************************************************************/


/*TIMER 1*/
#define ICR1         (*(volatile unsigned short*)0x46)
#define ICR1L     (*(volatile unsigned char*)0x46)
#define ICR1H     (*(volatile unsigned char*)0x47)
#define OCR1B     (*(volatile unsigned short*)0x48)
#define OCR1BL    (*(volatile unsigned char*)0x48)
#define OCR1BH       (*(volatile unsigned char*)0x49)
#define OCR1A     (*(volatile unsigned short*)0x4A)
#define OCR1AL    (*(volatile unsigned char*)0x4A)
#define OCR1AH      (*(volatile unsigned char*)0x4B)
#define TCNT1       (*(volatile unsigned short*)0x4C)
#define TCNT1L    (*(volatile unsigned char*)0x4C)
#define TCNT1H    (*(volatile unsigned char*)0x4D)
#define TCCR1B       (*(volatile unsigned char*)0x4E)
#define TCCR1A        (*(volatile unsigned char*)0x4F)

#define SFIOR       (*(volatile unsigned char*)0x50)

#define OSCCAL       (*(volatile unsigned char*)0x51)

/******************************************************************************/
/* Timer 2 */

#define OCR2     (*(volatile unsigned char*)0x43)
#define TCNT2    (*(volatile unsigned char*)0x44)
#define TCCR2    (*(volatile unsigned char*)0x45)


/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

/* ASSR */
/* bits 7-4 reserved */
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0

/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/* WDTCR */
#define WDTCR    (*(volatile unsigned char*)0x41)
/* bits 7-5 reserved */
#define WDTOE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0



//MODE SELECTION
typedef enum {
	NORMAL_MODE = 0,
	PHASECORRECT_PWM_MODE,
	CTC_MODE,
	FAST_PWM_MODE,
	}TIMER0_mode_t;

//OC0 output states for all timer modes (normal, CTC, Phase-correct PWM, Fast PWM)
typedef enum {
	DISCONNECTED = 0,
	TOGGLE_ON_COMPARE,
	CLEAR_ON_COMPARE,
	SET_ON_COMPARE,
	INVERTING_PWM,
	NON_INVERTING_PWM,
	}TIMER_output_compare_mode_t;         //APPLIES for TIMER0, TIMER1, and TIMER2


//CLK SELECT
typedef enum {
	STOP_TIMER = 0, 
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNAL_FALLING_EDGE,
	EXTERNAL_RAISING_EDGE,
	
	}TIMER_clk_select_mode_t;      //APPLIES for TIMER0, TIMER1, and TIMER2
	
typedef enum{
	DISABLE_INTERRUPT= 0,
	ENABLE_INTERRUPT = 1
	}TIMER_interrupt_mask_t;         //APPLIES for TIMER0, TIMER1, and TIMER2

typedef enum {
	TIMER0_OVERFLOW,
	TIMER0_ON_COMP,
	TIMER1_OVERFLOW,
	TIMER1_ON_COMP_A,
	TIMER1_ON_COMP_B,
	TIMER1_CAPT,
	TIMER2_OVERFLOW,
	TIMER2_ON_COMP,
	}TIMER_INT_SOURCE_t;    //APPLIES for TIMER0, TIMER1, and TIMER2

typedef struct{
	TIMER0_mode_t timer_mode;
	TIMER_output_compare_mode_t output_compare_mode;
	TIMER_clk_select_mode_t clk_mode;
	TIMER_interrupt_mask_t overflow_int ;
	TIMER_interrupt_mask_t oc_int ;
}TIMER0_config_t;


//TIMER0  
void TIMER0_init(TIMER0_config_t timer);
void TIMER0_stop();
void TIMER_set_callback(TIMER_INT_SOURCE_t src, void (*localFuncPTR)(void)); //APPLIES for TIMER0, TIMER1, and TIMER2

/************************************************************************/
/*                              TIMER1                                  */
/************************************************************************/ 
typedef enum{
	NORMAL =0,
	PC_PWM_8bit_0x00FF,
	PC_PWM_9bit_0x01FF,
	PC_PWM_10bit_0x03FF,
	CTC_OCR1A,
	FAST_PWM_8bit_0x00FF,
	FAST_PWM_9bit_0x01FF,
	FAST_PWM_10bit_0x03FF,
	PFC_PWM_ICR1,
	PFC_PWM_OCR1A,
	PC_PWM_ICR1,
	PC_PWM_OCR1A,
	CTC_ICR1,
	xXxXxXxXx,
	FAST_PWM_ICR1,
	FAST_PWM_OCR1A,
	}TIMER1_mode_t;


typedef enum{
	RISING = 0,
	FALLING = 1,
	}TIMER1_ICU_trigger_edge_t;
	
typedef struct{
	TIMER1_mode_t timer_mode;
	TIMER_output_compare_mode_t output_compare_modeA;  
	TIMER_output_compare_mode_t output_compare_modeB; 
	
	TIMER_clk_select_mode_t clk_mode;
	TIMER_interrupt_mask_t overflow_interrupt;
	TIMER_interrupt_mask_t comp_a_interrupt;
	TIMER_interrupt_mask_t comp_b_interrupt;
	TIMER_interrupt_mask_t capt_interrupt;	
	
}TIMER1_config_t;


void TIMER1_init(TIMER1_config_t timer);
void TIMER1_stop();
void TIMER1_ICU_trigger_edge(TIMER1_ICU_trigger_edge_t edge);
void TIMER_interrupt_mask(TIMER_INT_SOURCE_t interr,TIMER_interrupt_mask_t state);

#endif /* TIMER_H_ */

