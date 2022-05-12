
#include <p18f4620.h>
#include "Main.h"
#include "Fan_Support.h"
#include "stdio.h"

extern char HEATER;
//extern char FAN;
extern char duty_cycle;
extern char heater_set_temp;
extern signed int DS1621_tempF;

int get_duty_cycle(signed int temp, int set_temp)
{
// add code to check if temp is greater than set_temp. If so, set duty_cycle according to the handout
// check if duty_cycle is greater than 100. If so, set it to 100
// if duty_cycle is negative, set to 0
// return duty_cycle
    
//    if (temp >= set_temp)
//    {
//        duty_cycle = 0;
//    }
//    if (temp < set_temp)
//    {
//        int diff = set_temp - temp;
//        
//        if (diff > 50)
//            duty_cycle = 100;
//        
//        if ((diff >= 25) && (diff < 50))
//            duty_cycle = diff * 2;
//        
//        if ((diff >= 10) &&( diff < 25))
//            duty_cycle = diff * (3/2);
//        
//        if ((diff >= 0) && (diff < 10))
//            duty_cycle = diff;
//    }
    duty_cycle = (set_temp - temp) * 2;                                             // Calculate duty cycle based on set and ambient temperatures
    
    if (duty_cycle < 0){duty_cycle = 0;}                                                                  // If duty_cycle < 0,
                                                                    // Set duty_cycle equal to 0
    if (duty_cycle > 100){duty_cycle = 100;}                                                               // else if duty_cycle > 100,
                                                                   // Set duty_cycle equal to 100
    return (duty_cycle);                                                                // Return duty_cycle value

}

void Monitor_Heater()
{
    duty_cycle = get_duty_cycle(DS1621_tempF, heater_set_temp);
    do_update_pwm(duty_cycle);
    
    //update d1 and d2 here
    
    

    if (HEATER == 1) 
    {
        FAN_EN = 1;
    }
    else FAN_EN = 0;
}

void Toggle_Heater()
{
// add code just to flip the variable FAN
    printf("Heater Toggled\n");
    if (HEATER == 1) Turn_Off_Fan();
    else Turn_On_Fan();
}

int get_RPM()
{
// add old code
    int RPS = TMR3L / 2;        // read the count. Since there are 2 pulses per rev
                                // then RPS = count /2
    TMR3L = 0;                  // clear out the count
    return (RPS * 60);          // return RPM = 60 * RPS
    duty_cycle = 50;
    do_update_pwm(duty_cycle) ; 
}

void Turn_Off_Fan()
{
// add old code   
    printf("Fan Turned Off\n");
    HEATER = 0;
    FAN_EN = 0;
    FAN_LED = 0;
}

void Turn_On_Fan()
{
// add old code 
    printf("Fan Turned On\n");
    HEATER = 1;
    do_update_pwm(duty_cycle);
    FAN_EN = 1;
    FAN_LED = 1;
}







