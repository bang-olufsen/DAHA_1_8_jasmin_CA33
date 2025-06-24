/******************************************************************************

Copyright (c) 2020 Analog Devices.  All Rights Reserved.

This software is proprietary and confidential.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.
*******************************************************************************/

/*!
* @file      adi_sport_config_SC59x.h
*
* @brief     SPORT driver static configuration Header file
*
* @details
*            SPORT driver static configuration Header file
*/

/** @addtogroup SPORT_Driver SPORT Device Driver
 *  @{
 */
 
 
 /** @addtogroup SPORT_Driver_Static_Configuration SPORT Device Driver Static Configuration
 *  @{

  Static Configuration: Using this configuration application can configure the control registers
  parameters upfront which can be set to default before SPORT data transfer starts. This configuration
  has macros which can be configured through adi_sport_config_SC59x.h file which by default is available
  with SPORT driver. Example project can maintain a copy of it locally for custom configuration.
*/
 
 
 
#ifndef __ADI_SPORT_CONGIF_SC59X_H__
#define __ADI_SPORT_CONFIG_SC59X_H__

#include <sys/platform.h>
#include <stdint.h>

/*! Specifies the number of active SPORT devices accordingly the memory allotted will be optimized */
#define ADI_SPORT_STATIC_INSTANCES                   11u

/*!SPORT0A Instance*/
/*!Select SPORT0A Instance */
#define ADI_SPORT0A_INSTANCE                     	 1u
#define ADI_SPORT0B_INSTANCE                     	 1u

#define ADI_SPORT1A_INSTANCE                     	 1u

#define ADI_SPORT5A_INSTANCE                     	 1u

#define ADI_SPORT4A_INSTANCE                     	 1u
#define ADI_SPORT4B_INSTANCE                     	 1u
#define ADI_SPORT3A_INSTANCE                     	 1u
#define ADI_SPORT3B_INSTANCE                     	 1u

#define ADI_SPORT2A_INSTANCE                     	 1u
#define ADI_SPORT2B_INSTANCE                     	 1u

#define ADI_SPORT6A_INSTANCE                     	 1u
/*! Specifies the SPORT_0B_Control register Configuration*/
#define ADI_SPORT_0A_CTL 0xDA0919F0 /* Prim and Sec enable bit are reset. */
#define ADI_SPORT_0B_CTL 0xDA0919F0
#define ADI_SPORT_1A_CTL 0xDA0919F0

#define ADI_SPORT_5A_CTL 0xDA0919F0

#define ADI_SPORT_0A_DIV 0x001F0020
#define ADI_SPORT_0B_DIV 0x001F0020

#define ADI_SPORT_1A_DIV 0x001F0020

#define ADI_SPORT_5A_DIV 0x001F0020

#define ADI_SPORT_0A_MCTL 0x00
#define ADI_SPORT_0B_MCTL 0x00
#define ADI_SPORT_1A_MCTL 0x00

#define ADI_SPORT_5A_MCTL 0x00


/*! Specifies the SPORT0B_Multichannel Control register Configuration*/
#define ADI_SPORT_0A_CS0								0x00
#define ADI_SPORT_0A_CS1								0x00
#define ADI_SPORT_0A_CS2								0x00
#define ADI_SPORT_0A_CS3								0x00
#define ADI_SPORT_0B_CS0								0x00
#define ADI_SPORT_0B_CS1								0x00
#define ADI_SPORT_0B_CS2								0x00
#define ADI_SPORT_0B_CS3								0x00

#define ADI_SPORT_1A_CS0								0x00
#define ADI_SPORT_1A_CS1								0x00
#define ADI_SPORT_1A_CS2								0x00
#define ADI_SPORT_1A_CS3								0x00

#define ADI_SPORT_5A_CS0								0x00
#define ADI_SPORT_5A_CS1								0x00
#define ADI_SPORT_5A_CS2								0x00
#define ADI_SPORT_5A_CS3								0x00



/*! Specifies the SPORT_0B_Control register Configuration*/
#define ADI_SPORT_4A_CTL 0xDA0919F0/* Prim and Sec enable bit are reset. */
#define ADI_SPORT_4B_CTL 0xDA0919F0
#define ADI_SPORT_3A_CTL 0xDA0919F0
#define ADI_SPORT_3B_CTL 0xDA0919F0
#define ADI_SPORT_2A_CTL 0xDA0919F0
#define ADI_SPORT_2B_CTL 0xDA0919F0
#define ADI_SPORT_6A_CTL 0xDA0919F0

