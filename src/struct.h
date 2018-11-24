/******************************************************************************
*   FILE: struct.h
*
*   PURPOSE: Structures used throughout the code base are defined here.  
*
*   DEVICE: PPIC18F66K22
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
#ifndef __STRUCT_H_
#define __STRUCT_H_

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"             //Project specific header file

extern struct GlobalInformation         //  Structure to pass information that is shared among modules
{
    uint16_t    tick10ms;               // Increases every 50mili tick1000monds 
    uint16_t    tick100ms;              // Used to keep track of passing deci-tick1000monds
    uint16_t    tick1000ms;             // Use this to tick tick1000monds -- might not be used for audio interface board

} GlobalInformation;


#endif