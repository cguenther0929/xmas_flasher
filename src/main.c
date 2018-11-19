/******************************************************************************
*   FILE: main.c
*
*   PURPOSE: Main source
*
*   DEVICE: pic12lf1501
*
*   COMPILER: Microchip XC8 v1.32
*
*   IDE: MPLAB X v3.45
*
*   TODO:  
*
*   NOTE:
*
******************************************************************************/

#include "main.h" //Include header file associated with main.c

// CONFIG1L
#pragma config RETEN = OFF      // VREG Sleep Enable bit (Disabled - Controlled by SRETEN bit)
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = DIG    // SOSC Power Selection and mode Configuration bits (Digital (SCLKI) mode)
#pragma config XINST = OFF      // Extended Instruction Set (Disabled)

// CONFIG1H
#pragma config FOSC = EC3       // TODO Update this description Oscillator (Internal RC oscillator) with output on OSC2.  p45/550.  default IRCF<2:0> = 110 = 8MHz (on pin 8MHz/4 = 2MHz)
#pragma config PLLCFG = OFF     // PLL x4 Enable bit (Disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2L
#pragma config PWRTEN = ON      // Power Up Timer (Enabled)
#pragma config BOREN = SBORDIS  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 1         // Brown-out Reset Voltage bits (2.7V)
#pragma config BORPWR = ZPBORMV // BORMV Power level (ZPBORMV instead of BORMV is selected)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Disabled in HW
#pragma config WDTPS = 1024     // Watchdog Postscaler (1:1024)

// CONFIG3L
#pragma config RTCOSC = SOSCREF // RTCC Clock Select (RTCC uses SOSC)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 Mux (RC1)
#pragma config MSSPMSK = MSK7   // MSSP address masking (7 Bit address masking mode)
#pragma config MCLRE = ON       // Master Clear Enable (MCLR Enabled, RG5 Disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Overflow Reset (Enabled)
#pragma config BBSIZ = BB2K     // Boot Block Size (2K word Boot Block size)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protect 00800-03FFF (Disabled)
#pragma config CP1 = OFF        // Code Protect 04000-07FFF (Disabled)
#pragma config CP2 = OFF        // Code Protect 08000-0BFFF (Disabled)
#pragma config CP3 = OFF        // Code Protect 0C000-0FFFF (Disabled)

// CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Disabled)
#pragma config CPD = OFF        // Data EE Read Protect (Disabled)

// CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-03FFF (Disabled)
#pragma config WRT1 = OFF       // Table Write Protect 04000-07FFF (Disabled)
#pragma config WRT2 = OFF       // Table Write Protect 08000-0BFFF (Disabled)
#pragma config WRT3 = OFF       // Table Write Protect 0C000-0FFFF (Disabled)

// CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Disabled)
#pragma config WRTB = OFF       // Table Write Protect Boot (Disabled)
#pragma config WRTD = OFF       // Data EE Write Protect (Disabled)

// CONFIG7L
#pragma config EBRT0 = OFF      // Table Read Protect 00800-03FFF (Disabled)
#pragma config EBRT1 = OFF      // Table Read Protect 04000-07FFF (Disabled)
#pragma config EBRT2 = OFF      // Table Read Protect 08000-0BFFF (Disabled)
#pragma config EBRT3 = OFF      // Table Read Protect 0C000-0FFFF (Disabled)

// CONFIG7H
#pragma config EBRTB = OFF      // Table Read Protect Boot (Disabled)

struct GlobalInformation gblinfo;

void main()
{
    SetUp();
    
    while (true) {

    }

} //END Main()

void SetUp(void)
{
    /* PIN DIRECTIONS FOR LED DRIVERS */
    TRISA5 = input;
    
    Init_Interrupts();                  //Set up interrupts  

    gblinfo.tick10ms = 0;       // Initialize 100s of a tick1000mond counter to 0
    gblinfo.tick100ms = 0;      // Initialize 100s of a tick1000mond counter to 0
    gblinfo.tick1000ms = 0;     // Seconds counter

    /* DISABLE ANALOG CHANNELS */
    ANSELA = 0x00;          // Disable analog channels to select digital IO function.  p103

    /* SETUP TIMER FOR PWM GENERATION */  //TODO make sure the following is correct
    PWM1Init(TIMER2);				            //Initialize PWM 1 -- ARGS: Timer to use (options are 2, 4, 6, 8 and 10)
	PWM1EnableOuts('x');		                //ARGS: Output pin (ex 'a', 'b', 'c', or 'd').  'x' will leave the pin as digital I/O for now
	Timer2Init(0,PWM_Timer_Prescaler,1);  		//Args: Interrupts, Prescaler, Postscaler
	Timer2On(PWM_Timer_PR_Value);				//Args: Period register unsigned char

    /* SETUP TIMER FOR MEASRUING COMMUTATE POINTS */
    Timer4Init(0,T4_PRESCALER,T4_POSTSCALER);        //ARGS: No Interrupts; Prescaler of 16; Postscaler of 16
    Timer4Off();
    
    /* SETUP TIMER FOR OPEN LOOP STARTING */
    // 1 = Enable interrupts, true = high priority interrupt, 1 = prescaler (8 is max), 0 = clock (Fosc/4)    
    Timer1Init(1,true,1,0);  
    Timer1Off();
    
    /* TIMER FOR APPLICATION INTERRUPTS */
    Timer0Init(TMR0_INTUP_SETTING, TMR0_PRESCALER, TMR0_CLKSRC); // interrupts = yes, prescaler = 16, clksource = FOSC/4 
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