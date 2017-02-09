/*----------------------------------------------------------------------------
 Switches C file
 *----------------------------------------------------------------------------*/
#include "switches.h"

void init_switches(void){
	//Start clocks for ports A and D
	RCC->AHB1ENR |= RCC_PORTA_MASK;
	RCC->AHB1ENR |= RCC_PORTB_MASK;
	RCC->AHB1ENR |= RCC_PORTC_MASK;
	//RCC->AHB1ENR |= RCC_PORTD_MASK;

	//Set pins to input mode:
	GPIOB->MODER |= MODER_0(SWITCH_1);
	GPIOC->MODER |= MODER_0(SWITCH_2);
	GPIOC->MODER |= MODER_0(SWITCH_3);
	//GPIOD->MODER |= MODER_0(SWITCH_4);

	//Write your code here


	//Set pins to pull-up mode
	GPIOB->PUPDR |= PUPDR_0(SWITCH_1);
	GPIOC->PUPDR |= PUPDR_0(SWITCH_2);
	GPIOC->PUPDR |= PUPDR_0(SWITCH_3);
	//GPIOD->PUPDR |= PUPDR_0(SWITCH_4);
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
