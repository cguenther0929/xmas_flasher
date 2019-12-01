/******************************************************************************
 *   FILE: 
 *          main.h
 *
 *   PURPOSE:
 *          Header file for main.c. Target device PIC16F685T-I/SS
 *
 *   TODO:
 *
 *   NOTE:
 *
******************************************************************************/

#ifndef __MAIN_H
#define __MAIN_H

#include <xc.h>         
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "struct.h"
#include "isr.h"
#include "config.h"     
#include "timer.h"


/*
 * Function:  void tick10msDelay( uint16_t ticks );
 * --------------------
 * Blocking delay function.  Blocks in increments 
 * of 10ms chunks.  Number of "chunks" depends on 
 * "ticks" value passed to function.  This timing 
 * routine is fairly accurate as it uses a timer
 * w/ interrupts to count.  Timebase must first
 * be configured via SetUp function.    
 *
 * returns: Nothing 
 */
// void tick10msDelay( uint16_t ticks );

/*
 * Function:  void SetUp( void );
 * --------------------
 * SetUp routine covering all aspects of the application. 
 * Processor GPIOs are configured.  Peripherials are 
 * configured.  ADC is configured.  System timebase 
 * and general timing parameters are configured.  
 *
 * returns: Nothing 
 */
void SetUp( void );

#endif