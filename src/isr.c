/******************************************************************************
*   FILE: isr.c
*
*   PURPOSE: Interrupt service routines are contained in this file.  This file contains
*           algorithms that pertain to the interrupt service routine.
*
*   DEVICE: pic12lf1501
*
*   COMPILER: Microchip XC8 v2.0
*
*   IDE: MPLAB X v5.10
*
*   TODO:  
*
*   NOTE:
*
******************************************************************************/

#include "isr.h"                //Include the header file for this module.

struct GlobalInformation gblinfo;

void Init_Interrupts( void ) {
    GIE     = 1;                //p68
}



void interrupt tc_int ( void ) {     
    
    if(TMR0IF){                                     //Timer 1 interrupt
        TMR0H = TMR0HIGH;                        //Load the high register for the timer -- looking for 1/100 of a tick1000ms
        TMR0L = TMR0LOW;                        //Load the low register for the timer
        
        Events10ms();
        
        if(gblinfo.tick10ms >= 9) {
            gblinfo.tick10ms = 0;               //Reset centi-tick1000monds
            Events100ms();
            if(gblinfo.tick100ms >= 9) {         //Once Second Reached
                gblinfo.tick100ms = 0;           //Reset 100 milliseconds ounter
                Events1000ms();                 //Look at events that are to happen every 1s
                if(gblinfo.tick1000ms >= 59)                     //We've ticked away one minute, so reset
                    gblinfo.tick1000ms = 0;                      //Reset seconds counter
                else
                    gblinfo.tick1000ms += 1;                     //Increment seconds counter
            }
            else {
                 gblinfo.tick100ms += 1;                         //Increment 100 millisecond timer 
            }
        }
        else {
            gblinfo.tick10ms += 1;                               //Increment 1 millisecond timer
        }

        TMR0IF = 0;                         //Software is responsible for clearing this flag
    }   /* END IF FOR TMR1IF */
    

}

void Events10ms(void) {                  //Keep routine slim!

}

void Events100ms(void) {                //Keep routine slim!
    
}

void Events1000ms(void) {

}


void DisableInterrupts( void ) {
    GIE     = 0;                //p68
}

void EnableInterrupts( void ) {
    GIE     = 1;                //p68
}