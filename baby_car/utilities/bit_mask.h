/*
 * bit_mask.h
 *
 * Created: 10/15/2021 3:40:53 AM
 *  Author: Florida
 */ 


#ifndef BIT_MASK_H_
#define BIT_MASK_H_


typedef enum {
	BIT_0 = 0,
	BIT_1 = 1,
	BIT_2 = 2,
	BIT_3 = 3,
	BIT_4 = 4,
	BIT_5 = 5,
	BIT_6 = 6,
	BIT_7 = 7,
}BIT_NUMBER_t;

//FOR THE SAKE OF IO driver 
#define  UPDATE_BIT(reg,bit,lvl)    if(lvl){\
	SET_BIT(reg,bit);\
}\
else{\
	CLEAR_BIT(reg,bit);\
}

#define  SET_BIT(reg,bit)		reg |= (1<<bit)
#define  CLEAR_BIT(reg,bit)		reg &= ~(1<<bit)
#define  TOGGLE_BIT(reg,bit)	reg ^= (1<<bit)
#define  GET_BIT(reg,bit)		((reg & (1<<bit))>>bit)


//#define GET_BIT(REG,BIT) ((REG & (1<<BIT)) >> BIT)



#endif /* BIT_MASK_H_ */