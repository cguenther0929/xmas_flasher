/******************************************************************************
*   FILE: main.c
*
*   PURPOSE: Main source
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

#include "main.h" //Include header file associated with main.c

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

struct GlobalInformation gblinfo;

void main()
{
    SetUp();
    
    while (true) {

    }

} //END Main()

void SetUp(void)
{
    // Clock / Timing configuration
    /******************
    Multiple options on page 53, but some listed here
    0b1111  = 16MHz
    0b1101  = 4MHz
    0b1011  = 1MHz
    0b0111  = 500kHz    (Defult upon reset)
    0b0110  = 250KHz    
    0b0101  = 125kHz    
    0b0000  = 31kHz
    *****************/
    
    OSCCONbits.IRCF = 0             // Internal oscillator set to 31kHz.  Config bits above select the internal oscillator.
    
    /* PIN DIRECTIONS FOR LED DRIVERS */
    TRISA2 = output;
    TRISA4 = output;
    TRISA5 = output;
    
    /* SETUP TIMER FOR PWM GENERATION */  
    // Clear the PWMxCON register
    
    PR2                 = PWM_PR2       

    Timer2Init(TMR2_PRESCALER);
    Timer2On();
    
    //TODO left off here, pick back up on p154 for how to setup PWM
    
    Init_Interrupts();                  //Set up interrupts  

    gblinfo.tick10ms = 0;       // Initialize 100s of a tick1000mond counter to 0
    gblinfo.tick100ms = 0;      // Initialize 100s of a tick1000mond counter to 0
    gblinfo.tick1000ms = 0;     // Seconds counter

    /* DISABLE ANALOG CHANNELS */
    ANSELA = 0x00;          // Disable analog channels to select digital IO function.  p103


    //TODO need to fix the following
    // PWM1Init(TIMER2);				            //Initialize PWM 1 -- ARGS: Timer to use (options are 2, 4, 6, 8 and 10)
	// PWM1EnableOuts('x');		                    //ARGS: Output pin (ex 'a', 'b', 'c', or 'd').  'x' will leave the pin as digital I/O for now
	// Timer2Init(0,PWM_Timer_Prescaler,1);  		//Args: Interrupts, Prescaler, Postscaler
	// Timer2On(PWM_Timer_PR_Value);				//Args: Period register unsigned char

    /* TIMER FOR APPLICATION INTERRUPTS */
    Timer0Init(TMR0_INTUP_SETTING, TMR0_PRESCALER); // interrupts = yes, prescaler = 16, clksource = FOSC/4 
    Timer0On();             
}

void tick100msDelay(uint16_t ticks)
{
    uint16_t i = 0;
    uint16_t tick = 0; //Used to lock time value
    for (i = ticks; i > 0; i--)
    {
        tick = gblinfo.tick100ms;
        while (tick == gblinfo.tick100ms)
            ; //Wait for time to wrap around (in one half tick1000mond)
    }
}

void tick10msDelay(uint16_t ticks)
{
    uint16_t i = 0;
    uint16_t tick = 0; //Used to lock time value
    for (i = ticks; i > 0; i--)
    {
        tick = gblinfo.tick10ms;
        while (tick == gblinfo.tick10ms); //Wait for time to wrap around (in one half tick1000mond)
    }
}
/* END OF FILE */