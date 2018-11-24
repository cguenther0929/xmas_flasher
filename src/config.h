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
#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

/* MCU CRITICAL PARAMETERS */
#define OSC                            31000                    // Internal oscillator selected and IRCF set for 31kHz
#define MCU_TOSC                       1/OSC                    // Period of oscillator timer
#define OSC_DIV4                       (OSC/4.0)                //Instruction clock is oscillator frequency / 4

/* DEFINE CODE VERSION NUMBER */
#define MAJVER                          0x00
#define MINVER                          0x00
#define BUGVER                          0x01

/* REGISTER VALUES FOR 10MS TIME BASE */         
#define TMR0_INTUP_SETTING  1                                                           // 1 = Caused interrupts, 0 = do not cause interrupts
#define TMR0_PRESCALER      16                                                          // Options are 1, 2, 4, 8, 16, 32, 128, or 256
#define TMR0_INC_FREQ       (OSC_DIV4/TMR0_PRESCALER)                                   // Effective rate at which the timer increments
#define HEART_BEAT_MS       10                                                          // Interrupt every this many (mili-seconds)
#define TMR0_TICKS          ((HEART_BEAT_MS/1000.0)*TMR0_INC_FREQ)                      // How many timer ticks between interrupts
#define TMR0_REG_SETTING    (uint8_t)(256-TMR0_TICKS)                                   // Value to be loaded into the 8-bit register

/* PREPROCESSOR CALCULATIONS FOR PWM */
#define TMR2_PRESCALER      1
#define PWM_FREQ            120
#define PWM_PR2             (uint8_t)((1/(PWM_FREQ*4*MCU_TOSC*TMR2_PRESCALER))-1)

// Since we know the duty cycle ratio equation is represented by 
// Duty_Cycle_Ratio / 100 * 4 * (PR2 + 1) = REG_HIGH : REG_LOW
// we can allow the preprocessor to calculate (4 * (PR2 + 1))/100
// The value of 100 is in there so that we can pass integers into 
// the equation (i.e. 50 vs. 0.50)
// With the above, in the application we calculate the register values 
// via Duty_Cycle_Ratio * PWM_DUTY_CONSTANT = REG_HIGH : REG_LOW
#define PWM_DUTY_CONSTANT   (uint16_t)((4*(PWM_PR2+1))/100)


/* DEFINE VARIOUS PIN FUNCTIONS */
#define output              0           // Define the output pin direction setting
#define input               1

/* LED CONTROL */
#define ledon               0
#define ledoff              1

/* ALIASES FOR LED OUTPUT PINS */
//TODO should be able to remove
// #define RED_LED             LATAbits.LATA2
// #define GRN_LED             LATAbits.LATA4
// #define BLU_LED             LATAbits.LATA5

/* PWM BIT ASSIGNMENTS */
#define RED_LED_PWM_BIT     1           // This color attached to RA2 or PWM peripheral PWM 1              
#define GRN_LED_PWM_BIT     3           // This color attached to RA4 or PWM peripheral PWM 3
#define BLU_LED_PWM_BIT     4           // This color attached to RA5 or PWM peripheral PWM 4

#endif