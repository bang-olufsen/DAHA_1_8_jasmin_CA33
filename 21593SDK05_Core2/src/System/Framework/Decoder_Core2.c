/*****************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Decoder_Core2.c
*  Description      :   Decoder routines

******************************************************************************/
/******************************************************************************/
#pragma default_section(CODE,"Seg_Decoder_Core2")
#include "../src/System/Include/Decoder_Core2.h"
#include "../src/System/Include/Function_Prototype.h"

/******************************************************************************
*  Module Name        : PlayForgnd
*  Functionality      : All Decoders wrapper should be placed here, 
*						In addition to the decoder wrapper, Memory allocation of Kernel I/O Buffers for decoder will be done here
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
int PlayForgnd(void)
{
	Frmwk.Init_begin_core2	= *Init_Start_Command_c1;

#ifdef MCPCM_DECODER
	Frmwk.StreamType=0xF;
	Frmwk.MCLPCMEnable=1;
	if((Frmwk.StreamType==0xF)&&(Frmwk.MCLPCMEnable==1))
	{
		/* Check if there is a necessity for Allocating Memory */
		if(Frmwk.InitDoneForStreamType!= Frmwk.StreamType)
		{
			if(Free_AllotMemoryPackDac(Frmwk.pack_length_mcpcm, Frmwk.predac_length_mcpcm, 1)==1)
			{
				return 1;
			}

			FreeMemoryAll();									/* Free Previously allocated memory */
			Frmwk.Stream_Profile            = *Stream_Profile;
			Stream_Type_frm_Core1 	        = *stream_type;
			Frmwk.IOP.Predac.length	    	= *Predac_length;
			Frmwk.IOP.Predac.lengthhalf	    = *Predac_length_half;
			Frmwk.SampleBlock				= SAMPLE_BLOCK_MCPCM;
			Frmwk.Max_No_of_channel		    = NO_OF_PREDAC_CHANNEL;  /* Initialise stream detection variables to start fresh detection */
			BufSize                         = (Frmwk.SampleBlock*Frmwk.Max_No_of_channel);
			Frmwk.InitDoneForStreamType 	= 0xF;
			Init_Var();											//  General Initialization routine
			Frmwk.ADI_DecoderError 			= 2;
			return 0;
		}
		else
		{
			MCPCMDecoder();
			return 0;
		}
	}
#endif
	return 0;
}

