// DAC.c

// Runs on LM4F120 or TM4C123,

// Implementation of the 4-bit digital to analog converter

// Daniel Valvano, Jonathan Valvano

// December 29, 2014

// Port B bits 3-0 have the 4-bit DAC

#include "tm4c123gh6pm.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "buttons.h"

//Declare the prototype of the functions here

void DAC_Init(void);

void DAC_Out(unsigned long data);

void Timer_Init(void);

void SysTick_Handler(void);

extern unsigned long result;

// **************DAC_Init*********************

// Initialize 4-bit DAC

// Input: none

// Output: none v

void DAC_Init(void)
{

    volatile unsigned long delay;

    SYSCTL_RCGC2_R |= 0x02;             // activate Port B

    delay = SYSCTL_RCGC2_R;           // allow time for clock to stabilize

    GPIO_PORTB_PCTL_R &= ~0x0000FFFF; // configure PB3-0 as GPIO

    GPIO_PORTB_DIR_R |= 0x0F;         // make PB3-0 out

    GPIO_PORTB_DR8R_R |= 0x0F;        // enable 8 mA drive on PB3-0

    GPIO_PORTB_DEN_R |= 0x0F;         // enable digital I/O on PB3-0

}

// **************DAC_Out*********************

// output to DAC

// Input: ADC data

// Output: 12-bit to 4-bit conversion of analog signal

void DAC_Out(unsigned long data)
{
    //converts the 12-bit ADC signal into a 4-bit DAC output
    GPIOPinWrite(GPIO_PORTB_BASE,
                 GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, data / 256);
}

//  Systick periodic interrupts used instead of polling from lab 3

void Timer_Init(void)
{
    NVIC_ST_CTRL_R = 0;                          // disable SysTick during setup
    NVIC_ST_CURRENT_R = 0;                         // Clear the current register
    NVIC_ST_RELOAD_R = 0x1BBF;                               // Add reload value
    NVIC_SYS_PRI3_R = (NVIC_ST_CTRL_R & 0x00FFFFFF) | 0x20000000; // set priority 1 for systick
    NVIC_ST_CTRL_R = 0x0007; // enable SysTick with core clock (CLK_SRC=1) and interrupts

}

//Functional call changed in startup_ccs.c and set as new default handle

void SysTick_Handler(void)
{
    //takes the 12-bit digital "result" from the ADC and converts it into a 4-bit DAC result
    DAC_Out(result);

    //constantly reload the timer for systick_handler to run all the way through every time
    Timer_Init();

}
