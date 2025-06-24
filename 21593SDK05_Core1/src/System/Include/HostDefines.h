/***************************************************************************
*
Copyright(c) 2021 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	HostDefines.h
*  Description      :   Host Related macros can be added here
******************************************************************************/

#ifndef _HOSTDEFINES_H_
#define _HOSTDEFINES_H_

/*==============FLAG/GPIO  Definition==========================================*/
/* FLAG CONFIGURATION FOR SHARC INTERFACE */

#define DSP2MI_INT_FLG			FLG0	// This is connected to Micro
										// Used for generating negative edge triggered interrupt to Micro
								
#define DSP2MI_INT_FLG_IO		FLG0O	// Configure as Output	

#define UNLOCK_ADC_FLG			FLG1	

#define UNLOCK_ADC_FLG_IO		FLG1O 	// Configure as Input					

#define AUDIO_NONAUDIO_FLG		FLG2	

#define AUDIO_NONAUDIO_FLG_IO	FLG2O 	// Configure as Input					

#define DSP1_ERR_FLG_IO			FLG3O 

//----------------		Modification added for AVR V	--------------------------------------

/* FLAG CONFIGURATION FOR SHARC INTERFACE */

#define DSP_INT_FLG			FLG6	// This is connected to Micro
										// Used for generating negative edge triggered interrupt to Micro
								
#define DSP_INT_FLG_IO      FLG6O	// Configure as Output
/*********************************************************************************/

#define FS_OUT_DIVIDER_DOWN		0
/*==================================================================================================================*/


/*==============SPI  Definition=====================================================================================*/

#define TAGLOCATION32				Tag_Location32
#define TAGCOUNTADDR				Tag_Location32
#define COUNTLOCATION32				Tag_Location32 +1
#define ADDRLOCATION32				Tag_Location32 +2
#define TAGLOCATION16				Tag_Location32*2  
#define TAGLOCATION48				0x8C000 + (Tag_Location32-0x92000)*2/3	

#define READ_STATUS						0x0500
#define WRITE_STATUS_ENABLE 			0x0050
#define WRITE_STATUS					0x0100
#define READ_DATA_CMD					0x03000000
#define SPICTL_8BIT						0x5E01
#define SPICTL_16BIT					0x5E81
#define SPICTL_32BIT					0x5F01
#define SPICTL_32BIT_READ				0x5F00
#define SPIVAL1							0xF08
#define SPIVAL2							0x708
#define SPICTL_REGVAL					0x4100
#define SPI_TEMPBUF_SIZE				20
#define SPIBAUD_VAL		    			0x10

/*=================================================================================================================*/

/*==============Command status Definition==========================================================================*/

#define SIGNATURE_COMMAND_SUCCESSFUL	0x04
#define SIGNATURE_COMMAND_ERROR			0x06
#define COMMAND_TABLESIZE				64
#define SIGNATURE_ADI_BITS				0xFCC9
#define SIGNATURE_ADI_BUSY				0xFCCB
#define SIGNATURE_INITIALISATION_DONE	0x0001
#define SIGNATURE_DEFAULT				0x00C8
/*=================================================================================================================*/


/*==============Status information Definition======================================================================*/
#define SIGNATURE_STATUS_CHANGE			0x0010
#define SIGNATURE_STREAM_STATUS_CHANGE	0x0030
/*=================================================================================================================*/
 
#define AUTODETECT1 	0
#define AUTODETECT2 	1
#define FORCEPCM1   	2
#define FORCEPCM2   	3
#define FORCEPCM3   	4
#define FORCEADC    	5
#define AUTODETECT3 	9


#endif  /*	_HOSTDEFINES_H_  */
