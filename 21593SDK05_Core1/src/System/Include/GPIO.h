/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	GPIO.h
*  Description      :   Defines and variables
******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include <services/gpio/adi_gpio.h>

#pragma section("seg_gpio_data")
int Led_Toggle_Count=0;
#pragma section("seg_gpio_data")
int Led_Toggle_Count2=0;

#define Num_Of_Callbacks	2

//#define LED1             	"LED1"
//#define LED1_PORT      		(ADI_GPIO_PORT_C)
//#define LED1_PIN       		(ADI_GPIO_PIN_3)
//
//#define LED2             	"LED2"
//#define LED2_PORT      		(ADI_GPIO_PORT_C)
//#define LED2_PIN       		(ADI_GPIO_PIN_2)

#define LED1                "LED1"
#define LED1_PORT           (ADI_GPIO_PORT_B)
#define LED1_PIN            (ADI_GPIO_PIN_5)

#define LED2                "LED2"
#define LED2_PORT           (ADI_GPIO_PORT_B)
#define LED2_PIN            (ADI_GPIO_PIN_8)

//#define FLAG1               "FLAG1"					// DAHA IRQ (Active High)
//#define FLAG1_PORT          (ADI_GPIO_PORT_A)
//#define FLAG1_PIN           (ADI_GPIO_PIN_13)

#endif /* GPIO_H_ */
