/******************************************************************************

Copyright (c) 2020-2021 Analog Devices.  All Rights Reserved.

This software is proprietary and confidential.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.
*******************************************************************************/

/** @addtogroup Timer_Service GP Timer Service
*  @{
*/

/** @addtogroup Timer_Service_Static_Configuration GP Timer Service Static Configuration
 *  @{
 */
 
/*!
* @file      adi_tmr_config_SC59x.h
*
* @brief     Timer driver static configuration Header file
*
* @details
*            Timer driver static configuration Header file
*/

#ifndef __ADI_TMR_CONFIG_SC59x_H__
#define __ADI_TMR_CONFIG_SC59x_H__

#include <sys/platform.h>
#include <stdint.h>

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_19_4:"C macros shall only expand to a braced initializer, a constant, a string literal, a parenthesised expression, a type qualifier, a storage class specifier, or a do-while-zero construct.")
#endif /* _MISRA_RULES */

/*!Enable the static configuration for Timer 0*/
#define ADI_TMR_TMR0 1

/*------------------TIMER 0------------------------------------*/
#if (ADI_TMR_TMR0==1)
/* TIMER0 Instance */
/* Select TIMER0 Instance */
#define ADI_TIMER0_INSTANCE                     1u

/*!Selects the mode of operation for the Timer0. 
Following are the valid values that can be assigned to the macro
    
	ADI_TMR_MODE_IDLE     		 	- Idle mode          
    
	ADI_TMR_MODE_PERIOD_WD  		- Period watchdog mode 
   
    ADI_TMR_MODE_WIDTH_WD 			- Width watchdog mode 
    
	ADI_TMR_MODE_CAPTURE_ASSERT 	- Width capture mode at asserting edge 
    
	ADI_TMR_MODE_CAPTURE_DEASSERT 	- Width capture mode at de-asserting edge
    
	ADI_TMR_MODE_CONTINUOUS_PWMOUT 	- Continuous PWM out mode 
    
	ADI_TMR_MODE_SINGLE_PWMOUT   	- Single PWM out mode     
    
	ADI_TMR_MODE_EXTCLK             - External clock mode
    
	ADI_TMR_MODE_PINT               - Pin interrupt mode
*/
#define ADI_TIMER0_MODE        		ADI_TMR_MODE_CONTINUOUS_PWMOUT

/*!Selects the IRQ Mode of operation of the Timer0.
Following are the valid values that can be assigned to the macro
    
	ADI_TMR_IRQMODE_PULSE           - Generate interrupt every active edge.This IRQ Mode is valid for the PIN Interrupt mode only.
									  
    ADI_TMR_IRQMODE_DELAY           - Generate interrupt after timer counts till TMR_DELAY register value. This is valid for Continuous PWMOUT mode and Single Pulse PWMOUT mode.
									  
    ADI_TMR_IRQMODE_WIDTH_DELAY     - Generate interrupt after timer counts till TMR_DELAY + TMR_WIDTH register value. This is valid for Continuous PWMOUT mode and Single Pulse PWMOUT mode.

    ADI_TMR_IRQMODE_INSIDE_WINDOW   - Generate interrupt if de-asserting edge of timer input falls within width/period watchdog window. This is valid for the period and width WATCHDOG modes.

    ADI_TMR_IRQMODE_OUTSIDE_WINDOW  - Generate interrupt if de-asserting edge of timer input falls outside width/period watchdog window. This is valid for the period and width WATCHDOG modes.

    ADI_TMR_IRQMODE_PERIOD          - Generate interrupt after timer counts till TMR_PERIOD register value. This is valid for the Continuous PWMOUT mode and EXTCLK mode.
*/
#define ADI_TIMER0_IRQ_MODE			ADI_TMR_IRQMODE_PERIOD

/*!Selects the pulse polarity of the timer pin, true=active high, false=active low*/
#define ADI_TIMER0_PULSE_POLARITY  	false

/*!Selects the clock input source of the Timer0.
Following are the valid values that can be assigned to the macro
    
	ADI_TMR_CLKIN_SYSCLK        - Use system clock as clock input.
    
	ADI_TMR_CLKIN_ALTCLK0       - Use alternative clock input source 0.
    
	ADI_TMR_CLKIN_ALTCLK1       - Use alternative clock input source 1.
*/
#define ADI_TIMER0_CLKIN_SOURCE		ADI_TMR_CLKIN_SYSCLK

/*!Selects the input of the timer, true=Auxiliary input pin, false=timer pin input*/
#define ADI_TIMER0_INPUT_AUXIN		false

/*!The period value for timer operation in SCLK cycles. This field is valid only for PWM Out modes, Windowed WDOG modes and External clock mode. The valid range is 0 to (2^32)-1*/
#define ADI_TIMER0_PERIOD			2000u

/*!The width value for timer operation in SCLK cycles. This field is valid only for PWM Out modes. The valid range is 0 to (2^32)-1*/
#define ADI_TIMER0_WIDTH			500u

/*!The delay value for timer operation in SCLK cycles. This field is valid only for PWM Out modes and windowed WDOG modes. The valid range is 0 to (2^32)-1*/
#define ADI_TIMER0_DELAY			0u

/*!Choose the stop configuration of the timer as abrupt stop or graceful stop. This option is valid only in the PWM OUT modes*/
#define ADI_TIMER0_ENABLE_GRACEFUL_STOP    true

/*!If true, then the timer runs during emulation.*/
#define ADI_TIMER0_EMULATION_RUN          false

#endif /*(ADI_TMR_TMR0==1)*/

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

#endif /*__ADI_TMR_CONFIG_SC59x_H__*/

/* @}*/
/* @}*/
