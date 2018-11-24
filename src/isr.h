/******************************************************************************
*   FILE: isr.h
*
*   PURPOSE: Header file for isr.c
*
*   DEVICE: PIC18F66K22
*
*   COMPILER: Microchip XC8 v2.0
*
*   IDE: MPLAB X v5.10
*
*   TODO:  Need to clean this file up
*
*   NOTE:
*
******************************************************************************/

#ifndef __ISR_H_
#define __ISR_H_

#include <xc.h>                 //Part specific header file
#include <stdint.h>
#include <stdbool.h>
#include "config.h"             //Project specific header file
#include "main.h"
#include "struct.h"

/********************************************************
*FUNCTION: void Init_Interrupts( void )
*PURPOSE: This function is responsible for initializing
    interrupt features
*PRECONDITION: Desired interrupts not yet supports
*POSTCONDITION: Desired interrupts now enabled
*RETURN: Nothing
********************************************************/
void Init_Interrupts( void );

void interrupt tc_int ( void );  //TODO need to comment

/********************************************************
*FUNCTION: void DisableInterrupts( void )
*PURPOSE: Will prevent interrupts from firing
*PRECONDITION: Interrupts may be enabled.
*POSTCONDITION: Interrupts now disabled.
*RETURN: Nothing
********************************************************/
void DisableInterrupts( void );

/********************************************************
*FUNCTION: void EnableInterrupts( void )
*PURPOSE: Enable high and low priority interrupts
*PRECONDITION: Interrupts may be disabled.
*POSTCONDITION: Interrupts now enabled.
*RETURN: Nothing
********************************************************/
void EnableInterrupts( void );

/********************************************************
*FUNCTION: void Events10ms(void)
*PURPOSE: Runs on a 1 millisecond interrupt boundary.  
*       This routine shall be kept slim!
*PRECONDITION: Interrupts and time base should be setup
*POSTCONDITION: Action taken on a 1ms boundary
*RETURN: Nothing
********************************************************/
void Events10ms(void);  

/********************************************************
*FUNCTION: void Events100ms(void)
*PURPOSE: Runs on a 100 millisecond interrupt boundary.  
*       This routine shall be kept slim!
*PRECONDITION: Interrupts and time base should be setup
*POSTCONDITION: Action taken on a 100ms boundary
*RETURN: Nothing
********************************************************/
void Events100ms(void); 

/********************************************************
*FUNCTION: void Events1000ms(void)
*PURPOSE: Runs on a 1000 millisecond interrupt boundary.  
*       This routine shall be kept slim!
*PRECONDITION: Interrupts and time base should be setup
*POSTCONDITION: Action taken on a 1000ms boundary
*RETURN: Nothing
********************************************************/
void Events1000ms(void);       

#endif
/* END OF FILE */