#define ADI_SPORT_4A_DIV 0x00170020
#define ADI_SPORT_4B_DIV 0x00170020
#define ADI_SPORT_3A_DIV 0x00170020
#define ADI_SPORT_3B_DIV 0x00170020

#define ADI_SPORT_2A_DIV 0x00170020
#define ADI_SPORT_2B_DIV 0x00170020
#define ADI_SPORT_6A_DIV 0x00170020

#define ADI_SPORT_4A_MCTL 0x00
#define ADI_SPORT_4B_MCTL 0x00
#define ADI_SPORT_3A_MCTL 0x00
#define ADI_SPORT_3B_MCTL 0x00

#define ADI_SPORT_2A_MCTL 0x00
#define ADI_SPORT_2B_MCTL 0x00
#define ADI_SPORT_6A_MCTL 0x00
/*! Specifies the SPORT0B_Multichannel Control register Configuration*/
#define ADI_SPORT_4A_CS0								0x00
#define ADI_SPORT_4A_CS1								0x00
#define ADI_SPORT_4A_CS2								0x00
#define ADI_SPORT_4A_CS3								0x00
#define ADI_SPORT_4B_CS0								0x00
#define ADI_SPORT_4B_CS1								0x00
#define ADI_SPORT_4B_CS2								0x00
#define ADI_SPORT_4B_CS3								0x00
#define ADI_SPORT_3A_CS0								0x00
#define ADI_SPORT_3A_CS1								0x00
#define ADI_SPORT_3A_CS2								0x00
#define ADI_SPORT_3A_CS3								0x00
#define ADI_SPORT_3B_CS0								0x00
#define ADI_SPORT_3B_CS1								0x00
#define ADI_SPORT_3B_CS2								0x00
#define ADI_SPORT_3B_CS3								0x00

#define ADI_SPORT_2A_CS0								0x00
#define ADI_SPORT_2A_CS1								0x00
#define ADI_SPORT_2A_CS2								0x00
#define ADI_SPORT_2A_CS3								0x00
#define ADI_SPORT_2B_CS0								0x00
#define ADI_SPORT_2B_CS1								0x00
#define ADI_SPORT_2B_CS2								0x00
#define ADI_SPORT_2B_CS3								0x00
#define ADI_SPORT_6A_CS0								0x00
#define ADI_SPORT_6A_CS1								0x00
#define ADI_SPORT_6A_CS2								0x00
#define ADI_SPORT_6A_CS3								0x00

#define ADI_SPORT0A_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT0A_DMA_PSIZE ADI_DMA_PSIZE_4BYTES
#define ADI_SPORT0B_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT0B_DMA_PSIZE ADI_DMA_PSIZE_4BYTES

#define ADI_SPORT1A_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT1A_DMA_PSIZE ADI_DMA_PSIZE_4BYTES

#define ADI_SPORT5A_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT5A_DMA_PSIZE ADI_DMA_PSIZE_4BYTES

#define ADI_SPORT4A_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT4A_DMA_PSIZE ADI_DMA_PSIZE_4BYTES
#define ADI_SPORT4B_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT4B_DMA_PSIZE ADI_DMA_PSIZE_4BYTES
#define ADI_SPORT3A_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT3A_DMA_PSIZE ADI_DMA_PSIZE_4BYTES
#define ADI_SPORT3B_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT3B_DMA_PSIZE ADI_DMA_PSIZE_4BYTES

#define ADI_SPORT2A_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT2A_DMA_PSIZE ADI_DMA_PSIZE_4BYTES
#define ADI_SPORT2B_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT2B_DMA_PSIZE ADI_DMA_PSIZE_4BYTES
#define ADI_SPORT6A_DMA_MSIZE ADI_DMA_MSIZE_4BYTES
#define ADI_SPORT6A_DMA_PSIZE ADI_DMA_PSIZE_4BYTES
#endif /*__ADI_SPORT_CONGIF_SC59X_H__*/

/*@}*/

/*@}*/
