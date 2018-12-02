# BLDC Motor Controller #

This repository contains the source files for the RGB flasher which is the module that goes inside a tree ornament globe.    

### TOOL SUITE ###

The source files are to be compiled using the XC 8 compiler **V2.0**.  The IDE used at the time of development was MPLAB X **v5.10**.  The subsequent .hex file is to be deployed on the PIC12LF MCU.  

### VERSIONS ###
* V0.0.1 -- Snapshot when PWM control was correct, and timing functions were working as expected.  
* V0.1.0 -- Version loaded on globes for the 2018 XMAS season.  Note that oscillator speed was set to 250kHz.  It may be necessary to slow the internal clock down if battery life issues are discovered.  