#ifdef MCPCM_DECODER
void MCPCMDecoder(void)
{
	Frmwk.ADI_DecoderError = NO_ERROR;
	while(1)
	{
		int i,j;
		if(Frmwk.IOP.datacanbeprocessednow == 0)
		{
			Frmwk.IOP.Predac.rd_ptr_c2 		=*Latency_predac_wr_ptr_c1 ;
			Frmwk.IOP.Predac.wr_ptr_c2 		=*Latency_predac_wr_ptr_c1 ;
			*predac_wr_ptr_c1               =*Latency_predac_wr_ptr_c1 ;
			Frmwk.IOP.AddPreDac.heap		=*addpredac_heap;
			Frmwk.IOP.AddPreDac.rd_ptr_c2	=*addpredac_rd_ptr;
		    Frmwk.IOP.AddPreDac.wr_ptr_c2	=*addpredac_wr_ptr;
		    Frmwk.IOP.AddPreDac.length		=*addpredac_length;
		    Frmwk.IOP.AddPreDac.lengthhalf 	=*addpredac_lengthhalf;

			for(int i=0;i<BufSize;i++)
			{
				Predac_buffer_Int_c2[i]=0;
			}
			Frmwk.IOP.datacanbeprocessednow = 1;
		}

		Frmwk.IOP.Predac.wr_ptr_c1=*predac_wr_ptr_c1;

		i = Frmwk.IOP.Predac.wr_ptr_c1-Frmwk.IOP.Predac.rd_ptr_c2;

		if(i < 0)
		{
			i = i + ((Frmwk.IOP.Predac.length)*4);
		}
		if((i - ((Frmwk.SampleBlock*Frmwk.Max_No_of_channel)*4))  < 0)
		{
			Frmwk.ADI_DecoderError = FILLED_SPACE_ERROR;
			break;
		}

		Control_DataVariable_Update();
		*core2_sync_bit=1;

		#ifdef MDMA_COPY
			int BufSize_remain = 0,BufSize_MDMA = 0;
			Predac_Length_Ptr=Frmwk.IOP.Predac.heap+(Frmwk.IOP.Predac.length*4);
			bMemCopyInProgress_check = true;
			BufSize_MDMA=(Frmwk.SampleBlock*Frmwk.Max_No_of_channel);
			SrcBuf=Frmwk.IOP.Predac.rd_ptr_c2;
			DstBuf=(int)&Predac_buffer_Int_c2[0];

			if((Predac_Length_Ptr-SrcBuf)<(Frmwk.SampleBlock*Frmwk.Max_No_of_channel*4))
			{
				BufSize_remain=(Predac_Length_Ptr-SrcBuf)/4;
				MDMA_Copy(BufSize_remain, SrcBuf, DstBuf);
				while(bMemCopyInProgress_check)
				{
					adi_mdma_IsCopyInProgress (hMemDmaStream2, &bMemCopyInProgress_check);
				}
				BufSize_MDMA=BufSize_MDMA-BufSize_remain;
				SrcBuf=Frmwk.IOP.Predac.heap;
				DstBuf=DstBuf+(BufSize_remain*4);
			}
			bMemCopyInProgress_check = true;
			MDMA_Copy(BufSize_MDMA, SrcBuf, DstBuf);

			while(bMemCopyInProgress_check)
			{
				adi_mdma_IsCopyInProgress (hMemDmaStream2, &bMemCopyInProgress_check);
			}
		#else
			Predac_buffer_to_Predac_buffer_Int();
		#endif

		#ifdef  CUSTOMER_PP
			Customer_Post_Processing();
		#endif

		Predac_buffer_Int_to_Predac_buffer();

		Pre_Dac_Ptr_Update_Rd_C2();

		Pre_Dac_Ptr_Update();
		Shared_Memory_Var_Update();

		Frmwk.ADI_DecoderError = NO_ERROR;
		break;
	}//While Loop
}
#endif
void Shared_Memory_Var_Update(void)
{
	*predac_wr_ptr_c2 	 = Frmwk.IOP.Predac.wr_ptr_c2;  // Send Predac Write pointer to core for Filled space checking
	*Next_dac_count   	 = Frmwk.IOP.NextDacCount; 		// Send DAC count for transmitting data's
}

void Control_DataVariable_Update(void)
{
	Frmwk.OutputSampleRate  	  = *Frmwk_Outputsamplerate_c1;
	Sampling_freq				  = *Frmwk_Outputsamplerate_c1;
    /****2315****/
	Stream_Type_frm_Core1 		  = *stream_type;
	Frmwk.Customer_pp.ChannelMask = *Frmwk_nchannels_in_c1;
}

/******************************************************************************
*  Module Name        : Init_Var
*  Functionality      : Variables which is need to be initialized to restart the system process for any decoder switching and decoder error case should be placed here
						In this framework, Latency process & system process for decoder are initiated
						This function will be called during PLAY, STOP, SPORT INIT command & decoder error case
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
void Init_Var(void)
{
	Frmwk.IOP.datacanbeprocessednow = 0;
}

/******************************************************************************
*  Module Name        : Init_Var_Fs
*  Functionality      : Variables which is need to be initialized to restart the system process for decoder fs switching caseshould be placed here
						In this framework, Latency process & system process for decoder are initiated
						This function will be called in GENERAL_DECODING_COMMAND command Fs switching case
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
void Init_Var_Fs(void)
{
	Frmwk.IOP.datacanbeprocessednow = 0;
}

#ifdef MDMA_COPY
/******************************************************************************
 *  Module Name        : MDMA_init
 *  Functionality      : MDMA Initialization
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
void MDMA_init(void)
{
	adi_mdma_Open (ADI_DMA_MEMDMA_S1,
					  &MemDmaStreamMem2[0],
					  &hMemDmaStream2,
					  &hSrcDmaChannel2,
					  &hDestDmaChannel2,
					  NULL,
					  NULL);

}
/******************************************************************************
 *  Module Name        : MDMA_Copy
 *  Functionality      : Copying data using MDMA1
 *  Input Parameters   : Buffer size, Source buffer and Destination buffer
 *  Output Parameters  : None
 ******************************************************************************/
void MDMA_Copy(int BuffSize, int SrcBuff, int DstBuff)
{
	adi_mdma_Copy1D(
					hMemDmaStream2,
					(void*)DstBuff,
					(void*)SrcBuff,
					ADI_DMA_MSIZE_4BYTES,
					BuffSize);
}
#endif

