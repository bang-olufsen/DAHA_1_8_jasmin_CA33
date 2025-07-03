/*****************************************************************************
 *
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
 *
 *  Project          :  	21593SDK
 *  Organization     :  	Jasmin Infotech Private Limited,Chennai
 *  File Name        :		GPIO.c
 *  Description      :   	GPIO configuration routines

 ******************************************************************************/
#pragma default_section(CODE,"Seg_Gpio_Code")
#include "../Include/GPIO.h"
#include "../Include/Commn.h"

#ifdef LED_TOGGLE
void Led_Toggle_Routine(void)
{
	if( Led_Toggle_Count <= 0)
	{
		adi_gpio_Toggle(LED1_PORT, LED1_PIN);
		Led_Toggle_Count = 23;
	}
	Led_Toggle_Count--;

}

void Led1_Set_Routine(void)
{
	adi_gpio_Set(LED1_PORT, LED1_PIN);
}

void Led2_Set_Routine(void)
{
	adi_gpio_Set(LED2_PORT, LED2_PIN);
}

void Led2_Clr_Routine(void)
{
	adi_gpio_Clear(LED2_PORT, LED2_PIN);
}

void Initialize_Led(void)
{
//	adi_gpio_SetDirection(FLAG1_PORT, FLAG1_PIN, ADI_GPIO_DIRECTION_OUTPUT);
	adi_gpio_SetDirection(LED1_PORT, LED1_PIN, ADI_GPIO_DIRECTION_OUTPUT);
	adi_gpio_SetDirection(LED2_PORT, LED2_PIN, ADI_GPIO_DIRECTION_OUTPUT);
}
#endif
