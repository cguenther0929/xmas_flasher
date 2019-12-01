/******************************************************************************
 *   FILE: 
 *          isr.c
 *
 *   PURPOSE: 
 *          Main source file
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

    uint8_t total_pwm       = 0;    // Other colors will be some percentage of this PWM (i.e. half RED and GRN)
    
    uint8_t red_pwm_lvl     = 0;
    uint8_t red_pwm_ctr     = 0;

    uint8_t grn_pwm_lvl     = 0;
    uint8_t grn_pwm_ctr     = 0;

    uint8_t blu_pwm_lvl     = 0;
    uint8_t blu_pwm_ctr     = 0;

    State state             = state_quick_flicker_up_1;
    
    SetUp();
    
    red_pwm_lvl = 0;
    grn_pwm_lvl = 0;
    blu_pwm_lvl = 0;

    
    while (true) {
        
        if (gblinfo.event1ms) {
            gblinfo.event1ms = false;

            red_pwm_ctr < red_pwm_lvl ? (RED_LED = ledon) : (RED_LED = ledoff);
            grn_pwm_ctr < grn_pwm_lvl ? (GRN_LED = ledon) : (GRN_LED = ledoff);
            blu_pwm_ctr < blu_pwm_lvl ? (BLU_LED = ledon) : (BLU_LED = ledoff);

            red_pwm_ctr > PWM_FULL_COUNT ? (red_pwm_ctr = 0) : (red_pwm_ctr++);
            grn_pwm_ctr > PWM_FULL_COUNT ? (grn_pwm_ctr = 0) : (grn_pwm_ctr++);
            blu_pwm_ctr > PWM_FULL_COUNT ? (blu_pwm_ctr = 0) : (blu_pwm_ctr++);
        }
        
        if (gblinfo.event5ms) {
            gblinfo.event5ms = false;
            
        }
        
        if (gblinfo.event10ms) {
            gblinfo.event10ms = false;
            
            /* Quick flicker up 2 */
            if(state == state_quick_flicker_up_2) {
                if (total_pwm < 18) {
                    total_pwm++;
                    red_pwm_lvl = (uint8_t)(RED_PWM_PERCENT * total_pwm);
                    grn_pwm_lvl = (uint8_t)(GRN_PWM_PERCENT * total_pwm);
                    blu_pwm_lvl = (uint8_t)(BLU_PWM_PERCENT * total_pwm);
                }
                else {
                    state = state_quick_flicker_dn_2;
                }
            }
            
            /* Quick flicker dwn 3 */
            if(state == state_quick_flicker_dn_2) {
                if (total_pwm > 6) {
                    total_pwm--;
                    red_pwm_lvl = (uint8_t)(RED_PWM_PERCENT * total_pwm);
                    grn_pwm_lvl = (uint8_t)(GRN_PWM_PERCENT * total_pwm);
                    blu_pwm_lvl = (uint8_t)(BLU_PWM_PERCENT * total_pwm);
                }
                else {
                    state = state_quick_flicker_up_1;
                }
            }
        }
        
        if (gblinfo.event100ms) {
            gblinfo.event100ms = false;
            
            /* Quick flicker up */
            if(state == state_quick_flicker_up_1) {
                if (total_pwm < PWM_FULL_COUNT) {
                    total_pwm++;
                    red_pwm_lvl = (uint8_t)(RED_PWM_PERCENT * total_pwm);
                    grn_pwm_lvl = (uint8_t)(GRN_PWM_PERCENT * total_pwm);
                    blu_pwm_lvl = (uint8_t)(BLU_PWM_PERCENT * total_pwm);
                }
                else {
                    state = state_quick_flicker_dn_1;
                }
            }

            /* Quick flicker down */
            if(state == state_quick_flicker_dn_1) {
                if (total_pwm > 6) {
                    total_pwm--;
                    red_pwm_lvl = (uint8_t)(RED_PWM_PERCENT * total_pwm);
                    grn_pwm_lvl = (uint8_t)(GRN_PWM_PERCENT * total_pwm);
                    blu_pwm_lvl = (uint8_t)(BLU_PWM_PERCENT * total_pwm);
                }
                else {
                    state = state_quick_flicker_up_2;
                }
            }
            
        }

        if(gblinfo.event1000ms) {
            gblinfo.event1000ms = false;
            GRN_LED = ~GRN_LED;
        }

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
    
    TRISC5 = output;                    // Red LED
    TRISC3 = output;                    // Green LED
    TRISC4 = output;                    // Blue LED
    
    Init_Interrupts();                  //Set up interrupts  

    gblinfo.tick1ms     = 0;            // Initialize 1ms counter
    gblinfo.tick5ms     = 0;            // Initialize 5ms counter
    gblinfo.tick10ms    = 0;            // Initialize 10ms counter
    gblinfo.tick100ms   = 0;            // Initialize 100ms counter
    gblinfo.tick1000ms  = 0;            // Initialize 1000ms counter

    gblinfo.event1ms    = false;
    gblinfo.event5ms    = false;
    gblinfo.event10ms   = false;
    gblinfo.event100ms  = false;
    gblinfo.event1000ms = false;

    /* Disable analog channels */
    ANSEL = 0x00;                  // Disable analog channels to select digital IO function.  p116


    /* TIMER FOR APPLICATION INTERRUPTS */
    Timer0Init(TMR0_INTUP_SETTING, TMR0_PRESCALER); // interrupts = yes, prescaler = 16, clksource = FOSC/4 
    Timer0On();             
}

/*
void tick10msDelay(uint16_t ticks)
{
    uint16_t i = 0;
    uint16_t tick = 0;                      // Used to lock time value
    for (i = ticks; i > 0; i--)
    {
        tick = gblinfo.tick10ms;
        while (tick == gblinfo.tick10ms);   // Wait for time to wrap around (in one half tick1000mond)
    }
}
*/
/* END OF FILE */