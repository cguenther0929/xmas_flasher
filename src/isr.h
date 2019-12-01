/******************************************************************************
 *   FILE: 
 *          isr.h
 *
 *   PURPOSE: 
 *          Header file for isr.c
 *  
 *   TODO: 
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

/*
 * Function:  void Init_Interrupts( void )
 * --------------------
 * This function is responsible for initializing
 * interrupt features
 *
 * returns: Nothing
 */
void Init_Interrupts( void );

/*
 * Function: void __interrupt () my_isr_routine (void)
 * --------------------
 * Defines the interrupt vector
 *
 * returns: Nothing
 */
void __interrupt () my_isr_routine (void);  //TODO need to comment

/*
 * Function:  void DisableInterrupts( void )
 * --------------------
 * Disable interrupts for time-sensitive code. 
 * It only makes sense to call this function when 
 * interrupts have been established.  
 *
 * returns: Nothing
 */
// void DisableInterrupts( void );

/*
 * Function:  void EnableInterrupts( void )
 * --------------------
 * Enable high and low priority interrupts.
 * It only makes sense to call this function if 
 * interrupts have previously been configured.  
 *
 * returns: Nothing
 */
// void EnableInterrupts( void );

#endif
/* END OF FILE */