// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// September 30, 2013

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "..//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
  
// INPUT Port E init (input from 4 external switches) - switches=piano keys
//Piano key 3: G (783.991 Hz)  PE3
//Piano key 2: E (659.255 Hz)  PE2
//Piano key 1: D (587.330 Hz)  PE1
//Piano key 0: C (523.251 Hz)  PE0	
	GPIO_PORTE_AMSEL_R &= ~0x0F; // 3) disable analog function on PE2-0
  GPIO_PORTE_PCTL_R &= ~0x000000FF; // 4) enable regular GPIO
  GPIO_PORTE_DIR_R &= ~0x0F;   // 5) inputs on PE2-0
  GPIO_PORTE_AFSEL_R &= ~0x0F; // 6) regular function on PE2-0
  GPIO_PORTE_DEN_R |= 0x0F;    // 7) enable digital on PE2-0
	
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  //here I read all 4 switches and I return a single value
  return (GPIO_PORTE_DATA_R&0x0F);
}
