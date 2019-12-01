/******************************************************************************
 *   FILE: 
 *          timer.h
 *
 *   PURPOSE:
 *          Timer-related routines are defined here
 *
 *   TODO:
 *
 *   NOTE:
 *
******************************************************************************/
#ifndef __TIMER_H
#define __TIMER_H

#include <xc.h>                 //Part specific header file
#include <stdint.h>
#include <stdbool.h>
#include "config.h"             //Project specific header file

/*
 * Function:  void Timer0Init(uint8_t interrupts, uint16_t prescaler)
 * --------------------
 * Initialize timer zero.  This timer is responsible 
 * for the main application timer.  
 *
 * returns: Nothing
 */
void Timer0Init(uint8_t interrupts, uint16_t prescaler);

/*
 * Function: void Timer0On( void )
 * --------------------
 * Turn on timer zero.  
 *
 * returns: Nothing
 */
void Timer0On( void );

#endif
/* END OF FILE */