/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Commn.h
*  Description      :   Define MACRO added for all the Project files 
******************************************************************************/
#ifndef COMMN_H
#define COMMN_H

/*============== Decoder Definition==========================================*/

#define NOP10 asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");

#define NOP1 asm("nop;");

#define MCPCM_DECODER

#define ADI_VIRTUAL

#define STACK_MEM_L3 32768
//#define SAMPLE_PROCESSING_128
#define FRAMEWORK_24CH

#ifdef SAMPLE_PROCESSING_128
	#define NO_OF_SAMPLE_PROCESSING  128
#else
	#define NO_OF_SAMPLE_PROCESSING  256
#endif

#ifdef ADI_VIRTUAL
#define NO_OF_SAMPLE_PROCESSING_VIRTUAL	64
#endif

#define NO_OF_CACHE_MD_SDRAM 16
// DDPlus - 1536 words, TureHD - 1024 words, MAT-PCM - 1024 words
#define MAX_EVO_UNPACKED_MD_SIZE (1536+16)

#define TOTAL_MD_CACHE_SIZE (NO_OF_CACHE_MD_SDRAM*MAX_EVO_UNPACKED_MD_SIZE)

#define MD_BUFFER_SDRAM_LENGTH (2*512*8)		// Metadata 8 times faster rxion compare to audio sample

#define MD_BUFFER_SDRAM_LENGTH_HALF (MD_BUFFER_SDRAM_LENGTH/2)

/*==============I/O Buffer Definition===========================================*/
#ifdef FRAMEWORK_24CH
	#define NO_OF_PREDAC_CHANNEL		24
#else
	#define NO_OF_PREDAC_CHANNEL		32
#endif

#define BUFF_MAX_SIZE				NO_OF_SAMPLE_PROCESSING*NO_OF_PREDAC_CHANNEL

#define SAMPLE_BLOCK_MCPCM			NO_OF_SAMPLE_PROCESSING
/*==============================================================================*/
/*============== Framework Definition===========================================*/
#define SYNCSIGUNKNOWN	     	    0x0f    // detection under progress 
#define FORCEPCM3   				4
#define INVALID						-1
#define NO_ERROR 					0
#define HEADER_PLACE_WRITTEN_ERROR 	1
#define STREAM_NOT_DETECTED 		2
#define FILLED_SPACE_ERROR 			3
#define EMPTY_SPACE_ERROR 			4
#define DECODER_ERROR				5
/*===============================================================================*/
#define TRUE						1
#define FALSE						0

#define FS_32K  	0x00
#define FS_44K  	0x01
#define FS_48K  	0x02
#define FS_64K  	0x04
#define FS_88K  	0x05
#define FS_96K  	0x06
#define FS_128K  	0x08
#define FS_176K  	0x09
#define FS_192K  	0x0A

/*============== Downsampling Definition==========================================*/

#define  STREAM_TYPE_FORMUTE	0x82E3
/*
	bit 0 - PCMZERO		- Mute enabled
	bit 1 - PCM			- Mute enabled
	bit 2 - DOLBY		- No mute	
	bit 3 - DTSLDCD		- No mute
	bit 4 - DTSDVD		- No mute
	bit 5 - MPEGL1		- Mute enabled
	bit 6 - MPEGL2L3	- Mute enabled 		
	bit 7 - HDCD		- Mute enabled
	bit 8 - AAC			- No mute
	bit 9 - WMAPRO		- Mute enabled
	bit 10 - DDPLUS		- No mute
	bit 11 - TRUEHD		- No mute
	bit 12 - DTSMA		- No mute
	bit 13 - DTSHR 		- No mute
	bit 14 - DTSLBR		- No mute
	bit 15 - UNKNOWN	- Mute enabled
*/

#define MDMA_COPY

#define CUSTOMER_PP

#ifdef CUSTOMER_PP
	#define FLOAT
	#define CUSTOMER_PP_CHANNELS  24
    #define PP_BUFF_MAX_SIZE NO_OF_SAMPLE_PROCESSING*CUSTOMER_PP_CHANNELS
    #define FLOAT_PP 1
#endif
#endif
