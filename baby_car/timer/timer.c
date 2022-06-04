/*
 * timer.c
 *
 * Created: 11/4/2021 5:09:20 PM
 *  Author: Florida
 */ 

#include "timer.h"


//static pointers for interrupt service routines callbacks
static void (*TIMER0_OVERFLOW_PTR)(void)  = 0;
static void (*TIMER0_ON_COMP_PTR)(void)   = 0;
static void (*TIMER1_OVERFLOW_PTR)(void)  = 0;
static void (*TIMER1_ON_COMP_A_PTR)(void) = 0;
static void (*TIMER1_ON_COMP_B_PTR)(void) = 0;
static void (*TIMER1_CAPT_PTR)(void)	  = 0;
static void (*TIMER2_OVERFLOW_PTR)(void)  = 0;
static void (*TIMER2_ON_COMP_PTR)(void)   = 0;





void TIMER0_init(TIMER0_config_t timer)
{
	switch (timer.timer_mode)
	{
	//TIMER RUNNING in normal mode
		case NORMAL_MODE:
			CLEAR_BIT(TCCR0,WGM01);
			CLEAR_BIT(TCCR0,WGM00);
			break;
		//TIMER Running In CTC Mode :
		// so OC0 (on compare) mode need to be defined -> (toggle, set, clear, or disconnected and running as a normal port).
		case CTC_MODE:
			CLEAR_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
			break;
		/*
			timer running in phase-correct PWM mode: so we need to define 
			if it's inverting(CLEAR on match while down-counting and SET while up-counting)
			or non-inverting (SET on match while down-counting and CLEAR while up-counting) one.
			*/
		case PHASECORRECT_PWM_MODE:
			SET_BIT(TCCR0,WGM00);
			CLEAR_BIT(TCCR0,WGM01);
			break;
		/*
		Timer running in fast PWM mode: so, we need to define if it's - inverting: SET on compare match and CLEAR at BOTTOM/TOP,
		- non-inverting : CLEAR on compare match and SET at BOTTOM/TOP
		*/ 
		case FAST_PWM_MODE:
			SET_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
			break;
				
		default://NORMAL_MODE is my default timer mode
			CLEAR_BIT(TCCR0,WGM01);
			CLEAR_BIT(TCCR0,WGM00);
	}//switch timer mode
			
	switch(timer.output_compare_mode)
	{
			case DISCONNECTED:
				CLEAR_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
				break;
			case NON_INVERTING_PWM:
				CLEAR_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
				break;
			case INVERTING_PWM:
				SET_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
				break;
			case TOGGLE_ON_COMPARE:
				SET_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
				break;
			case CLEAR_ON_COMPARE:
				CLEAR_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
				break;
			case SET_ON_COMPARE:
				SET_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
				break;
			default: //Disconnected is my default behavior
				CLEAR_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
	}//switch compare mode
	
	
	//Overflow interrupt masking option
	UPDATE_BIT(TIMSK,TOIE0,timer.overflow_int);			
	//On Compare Match interrupt masking option	
	UPDATE_BIT(TIMSK,OCIE0,timer.overflow_int);
	
				
				
	TCCR0 &= 0xf8;                       //clearing first three bits from previous data
	TCCR0 |= timer.clk_mode;              //updating their values 
					
}//function-end


void TIMER_set_callback(TIMER_INT_SOURCE_t src, void (*localFuncPTR)()){
	switch (src)
	{
	case TIMER0_OVERFLOW:
		TIMER0_OVERFLOW_PTR = localFuncPTR  ;
		break;
	case TIMER0_ON_COMP:
		TIMER0_ON_COMP_PTR = localFuncPTR ;
		break;
	case TIMER1_OVERFLOW:
		TIMER1_OVERFLOW_PTR = localFuncPTR ;
		break;
	case TIMER1_ON_COMP_A:
		TIMER1_ON_COMP_A_PTR = localFuncPTR;
		break;
	case TIMER1_ON_COMP_B:
		TIMER1_ON_COMP_B_PTR = localFuncPTR;
		break;
	case TIMER1_CAPT:
		TIMER1_CAPT_PTR = localFuncPTR;
		break;
	case TIMER2_OVERFLOW:
		TIMER2_OVERFLOW_PTR = localFuncPTR;
		break;
	case TIMER2_ON_COMP: 
		TIMER2_ON_COMP_PTR = localFuncPTR ;
		break;
	}
}

