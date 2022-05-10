#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include <p18f4620.h>
#include "utils.h"
#include "Main.h"

extern char found;
extern char Nec_code1;
extern short nec_ok;
extern char array1[21];
extern char duty_cycle;


char check_for_button_input()
{       
    if (nec_ok == 1)
    {
            nec_ok = 0;


            INTCONbits.INT0IE = 1;          // Enable external interrupt
            INTCON2bits.INTEDG0 = 0;        // Edge programming for INT0 falling edge

            found = 0xff;
            for (int j=0; j< 21; j++)
            {
                if (Nec_code1 == array1[j]) 
                {
                    found = j;
                    j = 21;
                }
            }
            
            if (found == 0xff) 
            {
                printf ("Cannot find button \r\n");
                return (0);
            }
            else
            {
                return (1);
            }
    }
    return NULL;
}

char bcd_2_dec (char bcd)
{
    int dec;
    dec = ((bcd>> 4) * 10) + (bcd & 0x0f);
    return dec;
}

int dec_2_bcd (char dec)
{
    int bcd;
    bcd = ((dec / 10) << 4) + (dec % 10);
    return bcd;
}

void Do_Beep()
{
    KEY_PRESSED = 1;
    Activate_Buzzer();
    Wait_One_Sec();
    KEY_PRESSED = 0;
    Deactivate_Buzzer();
    do_update_pwm(duty_cycle);
}

void Do_Beep_Good()
{
    Activate_Buzzer_2KHz();
}

void Do_Beep_Bad()
{
    Activate_Buzzer_500Hz();

}

void Wait_One_Sec()
{
    for (int k=0;k<0x8000;k++);
}

void Activate_Buzzer()
{
    PR2 = 0b11111001 ;      // 249 , Timer 2 Period Register
    T2CON = 0b00000101 ;    // 5 , Timer 2 Control
    CCPR2L = 0b01001010 ;   // 74 , Capture/Compare/PWM Register 2 Low Byte
    CCP2CON = 0b00111100 ;  // 60 , Capture/Compare/PWM Register 2 Control
}

void Activate_Buzzer_500Hz()
{
    // add code here
    PR2 = 0b11111001 ;
    T2CON = 0b00000111 ;
    CCPR2L = 0b01111100 ;
    CCP2CON = 0b00111100 ;
}

void Activate_Buzzer_2KHz()
{
    // add code here
    PR2 = 0b11111001 ;
    T2CON = 0b00000101 ;
    CCPR2L = 0b01111100 ;
    CCP2CON = 0b00111100 ;
}

void Activate_Buzzer_4KHz()
{
    // add code here
    PR2 = 0b01111100 ;
    T2CON = 0b00000101 ;
    CCPR2L = 0b00111110 ;
    CCP2CON = 0b00011100 ;
}

void Deactivate_Buzzer()
{
    CCP2CON = 0x0;
	PORTBbits.RB3 = 0;
}

void do_update_pwm(char duty_cycle) 
{ 
	float dc_f;
	int dc_I;
	PR2 = 0b00000100 ;                      // Set the frequency for 25 Khz 
	T2CON = 0b00000111 ;                    // As given in website
	dc_f = ( 4.0 * duty_cycle / 20.0) ;     // calculate factor of duty cycle versus a 25 Khz signal
	dc_I = (int) dc_f;                      // Truncate integer
	if (dc_I > duty_cycle) dc_I++;          // Round up function
	CCP1CON = ((dc_I & 0x03) << 4) | 0b00001100;
	CCPR1L = (dc_I) >> 2;
}

void Set_RGB_Color(char color)
{
    // add code here
    if (color == 0)                                                             // If color is 0 (no color),
    {
        RGB_RED = 0;                                                            // Set RGB_RED to 0
        RGB_GREEN = 0;                                                          // Set RGB_GREEN to 0
        RGB_BLUE = 0;                                                           // Set RGB_BLUE to 0
    }
    else if (color == 1)                                                        // else if color is 1 (red),
    {
        RGB_RED = 1;                                                            // Set RGB_RED to 1
        RGB_GREEN = 0;                                                          // Set RGB_GREEN to 0
        RGB_BLUE = 0;                                                           // Set RGB_BLUE to 0
    }
    else if (color == 2)                                                        // else if color is 2 (green),
    {
        RGB_RED = 0;                                                            // Set RGB_RED to 0
        RGB_GREEN = 1;                                                          // Set RGB_GREEN to 1
        RGB_BLUE = 0;                                                           // Set RGB_BLUE to 0
    }
    else if (color == 3)                                                        // else if color is 3 (yellow),
    {
        RGB_RED = 1;                                                            // Set RGB_RED to 1
        RGB_GREEN = 1;                                                          // Set RGB_GREEN to 1
        RGB_BLUE = 0;                                                           // Set RGB_BLUE to 0
    }
    else if (color == 4)                                                        // else if color is 4 (blue),
    {
        RGB_RED = 0;                                                            // Set RGB_RED to 0
        RGB_GREEN = 0;                                                          // Set RGB_GREEN to 0
        RGB_BLUE = 1;                                                           // Set RGB_BLUE to 1
    }
    else if (color == 5)                                                        // else if color is 5 (purple),
    {
        RGB_RED = 1;                                                            // Set RGB_RED to 1
        RGB_GREEN = 0;                                                          // Set RGB_GREEN to 0
        RGB_BLUE = 1;                                                           // Set RGB_BLUE to 1
    }
    else if (color == 6)                                                        // else if color is 6 (cyan),
    {
        RGB_RED = 0;                                                            // Set RGB_RED to 0
        RGB_GREEN = 1;                                                          // Set RGB_GREEN to 1
        RGB_BLUE = 1;                                                           // Set RGB_BLUE to 1
    }
    else if (color == 7)                                                        // else if color is 7 (white),
    {
        RGB_RED = 1;                                                            // Set RGB_RED to 1
        RGB_GREEN = 1;                                                          // Set RGB_GREEN to 1
        RGB_BLUE = 1;                                                           // Set RGB_BLUE to 1
    }
}

float read_volt()
{
    // add code here
    int nStep = get_full_ADC();                                                 // Get full ADC value
    int volt = nStep * 5 /1024.0;                                                   // Convert nstep to volt
    
	return (volt);
}

unsigned int get_full_ADC()
{
    // add code here
    unsigned int result;                                                            // variable for ADC result
    ADCON0bits.GO=1;                                                            // Start Conversion
    while(ADCON0bits.DONE==1);                                                  // wait for conversion to be completed
    result = (ADRESH * 0x100) + ADRESL;                                         // combine result of upper byte and
                                                                                // lower byte into result
    return result; 
}

void Init_ADC()
{
    // add code here
    ADCON0 = 0x01;                                                              // Set ADCON0 to 0x01
    ADCON1 = 0x0E;                                                              // Set ADCON1 to 0x0E
    ADCON2 = 0xA9;                                                              // Set ADCON2 to 0xA9
}


