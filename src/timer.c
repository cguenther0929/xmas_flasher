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
    T0CS = 0;                   // Increment on FOSC/4 
}

void Timer0Init(uint8_t interrupts, uint16_t prescaler) {
    T0IF       = 0;                // Reset the overflow bit  TODO
    
    switch(interrupts){
        case 0:
            T0IE = 0;     //Do not cause an interrupt
            break;
        case 1:
            T0IE = 1;
            break;
        default:
            T0IE = 0;     //Default is do not cause an interrupt
            break;

    }
    
    switch (prescaler){                 // Set the prescaler, see page 81/298
        case 0:                         // User wished not to use prescaler.  Will run FOSC/4
            OPTION_REGbits.PSA = 1;     // Assign prescaler to WDT p81/298
            break;
        case 2:
            OPTION_REGbits.PSA = 0;                      
            OPTION_REGbits.PS = 0;                      
            break;
        case 4:
            OPTION_REGbits.PSA = 0;                      
            OPTION_REGbits.PS = 1;                       
            break;
        case 8:
            OPTION_REGbits.PSA = 0;                      
            OPTION_REGbits.PS = 2;                       
            break;
        case 16:
            OPTION_REGbits.PSA = 0;                      
            OPTION_REGbits.PS = 3;                       
            break;
        case 32:
            OPTION_REGbits.PSA = 0;                      
            OPTION_REGbits.PS = 4;                       
            break;
        case 64:
            OPTION_REGbits.PSA = 0;                      
            OPTION_REGbits.PS = 5;                       
            break;
        case 128:
            OPTION_REGbits.PSA = 0;                      
            OPTION_REGbits.PS = 6;                       
            break;
        case 256:
            OPTION_REGbits.PSA = 0;                      
            OPTION_REGbits.PS = 7;                       
            break;
        default:                //Will not use the prescaler
            OPTION_REGbits.PSA = 1;                // Disables the prescaler for 1:1 relationship p144
            break;
    }
}