void TIMER0_stop(){
		TCCR0 &= 0xf8;                       //clearing first three bits from previous data
		TCCR0 |= 0;							  //updating their values

}

/************************************************************************/
/*                              TIMER 1                                 */
/************************************************************************/

void TIMER1_init(TIMER1_config_t timer){
	switch (timer.timer_mode)
	{
		case NORMAL:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case PC_PWM_8bit_0x00FF:
		SET_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case PC_PWM_9bit_0x01FF:
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case PC_PWM_10bit_0x03FF:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case CTC_OCR1A:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case FAST_PWM_8bit_0x00FF:
		SET_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case FAST_PWM_9bit_0x01FF:
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case FAST_PWM_10bit_0x03FF:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
		break;
		case PFC_PWM_ICR1:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case PFC_PWM_OCR1A:
		SET_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case PC_PWM_ICR1:
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case PC_PWM_OCR1A:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case CTC_ICR1:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case FAST_PWM_ICR1:
		CLEAR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case FAST_PWM_OCR1A:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		case xXxXxXxXx:
		default://normal mode is my default:
		CLEAR_BIT(TCCR1A,WGM10);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
	}
	
	//COMP A MODE :
	switch (timer.output_compare_modeA)
	{
		case DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;
		case TOGGLE_ON_COMPARE:
		SET_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;
		case CLEAR_ON_COMPARE:
		case NON_INVERTING_PWM: //Both options have the same bits configuration
		CLEAR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case SET_ON_COMPARE:
		case INVERTING_PWM: //Both options have the same bits configuration
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		default://my default is NORMAL mode
		CLEAR_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
	}
	
	//COMP B MODE :
	switch (timer.output_compare_modeB)
	{
		case DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;
		case TOGGLE_ON_COMPARE:
		SET_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;
		case CLEAR_ON_COMPARE:
		case NON_INVERTING_PWM: //Both options have the same bits configuration
		CLEAR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case SET_ON_COMPARE:
		case INVERTING_PWM: //Both options have the same bits configuration
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		default://my default is NORMAL mode
		CLEAR_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
	}
	
	//Timer1's clock prescaler
	TCCR1B &= 0xD8;                       //clearing first three bits' old values and the reserved 5bit is also cleared(as data sheet recommends)
	//0b1101 1000    -> 0xD8;
	TCCR1B |= timer.clk_mode;              //updating their values
	
	//Interrupt masking options
	UPDATE_BIT(TIMSK,TOIE1,timer.overflow_interrupt);
	UPDATE_BIT(TIMSK,OCIE1A,timer.comp_a_interrupt);
	UPDATE_BIT(TIMSK,OCIE1B,timer.comp_b_interrupt);
	UPDATE_BIT(TIMSK,TICIE1,timer.capt_interrupt);
	
}

void TIMER1_stop(){
	//Timer1's clock prescaler
	TCCR1B &= 0xD8;                       //clearing first three bits' old values and the reserved 5bit is also cleared(as data sheet recommends)
	//0b1101 1000    -> 0xD8;
	TCCR1B |= 0;              //updating their values
	
}

void TIMER1_ICU_trigger_edge(TIMER1_ICU_trigger_edge_t edge){
	switch(edge){
		case RISING:
			SET_BIT(TCCR1B,ICES1);
			break;
		case FALLING:
		default:
			CLEAR_BIT(TCCR1B,ICES1);
			break;
	}
}

