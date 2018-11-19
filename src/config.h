/******************************************************************************
*   FILE: config.h
*
*   PURPOSE: Configuration file specific to the processor being used and the 
*           underlying hardware. 
*
*   DEVICE: pic12lf1501
*
*   COMPILER: Microchip XC8 v1.32
*
*   IDE: MPLAB X v3.45
*
*   TODO:  
*
*   NOTE:
*
******************************************************************************/
#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

/* MCU CRITICAL PARAMETERS */
#define OSC                            32768000               //Oscillator (MCU Clock Input) is 32.768MHz
#define OSC_DIV4                       (OSC/4.0)              //Instruction clock is oscillator frequency / 4

/* DEFINE CODE VERSION NUMBER */
#define MAJVER                          0x00
#define MINVER                          0x00
#define BUGVER                          0x01

/* PREPROCESSOR CALCULATION TO DETERMINE TIMER4'S INCREMENT RATE */
#define T4_OSC                          OSC                   // Oscillator is same as clock source used for MCU
#define T4_PRESCALER                    16.0
#define T4_POSTSCALER                   16.0
#define T4_FOSCBY4                      (T4_OSC/4.0)
#define T4_SCALER                       (T4_PRESCALER*T4_POSTSCALER)
#define T4_INC_FREQ                     (T4_FOSCBY4/T4_SCALER)

/* DEFINES FOR MC PINS */
#define APH_CROSSED         PORTBbits.RB0           // Digital input indicating A phase crossed
#define BPH_CROSSED         PORTBbits.RB1           // Digital input indicating B phase crossed
#define CPH_CROSSED         PORTBbits.RB2           // Digital input indicating C phase crossed


/* DEFINES FOR PUSH BUTTONS */

/* DEFINES FOR ANALOG SENSE */

/* REGISTER VALUES FOR 10MS TIME BASE */         
#define TMR0_INTUP_SETTING  1                                                           // 1 = Caused interrupts, 0 = do not cause interrupts
#define TMR0_PRESCALER      16                                                          // Options are 1, 2, 4, 8, 16, 32, 128, or 256
#define TMR0_CLKSRC         0                                                           // 0 = OSC/4 as the rate of the instruction clock.  This freq further divided by prescaler
#define TMR0_INC_FREQ       (OSC_DIV4/TMR0_PRESCALER)                                   // Effective rate at which the timer increments
#define HEART_BEAT_MS       10                                                          // Interrupt every this many (mili-seconds)
#define TMR0_TICKS          ((HEART_BEAT_MS/1000.0)*TMR0_INC_FREQ)                      // How many timer ticks between interrupts
#define TMR0_REG_SETTING    (65535-TMR0_TICKS)                                          // Finally, the register setting (16 bit mode) shall be set to this
#define TMR0HIGH            (uint8_t)(TMR0_REG_SETTING/256)                             // Upper eight bits of Timer 0's register
#define TMR0LOW             (uint8_t)((TMR0_REG_SETTING-256)*(TMR0_REG_SETTING/256))    // Lower eight bits of timer 0's register (modulo math)   

/* DEFINE VARIOUS PIN FUNCITONS */
#define output              0           // Define the output pin direction setting
#define input               1

/* INTUTIVE TIMER NAMES */
#define TIMER1              1
#define TIMER2              2
#define TIMER3              3
#define TIMER4              4

/* LED CONTROL */
#define ledon               0
#define ledoff              1

#endif