/******************************************************************************
*   FILE: pwm.c
*
*   PURPOSE: Handles features related to PWM modules.
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

#include "pwm.h"

void InitPWM( void ){
	
    // Clear PWMxCON registers
	PWM1CON = 0;
    PWM2CON = 0;
    PWM3CON = 0;
    PWM4CON = 0;
    
	// Clear duty cycle registers
    PWM1DCHbits.PWM1DCH = 0;
    PWM1DCLbits.PWM1DCL = 0;
    
    PWM2DCHbits.PWM2DCH = 0;
    PWM2DCLbits.PWM2DCL = 0;
    
    PWM3DCHbits.PWM3DCH = 0;
    PWM3DCLbits.PWM3DCL = 0;
    
    PWM4DCHbits.PWM4DCH = 0;
    PWM4DCLbits.PWM4DCL = 0;

    // loaded the period register into timer two
    PR2 = PWM_PR2;

	// Configure and start timer 2
    Timer2Init(TMR2_PRESCALER);
    Timer2On();
}

void PWM_ON(uint8_t pwm_bit, uint8_t pwm_duty) {

	uint16_t reg_val = 0;
	
	switch (pwm_bit) {
		case 1:
			reg_val = pwm_duty * PWM_DUTY_CONSTANT;
    		
			PWM1DCHbits.PWM1DCH = (uint8_t)((reg_val >> 2) & 0xFF);
    		PWM1DCLbits.PWM1DCL = (uint8_t)(reg_val & 0x03);

			PWM1CONbits.PWM1EN = 1;
			PWM1CONbits.PWM1OE = 1;
		break;

		case 2:
			reg_val = pwm_duty * PWM_DUTY_CONSTANT;
    		
			PWM1DCHbits.PWM1DCH = (uint8_t)((reg_val >> 2) & 0xFF);
    		PWM1DCLbits.PWM1DCL = (uint8_t)(reg_val & 0x03);
			
			PWM2CONbits.PWM2EN = 1;
			PWM2CONbits.PWM2OE = 1;
		break;

		case 3:
			reg_val = pwm_duty * PWM_DUTY_CONSTANT;
    		
			PWM1DCHbits.PWM1DCH = (uint8_t)((reg_val >> 2) & 0xFF);
    		PWM1DCLbits.PWM1DCL = (uint8_t)(reg_val & 0x03);
			
			PWM3CONbits.PWM3EN = 1;
			PWM3CONbits.PWM3OE = 1;
		break;

		case 4:
			reg_val = pwm_duty * PWM_DUTY_CONSTANT;
    		
			PWM1DCHbits.PWM1DCH = (uint8_t)((reg_val >> 2) & 0xFF);
    		PWM1DCLbits.PWM1DCL = (uint8_t)(reg_val & 0x03);
			
			PWM4CONbits.PWM4EN = 1;
			PWM4CONbits.PWM4OE = 1;
		break;

		default:
			// Clear PWMxCON registers
			PWM1CON = 0;
    		PWM2CON = 0;
    		PWM3CON = 0;
    		PWM4CON = 0;
		break;
	}

}

void PWM_OFF(uint8_t pwm_bit) {

	switch (pwm_bit) {
		case 1:
			PWM1CONbits.PWM1EN = 0;
			PWM1CONbits.PWM1OE = 0;
		break;

		case 2:
			PWM2CONbits.PWM2EN = 0;
			PWM2CONbits.PWM2OE = 0;
		break;

		case 3:
			PWM3CONbits.PWM3EN = 0;
			PWM3CONbits.PWM3OE = 0;
		break;

		case 4:
			PWM4CONbits.PWM4EN = 0;
			PWM4CONbits.PWM4OE = 0;
		break;

		default:
			// Clear PWMxCON registers
			PWM1CON = 0;
			PWM2CON = 0;
			PWM3CON = 0;
			PWM4CON = 0;
		break;
	}

}