/******************************************************************************
 *   FILE: config.h
 *
 *   PURPOSE: Configuration file specific to the processor being used and the 
 *           underlying hardware. 
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
#ifndef __CONFIG_H
#define __CONFIG_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/* Define States */
typedef enum
{
    state_1,
    state_2,
    state_3,
    state_4
}State;


/* MCU CRITICAL PARAMETERS */
#define OSC                            8000000                  // Internal oscillator selected and FOSC<2:0> set to select HFINTOSC (8MHz) -- p45
#define MCU_TOSC                       1/OSC                    // Period of oscillator timer
#define OSC_DIV4                       (OSC/4.0)                //Instruction clock is oscillator frequency / 4

/* DEFINE CODE VERSION NUMBER */
#define MAJVER                          0x00
#define MINVER                          0x00
#define BUGVER                          0x01

/* REGISTER VALUES FOR 10MS TIME BASE */         
#define TMR0_INTUP_SETTING  1                                           // 1 = Caused interrupts, 0 = do not cause interrupts
#define TMR0_PRESCALER      64.0                                        // Options are 1, 2, 4, 8, 16, 32, 64, 128, or 256
#define TMR0_INC_FREQ       (OSC_DIV4/TMR0_PRESCALER)                   // Effective rate at which the timer increments
#define HEART_BEAT_MS       1.0                                         // Interrupt every this many (mili-seconds)
#define TMR0_TICKS          ((HEART_BEAT_MS/1000.0)*TMR0_INC_FREQ)      // How many timer ticks between interrupts
// #define TMR0_REG_SETTING    (uint8_t)(256-TMR0_TICKS)                // Value to be loaded into the 8-bit register
#define TMR0_REG_SETTING    230                                         // Empirically derived value 

/* DEFINE VARIOUS PIN FUNCTIONS */
#define output              0           // Define the output pin direction setting
#define input               1

/* LED CONTROL */
#define ledon               1
#define ledoff              0

/* To make a fire color, the breakdown is as follows */
#define RED_PWM_PERCENT     0.65
#define GRN_PWM_PERCENT     0.30
#define BLU_PWM_PERCENT     0.05

/*
 * Maximum Red Voltage = 2.0V
 * Maximum Grn Voltage = 3.2V
 * Maximum Blu Voltage = 3.2V
 */
#define PWM_FULL_COUNT          18

/* ALIASES FOR LED OUTPUT PINS */
#define RED_LED                 RC5
#define GRN_LED                 RC3
#define BLU_LED                 RC4

#endif