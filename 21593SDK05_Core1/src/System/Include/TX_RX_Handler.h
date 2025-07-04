/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	TX_RX_Handler.h
*  Description      :
******************************************************************************/
#ifndef TX_RX_HANDLER_H_
#define TX_RX_HANDLER_H_


#include "Commn.h"
#include "Extern_Core1.h"
#include <services/dma/adi_dma.h>
#include <drivers/sport/adi_sport.h>
#include "string.h"
#include "Def_Struct.h"
#pragma default_section(DATA,"Seg_TX_RX_Handler_Data")

extern int TX_EXT_DMA_BUFFER[];
extern int *Next_dac_count;
extern int *predac_rd_ptr_c1;
extern ADI_DMA_STREAM_HANDLE   hMemDmaStream;

int Current_DMA_address = 0;
int *Reference_Start_Address;
int srcAddress;
int dstAddress;
int mdma_done = 0;
int Dma_Buff_Size = NO_OF_PREDAC_CHANNEL*NO_OF_TX_SAMPLE_COUNT;
int counttransmitter;
int read_status = 0;
int curr_DMA_ptr_tx=0;
static bool bMemCopyInProgress = true;
#ifdef DSD2PCM_TESTING
int enable = 0;
int Data_Valid =0;
//int input_L_buf_ptr;
#endif

void receiver1(void);
void receiver2(void);
void transmitter(void);
void SET_TIMER(void);
void CALCULATE_MIPS(int*);


#endif  /*	TX_RX_HANDLER_H_  */
