/***************************************************************************
 *
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
 *
 *  Project          :  	21593SDK
 *  Organization     :  	Jasmin Infotech Private Limited,Chennai
 *  File Name        :	Tx_Rx_Handler.c
 *  Description      :   Rx and Tx interrupt functions
 ******************************************************************************/
#pragma default_section(CODE,"Seg_TX_RX_Handler_Code")
#pragma default_section(ALLDATA,"Seg_TX_RX_Handler_Data")
#include "..\src\system\Include\TX_RX_Handler.h"
#include <cdef21593.h>
#include "../Include/Function_Prototype.h"

//#define MDMA_DEBUG  //only for debugging purpose not to releses for customers
#ifdef MDMA_DEBUG
int Tx_DMA_Wait_Cnt = 0;
#endif

/******************************************************************************
 *  Module Name        : Rx_DMA_HANDLER
 *  Functionality      : Input buffer fill completed Trigger DMA Receiver
 *  					 Handler either Single I2S or Four I2S
 *  					 based on auto_detection mode
 *  Input Parameters   : handlerArg
 *  Output Parameters  : None
 ******************************************************************************/
void Rx_DMA_HANDLER(int iid, void *handlerArg)
{
#ifdef SPDIF_MODULE
	if(SPDIF_Enable == 1)
	{
		Current_DMA_address=(int)*pREG_DMA12_ADDRSTART;
	}
	else
#endif
	{
		Current_DMA_address=(int)*pREG_DMA0_ADDRSTART;
	}

	Reference_Start_Address= (int*)((int)RX_SP0A_BUFFER_LCRSW0|(int)MP_OFFSET);

	if(Current_DMA_address==(int)Reference_Start_Address)
	{
		counttransmitter=1;
		if(((Frmwk.autodetect_mode<4) || (Frmwk.autodetect_mode==0xa))
#ifdef DSD2PCM_DEC
				&& (!Frmwk.InitDoneForDSD2PCM)
#endif
		)
		{
			receiver1();
		}
		else
		{
			receiver2();
		}
	}
	else 
	{
		counttransmitter=0;
		if(((Frmwk.autodetect_mode<4) || (Frmwk.autodetect_mode==0xa))
#ifdef DSD2PCM_DEC
				&& (!Frmwk.InitDoneForDSD2PCM)
#endif
		)
		{
			receiver1();
		}
		else
		{
			receiver2();
		}
	}

}

/******************************************************************************
 *  Module Name        : Tx_DMA_HANDLER
 *  Functionality      : Input buffer fill completed Trigger DMA Transmitter
 *  					 Handler for Transmission
 *  Input Parameters   : iid ,handlerArg
 *  Output Parameters  : None
 ******************************************************************************/
void Tx_DMA_HANDLER(int iid, void *handlerArg)
{
	uint32_t Event = (uint32_t)handlerArg;
	if(Event & (ADI_SPORT_HW_ERR_FS | ADI_SPORT_HW_ERR_SECONDARY_CHNL_OVERFLOW | ADI_SPORT_HW_ERR_SECONDARY_CHNL_UNDERFLOW | ADI_SPORT_HW_ERR_PRIMARY_CHNL_OVERFLOW | ADI_SPORT_HW_ERR_PRIMARY_CHNL_UNDERFLOW))
	{
		return;
	}


	#ifdef BEO_Framework
	if((I2S_TDM_MODE == I2S_MODE) || (I2S_TDM_MODE == ASRC_TDM_MODE))
	{
		Current_DMA_address=(int)*pREG_DMA4_ADDRSTART;
		Reference_Start_Address= (int*)((int)TX_SP2A_BUFFER_LCRSW0|(int)MP_OFFSET);
	}
	#else
	Current_DMA_address=(int)*pREG_DMA10_ADDRSTART;
	Reference_Start_Address= (int*)((int)TX_SP4A_BUFFER_LCRSW0|(int)MP_OFFSET);
	#endif /* BEO_Framework */

#ifdef CORE1_TX
	Frmwk.IOP.NextDacCount=Frmwk.SampleBlock;
#else
	Frmwk.IOP.NextDacCount=*Next_dac_count;
	Frmwk.IOP.Predac.wr_ptr_c2=*predac_wr_ptr_c2;
#endif

	Frmwk.internal_Tx_buff =(int )&TX_EXT_DMA_BUFFER[0];


	if(mdma_done==1)
	{
#ifdef MDMA_DEBUG
		Tx_DMA_Wait_Cnt = 666666;
		while(bMemCopyInProgress && Tx_DMA_Wait_Cnt>=0)
		{
			Tx_DMA_Wait_Cnt--;
			adi_mdma_IsCopyInProgress (hMemDmaStream, &bMemCopyInProgress);
		}
#else
		while(bMemCopyInProgress)
		{
			adi_mdma_IsCopyInProgress (hMemDmaStream, &bMemCopyInProgress);
		}
#endif
		curr_DMA_ptr_tx=Frmwk.IOP.Predac.rd_ptr;
		mdma_done=0;
	}

	if(Current_DMA_address==(int)Reference_Start_Address)
		PP_flag=1;
	else
		PP_flag=0;

	transmitter();
	*predac_rd_ptr_c1=Frmwk.IOP.Predac.rd_ptr;
	mdma_done = 0;

	if(Frmwk.IOP.DataValid==1)
	{
		srcAddress = curr_DMA_ptr_tx;
		dstAddress = (int)&TX_EXT_DMA_BUFFER[0];

#if defined (USE_MDMA_EXTCHANNEL) || defined (TX_NEW_LOGIC)
		if(srcAddress!=0)
		{
			EXTMDMA_enable(Dma_Buff_Size, srcAddress, dstAddress);
		}
		else
		{
			/* Clear the given memory */
			memset((void*)dstAddress, 0, Dma_Buff_Size);
		}
		curr_DMA_ptr_tx=Frmwk.IOP.Predac.rd_ptr;
		mdma_done = 1;
#else//striaght copy instead of MDMA
		Predac_buffer_to_Tx_DMA(srcAddress,dstAddress);
		curr_DMA_ptr_tx=Frmwk.IOP.Predac.rd_ptr;
		mdma_done = 1;
#endif
		bMemCopyInProgress=true;
	}
	else
	{
		curr_DMA_ptr_tx=Frmwk.IOP.Predac.rd_ptr;

	}
}

void Predac_buffer_to_Tx_DMA(int* srcptr,int* dstptr)
{
	int k=0,l=0;
	for(int i = 0;i<NO_OF_TX_SAMPLE_COUNT;i++)
	{
		for(int j = 0;j<NO_OF_PREDAC_CHANNEL;j++)
		{
			dstptr[l++] = srcptr[k++];
		}	
	}
}

