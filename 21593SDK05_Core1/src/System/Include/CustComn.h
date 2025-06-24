/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	CustCommn.h
*  Description      :
******************************************************************************/
#ifndef CUSTCOMMN_H_
#define CUSTCOMMN_H_


#define TDIV0_VAL	    0
#define RDIV0_VAL	    0
#define MTCS0_VAL       0
#define MRCS0_VAL	    0
#define MTCCS0_VAL      0x0
#define MRCCS0_VAL      0x0
#define SPCTL2_VAL	    0x37d09f1	// transmit on ports A and B (chained DMA)
#define SPCTL0_VAL	    0x000d09f1	// receive on port A (chained DMA)

#define TDIV1_VAL	    0
#define RDIV1_VAL	    0
#define MTCS1_VAL       0
#define MRCS1_VAL       0
#define MTCCS1_VAL      0x0
#define MRCCS1_VAL	    0x0
#define SPCTL3_VAL	    0x37d09f1	// transmit on ports A and B (chained DMA)
#define SPCTL1_VAL	    0x000d09f1	// receive on port A (chained DMA)

/* GPIO bits and Flags definations for 21161N */

/******************** BIT DEFINATIONS FOR FPGA_CNTRL_PORT *********************/

#define   BRD_CLK_SEL0_BIT          0x00000080
#define   BRD_CLK_SEL1_BIT          0x00000040
#define   AUDIO_RESET_BIT	        0x00000020
#define   CS12_BIT		            0x00000010
#define   CS12_SEL_BIT	            0x00000008
#define   DIAGNOSTIC_BIT	        0x00000004
#define   I_P_RELAY_BIT 	        0x00000002
/*This bit is reserved#define   	0x00000001*/
/******************** BIT DEFINATIONS FOR GPIO_PORT_WR1 *******************/
#define   ADC_DFS_BIT	             0x00000080
#define   ADC_CAL_BIT                0x00000040
#define   SEL0_48_96_BIT             0x00000020
#define   SEL1_48_96_BIT             0x00000002
#define   ADC_PWDN_BIT               0x00000004 
#define   X2MCLK0_BIT                0x00000008 
#define   X2MCLK1_BIT                0x00000010


/* D7 Bit is reserved*/

/******************** BIT DEFINATIONS FOR GPIO_PORT_WR2 *******************/
#define   OP_RELAY1_BIT				 0x00000001 
#define   OP_RELAY2_BIT	             0x00000002
#define   DAC_MUTE_BIT				 0x00000004 
#define   DAC_PWDN_BIT				 0x00000008
#define   SPDIF_PWDN_BIT			 0x00000010
#define   F1C0_BIT					 0x00000020
#define   F1C1_BIT		             0x00000040
#define   HDCD_BIT				     0x00000080



/********************* FLAG DEFINATIONS FOR 21161N ************************/
/*
#define 	Tx_LRCLK_FLG		FLGO		
#define 	MICRO_CMD_FLG		FLG1		
#define 	MICRO_RST_FLG		FLG2		
#define 	FLSH_PRGM_FLG		FLG3		
#define 	NFLASH_R_B_FLG		FLG4		
#define 	UP_DWN_SEL_FLG		FLG5		
#define 	DIAG_LED_FLG		FLG6		
#define 	MICRO_INT_FLG		FLG7		
#define 	I2C_SCLK_FLG		FLG8		
#define 	I2C_DATA_FLG		FLG9		
#define 	RY_BY_FLG			FLG10		  //Can be used when Booting instead of data polling
#define 	BRD_CLK_SEL_FLG	    FLG11		//This flag selects b/w Spdif and Adc 0-SPDIF 1-ADC and BOARD CLK
*/
/********************* FLAG STATUS  DEFINATIONS FOR 21161N ************************/
/*These bit are to set in order to tell whether they are input or output*/
#define 	Tx_LRCLK_IO			FLG0O		
#define 	MICRO_CMD_IO		FLG1O	
#define 	MICRO_RST_IO		FLG2O		
#define 	FLSH_PRGM_IO		FLG3O		
#define 	NFLASH_R_B_IO		FLG4O		
#define 	UP_DWN_SEL_IO		FLG5O		
#define 	DIAG_LED_IO			FLG6O		
#define 	MICRO_INT_IO		FLG7O		
#define 	I2C_SCLK_IO			FLG8O		
#define 	I2C_DATA_IO			FLG9O		
#define 	RY_BY_IO  			FLG10O		//Can be used when Booting instead of data polling
#define 	BRD_CLK_SEL_IO	    FLG11O		

