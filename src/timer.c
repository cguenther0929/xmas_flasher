/******************************************************************************
*   FILE: timer.c
*
*   PURPOSE: Source file containing all timer-related routines.  
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

#include "timer.h"              //Include the header file for this module
#include "struct.h"             //Include the structure header file for global information

struct GlobalInformation gblinfo;

void Timer0On( void ){
    #ifndef TMR0_REG_SETTING                    //Assume TMR0LOW is also not defined
        TMR0 = TMR0_REG_SETTING;
    #else
        TMR0 = 125;
    #endif
    OPTION_REGbits.TMR0CS = 0;           //Place into 8-bit timer mode
}

void Timer0Init(uint8_t interrupts, uint16_t prescaler) {
    INTCONbits.TMR0IF       = 0;                // Reset the overflow bit
    OPTION_REGbits.TMR0CS   = 0;                // Select 8-bit timer mode p143
    
    switch(interrupts){
        case 0:
            INTCONbits.TMR0IE = 0;     //Do not cause an interrupt
            break;
        case 1:
            INTCONbits.TMR0IE = 1;      //Cause an interrupt when timer overflows
            INTCONbits.PEIE = 1;        //INTCON p72
            break;
        default:
            INTCONbits.TMR0IE = 0;     //Default is do not cause an interrupt
            break;

    }
    
    switch (prescaler){     //Set the prescaler
        case 1:         //User wished not to use prescaler.  Will run FOSC/4
            OPTION_REGbits.PSA = 1;                      // Disables the prescaler for 1:1 relationship p144
            break;
        case 2:
            OPTION_REGbits.PSA = 0;                      // Must be cleared in order to enable the prescaler 
            OPTION_REGbits.PS = 0;                      //Prescaler of 1:2 (p145)
            break;
        case 4:
            OPTION_REGbits.PSA = 0;                      // Must be cleared in order to enable the prescaler 
            OPTION_REGbits.PS = 1;                       //Prescaler of 1:4 (p145)
            break;
        case 8:
            OPTION_REGbits.PSA = 0;                      // Must be cleared in order to enable the prescaler 
            OPTION_REGbits.PS = 2;                       //Prescaler of 1:8 (p145)
            break;
        case 16:
            OPTION_REGbits.PSA = 0;                      // Must be cleared in order to enable the prescaler 
            OPTION_REGbits.PS = 3;                       //Prescaler of 1:16 (p145)
            break;
        case 32:
            OPTION_REGbits.PSA = 0;                      // Must be cleared in order to enable the prescaler 
            OPTION_REGbits.PS = 4;                       //Prescaler of 1:32 (p145)
            break;
        case 64:
            OPTION_REGbits.PSA = 0;                      // Must be cleared in order to enable the prescaler 
            OPTION_REGbits.PS = 5;                       //Prescaler of 1:64 (p145)
            break;
        case 128:
            OPTION_REGbits.PSA = 0;                      // Must be cleared in order to enable the prescaler 
            OPTION_REGbits.PS = 6;                       //Prescaler of 1:128 (p145)
            break;
        case 256:
            OPTION_REGbits.PSA = 0;                      // Must be cleared in order to enable the prescaler 
            OPTION_REGbits.PS = 7;                       //Prescaler of 1:256 (p145)
            break;
        default:                //Will not use the prescaler
            OPTION_REGbits.PSA = 1;                // Disables the prescaler for 1:1 relationship p144
            break;
    }
}

void Timer2Init(uint8_t prescaler) {
    
    PIR1bits.TMR2IF = 0;
    
    /******************
    Prescaler options are 
    0b00    = 1
    0b01    = 4
    0b10    = 16
    0b11    = 64
    *****************/
    switch (prescaler){     //Set the prescaler
        case 1:
            T2CONbits.T2CKPS    = 0;
            break;
        case 4:
            T2CONbits.T2CKPS    = 1;
            break;
        case 16:
            T2CONbits.T2CKPS    = 2;
            break;
        case 64:
            T2CONbits.T2CKPS    = 3;
            break;
        default:                //Will not use the prescaler
            T2CONbits.T2CKPS    = 0;
            break;
    }
    
}

void Timer2On( void ) {
    T2CONbits.TMR2ON    = 1;

}