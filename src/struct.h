/******************************************************************************
 *   FILE: 
 *          struct.h
 *
 *   PURPOSE:
 *          Structures used throughout the code base are defined here.  
 *
 *   TODO:
 *
 *   NOTE:
 *
******************************************************************************/
#ifndef __STRUCT_H
#define __STRUCT_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"             //Project specific header file

extern struct GlobalInformation         //  Structure to pass information that is shared among modules
{
    uint16_t    tick1ms;                // Increases every 1ms
    uint16_t    tick5ms;                // Increases every 5ms
    uint16_t    tick10ms;               // Increases every 10ms  
    uint16_t    tick100ms;              // Increases every 100ms
    uint16_t    tick1000ms;             // Increases every 1000ms
    
    bool        event1ms;               // Flag set to true every 1ms
    bool        event5ms;               // Flag set to true every 5ms
    bool        event10ms;              // Flag set to true every 10ms
    bool        event100ms;             // Flag set to true every 100ms
    bool        event1000ms;            // Flag set to true every 1000ms

} GlobalInformation;


#endif