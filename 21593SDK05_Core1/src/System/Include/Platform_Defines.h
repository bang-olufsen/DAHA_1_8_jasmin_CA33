/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Platform_Defines.h
*  Description      :   Define hardware platform specific Macros  
******************************************************************************/
#ifndef PLATFORM_H
#define PLATFORM_H
#include "..\src\system\Include\Commn.h"

/*==============Platform Definition================================================================================*/
//#define EZKIT_PLATFORM
#define SHARCAVRV_PLATFORM

                             
//If not defined the code can be tested in AVRII Platform
//Hence, this define is required for the final end platform.

#ifdef SHARCAVRII_PLATFORM
	#ifdef INTER_DSP_COMM_I2S
		#define SHARCAVRII_UPSAMPLING_TESTING
	#endif
#endif

#if defined (EZKIT_PLATFORM) || defined (SHARCAVRV_PLATFORM)
	//#define EZKIT_CONFIG_CODEC_TESTING //For AD1939 Codec Config through SPI;
	//#define EZKIT_SPI_TESTING
#endif
/*=================================================================================================================*/


/*==============SDRAM, PCG, PLL Definitions for platform specific =================================================*/
/*  These defines are same for  SMAVRII, Ezkit and Customer platform */
#define FS_OUT_DIVIDER_DOWN  		0

#ifdef CUSTOMER_PLATFORM
#define SDRAM_DIVIDER				0x30816
#define SDCONTROLWORD				0x22054263
#define AMICTL1_VALUE				0x002003C3
#else
#define SDRAM_DIVIDER				0x309BA
#define SDCONTROLWORD				0x23055373
#define AMICTL1_VALUE				0x002003C1
#endif

#define SDRAM_BANK_ADDRESS			0x00200000

#define PLL_MULTIPLIER				PLLM16
#define SDCLOCK_RATIO				SDCKR2_5		//SDRAM configured to 133MHz

#define SPI_BAUDRATE				16

#define FS_OUT_DIVIDER  		0
#define FS_IN_DIVIDER  			64
#define FSA_PHASE				63
#define CLK_DIVIDER  			1

#define FS_IN_DIVIDER_RX  		64
#define CLK_DIVIDER_RX  		1
#define FS_IN_PHASE_RX			63

#define CLK_DIVIDER_TX  		2
#define FS_IN_DIVIDER_TX  		128
#define FS_IN_PHASE_TX			127

#define FS_IN_DIVIDER_TX_US4  	128
#define FS_IN_PHASE_TX_US4		127
#define CLK_DIVIDER_TX_US4		2

/*=================================================================================================================*/
#endif

