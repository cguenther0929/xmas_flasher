/******************************************************************************
*   FILE: pwm.h
*
*   PURPOSE:  Header file for PWM souce file.  
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

#ifndef _H_PWM_H
#define _H_PWM_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "struct.h"
#include "timer.h"

void InitPWM( void );  //TODO need to comment

void PWM_ON(uint8_t pwm_bit, uint8_t pwm_duty); //TODO need to comment

void PWM_OFF(uint8_t pwm_bit);  //TODO need to comment

#endif	