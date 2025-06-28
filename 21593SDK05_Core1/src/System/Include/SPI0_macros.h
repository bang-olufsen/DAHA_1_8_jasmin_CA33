/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	SPIO_macros.h
*  Description      :
******************************************************************************/
#ifndef SPI0_FUNC_H_
#define SPI0_FUNC_H_

#define 	SPI0_EN		1
#define		SPI0_TEN	1			//	1:	Transmit channel Enable
#define		SPI0_REN	1			//	1:	Receive channel Enable

#define SPI0_TxDMA_EN	0
#define SPI0_RxDMA_EN	0

/**************************************************************************************************
 	 	 	 *******************		macros related to SPI0 CONTROL REGISTER 	***************
***************************************************************************************************/
		#define 	SPI0_MSTR		0			//		0: Slave,		1: Master
		#define 	SPI0_SIZE		2			//		0: 8-bit, 		1: 16-bit, 		2: 32-bit, 		3: reserved
		#define 	SPI0_CPHA		0			//		0: SCK toggles from middle of the first data bit
												//		1: SCK toggles from beginning of the first data bit
		#define 	SPI0_CPOL		0			//		0: Active low SCK, 			1: Active high SCK
		#define 	SPI0_ASSEL		1			//		0: SSEL controlled through SW,		1: SSEL controlled through HW
		#define 	SPI0_SELST		0			//	    SSEL state between transfers
												//		0: deasserted (high),		1: asserted (low) between transfers
		#define 	SPI0_LSBF		0			//		0: MSB Tx/Rx first,			1: LSB Tx/Rx first
		#define 	SPI0_EMISO		1			//	    applicable only when slave (in transmit mode)
												//		0: Disable MISO pin,		1: Enable MISO pin.....
		#define		SPI0_PSSE		0			//	    Enable signaling of MODF error when configured as a master
		#define	 	SPI0_ODM		0			//	    Enable Open Drain Mode

		#define 	SPI0_FCEN		0			//		1: Flow control enabled
		#define 	SPI0_FCCH		0			//		0: Flow-control on RX FIFO,	1: Flow-control on Tx FIFO
		#define 	SPI0_FCPL		0			//	Active polarity of RDY signal: Active implies ready for transfer
												//		0: Active low polarity,		1: Active high polarity
		#define 	SPI0_FCWM		2			//	Flow-control water-mark
												//		0: TFIF0 empty or RFIFO full
												//		1: TFIFO 75% or more empty or RFIFO 75% or more full
												//		2: TFIFO 50% or more empty or RFIFO 50% or more full
		#define 	SPI0_FMODE		0			//	1: Fast mode enable
		#define 	SPI0_MIOM		0			//	Multiple IO modes enable
												//		0: Disable Multiple IO mode
												//		1: Dual IO mode (DIOM)
												//		2: Quad SPI mode (QSPI)
		#define 	SPI0_SOSI		0			//	Valid only in MIOM
												//		0: start on MISO(in DOIM) or on SPIQ3 (in QSPI)
												//		1: start on MOSI

/**************************************************************************************************
 	 	 	 *******************		macros related to SPI0 TX CONTROL REGISTER 	***************
***************************************************************************************************/
		#define		SPI0_TTI		0			//	1:	Transmit Transfer Initiate
		#define		SPI0_TWCEN		0			//	1:	Transmit word count Enable
		#define		SPI0_TDU		1			//	0:	send last word on underrun, 	1: send zero on underrun
		#define		SPI0_TDR		1			//	Assert Transmit Data Request on following condition
												//		0:	Disabled
												//		1:	TFIFO not full
												//		2:	TFIFO 25% empty
												//		3:	TFIFO 50% empty
												//		4:	TFIFO 75% empty
												//		5:	TFIFO empty
		#define		SPI0_TRWM		0			//	FIFO regular water-mark (condition to clear TUWM flag)
												//		0:	TFIFO full
												//		1:	TFIFO 25% empty
												//		2:	TFIFO 50% empty
												//		3:	TFIFO 75% empty
		#define		SPI0_TUWM		0			//	FIFO urgent water-mark (condition to set TUWM flag and assert intr)
												//		0:	Disabled
												//		1:	TFIFO 25% empty
												//		2:	TFIFO 50% empty
												//		3:	TFIFO 75% empty
												//		4:	TFIFO empty

/**************************************************************************************************
 	 	 	 *******************		macros related to SPI0 RX CONTROL REGISTER 	***************
***************************************************************************************************/
		#define		SPI0_RTI		1			//	1:	Receive Transfer Initiate
		#define		SPI0_RWCEN		0			//	1:	Receive word count Enable
		#define		SPI0_RDO		1			//	0:	Discard incoming data on overflow, 	1: overwrite old data on overflow
		#define		SPI0_RDR		1			//	Assert Receive Data Request on following condition
												//		0:	Disabled
												//		1:	RFIFO not empty
												//		2:	RFIFO 25% full
												//		3:	RFIFO 50% full
												//		4:	RFIFO 75% full
												//		5:	RFIFO full
		#define		SPI0_RRWM		3			//	FIFO regular water-mark (condition to clear RUWM flag)
												//		0:	RFIFO empty
												//		1:	RFIFO 25% full
												//		2:	RFIFO 50% full
												//		3:	RFIFO 75% full
		#define		SPI0_RUWM		0			//	FIFO urgent water-mark (condition to set RUWM flag and assert intr)
												//		0:	Disabled
												//		1:	RFIFO 25% full
												//		2:	RFIFO 50% full
												//		3:	RFIFO 75% full
												//		4:	RFIFO full

/**************************************************************************************************
 	 	 	*******************		macros related to SPI0 CLOCK and DELAY REGISTER 	***********
***************************************************************************************************/

		#define 	SPI0_BAUD		100			//	[15:0]	BAUD = [SCLK1/(SPI_clock)] - 1 ;
		#define 	SPI0_STOP		1			//	[ 7:0]	Transfer delay time in multiples of SCK
		#define 	SPI0_LEADx		0			//	1:		Extended (1 SCK) LEAD control
		#define 	SPI0_LAGx		0			//	1:		Extended (1 SCK) LAG  control


/**************************************************************************************************
 	 	 	 *******************		macros related to SPI0 SSEL REGISTER 	*******************
**************************************************************************************************/

		#define 	SPI0_SSE1		0			//	1: SPI_SSEL1 enable
		#define 	SPI0_SSE2		0			//	1: SPI_SSEL2 enable,  muxed with SPI0D3
		#define 	SPI0_SSE3		0			//	1: SPI_SSEL3 enable,  muxed with SPI0D2
		#define 	SPI0_SSE4		0			//	1: SPI_SSEL4 enable
		#define 	SPI0_SSE5		0			//	1: SPI_SSEL5 enable,  muxed with SPI1_SSEL4
		#define 	SPI0_SSE6		0			//	1: SPI_SSEL6 enable
		#define 	SPI0_SSE7		0			//	1: SPI_SSEL7 enable



#endif /* SPI_FUNC_H_ */
