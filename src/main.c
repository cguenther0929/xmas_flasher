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

#include "main.h" 

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

struct GlobalInformation gblinfo;

void main()
{
    uint8_t main_sec_ctr    = 0;
    
    uint8_t red_pwm_lvl     = 0;
    uint8_t red_pwm_ctr     = 0;

    uint8_t grn_pwm_lvl     = 0;
    uint8_t grn_pwm_ctr     = 0;

    uint8_t blu_pwm_lvl     = 0;
    uint8_t blu_pwm_ctr     = 0;
    
    // uint8_t pwm_val             = 0;                 // For loop counter
    // uint8_t initial_pwm_val     = 10;
    SetUp();
    
    // PWM_OFF(GRN_LED_PWM_BIT);
    // PWM_OFF(RED_LED_PWM_BIT);
    // PWM_OFF(BLU_LED_PWM_BIT);
    
    // Setup for soft glow
    // PWM_ON(GRN_LED_PWM_BIT,initial_pwm_val);
    // PWM_ON(RED_LED_PWM_BIT,initial_pwm_val);

    red_pwm_lvl = 6;
    grn_pwm_lvl = 0;
    blu_pwm_lvl = 0;

    // RED_LED = ledon;
    
    while (true) {
        
        if(gblinfo.event1ms) {
            gblinfo.event1ms = false;

            red_pwm_ctr < red_pwm_lvl ? (RED_LED = ledon) : (RED_LED = ledoff);
            grn_pwm_ctr < grn_pwm_lvl ? (GRN_LED = ledon) : (GRN_LED = ledoff);
            blu_pwm_ctr < blu_pwm_lvl ? (BLU_LED = ledon) : (BLU_LED = ledoff);

            red_pwm_ctr > PWM_FULL_COUNT ? (red_pwm_ctr = 0) : (red_pwm_ctr++);
            grn_pwm_ctr > PWM_FULL_COUNT ? (grn_pwm_ctr = 0) : (grn_pwm_ctr++);
            blu_pwm_ctr > PWM_FULL_COUNT ? (blu_pwm_ctr = 0) : (blu_pwm_ctr++);
        }
        
        if(gblinfo.event5ms) {
            gblinfo.event5ms = false;
        }
        
        if(gblinfo.event10ms) {
            gblinfo.event10ms = false;
        }
        
        if(gblinfo.event100ms) {
            gblinfo.event100ms = false;
            
            main_sec_ctr > 9 ? (main_sec_ctr = 0) : (main_sec_ctr++);

            if(main_sec_ctr < 3) {
                red_pwm_lvl = 6;
                grn_pwm_lvl = 0;
                blu_pwm_lvl = 0;
            }
            else if(main_sec_ctr >= 3 && main_sec_ctr < 6) {
                red_pwm_lvl = 0;
                grn_pwm_lvl = 6;
                blu_pwm_lvl = 0;
            }
            else {
                red_pwm_lvl = 0;
                grn_pwm_lvl = 0;
                blu_pwm_lvl = 6;
            }

        }


        
        
        
        
        // // Quick 'flicker' up
        // for(pwm_val = initial_pwm_val; pwm_val < 30; pwm_val++) {
        //     PWM_ON(GRN_LED_PWM_BIT,pwm_val);
        //     PWM_ON(RED_LED_PWM_BIT,pwm_val);
        //     tick10msDelay(1);
        // }
        
        // Ramdon Delay
        // tick10msDelay(1);

        // Quick 'flicker' dwn
        // for(pwm_val = pwm_val; pwm_val > initial_pwm_val; pwm_val-=2) {
        //     PWM_ON(GRN_LED_PWM_BIT,pwm_val);
        //     PWM_ON(RED_LED_PWM_BIT,pwm_val);
        //     tick10msDelay(1);
        // }

        // Ramdon Delay
        // tick10msDelay(2);

        // Quick 'flicker' up 2
        // for(pwm_val = initial_pwm_val; pwm_val < 55; pwm_val++) {
        //     PWM_ON(GRN_LED_PWM_BIT,pwm_val);
        //     PWM_ON(RED_LED_PWM_BIT,pwm_val);
        //     tick10msDelay(2);
        // }
        
        // Ramdon Delay
        // tick10msDelay(2);

        // Quick 'flicker' dwn
        // for(pwm_val = pwm_val; pwm_val > initial_pwm_val; pwm_val-=2) {
        //     PWM_ON(GRN_LED_PWM_BIT,pwm_val);
        //     PWM_ON(RED_LED_PWM_BIT,pwm_val);
        //     tick10msDelay(1);
        // }
        
        // Ramdon Delay
        // tick10msDelay(3);
        
        // // Quick 'flicker' up 2
        // for(pwm_val = initial_pwm_val; pwm_val < 60; pwm_val++) {
        //     PWM_ON(GRN_LED_PWM_BIT,pwm_val);
        //     PWM_ON(RED_LED_PWM_BIT,pwm_val);
        //     tick10msDelay(2);
        // }
    
    }

} //END Main()

void SetUp(void)
{
    // Clock / Timing configuration
    /*
     * Multiple options on page 46, but some listed here
     * 0b111  = 8MHz
     * 0b110  = 4MHz    (Defult upon reset)
     * 0b101  = 2MHz
     * 0b100  = 1MHz    
     * 0b011  = 500kHz    
     * 0b010  = 250kHz
     * 0b001  = 125kHz    
     * 0b000  = 31kHz   (LFINTOSC)
     */
    OSCCONbits.IRCF = 7;             // Internal oscillator set to 8MHz. 
    
    /* Pin directions for pins tied to LED outputs */
    // RED_LED = ledoff;
    // GRN_LED = ledoff;
    // BLU_LED = ledoff;

    TRISC5 = output;                    // Red LED
    TRISC3 = output;                    // Green LED
    TRISC4 = output;                    // Blue LED
    
    Init_Interrupts();                  //Set up interrupts  

    gblinfo.tick1ms     = 0;            // Initialize 100s of a tick1000mond counter to 0
    gblinfo.tick5ms     = 0;            // Initialize 100s of a tick1000mond counter to 0
    gblinfo.tick10ms    = 0;            // Initialize 100s of a tick1000mond counter to 0
    gblinfo.tick100ms   = 0;            // Initialize 100s of a tick1000mond counter to 0
    gblinfo.tick1000ms  = 0;            // Seconds counter

    gblinfo.event1ms    = false;
    gblinfo.event5ms    = false;
    gblinfo.event10ms   = false;
    gblinfo.event100ms  = false;

    /* Disable analog channels */
    ANSEL = 0x00;                  // Disable analog channels to select digital IO function.  p116

    /* CONFIGURE PWM */ 
    // InitPWM();

    /* TIMER FOR APPLICATION INTERRUPTS */
    Timer0Init(TMR0_INTUP_SETTING, TMR0_PRESCALER); // interrupts = yes, prescaler = 16, clksource = FOSC/4 
    Timer0On();             
}

// void tick100msDelay(uint16_t ticks)
// {
//     uint16_t i = 0;
//     uint16_t tick = 0; //Used to lock time value
//     for (i = ticks; i > 0; i--)
//     {
//         tick = gblinfo.tick100ms;
//         while (tick == gblinfo.tick100ms)
//             ; //Wait for time to wrap around (in one half tick1000mond)
//     }
// }

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