/*PORTS ADDRESS FOR LCHH ON */

#define   FPGA_CTRL_PORT	 	0x04E00004
#define   GPIO_PORT_WR1         0x04E00006
#define   GPIO_PORT_WR2         0x04E00002
#define   CS8414_PORT		 	0x04C00000

#define   USB_ADDR_PORT		 	0x04E00000
#define   USB_DATA_PORT		 	0x04E00001

#define   MICRO_RW_PORT		 	0x04E00007



/********************* FLAG DEFINATIONS FOR 21161N ************************/

#define DSP_BOOT_FLG	FLG0		// This flag is used for indicating booting in progress
									// This flag is set when code is loaded in to ADSP

#define RX_LRCLK_FLG	FLG2		// Used for synchronizing the input left and right channel data

#define DIAG_LED_FLG	FLG3		// Diagnoistic LED

#define Tx_LRCLK_FLG	FLG5		// Used for synchronizing the input left and right channel data

#define SAMP_SEL_FLG	FLG6		// Used for Straight sampling or upsampling
									// 0 - Straight sampling;	1 - Upsampling

#define SPARE1_FLG		FLG7

#define SPARE2_FLG		FLG8

#define SPARE3_FLG		FLG9

#define HDCDDET_FLG		FLG10		// Output LED for saying input is from HDCD

#define HDCDGS_FLG		FLG11		// Input flag for HDCD gain scaling

/********************* FLAG STATUS  DEFINATIONS FOR 21161N ************************/
/*These bit are to set in order to tell whether they are input or output*/

#define DSP_BOOT_FLG_IO		FLG0O		// Configure as Output

#define RX_LRCLK_FLG_IO		FLG2O		// Configure as Input

#define DIAG_LED_FLG_IO		FLG3O		// Configure as Output

#define Tx_LRCLK_FLG_IO		FLG5O		// Configure as Input

#define SAMP_SEL_FLG_IO	    FLG6O		// Configure as Output

#define SPARE1_FLG_IO	    FLG7O		// Spare flag

#define SPARE2_FLG_IO	    FLG8O		// Spare flag

#define SPARE3_FLG_IO	    FLG9O		// Spare flag

#define HDCDDET_FLG_IO	    FLG10O		// Configure as Output

#define HDCDGS_FLG_IO	    FLG11O		// Configure as Input



/*These bit are to set in order to tell whether they are input or output*/
#define 	SPI_EEPROM_CS_O		FLG0O
#define 	FLAG_LATCH_O		FLG2O		
#define 	FLASH_EN_O  		FLG3O		
		

/********************* FLAG DEFINATIONS FOR 21161N ************************/

#define SPI_EEPROM_CS	FLG0		// This flag is used for indicating booting in progress
									// This flag is set when code is loaded in to ADSP

#define FLAG_LATCH		FLG2		// Used for synchronizing the input left and right channel data

#define FLASH_EN		FLG3		// Diagnoistic LED



/* FLAG CONFIGURATION FOR SHARC INTERFACE */

#define DSP2MI_INT_FLG			FLG0	// This is connected to Micro
										// Used for generating negative edge triggered interrupt to Micro
								
#define DSP2MI_INT_FLG_IO		FLG0O	// Configure as Output	

#define UNLOCK_ADC_FLG			FLG1	

#define UNLOCK_ADC_FLG_IO		FLG1O 	// Configure as Input					

#define AUDIO_NONAUDIO_FLG		FLG2	

#define AUDIO_NONAUDIO_FLG_IO	FLG2O 	// Configure as Input					

#endif  /*  CUSTCOMMN_H_  */
