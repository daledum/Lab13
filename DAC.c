// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// March 13, 2014
// Port B bits 3-0 have the 4-bit DAC

#include "DAC.h"
#include "tm4c123gh6pm.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC (or 6 bits)
// Input: none
// Output: none
void DAC_Init(void){
//OUTPUT	
//DAC bit 3  PB3
//DAC bit 2  PB2
//DAC bit 1  PB1
//DAC bit 0  PB0
	GPIO_PORTB_AMSEL_R &= ~0x0F; // disable analog function on PB3-0
  GPIO_PORTB_PCTL_R &= ~0x00FFFFFF; // enable regular GPIO
  GPIO_PORTB_DIR_R |= 0x0F;    // outputs on PB3-0
  GPIO_PORTB_AFSEL_R &= ~0x0F; // regular function on PB3-0
  GPIO_PORTB_DEN_R |= 0x0F;    // enable digital on PB3-0
  GPIO_PORTB_DR8R_R |= 0x0F; //  can drive up to 8mA out though PB3-0

//INPUT ? you must connect PD3 to your DAC output
	GPIO_PORTD_AMSEL_R &= ~0x04; // disable analog function on PD3
  
  GPIO_PORTD_PCTL_R &= ~0x0000F00F; 	//no analog on Port D
  
	GPIO_PORTD_DIR_R &= ~0x04;   // input on PD3
  GPIO_PORTD_AFSEL_R &= ~0x04; // regular function on PD3
  GPIO_PORTD_DEN_R |= 0x04;    // enable digital on PD3
	
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
  GPIO_PORTB_DATA_R = data;
}
