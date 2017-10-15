/* File name: LabOne.c
 * Target board: TIVA C: Tiva TM4C123GH6PM
 * Compiler version: TI v16.9.0.LTS
 * Description: This file provides the template for LabOne.
 * The completed lab will have the following functionalities:
 * 1. Blink on-board Red LED for 10 times at 0.5s blink intervals when left switch
 * on Tiva C board is pressed.
 * 2. Blink on-board Blue LED for 5 times at 1s blink intervals when right switch
 * on Tiva C board is pressed.
 *
 *  Copyright 2016 by ABHILASH DR, adevalap@uncc.edu
 *  You may use, edit, run or distribute this file
 *  as long as the above copyright notice remains
 *  THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *  OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *  AUTHOR SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 *  OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "buttons.h"

/****************************************************/
//Declare Preprocessor definition
/****************************************************/

/****************************************************/
//Declare the prototype of the functions here
/****************************************************/
void DAC_Out(unsigned long data);
void DAC_Init(void);
void ADC0_Init(void);
unsigned long ADC0_In(void);
void Timer_Init(void);

unsigned long result;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

/****************************************************/
//Start of main routine
/****************************************************/

/****************************************************/
/* Function: main
 * Description: Functional call to DAC.c and ADC.c
 * files in project that initializes the SysCtl clock,,
 * sets the peripherals for the GPIO of B, E, and ADC0,
 * and initializes the DAC and ADC for digitizing a
 * function generated sine wave.
 * Arguments: void
 * Return: zero
 */
/****************************************************/
int main(void)
{

    /****************************************************/
    //Do not edit the below line
    /****************************************************/
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
    SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    /****************************************************/

    /****************************************************/
    //Write your logic below
    /****************************************************/

    ADC0_Init();        //Initialize the Analog to Digital Converter
    DAC_Init();         // Initialize the Digital to Analog Converter
    Timer_Init();       // Initialize the periodic interrupts in Systick_handler

    while (1)
    {
     // Continuously stores the digitized ADC value from the function generator.
        result = ADC0_In();

    }

    return 0;

}
