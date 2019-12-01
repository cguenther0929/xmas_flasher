/******************************************************************************
 *   FILE: 
 *          isr.c
 *
 *   PURPOSE: 
 *          Interrupt service routines are contained in this file.  This file contains
 *          algorithms that pertain to the interrupt service routine.
 *
 *   TODO: 
 *
 *   NOTE:
 *
******************************************************************************/

#include "isr.h"                //Include the header file for this module.

struct GlobalInformation gblinfo;

void Init_Interrupts( void ) {
    GIE     = 1;                // p37 of 298
}



void __interrupt () my_isr_routine (void) {  
    
    if(T0IF){                                     //Timer 1 interrupt
        TMR0 = TMR0_REG_SETTING;
        gblinfo.event1ms = true;

        if(gblinfo.tick1ms > 4) {
            gblinfo.tick1ms = 0;
            gblinfo.event5ms = true;
            
            if (gblinfo.tick5ms >= 1)
            {
                gblinfo.tick5ms = 0;               
                gblinfo.event10ms = true;
                
                if(gblinfo.tick10ms >= 9) {
                    gblinfo.tick10ms = 0;            
                    gblinfo.event100ms = true;
                    
                    if(gblinfo.tick100ms >= 9) {        
                        gblinfo.tick100ms = 0;           
                        
                        gblinfo.event1000ms = true;
                        
                        if(gblinfo.tick1000ms >= 59)                    
                            gblinfo.tick1000ms = 0;                     
                        else
                            gblinfo.tick1000ms += 1;                    
                    }
                    else {
                        gblinfo.tick100ms += 1;                         
                    }
                }
                else {
                    gblinfo.tick10ms += 1;                              
                }
            }
            else {
                gblinfo.tick5ms++;

            }
        }
        else {
            gblinfo.tick1ms++;
        }

        T0IF = 0;                         //Software is responsible for clearing this flag
    }   /* END IF FOR TMR1IF */
    

}

/*
void DisableInterrupts( void ) {
    GIE     = 0;                //p68
}
*/

/*
void EnableInterrupts( void ) {
    GIE     = 1;                //p68
}
*/