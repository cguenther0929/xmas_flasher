/******************************************************************************
*   FILE: timer.h
*
*   PURPOSE: Header file for timer.c
*
*   DEVICE: PIC18F66K22
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

#ifndef __TIMER_H_
#define __TIMER_H_

#include <xc.h>                 //Part specific header file
#include <stdint.h>
#include <stdbool.h>
#include "config.h"             //Project specific header file

/********************************************************
*FUNCTION: void Timer0Init(bool interrupts, uint8_t prescaler, uint8_t clksource )
*PURPOSE: To initialize timer 0.  Note: function set up so that
        timer will operate in 16 bit mode.
*PRECONDITION: Timer 1 is not initialized
*POSTCONDITION: Timer 1 is ready to use
*RETURN: Nothing
********************************************************/
void Timer0Init(uint8_t interrupts, uint8_t prescaler) ;

/********************************************************
*FUNCTION: void Timer0On( void )
*PURPOSE: To turn ON timer 0
*PRECONDITION: Timer 1 could be OFF
*POSTCONDITION: Timer 1 is now ON
*RETURN: Nothing
********************************************************/
void Timer0On( void );

void Timer2Init(uint8_t prescaler);  //TODO comment

void Timer2On ( void ); //TODO comment

#endif
/* END OF FILE */