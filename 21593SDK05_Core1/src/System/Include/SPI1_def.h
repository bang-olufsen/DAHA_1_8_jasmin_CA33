/***************************************************************************
*
Copyright(c) 2021 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	SPI1_def.h
*  Description      :
******************************************************************************/
#ifndef SYSTEM_INCLUDE_SPI1_DEF_H_
#define SYSTEM_INCLUDE_SPI1_DEF_H_

/**************************************************************************************************/
/*									Includes Header Files Section								  */
/**************************************************************************************************/
#include "ProcInclude.h"
/**************************************************************************************************/
/*									Define Macros Section										  */
/**************************************************************************************************/

#define SPI_CLK 		(0x2)	 	//2 Mhz
#define SYS_CLK 	 	(100000000)		//100 Mhz

#define SPI0_CLK_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<12))
#define SPI0_MISO_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<14))
#define SPI0_MOSI_PORTA_MUX  ((uint32_t) ((uint32_t) 0<<16))
#define SPI0_RDY_PORTB_MUX  ((uint32_t) ((uint32_t) 1<<22))
#define SPI0_SEL1_PORTA_MUX  ((uint32_t) ((uint32_t) 0<<18))
#define SPI0_SEL2_PORTB_MUX  ((uint16_t) ((uint16_t) 2<<10))
#define SPI0_SEL3_PORTB_MUX  ((uint32_t) ((uint32_t) 1<<28))
#define SPI0_SEL4_PORTB_MUX  ((uint32_t) ((uint32_t) 1<<30))
#define TWI2_SCL_PORTA_MUX  ((uint32_t) ((uint32_t) 0<<28))
#define TWI2_SDA_PORTA_MUX  ((uint32_t) ((uint32_t) 0<<30))

#define SPI0_CLK_PORTA_FER  ((uint16_t) ((uint16_t) 1<<6))
#define SPI0_MISO_PORTA_FER  ((uint16_t) ((uint16_t) 1<<7))
#define SPI0_MOSI_PORTA_FER  ((uint32_t) ((uint32_t) 1<<8))
#define SPI0_RDY_PORTB_FER  ((uint32_t) ((uint32_t) 1<<11))
#define SPI0_SEL1_PORTA_FER  ((uint32_t) ((uint32_t) 1<<9))
#define SPI0_SEL2_PORTB_FER  ((uint16_t) ((uint16_t) 1<<5))
#define SPI0_SEL3_PORTB_FER  ((uint32_t) ((uint32_t) 1<<14))
#define SPI0_SEL4_PORTB_FER  ((uint32_t) ((uint32_t) 1<<15))
#define TWI2_SCL_PORTA_FER  ((uint32_t) ((uint32_t) 1<<14))
#define TWI2_SDA_PORTA_FER  ((uint32_t) ((uint32_t) 1<<15))

#define SPI1_CLK_PORTA_MUX  ((uint32_t) ((uint32_t) 1<<20))
#define SPI1_MISO_PORTA_MUX  ((uint32_t) ((uint32_t) 1<<22))
#define SPI1_MOSI_PORTA_MUX  ((uint32_t) ((uint32_t) 1<<24))
#define SPI1_RDY_PORTB_MUX  ((uint16_t) ((uint16_t) 1<<8))
#define SPI1_RDY_PORTC_MUX  ((uint16_t) ((uint16_t) 1<<12))
#define SPI1_SEL1_PORTA_MUX  ((uint32_t) ((uint32_t) 1<<26))
#define SPI1_SEL2_PORTB_MUX  ((uint32_t) ((uint32_t) 1<<20))
#define SPI1_SEL3_PORTB_MUX  ((uint32_t) ((uint32_t) 1<<26))
#define SPI1_SEL4_PORTC_MUX  ((uint16_t) ((uint16_t) 3<<0))
#define SPI1_SEL5_PORTB_MUX  ((uint16_t) ((uint16_t) 1<<12))
#define SPI1_SEL6_PORTC_MUX  ((uint16_t) ((uint16_t) 3<<4))
#define SPI1_SEL7_PORTB_MUX  ((uint32_t) ((uint32_t) 1<<16))


#define SPI1_CLK_PORTA_FER  ((uint32_t) ((uint32_t) 1<<10))
#define SPI1_MISO_PORTA_FER  ((uint32_t) ((uint32_t) 1<<11))
#define SPI1_MOSI_PORTA_FER  ((uint32_t) ((uint32_t) 1<<12))
#define SPI1_RDY_PORTB_FER  ((uint16_t) ((uint16_t) 1<<4))
#define SPI1_RDY_PORTC_FER  ((uint16_t) ((uint16_t) 1<<6))
#define SPI1_SEL1_PORTA_FER  ((uint32_t) ((uint32_t) 1<<13))
#define SPI1_SEL2_PORTB_FER  ((uint32_t) ((uint32_t) 1<<10))
#define SPI1_SEL3_PORTB_FER  ((uint32_t) ((uint32_t) 1<<13))
#define SPI1_SEL4_PORTC_FER  ((uint16_t) ((uint16_t) 1<<0))
#define SPI1_SEL5_PORTB_FER  ((uint16_t) ((uint16_t) 1<<6))
#define SPI1_SEL6_PORTC_FER  ((uint16_t) ((uint16_t) 1<<2))
#define SPI1_SEL7_PORTB_FER  ((uint32_t) ((uint32_t) 1<<8))

#endif /* SYSTEM_INCLUDE_SPI1_DEF_H_ */
