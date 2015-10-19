// Lab13.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// edX Lab 13 
// Daniel Valvano, Jonathan Valvano
// March 13, 2014
// Port B bits 3-0 have the 4-bit DAC
// Port E bits 3-0 have 4 piano keys

#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);

unsigned long input,previous;

int main(void){ volatile unsigned long retard;
	
	// Real Lab13 
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz
  //PortE used for piano keys, PortB used for DAC 
  
	SYSCTL_RCGC2_R |= 0x1A;      // ports B D F, in main(), you must connect PD3 to your DAC output
	retard = SYSCTL_RCGC2_R;      	
	
  Sound_Init(); // initialize SysTick timer and DAC
  Piano_Init();
  EnableInterrupts();  // enable after all initialization are done
  previous = Piano_In();
	while(1){                
// input from keys to select tone
		
		input = Piano_In(); 
    if(input&&(previous==0)) // just pressed     
      {				
			  if(input==0x01)  //Piano key 0 pressed: : C (523.251 Hz)  PE0	
           { Sound_Tone(4778);   	//80000000/(16*523.251)=9556/2=4778
						 }									
      
				else { 
				       if(input==0x02) //		Piano key 1 pressed: D (587.330 Hz)  PE1			
							 { Sound_Tone(4257); //80000000/(16*587.330)=8513/2=4257 
								 }
								 else {
				            if(input==0x04) //Piano key 2 pressed: E (659.255 Hz)  PE2
										{ Sound_Tone(3792); //80000000/(16*659.255)=7584/2=3792
											}
										else {  if(input==0x08) ////Piano key 3 pressed: G (783.991 Hz)  PE3								 
										         { Sound_Tone(3189); //80000000/(16*783.991)=6378/2=3189
															 }
										     } 
								} 
						} 
				}
  	
		if(input&&previous) 
		{ 
			if(input==0x01)  
           { Sound_Tone(4778);
						 }									
      
				else { 
					     
				       if(input==0x02) 		
							 { Sound_Tone(4257);
								}
								 else {
				            if(input==0x04) 
										{ Sound_Tone(3792); 
											}
											 
										else {  if(input==0x08) 					 
										         { Sound_Tone(3189);
															 }
										        else
				                          {Sound_Off();

																	} 
										    } 
											} 
						} 
				
		
		}
			
		if(previous&&(input==0)){ // just released     
      Sound_Off(); 
    }
    previous = input; 
    delay(10);  // remove switch bounce    
  }		
            
}

// Inputs: Number of msec to delay
// Outputs: None
void delay(unsigned long msec){ 
  unsigned long count;
  while(msec > 0 ) {  // repeat while there are still delay
    count = 16000;    // about 1ms
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    msec--;
  }
}