void TIMER_interrupt_mask(TIMER_INT_SOURCE_t interr,TIMER_interrupt_mask_t state){
	switch (interr)
	{
		case TIMER0_OVERFLOW:
			switch (state)
			{
				case ENABLE_INTERRUPT:
				SET_BIT(TIMSK,TOIE1);
				break;
				case DISABLE_INTERRUPT:
				default:
				CLEAR_BIT(TIMSK,TOIE1);
				break;
			}
			break;
		case TIMER0_ON_COMP:
			switch (state)
			{
				case ENABLE_INTERRUPT:
				SET_BIT(TIMSK,OCIE0);
				break;
				case DISABLE_INTERRUPT:
				default:
				CLEAR_BIT(TIMSK,OCIE0);
				break;
			}
			break;
		case TIMER1_OVERFLOW:
			switch (state)
			{
				case ENABLE_INTERRUPT:
				SET_BIT(TIMSK,TOIE1);
				break;
				case DISABLE_INTERRUPT:
				default:
				CLEAR_BIT(TIMSK,TOIE1);
				break;
			}
			break;
		case TIMER1_ON_COMP_A:
			switch (state)
			{
				case ENABLE_INTERRUPT:
				SET_BIT(TIMSK,OCIE1A);
				break;
				case DISABLE_INTERRUPT:
				default:
				CLEAR_BIT(TIMSK,OCIE1A);
				break;
			}
			break;
		case TIMER1_ON_COMP_B:
			switch (state)
			{
				case ENABLE_INTERRUPT:
				SET_BIT(TIMSK,OCIE1B);
				break;
				case DISABLE_INTERRUPT:
				default:
				CLEAR_BIT(TIMSK,OCIE1B);
				break;
			}
			break;
		case TIMER1_CAPT:
			switch (state)
			{
				case ENABLE_INTERRUPT:
				SET_BIT(TIMSK,TICIE1);
				break;
				case DISABLE_INTERRUPT:
				default:
				CLEAR_BIT(TIMSK,TICIE1);
				break;
			}
			break;
		case TIMER2_OVERFLOW:
			switch (state)
			{
				case ENABLE_INTERRUPT:
				SET_BIT(TIMSK,TOIE2);
				break;
				case DISABLE_INTERRUPT:
				default:
				CLEAR_BIT(TIMSK,TOIE2);
				break;
			}
			break;
		case TIMER2_ON_COMP:
			switch (state)
			{
				case ENABLE_INTERRUPT:
				SET_BIT(TIMSK,OCIE2);
				break;
				case DISABLE_INTERRUPT:
				default:
				CLEAR_BIT(TIMSK,OCIE2);
				break;
			}
		break;
	}
}


/************************************************************************/
/*                               ISRs                                   */
/************************************************************************/
ISR(TIMER0_OVF_vect){
	
	if (TIMER0_OVERFLOW_PTR != 0)
	{
		TIMER0_OVERFLOW_PTR();
	}
}

ISR(TIMER0_COMP_vect){
	if (TIMER0_ON_COMP_PTR != 0)
	{
		TIMER0_ON_COMP_PTR();
	}
}

ISR(TIMER1_OVF_vect){
	if(TIMER1_OVERFLOW_PTR != 0)
	{
			TIMER1_OVERFLOW_PTR();	
	}
}

ISR(TIMER1_COMPA_vect){
	if(TIMER1_ON_COMP_A_PTR != 0)
	{
			TIMER1_ON_COMP_A_PTR();
	}
}

ISR(TIMER1_COMPB_vect){
	if (TIMER1_ON_COMP_B_PTR != 0)
	{
			TIMER1_ON_COMP_B_PTR();
	}
}

ISR(TIMER1_CAPT_vect){
	if (TIMER1_CAPT_PTR != 0)
	{
			TIMER1_CAPT_PTR();
	}
}

ISR(TIMER2_OVF_vect){
	if (TIMER2_OVERFLOW_PTR != 0)
	{
			TIMER2_OVERFLOW_PTR();
	}
}

ISR(TIMER2_COMP_vect){
	if (TIMER2_ON_COMP_PTR != 0)
	{
			TIMER2_ON_COMP_PTR();
	}
}