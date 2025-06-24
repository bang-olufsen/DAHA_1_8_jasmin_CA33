/***************************************************************************
 *
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
 *
 *  Project          :  	21593SDK
 *  Organization     :  	Jasmin Infotech Private Limited,Chennai
 *  File Name        :	System_Modules.c
 *  Description      :
 ******************************************************************************/
#pragma default_section(CODE,"Seg_System_Init_Code")
#pragma default_section(ALLDATA,"Seg_System_Init_Data")
#pragma default_section(SWITCH,"Seg_System_Init_Data")
#include "../Include/System_Modules.h"
#include "../Include/Function_Prototype.h"
#include "sru.h"
#include "../Include/Extern_Core1.h"
#include "../Include/Buff_Ptr_Defines.h"



/**************************************************************************************************
 *  Module Name        : FreeMemoryAll
 *  Functionality      : Kernel I/O buffers should be cleared here
 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/
void FreeMemoryAll(void)
{
	if(Frmwk.MemoryAllotPack)
	{
		for(int i=0;i<Frmwk.IOP.Pack.length;i++)
		{
			Pack_buffer_ext[i]=0;
		}
		Frmwk.MemoryAllotPack = 0;
	}
	if(Frmwk.MemoryAllotDac)
	{
		for(int i=0;i<Frmwk.IOP.Predac.length;i++)
		{
			Predac_buffer_Ext[i]=0;
		}
		Frmwk.MemoryAllotDac=0;
	}
#ifdef NOISEGEN

	if(Frmwk.MemoryAllotNoise)
	{
		//free (Frmwk.NoiseGen.noise_dummyptr);
		for(int i=0;i<(10*sizeof (int));i++)
			Frmwk.NoiseGen.noise_dummyptr[i]=0;

		//free (Frmwk.NoiseGen.noise_heap->pcmout_buf_heap);
		for(int i=0;i<(8*sizeof (int));i++)
			Frmwk.NoiseGen.noise_heap->pcmout_buf_heap[i]=0;

		//free (Frmwk.NoiseGen.noise_heap->random_heap);
		for(int i=0;i<(512*sizeof (int));i++)
			Frmwk.NoiseGen.noise_heap->random_heap[i]=0;

		//free (Frmwk.NoiseGen.noise_heap->pink_outbuf_temp_heap);
		for(int i=0;i<(256*sizeof (int));i++)
			Frmwk.NoiseGen.noise_heap->pink_outbuf_temp_heap[i]=0;

		//free (Frmwk.NoiseGen.noise_heap);
		for(int i=0;i<(sizeof(struct noise_lib)*4);i++)
			Noisegen_structure_Buffer[i]=0;

		Frmwk.MemoryAllotNoise=0;
	}
#endif

}
/**************************************************************************************************
 *  Module Name        : Init_Var
 *  Functionality      : Variables which is need to be initialized to restart the system process for
 *  					any decoder switching and decoder error case should be placed here
						In this framework, Latency process & system process for decoder are initiated
						This function will be called during PLAY, STOP, SPORT INIT command & decoder error case
 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/
void Init_Var(void)
{
	Frmwk.IOP.LatencyDone			= 0;
	Frmwk.IOP.datacanbeprocessednow	= 0;
	Frmwk.IOP.DataValid             = 0;
	PP_process_cnt 					= 0;
#ifdef NOISEGEN
	Frmwk.init_noise_gen 			= 1;	// Noise Generator
#endif
#ifdef DE_EMPHASIS_PP
	Frmwk.init_deemphasis			= 1;	// For De-Emphasis
#endif
#ifdef AAC_DEC
	Frmwk.AAC.error_frame			= 0;
	Frmwk.AAC.CRC_ERROR				= 0;
	Frmwk.AAC.Profile				= 0;
	Frmwk.AAC.Framecount_AAC 		= 0;
	Frmwk.AAC.FrameSize_768_flag 	= 0;
#endif
#ifdef MPEGH_DECODER
	Input_Channel_Config_Mask         = 0;
	Mpegh_LFE_Present                 = 0;
#endif

#ifdef DSD2PCM_DEC
	DSD2PCM_Initialisation = 0;
#endif

#if defined (DOLBY_DDP)|| defined (DOLBY_DD)
	Frmwk.DDPlus.InitDecoder    			= 0;
	Frmwk.DDPlus.FramenumberDDP 			= 0;
	Frmwk.DDPlus.prevddpsamplerate			= 0;
	Frmwk.DDPlus.previousoutputmap			= 0;
	Frmwk.DDPlus.prevjocd_out_mode			= 0;
	Frame_DD_Error 							= 0;
#endif /* (DOLBY_DDP)|| (DOLBY_DD) */
#ifdef DOLBY_LIB
	Frmwk.ATMOS_Info 						= 0;
#endif
#ifdef DOLBY_DMX
	Frmwk.dmx_Frmwk.dmx_init_done 			= 0;
	Frmwk.dmx_Frmwk.dmx_params_b_bypass 	= 0;
	Frmwk.DAP_krnl.Prev_DMX_ChannelMapping 	= 0;
#endif /* DOLBY_DMX */

#ifdef DOLBY_DAP
	Frmwk.DAP_krnl.DAP_Init_Done 			= 0;
	Frmwk.DAP_krnl.DMX_ChannelMapping 		= 0;
	Frmwk.DAP_krnl.DAP_Process_Error 		= 0;
	Frmwk.DAP_krnl.DAP_ON_OFF 				= 1;
	Frmwk.DAP_krnl.DAP_first_frame 			= 1;
	Frmwk.FADER_Frmwk.fader_active 			= 0;
	Frmwk.DAP_krnl.DAP_prev_nchannels_in 	= 0;
	Frmwk.DAP_krnl.DAP_Init_Skip			= 0;
	Frmwk.DAP_krnl.DolbyUpmixer_Done_temp	= 0;
#endif /* DOLBY_DAP */
#ifdef DOLBY_OAR
	Frmwk.OAR_Frmwk.OARiInitFlag 			= 1;
	Frmwk.OAR_Frmwk.OAR_b_enable_limiter	= 1;
	Frmwk.OAR_Frmwk.Do_OARi_OAR_Process 	= 0;
	Frmwk.OAR_Frmwk.OAR_Done_temp 			= 0;
	Sync_detected							= 0;
#endif /* DOLBY_OAR */
#if defined (DOLBY_THD)|| defined (DOLBY_MAT)
	Frmwk.TRUEHD.IEC_MAT_BUF_FLAG 			= 1;
	Frmwk.TRUEHD.MDcnt 						= 0;
	Frmwk.TRUEHD.Prev_MDcnt 				= 0;
	//Frmwk.MAT.Decoder_cnt_MAT 			= 0;
	Frmwk.TRUEHD.PP_flag 					= 0;
	Frmwk.mat_direct_mode 					= 0;

#endif /* (DOLBY_THD) || (DOLBY_MAT) */
	#ifdef DOLBY_THD_DA
	THD_Info_Ret							= 0;
	#endif /* DOLBY_THD_DA */
#ifdef DOLBY_LIB
#if defined (DOLBY_DDP) || defined (DOLBY_MAT)
	Frmwk.Obj_Obj_Switch					= 0;
	Frmwk.Obj_Ch_Switch 					= 0;
	Frmwk.Ch_Obj_Switch	 					= 0;
	Frmwk.Ch_Ch_Switch 						= 0;
	prev_stream_decoder_assign				= 0;
	prev_stream_profile_mat					= 0;
	Frmwk.End_of_Sequence_MAT_DDP 			= 0;
#endif /* (DOLBY_DDP) || (DOLBY_MAT) */
#endif /* DOLBY_LIB */
	Frmwk.init_ds_processing 				= 1;
	mono_chnl_Modifier = 1;

}
/**************************************************************************************************
 *  Module Name        : Init_Var_Fs
 *  Functionality      : Variables which is need to be initialized to restart the
 *  					system process for decoder fs switching case should be placed here
						In this framework, Latency process & system process for decoder are initiated
						This function will be called in GENERAL_DECODING_COMMAND command Fs switching case

 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/
void Init_Var_Fs(void)
{
	Frmwk.IOP.LatencyDone			= 0;
	Frmwk.InitDoneForStreamType		= INVALID;
	Frmwk.IOP.datacanbeprocessednow	= 0;
	Frmwk.MemoryAllotMCLPCM			= 0;
	Frmwk.init_ds_processing 				= 1;
#ifdef DE_EMPHASIS_PP
	Frmwk.init_deemphasis			= 1;
#endif
}

/**************************************************************************************************
 *  Module Name        : Free_AllotMemoryPackDac
 *  Functionality      : Initializing Receiver & transmitter SPORT DMA buffer pointers, SPI buffer pointers
 *  Input Parameters   : size1, size2, val1
 *  Output Parameters  : None
 *************************************************************************************************/
void Free_AllotMemoryPackDac( int size1, int size2, int val1)
{
	Frmwk.Autdet.StreamDetectEnable   = 0;
	Frmwk.IOP.Pack.length 			  = size1;
	Frmwk.IOP.Pack.lengthhalf 		  = size1/TWO_HALF;
#ifdef MPEGH_DECODER
	if(Frmwk.Enable_Factor_MPEGH == 1)
	{
		Frmwk.IOP.Pack.lengthhalf 	  = size1/FOUR_HALF;
	}
#endif
	FreeMemoryAll();

	if(Frmwk.MemoryAllotPack==0)
	{
		Frmwk.IOP.Pack.heap   		  = (int) Pack_buffer_ext;
		Frmwk.MemoryAllotPack 	  	  = 1;
	}
	Frmwk.IOP.Pack.rd_ptr			  = (int)Frmwk.IOP.Pack.heap;
	Frmwk.IOP.Pack.wr_ptr 			  = (int)Frmwk.IOP.Pack.heap;
	Frmwk.Autdet.HeaderAddress 		  = (int)Frmwk.IOP.Pack.heap;

	//After memory allocation of kernel I/O buffers, Re-initiate the stream detection process
	Frmwk.Autdet.AlignFlg   		  = 0;
	Frmwk.Autdet.MSGR_Save 			  = SYNCSIGUNKNOWN;
	Frmwk.Autdet.MSGR4 				  = SYNCSIGUNKNOWN;
	Frmwk.StreamType 				  = SYNCSIGUNKNOWN;
	if(Frmwk.MemoryAllotDac == 0)
	{
		Frmwk.IOP.Predac.heap     	  = (int)Predac_buffer_Ext;
		Frmwk.IOP.AddPreDac.heap  	  = (int)AddPredac_buffer_Int;
		Frmwk.MemoryAllotDac          = 1;
	}
	while(Frmwk.IOP.DataValid==1);
#ifndef CORE1_TX
	*datacanbeprocessnow=0;
	Wait_Core1(core2_dcpn_done,0);
#endif

	Frmwk.IOP.Predac.length 	 	  = size2;
	Frmwk.IOP.Predac.lengthhalf  	  = size2/THREE_HALF;
	Frmwk.IOP.Predac.wr_ptr		  	  = (int)Frmwk.IOP.Predac.heap;
	Frmwk.IOP.Predac.wr_ptr_dec		  = (int)Frmwk.IOP.Predac.heap;
	Frmwk.IOP.Predac.rd_ptr   		  = (int)Frmwk.IOP.Predac.heap;
#ifdef MPEGH_DECODER
	if(Frmwk.Enable_Factor_MPEGH == 1)
	{
		Frmwk.IOP.Predac.lengthhalf  	  = size2/MPEGH_Predac_Factor;
	}
#endif
	Frmwk.IOP.AddPreDac.length		  = val1;
	Frmwk.IOP.AddPreDac.lengthhalf	  = val1/THREE_HALF;
	Frmwk.IOP.AddPreDac.rd_ptr		  = (int)Frmwk.IOP.AddPreDac.heap;
	Frmwk.IOP.AddPreDac.wr_ptr		  = (int)Frmwk.IOP.AddPreDac.heap;
	Frmwk.Autdet.StreamDetectEnable   = 1;

	*predac_wr_ptr_c2   	  		  = (int)Frmwk.IOP.Predac.heap;
	*Predac_length			          = size2;
	*predac_heap                      = (int)Predac_buffer_Ext;
	*predac_wr_ptr		              = (int)Frmwk.IOP.Predac.heap;
	*Latency_predac_wr_ptr_c1         = (int)Frmwk.IOP.Predac.heap;
	*Init_Start_Command_c1            = 0;

	*addpredac_heap                   = (int)Frmwk.IOP.AddPreDac.heap;
	*addpredac_wr_ptr		          = (int)Frmwk.IOP.AddPreDac.heap;
	*addpredac_rd_ptr                 = (int)Frmwk.IOP.AddPreDac.heap;
	*addpredac_length                 = (int)Frmwk.IOP.AddPreDac.length;
}
/**************************************************************************************************
 *  Module Name        : AllocateMemoryKernel
 *  Functionality      : Memory allocation for Transmitter and receiver DMA's
 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/
void AllocateMemoryKernel(void)
{
	int InAutobuf_temp_ptr;
	InAutobuf_temp_ptr =  (int)&InAutobuf[0];
	Frmwk.Autdet.InAutbuf_ptr	 			  = (int*)InAutobuf_temp_ptr;


	Frmwk.Rx.DummyInAutbuf0_ptr				  = RX_SP0A_BUFFER_LCRSW0;
	Frmwk.Rx.DummyInAutbuf1_ptr				  = RX_SP0A_BUFFER_LCRSW1;
	Frmwk.Rx.DummyInAutbuf2_ptr				  = RX_SP0B_BUFFER_LsLsrRsRsr0;
	Frmwk.Rx.DummyInAutbuf3_ptr				  = RX_SP0B_BUFFER_LsLsrRsRsr1;
	#ifdef BEO_Framework
	if((I2S_TDM_MODE == I2S_MODE) || (I2S_TDM_MODE == ASRC_TDM_MODE))
	{
		Frmwk.Tx.dac_buf_LCRSw0_ptr 			  = TX_SP2A_BUFFER_LCRSW0;
		Frmwk.Tx.dac_buf_LCRSw1_ptr				  = TX_SP2A_BUFFER_LCRSW1;
		Frmwk.Tx.dac_buf_LsLsrRsRsr0_ptr		  = TX_SP2B_BUFFER_LsLsrRsRsr0;
		Frmwk.Tx.dac_buf_LsLsrRsRsr1_ptr		  = TX_SP2B_BUFFER_LsLsrRsRsr1;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set0_ptr = TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set1_ptr = TX_SP3A_BUFFER_Addch1ch3ch2ch4_set1;
		Frmwk.Tx.dac_buf_addch5ch7ch6ch8_set0_ptr = TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0;
		Frmwk.Tx.dac_buf_addch5ch7ch6ch8_set1_ptr = TX_SP3B_BUFFER_Addch5ch7ch6ch8_set1;
	}
	#else
#ifdef I2S_TDM_MODE_ENABLE
	if((I2S_TDM_MODE == I2S_MODE) || (I2S_TDM_MODE == ASRC_MODE)||(I2S_TDM_MODE == ASRC_TDM_MODE))
#endif
	{
		Frmwk.Tx.dac_buf_LCRSw0_ptr 			  = TX_SP4A_BUFFER_LCRSW0;
		Frmwk.Tx.dac_buf_LCRSw1_ptr				  = TX_SP4A_BUFFER_LCRSW1;
		Frmwk.Tx.dac_buf_LsLsrRsRsr0_ptr		  = TX_SP4B_BUFFER_LsLsrRsRsr0;
		Frmwk.Tx.dac_buf_LsLsrRsRsr1_ptr		  = TX_SP4B_BUFFER_LsLsrRsRsr1;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set0_ptr = TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set1_ptr = TX_SP3A_BUFFER_Addch1ch3ch2ch4_set1;
		Frmwk.Tx.dac_buf_addch5ch7ch6ch8_set0_ptr = TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0;
		Frmwk.Tx.dac_buf_addch5ch7ch6ch8_set1_ptr = TX_SP3B_BUFFER_Addch5ch7ch6ch8_set1;
		if(I2S_TDM_MODE == I2S_MODE)
		{
		Frmwk.Tx.dac_buf_addch9ch11ch10ch12_set0_ptr 	= TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0;
		Frmwk.Tx.dac_buf_addch9ch11ch10ch12_set1_ptr	= TX_SP6A_BUFFER_Addch9ch11ch10ch12_set1;
		Frmwk.Tx.dac_buf_addch13ch15ch14ch16_set0_ptr 	= TX_SP2A_BUFFER_Addch13ch15ch14ch16_set0;
		Frmwk.Tx.dac_buf_addch13ch15ch14ch16_set1_ptr	= TX_SP2A_BUFFER_Addch13ch15ch14ch16_set1;
	}
 }
 	#endif /* BEO_Framework */
#ifdef I2S_TDM_MODE_ENABLE	
	else if(I2S_TDM_MODE == TDM_MODE)
	{
		Frmwk.Tx.dac_buf_LCRSw0_ptr 				= TX_SP4A_BUFFER_LCRSW0;
		Frmwk.Tx.dac_buf_LCRSw1_ptr					= TX_SP4B_BUFFER_LsLsrRsRsr0;

		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set0_ptr 	= TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set1_ptr 	= TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0;

		Frmwk.Tx.dac_buf_addch9ch11ch10ch12_set0_ptr = TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0;
		Frmwk.Tx.dac_buf_addch9ch11ch10ch12_set1_ptr = TX_SP2A_BUFFER_Addch13ch15ch14ch16_set0;

		TX_SP4A_BUFFER_LCRSW0_BUF 					= &TX_SP4A_BUFFER_LCRSW0[0];
		TX_SP4A_BUFFER_LsLsrRsRsr0_BUF				= &TX_SP4B_BUFFER_LsLsrRsRsr0[0];
		TX_SP3A_BUFFER_Addch1ch3Addch2ch4_set0_BUF	= &TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0[0];
		TX_SP3A_BUFFER_Addch5ch7Addch6ch8_set0_BUF 	= &TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0[0];
		TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0_BUF	= &TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0[0];
		TX_SP6A_BUFFER_Addch13ch15ch14ch16_set0_BUF	= &TX_SP2A_BUFFER_Addch13ch15ch14ch16_set0[0];
	}
#endif

#ifdef MPEGH_DECODER
	Frmwk.MPEGH_DecoderEnable = 1;
#endif
#ifdef AAC_DEC
	Frmwk.AACDecoderEnable = 1;
#endif
	Frmwk.LBRDecoderEnable = 1;
	Frmwk.DTSXDecoderEnable = 1;
#if defined (DOLBY_DDP) || defined (DOLBY_DD)	
	Frmwk.DOLBYDecoderEnable = 1;
	Frmwk.DDPLUSDecoderEnable = 1;
#endif
#if defined (DOLBY_THD) || defined (DOLBY_MAT)	
	Frmwk.TRUEHDDecoderEnable = 1;
#endif	
	switch(Frmwk.autodetect_mode)
	{
	case AUTODETECT1:
		Frmwk.Misc.Control.ForcePcm = 0;
		Frmwk.LPCMDelaySize_host = 0;
		Frmwk.PCMEnable = 1;
		Frmwk.MCLPCMEnable = 0;
		Frmwk.ADCEnable = 0;
		Frmwk.Autdet.autodetect3 = 0;
		break;

	case AUTODETECT2:
		Frmwk.Misc.Control.ForcePcm = 1;
		if(Frmwk.LPCM_delay_index==0) Frmwk.LPCMDelaySize_host = 1024;
		else if(Frmwk.LPCM_delay_index==1) Frmwk.LPCMDelaySize_host = 2048;
		else if(Frmwk.LPCM_delay_index==2) Frmwk.LPCMDelaySize_host = 4096;
		else if(Frmwk.LPCM_delay_index==3) Frmwk.LPCMDelaySize_host = 12288;
		else if(Frmwk.LPCM_delay_index==4) Frmwk.LPCMDelaySize_host = 16384;
		Frmwk.SampleDropCount = Frmwk.LPCMDelaySize_host;
		Frmwk.PCMEnable = 1;
		Frmwk.MCLPCMEnable = 0;
		Frmwk.ADCEnable = 0;
		Frmwk.Autdet.autodetect3 = 0;
#ifdef AAC_DEC
		Frmwk.AACDecoderEnable      = 0;
#endif
#ifdef MPEGH_DECODER
		Frmwk.MPEGH_DecoderEnable = 0;
#endif
		break;

	case AUTODETECT3:
		Frmwk.Misc.Control.ForcePcm = 0;
		Frmwk.LPCMDelaySize_host = 0;
		Frmwk.PCMEnable = 0;
		Frmwk.MCLPCMEnable = 0;
		Frmwk.Autdet.autodetect3 = 1;
		Frmwk.ADCEnable = 0;
		InAutobuf_temp_ptr =  (int)&InAutobuf[0];
		Frmwk.Rx.INPUTsamples_ptr 	= (int*)InAutobuf_temp_ptr;
		//  Frmwk.Rx.INPUTsamples_ptr = InAutobuf;
		Frmwk.Autdet.InAutbuf_ptr 	= Frmwk.Rx.INPUTsamples_ptr + (Frmwk.Misc.Control.InAutobufsizeby2*4);
#ifdef AAC_DEC
		Frmwk.AACDecoderEnable      = 0;
#endif
		break;

	case FORCEPCM2:
		Frmwk.Misc.Control.ForcePcm = 1;
		Frmwk.LPCMDelaySize_host = 0;
		Frmwk.PCMEnable=1;
		Frmwk.MCLPCMEnable=0;
		Frmwk.ADCEnable=0;
		Frmwk.Autdet.autodetect3 = 0;
#ifdef AAC_DEC
		Frmwk.AACDecoderEnable		= 0;
#endif
#if defined (DOLBY_DDP) || defined (DOLBY_DD)
		Frmwk.DOLBYDecoderEnable	= 0;
		Frmwk.DDPLUSDecoderEnable	= 0;
#endif	
#if defined (DOLBY_THD) || defined (DOLBY_MAT)	
		Frmwk.TRUEHDDecoderEnable	= 0;
#endif		
#ifdef MPEGH_DECODER
		Frmwk.MPEGH_DecoderEnable    = 0;
#endif
		break;

	case FORCEPCM3:
		Frmwk.Misc.Control.ForcePcm = 0;
		Frmwk.LPCMDelaySize_host = 0;
		Frmwk.PCMEnable = 0;
		Frmwk.MCLPCMEnable = 1;
		Frmwk.Autdet.autodetect3 = 0;
		Frmwk.ADCEnable = 0;
		Frmwk.MCLPCM_ON = 1;
		break;

	case FORCEADC:
		Frmwk.Misc.Control.ForcePcm = 0;
		Frmwk.LPCMDelaySize_host = 0;
		Frmwk.PCMEnable=1;
		Frmwk.MCLPCMEnable=0;
		Frmwk.ADCEnable=1;
		Frmwk.Autdet.autodetect3 = 0;
		break;

#ifdef CUSTOMIZATION
	case CUSTOMAUTODETECT1:
		Frmwk.Misc.Control.ForcePcm =0;
		Frmwk.LPCMDelaySize_host =0;
		Frmwk.PCMEnable =1;
		Frmwk.MCLPCMEnable =0;
		Frmwk.ADCEnable =0;
		Frmwk.Autdet.autodetect3 =0;
		break;
#endif

	default:
		break;
	}
}
#ifdef PCM_DEC
/**************************************************************************************************
 *  Module Name        : AllocateMemoryPCMDelay
 *  Functionality      : Allocation of Memory for LPCM delay pointers
 *  Input Parameters   : LPCMDelaySize
 *  Output Parameters  : None
 *************************************************************************************************/
void AllocateMemoryPCMDelay(int LPCMDelaySize)
{
	if(Frmwk.MemoryAllotPcm==0)
	{
		Frmwk.LPCMDelayBuffer_heap = (int)&LPCMDelayBuffer[0];
		Frmwk.MemoryAllotPcm=1;
	}
}
#endif
#ifdef DSD2PCM_DEC
#pragma section("seg_DSD2PCM_Code")
void DSD2PCM_MemoryAlloc()
{
	Free_AllotMemoryPackDac(Frmwk.pack_length_DSD2PCM,Frmwk.predac_length_DSD2PCM,Frmwk.addpredac_length_DSD2PCM);
	Frmwk.SampleBlock 		 = Frmwk.IOP.Predac.lengthhalf/NO_OF_PREDAC_CHANNEL;

#ifdef DOWNSAMPLING
	Frmwk.SampleBlock_DS = Frmwk.SampleBlock;
#endif
}
#pragma section("seg_DSD2PCM_Code")
void AllocateMemoryKernel_DSD2PCM()
{
	Frmwk.Autdet.InAutbuf_ptr	 			= InAutobuf;
	Frmwk.Rx.DSD2PCMInAutbuf_LR0_ptr		= RX_SP0A_BUFFER_LCRSW0;  		//LR
	Frmwk.Rx.DSD2PCMInAutbuf_LR1_ptr		= RX_SP0A_BUFFER_LCRSW1;
	Frmwk.Rx.DSD2PCMInAutbuf_CSW0_ptr		= RX_SP1A_BUFFER_DSD2PCM0;		//CSW
	Frmwk.Rx.DSD2PCMInAutbuf_CSW1_ptr		= RX_SP1A_BUFFER_DSD2PCM1;
	Frmwk.Rx.DSD2PCMInAutbuf_LsRs0_ptr		= RX_SP0B_BUFFER_LsLsrRsRsr0;	//LsRs
	Frmwk.Rx.DSD2PCMInAutbuf_LsRs1_ptr		= RX_SP0B_BUFFER_LsLsrRsRsr1;
}
#endif
/**************************************************************************************************
 *  Module Name        : SRU_Reconfigure
 *  Functionality      : Reconfiguring PCG clock based on input and output sample rate
 *  Input Parameters   : sample_fs_micro,
 *  Output Parameters  : Output_SampleRate
 *************************************************************************************************/
void SRU_Reconfigure(int sample_fs_micro,int Output_SampleRate)
{
//	PCG_Clock_Divider(sample_fs_micro, Output_SampleRate);
//
//	if(Prev_Clock_Div_Value != Clock_Div_Value)
//	{
//#ifdef I2S_TDM_MODE_ENABLE
//		if((I2S_TDM_MODE == I2S_MODE)||(I2S_TDM_MODE == ASRC_MODE)||(I2S_TDM_MODE == ASRC_TDM_MODE))
//#endif
//		{
//#ifdef SPDIF_MODULE
//			if (SPDIF_Enable == 1)
//			{
//				int CLKPHASE,CLKDIV;
//
//				CLKDIV = (4 * Spdif_fs_table[sample_fs_micro])/Spdif_fs_table[Output_SampleRate];
//
//				CLKPHASE = ((3+CLKDIV/2)%CLKDIV);    //To synchronize 64*fs2 with fs1 and it's falling edge with fs2
//
//				ADI_PCG_CLK_INFO gClkInfo_C;
//					gClkInfo_C.eClkInput = ADI_PCG_CLK_EXT;      	      /* Clock Source */
//					gClkInfo_C.nDiv = 0u;          					      /* Clock Divisor */
//					gClkInfo_C.bExternalTrigger = false;                  /* External Trigger */
//				ADI_PCG_FS_INFO gFsInfo_C;
//					gFsInfo_C.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_FS_EXT;                     /* Clock Source */
//					gFsInfo_C.nDiv = CLKDIV;     				              /* Frame Sync Divisor */
//					gFsInfo_C.nPulseWidth = CLKDIV/2;                         /* Pulse Width */
//					gFsInfo_C.nPhase = CLKPHASE;                              /* Phase */
//					gFsInfo_C.bExternalTrigger = true;                        /* External Trigger */
//					gFsInfo_C.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */
//
//				ADI_PCG_CLK_INFO gClkInfo_D;
//					gClkInfo_D.eClkInput = ADI_PCG_CLK_EXT;      	/* Clock Source */
//					gClkInfo_D.nDiv = 0u;          					/* Clock Divisor */
//					gClkInfo_D.bExternalTrigger = false;            /* External Trigger */
//				ADI_PCG_FS_INFO gFsInfo_D;
//					gFsInfo_D.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_FS_EXT;                    /* Clock Source */
//					gFsInfo_D.nDiv = 64*CLKDIV;     				         /* Frame Sync Divisor */
//					gFsInfo_D.nPulseWidth = 32*CLKDIV;                       /* Pulse Width */
//					gFsInfo_D.nPhase = FSPHASE;                              /* Phase */
//					gFsInfo_D.bExternalTrigger = true;                       /* External Trigger */
//					gFsInfo_D.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;  /* Bypass Mode */
//
//
//				adi_pcg_Init(ADI_PCG_DEV_C,&gClkInfo_C,&gFsInfo_C);
//				adi_pcg_Init(ADI_PCG_DEV_D,&gClkInfo_D,&gFsInfo_D);
//			}
//			else
//#endif
//			{
//				ADI_PCG_CLK_INFO gClkInfo;
//				gClkInfo.eClkInput = ADI_PCG_CLK_EXT;              /* Clock Source */
//				gClkInfo.nDiv = Clock_Div_Value/64;                /* Clock Divisor */
//				gClkInfo.bExternalTrigger = false;                 /* External Trigger */
//				gClkInfo.bHwTriggerCtl= false;
//
//				ADI_PCG_FS_INFO gFsInfo;
//				gFsInfo.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_CLK_EXT;                   /* Clock Source */
//				gFsInfo.nDiv = Clock_Div_Value;                        /* Frame Sync Divisor */
//				gFsInfo.nPulseWidth = (gFsInfo.nDiv)/2u;               /* Pulse Width */
//				gFsInfo.nPhase = gClkInfo.nDiv/2;                      /* Phase */
//				gFsInfo.bExternalTrigger = false;                      /* External Trigger */
//				gFsInfo.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;  /* Bypass Mode */
//
//				adi_pcg_Init(ADI_PCG_DEV_C,&gClkInfo,&gFsInfo);
//			}
//		}
//
//#ifdef I2S_TDM_MODE_ENABLE
//		else if(I2S_TDM_MODE == TDM_MODE)
//#endif
//		{
//			ADI_PCG_CLK_INFO gClkInfo;
//			gClkInfo.eClkInput = ADI_PCG_CLK_EXT;              	 /* Clock Source */
//			gClkInfo.nDiv = Clock_Div_Value/256;                       			 /* Clock Divisor */
//			gClkInfo.bExternalTrigger = false;                   /* External Trigger */
//			gClkInfo.bHwTriggerCtl= false;
//
//			ADI_PCG_FS_INFO gFsInfo;
//			gFsInfo.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_CLK_EXT;                	/* Clock Source */
//			gFsInfo.nDiv = Clock_Div_Value;                                    /* Frame Sync Divisor */
//			gFsInfo.nPulseWidth = (gFsInfo.nDiv)/256u;                /* Pulse Width */
//			gFsInfo.nPhase = 0;                       /* Phase */
//			gFsInfo.bExternalTrigger = false;                       /* External Trigger */
//			gFsInfo.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */
//
//			adi_pcg_Init(ADI_PCG_DEV_C,&gClkInfo,&gFsInfo);
//		}
//#ifdef ASRC_ENABLE
//	if((I2S_TDM_MODE == ASRC_MODE)||(I2S_TDM_MODE == ASRC_TDM_MODE))
//	{
//	   Asrc_SRU_Reconfigure();
//		}
//#endif
//		Prev_Clock_Div_Value = Clock_Div_Value;
//	}
//
//#ifdef OPTICAL_MODULE
//	if(Prev_OutputSampleRate != Output_SampleRate)
//	{
//		SPI1_Init_DIT(Output_SampleRate);
//		Prev_OutputSampleRate = Output_SampleRate;
//	}
//#endif
}
/**************************************************************************************************
 *  Module Name        : PCG_Clock_Divider
 *  Functionality      : PCG Clock_Divider calculation based on input and output sample rate
 *  Input Parameters   : sample_fs_micro,
 *  Output Parameters  : Output_SampleRate
 *************************************************************************************************/
#pragma section("Seg_Kernal_Code_L3")
void PCG_Clock_Divider(int sample_fs_micro,int Output_SampleRate)
{
	if(Custom_MCLK_Mode == 1)
	{

		Clock_Div_Value = Custom_Clock_Ratio;

	}
#ifdef eARC_ENABLE	
	else if(eARC_Mode == 1)		//Melody9 Platform
	{
		eARC_PCG_Clock_Divider(sample_fs_micro,Output_SampleRate);
	}
#endif
	else
	{

		if((sample_fs_micro == FS_48K)||(sample_fs_micro == FS_44K)||(sample_fs_micro == FS_32K))
		{
			Clock_Div_Value = ((Freq_Table_SRU[sample_fs_micro]*Mclk_48Khz)/Freq_Table_SRU[Output_SampleRate]);
		}
		else if((sample_fs_micro == FS_96K)||(sample_fs_micro == FS_88K)||(sample_fs_micro == FS_64K))
		{
			Clock_Div_Value = (Freq_Table_SRU[sample_fs_micro]*Mclk_96Khz)/Freq_Table_SRU[Output_SampleRate];
		}
		else if((sample_fs_micro == FS_192K)||(sample_fs_micro == FS_176K)||(sample_fs_micro == FS_128K))
		{
			Clock_Div_Value = (Freq_Table_SRU[sample_fs_micro]*Mclk_192Khz)/Freq_Table_SRU[Output_SampleRate];
		}

	}

}

#if defined (DOLBY_DDP) || defined (DOLBY_DD)
/**************************************************************************************************
 *  Module Name        : Clear_Decoder_Buffer
 *  Functionality      : Clearing the library buffers
 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/
#pragma section("Seg_DDP_Kernel_Code_L3")
void Clear_Decoder_Buffer(void)
{
	for(int i=0;i<169392;i++)
		libraray_l2_data[i]=0;

	for(int i=0;i<122880;i++)
		TRUEHD_predac_heap_buf[i]=0;

	for(int i=0;i<29984;i++)
		joc_phse[i]=0;
}
/**************************************************************************************************
 *  Module Name        : ddp_dec_configure
 *  Functionality      : DDP decoder Out channel configuration
 *  Input Parameters   : Legacy_Decoding_Mode,core_config,Speaker Presence received from command
 *  Output Parameters  : Decoder output channel configuration
 *************************************************************************************************/
#pragma section("Seg_DDP_Kernel_NW_Code_L3",NW)
int ddp_dec_configure(void)
{
	datmos_speaker_legacy();
	if((((Frmwk.datmos_speaker_legacy_option>>8) & 0x00000001)==1) && (((Frmwk.datmos_speaker_legacy_option>>11) & 0x00000001)==0) && (((Frmwk.datmos_speaker_legacy_option>>26) & 0x00000001)==0))
	{
		Frmwk.DDPlus.outchanconfig 			= UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS;
		Frmwk.DDPlus.outlfe 				= 1;
		Frmwk.DDPlus.Legacy_Decoding_Mode 	= 1;
		Frmwk.Legacy_Mode_enable			= 1;
	    graph_type_cmd  				= 0;
		return 0;
	}
	else if((((Frmwk.datmos_speaker_legacy_option>>8) & 0x00000001)==0) && (((Frmwk.datmos_speaker_legacy_option>>11) & 0x00000001)==1) && (((Frmwk.datmos_speaker_legacy_option>>26) & 0x00000001)==0))
	{
		Frmwk.Speakers_presence_7_1 		= (Frmwk.speakers_bitmask) & AR_SPEAKER_71_MASK;
		Frmwk.DDPlus.Legacy_Decoding_Mode 	= 1;
		Frmwk.Legacy_Mode_enable			= 1;
	    graph_type_cmd  				= 0;
	}
	else if((((Frmwk.datmos_speaker_legacy_option>>8) & 0x00000001)==1) && (((Frmwk.datmos_speaker_legacy_option>>11) & 0x00000001)==1) && (((Frmwk.datmos_speaker_legacy_option>>26) & 0x00000001)==0))
	{
		Frmwk.Speakers_presence_7_1 		= (Frmwk.speakers_bitmask) & AR_SPEAKER_71_MASK;
		Frmwk.DDPlus.Legacy_Decoding_Mode 	= 1;
		Frmwk.Legacy_Mode_enable			= 1;
	    graph_type_cmd  				= 0;
	}
	int datmos_speaker_presence = Frmwk.Speakers_presence_7_1;
#ifdef EXT_DNMIX_DDP
	if (((Frmwk.Speakers_presence_7_1==0x29)||(Frmwk.Speakers_presence_7_1==0x2B)||(Frmwk.Speakers_presence_7_1==0x409)||(Frmwk.Speakers_presence_7_1 == 0x2D)
			|| (Frmwk.Speakers_presence_7_1 == 0x2F)|| (Frmwk.Speakers_presence_7_1 == 0x40D)) && (Frmwk.DDPlus.Legacy_Decoding_Mode == 1))
	{
		DDPlus_outchanconfigFromCmd = 0;

		if(Frmwk.Speakers_presence_7_1 == 0x29)   
		{
			DDPlus_outchanconfigFromCmd = 0x29;
			Frmwk.DDPlus.outchanconfig = UDC_OUTPUT_CHAN_ID_L_R_LS_RS_LRS_RRS;
			Frmwk.DDPlus.outlfe = ((Frmwk.Speakers_presence_7_1 >> 2) & 0x1);
		}
		else if(Frmwk.Speakers_presence_7_1 == 0x2D)
		{
			DDPlus_outchanconfigFromCmd = 0x2D;
			Frmwk.DDPlus.outchanconfig = UDC_OUTPUT_CHAN_ID_L_R_LS_RS_LRS_RRS;
			Frmwk.DDPlus.outlfe = ((Frmwk.Speakers_presence_7_1 >> 2) & 0x1);
		}


		if(Frmwk.Speakers_presence_7_1 == 0x2B)   
		{
			DDPlus_outchanconfigFromCmd = 0x2B;
			Frmwk.DDPlus.outchanconfig = UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS_LRS_RRS;
			Frmwk.DDPlus.outlfe = ((Frmwk.Speakers_presence_7_1 >> 2) & 0x1);
		}
		else if(Frmwk.Speakers_presence_7_1 == 0x2F)
		{
			DDPlus_outchanconfigFromCmd = 0x2F;
			Frmwk.DDPlus.outchanconfig = UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS_LRS_RRS;
			Frmwk.DDPlus.outlfe = ((Frmwk.Speakers_presence_7_1 >> 2) & 0x1);
		}


		if(Frmwk.Speakers_presence_7_1 == 0x409)   
		{
			DDPlus_outchanconfigFromCmd = 0x409;
			Frmwk.DDPlus.outchanconfig = UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS_LRS_RRS_LTS_RTS;
			Frmwk.DDPlus.outlfe = ((Frmwk.Speakers_presence_7_1 >> 2) & 0x1);
		}
		else if(Frmwk.Speakers_presence_7_1 == 0x40D)
		{
			DDPlus_outchanconfigFromCmd = 0x40D;
			Frmwk.DDPlus.outchanconfig = UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS_LRS_RRS_LTS_RTS;
			Frmwk.DDPlus.outlfe = ((Frmwk.Speakers_presence_7_1 >> 2) & 0x1);
		}

	}
	else if (Frmwk.DDPlus.Legacy_Decoding_Mode == 1 || Frmwk.core_config == 1)
#else
	if (Frmwk.DDPlus.Legacy_Decoding_Mode == 1 || Frmwk.core_config == 1)
#endif
	{
		DDPlus_outchanconfigFromCmd = 0;
		int center = ((datmos_speaker_presence >> 1) & 0x1);
		if (Frmwk.DDPlus.Legacy_Decoding_Mode == 1)
		{
			Frmwk.DDPlus.outlfe = ((datmos_speaker_presence >> 2) & 0x1);
			if (((datmos_speaker_presence >> 4) & 0x1) != 0)
			{
				Frmwk.DDPlus.outchanconfig = center ? UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS_LRS_RRS : UDC_OUTPUT_CHAN_ID_L_R_LS_RS_LRS_RRS;
			}
			else if (((datmos_speaker_presence >> 3) & 0x1) != 0)
			{
				Frmwk.DDPlus.outchanconfig = center ? UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS : UDC_OUTPUT_CHAN_ID_L_R_LS_RS;
			}
			else
			{
				Frmwk.DDPlus.outchanconfig = center ? UDC_OUTPUT_CHAN_ID_L_R_C : UDC_OUTPUT_CHAN_ID_L_R;
			}
		}
		else
		{
			/* In standard decode mode we output 5.1 configuration from the decoder
			so that DAP receives surround speakers and can perform virtualization. */
			Frmwk.DDPlus.outchanconfig = UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS;
			Frmwk.DDPlus.outlfe = 1;
		}
	}
	else
	{
		Frmwk.DDPlus.outchanconfig = UDC_OUTPUT_RAW;
		Frmwk.DDPlus.outlfe=1;
	}
	return 0;
}
#endif /* DOLBY_DDP */

/******************************************************************************
 *  Module Name        : Control_DataVariable_Update
 *  Functionality      : Variable updates
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Dolby_Kernel_NW_Code_L3",NW)
void Control_DataVariable_Update(void)
{
#ifdef DOLBY_LIB
	Frmwk.DAP_krnl.Direct_Decode = 0;
	Frmwk.dmx_Frmwk.dmx_params_b_mat_pcm_mode = Frmwk.b_mat_pcm_mode;
#endif

	//	NeuralX_Enable = 0;
#ifdef AURO_3D
	Frmwk.graph_type = graph_type_cmd;
	if ((MAT_AuroUpmixer == 0) && (MAT_Detected == 1))
	{
		obj_mat_auro_flag = 1;
	}
	if((AuroEngine_Enable == 1) && (obj_mat_auro_flag != 1) )
	{
		if ((Frmwk.StreamType == 11) || (Frmwk.StreamType == 10) || (Frmwk.StreamType == 0x2))
		{
			Dolby_AuroEnable = 1;
		}

		Frmwk.graph_type = 0;
		Frmwk.Object_Audio = 0;
		Frmwk.DAP_krnl.DAP_upmixer_On_Off = 0;
		DAP_Enable = 0;
		Frmwk.DAP_krnl.DAP_ON_OFF = 0; // changed from GL

	}
	else
	{
		Dolby_AuroEnable = 0;
#endif
#ifdef DOLBY_DAP
		DAP_Enable = Frmwk.DAP_krnl.DAP_ON_OFF;

		if((Frmwk.StreamType == 0xA) || (Frmwk.StreamType == 0xB) || (Frmwk.StreamType == 0x2))
		{
#ifdef EXT_DNMIX
			if((Frmwk.b_mat_pcm_mode && Frmwk.DAP_krnl.DAP_Tuning_ON_OFF==0) && (centre_downmix_check_flag==0)/* && (centre_downmix_check_flag_ddp==0)*/)
#else
				if(Frmwk.b_mat_pcm_mode && Frmwk.DAP_krnl.DAP_Tuning_ON_OFF==0)
#endif
				{
					Frmwk.dmx_Frmwk.dmx_params_speakers =Frmwk.dmx_Frmwk.dmx_params_speakers& AR_SPEAKER_71_MASK;
#if defined (DOLBY_DDP)||defined (DOLBY_MAT) ||defined (DOLBY_OAR) || defined (DOLBY_DAP)
					if(Frmwk.Ch_Obj_Switch == 0)
					{
						if(Frmwk.Object_Audio)
							Frmwk.dmx_Frmwk.dmx_params_b_bypass = 1;
					}
#endif
					DAP_Enable = 0;
				}
		else if(Frmwk.Legacy_Mode_enable==1 && Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 1)
		{
			DAP_Enable = 1;
			Frmwk.DAP_krnl.Direct_Decode = 1;
		}
				else if(Frmwk.Legacy_Mode_enable==1)
				{
					DAP_Enable = 0;
					Frmwk.dmx_Frmwk.dmx_params_b_bypass=1;
				}
				else
				{
					DAP_Enable = 1;
				}
		}
		else if(((Frmwk.StreamType == 0xF) ||(Frmwk.StreamType == 0x1)) && (Frmwk.Post_decoding_option_command == 1))
	{
		if(Frmwk.Legacy_Mode_enable==1 && Frmwk.DAP_krnl.DAP_Tuning_ON_OFF==1)
		{
			DAP_Enable = 1;
			Frmwk.DAP_krnl.Direct_Decode = 1;
		}
		else if(Frmwk.Legacy_Mode_enable==1 && Frmwk.DAP_krnl.DAP_Tuning_ON_OFF==0)
		{
			DAP_Enable = 0;
			Frmwk.b_mat_pcm_mode = 1;
			Frmwk.dmx_Frmwk.dmx_params_b_mat_pcm_mode = 1;
			Frmwk.dmx_Frmwk.dmx_params_speakers= Frmwk.speakers_bitmask;
		}
		else
		{
			DAP_Enable = 1;
		}
	}

		else if((Frmwk.Post_decoding_option_command) == 1)
		{
			DAP_Enable = 1;
		}
		else if(((Frmwk.Post_decoding_option_command) == 0) || ((Frmwk.Post_decoding_option_command) == 3))
		{
			DAP_Enable = 0;
		}
		if((DAP_Enable == 0) || (Frmwk.tuning_mode_enable == 1))
	{
		Frmwk.DAP_krnl.DAP_upmixer_On_Off = 0;
	}
#endif
		Frmwk.DAP_krnl.DAP_ON_OFF = DAP_Enable;
#ifdef AURO_3D
	}//brace for else
#endif

#ifdef DOLBY_DAP
	Frmwk.DAP_krnl.DAP_ON_OFF = DAP_Enable;
#endif
}

#ifdef DOLBY_DMX
/**************************************************************************************************
 *  Module Name        : set_output_config
 *  Functionality      : Convert an ar_speaker mask to a DPF channel map for DAP and downmixer
 *  					 return Number of channels present in the channel map

 *************************************************************************************************/
#pragma section("Seg_Dolby_Kernel_NW_Code_L3",NW)
int set_output_config(int outputmap, uint8_t *ch_map)
{
	unsigned int i;
	unsigned int channel = 0;
	unsigned int channel_order[UDC_MAX_OBJECTS];

	for(i = 0; i < DPF_MAX_CHANNELS; i++)
	{
		/* Initialize the channel order array */
		ch_map[i] = DPF_CHANNEL_UNUSED;
	}
	/**
	 * Check if L and C exist, set channel map appropriately.
	 * (R is assumed to exist if L exists)
	 */
	/**
	 * Check if L and C exist, set channel map appropriately.
	 * (R is assumed to exist if L exists)
	 */
	if(    (CHAN_EXISTS_IN_OUTMAP(UDC_OUTPUTMAP_L, outputmap))
			&& (CHAN_EXISTS_IN_OUTMAP(UDC_OUTPUTMAP_C, outputmap))
	)
	{
		/* Channel ordering is L/R/C */
		ch_map[channel++] = DPF_CHANNEL_LEFT;
		ch_map[channel++] = DPF_CHANNEL_RIGHT;
		ch_map[channel++] = DPF_CHANNEL_CENTER;

	}
	else
		if(CHAN_EXISTS_IN_OUTMAP(UDC_OUTPUTMAP_C, outputmap))
		{
			ch_map[channel++] = DPF_CHANNEL_CENTER;

		}
		else
		{
			/* This stream has L/R, but not C */
			ch_map[channel++] = DPF_CHANNEL_LEFT;
			ch_map[channel++] = DPF_CHANNEL_RIGHT;

		}
	/* Then, check for LFE */
	if(CHAN_EXISTS_IN_OUTMAP(UDC_OUTPUTMAP_LFE, outputmap))
	{
		ch_map[channel++] = DPF_CHANNEL_LFE;
	}
	/* Check for Ls/Rs */
	if(CHAN_EXISTS_IN_OUTMAP(UDC_OUTPUTMAP_LS, outputmap))
	{
		if(CHAN_EXISTS_IN_OUTMAP(UDC_OUTPUTMAP_RS, outputmap))
		{
			ch_map[channel++] = DPF_CHANNEL_SIDE_LEFT;
			ch_map[channel++] = DPF_CHANNEL_SIDE_RIGHT;
		}
		else
		{
			ch_map[channel++] = DPF_CHANNEL_BACK_CENTER;
		}
	}

	/* Finally, check for the extension channels */
	for(i  = UDC_MAX_I0_FCHANS; i < UDC_OUTPUTMAP_LFE; i++)
	{
		if(CHAN_EXISTS_IN_OUTMAP(i, outputmap))
		{
			ch_map[channel++] = outputmap_channels[i];
			if(IS_OUTMAP_PAIR(i))
			{
				ch_map[channel++] = outputmap_pairs[i];
			}
		}
	}

	return channel;
}

#endif
/**************************************************************************************************
 *  Module Name        : dpf_node_build_channel_map_dwx
 *  Functionality      : Convert an ar_speaker mask to a DPF channel map for DAP and downmixer
 *  					 return Number of channels present in the channel map

 *************************************************************************************************/
#ifdef DOLBY_LIB
#pragma section("Seg_Dolby_Kernel_NW_Code_L3",NW)
unsigned int
dpf_node_build_channel_map_dwx
(unsigned long   ar_speaker_mask
		,uint8_t*        channel_map
)
{
	unsigned int chan = 0;
	unsigned int channels_used = 0;
	if (ar_speaker_mask & AR_SPEAKER_L_R_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT;
		channel_map[chan++] = DPF_CHANNEL_RIGHT;
	}
	if (ar_speaker_mask & AR_SPEAKER_C_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_CENTER;
	}
	if (ar_speaker_mask & AR_SPEAKER_LFE_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LFE;
	}
	if (ar_speaker_mask & AR_SPEAKER_LS_RS_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_SIDE_LEFT;
		channel_map[chan++] = DPF_CHANNEL_SIDE_RIGHT;
	}
	if (ar_speaker_mask & AR_SPEAKER_LRS_RRS_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_BACK_LEFT;
		channel_map[chan++] = DPF_CHANNEL_BACK_RIGHT;
	}
	if (ar_speaker_mask & AR_SPEAKER_CS_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_BACK_CENTER;
	}
	if (ar_speaker_mask & AR_SPEAKER_LC_RC_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_CENTER_LEFT;
		channel_map[chan++] = DPF_CHANNEL_CENTER_RIGHT;
	}
	if (ar_speaker_mask & AR_SPEAKER_LW_RW_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_WIDE;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_WIDE;
	}
	if (ar_speaker_mask & AR_SPEAKER_LFH_RFH_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_FRONT_HEIGHT;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_FRONT_HEIGHT;
	}
	if (ar_speaker_mask & AR_SPEAKER_LTF_RTF_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_TOP_FRONT;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_TOP_FRONT;
	}
	if (ar_speaker_mask & AR_SPEAKER_LTM_RTM_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_TOP_MIDDLE;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_TOP_MIDDLE;
	}
	if (ar_speaker_mask & AR_SPEAKER_LTR_RTR_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_TOP_REAR;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_TOP_REAR;
	}
	if (ar_speaker_mask & AR_SPEAKER_LRH_RRH_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_REAR_HEIGHT;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_REAR_HEIGHT;
	}
	if (ar_speaker_mask & AR_SPEAKER_LSC_RSC_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_SCREEN;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_SCREEN;
	}
	if (ar_speaker_mask & AR_SPEAKER_LS1_RS1_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_SUR_1;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_SUR_1;
	}
	if (ar_speaker_mask & AR_SPEAKER_LS2_RS2_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_SUR_2;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_SUR_2;
	}
	if (ar_speaker_mask & AR_SPEAKER_LRS1_RRS1_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_REAR_SUR_1;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_REAR_SUR_1;
	}
	if (ar_speaker_mask & AR_SPEAKER_LRS2_RRS2_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_REAR_SUR_2;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_REAR_SUR_2;
	}
	if (ar_speaker_mask & AR_SPEAKER_LCS_RCS_MASK)
	{
		channel_map[chan++] = DPF_CHANNEL_LEFT_CENTER_SUR;
		channel_map[chan++] = DPF_CHANNEL_RIGHT_CENTER_SUR;
	}
	channels_used = chan;
	while (chan < DPF_MAX_CHANNELS)
	{
		channel_map[chan++] = DPF_CHANNEL_UNUSED;
	}
	return channels_used;
}

#endif
/******************************************************************************
 *  Module Name        : OARI_Init_Call
 *  Functionality      : OAR library init MIPS is huge, for handling that OAR library init for default speaker configuration is called before start processing
 *  					This module init is called for 7.1.4 configuration
 *
 ******************************************************************************/
#ifdef DOLBY_OAR
#pragma section("Seg_OARI_Kernel_Code_L3")
void OARI_Init_Call(void)
{
	Frmwk.OAR_Frmwk.OARiInitFlag 	= 1;
	if(Frmwk.OAR_Frmwk.MAT_legacy_oar_flag)
	{
		Frmwk.OAR_Frmwk.SampleRate 		= (int) Freq_Table[Frmwk.OutputSampleRate];

		Frmwk.OAR_Frmwk.Speaker_Output_Config &= 0x001F;

		Frmwk.OAR_Frmwk.MAT_legacy_oar_flag = 0;
	}
	else
	{
		Frmwk.OAR_Frmwk.SampleRate 		= 48000;

		Frmwk.OAR_Frmwk.Speaker_Output_Config = 0xa1f;

	}
	if(Frmwk.OAR_Frmwk.Prev_Speaker_Output_Config!= Frmwk.OAR_Frmwk.Speaker_Output_Config)
	{
		Frmwk.OAR_Frmwk.OAR_b_enable_limiter = 1;
		Frmwk.OAR_Frmwk.Prev_Speaker_Output_Config = Frmwk.OAR_Frmwk.Speaker_Output_Config;
		InitOARiModule();
	}
}
#endif /* DOLBY_OAR */

#if defined (DOLBY_THD) || defined (DOLBY_MAT)
/**************************************************************************************************
 *  Module Name        : AllocateMemoryTrueHD
 *  Functionality      : Memory allocation for TrueHD and MAT library pointers
 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/

#pragma section("Seg_THD_Kernel_Code_L3")
void AllocateMemoryTrueHD()
{
	int index;
	int ptr;

	Frmwk.MAT.matpstate		 			= (struct mat_dthd_dec_node_state * )mat_pstate_structure;
	Frmwk.MAT.mat_static_memory_requirements 	= (int) p_mat_dec_static_mem;
	Frmwk.MAT.mat_dynamic_memory_requirements 	= (int) p_mat_dec_dynamic_mem;
	Frmwk.MAT.a_metadatapayload_pstate 	= (int) metadata_payload_pstate;
	Frmwk.MAT.a_mat_outputbuffer 		= (int) mat_output_buffer;
	Frmwk.MAT.a_mat_inputbuffer 		= (int) mat_input_buffer;

	Frmwk.TRUEHD.LibTrueHDPtr  			= (struct TrueHD *) TrueHDLibvar;
	Frmwk.TRUEHD.IEC_MAT_Buf_heap 		= (int) IEC_MAT_Buf;
	Frmwk.TRUEHD.pstate  				= (struct dthd_dec_state *)TrueHDLibstruct;

	#ifdef DOLBY_L2_BUFFER_POINTER
	/*presentationmem - 54612 */
	Frmwk.TRUEHD.presentationmem  		= (int)libraray_l2_data;
	#else
	Frmwk.TRUEHD.presentationmem  		= (int)&(libraray_l2_data[0]);
	#endif /* DOLBY_L2_BUFFER_POINTER */
	/*decinstancemem - 72 */
	Frmwk.TRUEHD.decinstancemem  		= (int)(Frmwk.TRUEHD.presentationmem  + (54612+4));
	/*scratchbufmem - 2592 */
	Frmwk.TRUEHD.scratchbufmem  		= (int) (Frmwk.TRUEHD.decinstancemem + (72 +4));
	/*dvlimmem - 9324 */
	Frmwk.TRUEHD.dvlimmem  				= (int) (Frmwk.TRUEHD.scratchbufmem + (2592+4));
	/*delaybufmem - 10432 */
	Frmwk.TRUEHD.delaybufmem  			= (int) (Frmwk.TRUEHD.dvlimmem  + (9324+4));
	/*MLP_INPUT_Buf_heap - 4096 */
	Frmwk.TRUEHD.MLP_INPUT_Buf_heap 	= (int) (Frmwk.TRUEHD.delaybufmem  +(10432+4));
	/*timing_state_mem - 76 */
	Frmwk.TRUEHD.timing_state_mem       = (int) (Frmwk.TRUEHD.MLP_INPUT_Buf_heap +(4096+4));
	/*pres_mgr_prams_mem - 140 */
	Frmwk.TRUEHD.pres_mgr_prams_mem     = (int) (Frmwk.TRUEHD.timing_state_mem + (76+4));
	/*dec_output_mem - 10432 */
	Frmwk.TRUEHD.dec_output_mem         = (int) (Frmwk.TRUEHD.pres_mgr_prams_mem +(140+4));
	/*TRUEHD_predac_heap - 30720 */
	//Frmwk.TRUEHD.TRUEHD_predac_heap 	= (int) (Frmwk.TRUEHD.dec_output_mem  + (10432+4));
	Frmwk.TRUEHD.TRUEHD_predac_heap 	= (int) TRUEHD_predac_heap_buf;//(int) (Frmwk.TRUEHD.dec_output_mem  + (10432+4));


	/*au_decoder_instance_mem - 19180 */
	Frmwk.TRUEHD.au_decoder_instance_mem= L1_BLOCK2_POINTER_OFFSET6;
	/*drcmem - 468 */
	Frmwk.TRUEHD.drcmem  				= (int) (Frmwk.TRUEHD.au_decoder_instance_mem + (19180 + 4));//(24000 + 4));
	/*ss_mem - 3484 */
	Frmwk.TRUEHD.ss_mem					= (int) (Frmwk.TRUEHD.drcmem  + (468+4));
	/*outputstatemem - 912*/
	Frmwk.TRUEHD.outputstatemem  		= (int) (Frmwk.TRUEHD.ss_mem	 + (3484+4)); //(3595+4));
	Frmwk.TRUEHD.evolutionmem  			= (int)TrueHDLibEvolutionStruct;
	#ifdef DOLBY_L2_BUFFER_POINTER
	Frmwk.TRUEHD.evo_buf 				= L2_POINTER_OFFSET2;
	#else
	Frmwk.TRUEHD.evo_buf 				= (int) evo_buf;
	#endif /* DOLBY_L2_BUFFER_POINTER */
}
/**************************************************************************************************
 *  Module Name        : TrueHD_Variable_Init
 *  Functionality      : TrueHD Init process and state structure default parameter initialization
 *  Input Parameters   : TrueHD_Variable_Init
 *  Output Parameters  : None
 *************************************************************************************************/
#pragma section("Seg_THD_Kernel_Code_L3")
void TrueHD_Variable_Init(void)
{

#ifdef EXT_DNMIX
	TrueHD_outchanconfigFromCmd = 0;
	ext_dnmix_flag              = 0;
#endif

	char *delay_ptr,*scratch_ptr,*drc_ptr,*limiter_ptr,*ptr_TrueHDoutbuf;
	ptr_TrueHDoutbuf = (char *)Frmwk.TRUEHD.TRUEHD_predac_heap;

	delay_ptr 	= (char *)Frmwk.TRUEHD.delaybufmem;
	scratch_ptr	= (char *)Frmwk.TRUEHD.scratchbufmem;
	drc_ptr		= (char *)Frmwk.TRUEHD.drcmem;
	limiter_ptr = (char *)Frmwk.TRUEHD.dvlimmem;


	for(int i=0;i<122880;i++)
		ptr_TrueHDoutbuf[i]=0;

	for(int i=0;i<10432;i++)
		delay_ptr[i]=0;

	for(int i=0;i<2592;i++)
		scratch_ptr[i]=0;

	for(int i=0;i<468;i++)
		drc_ptr[i]=0;

	for(int i=0;i<9324;i++)
		limiter_ptr[i]=0;


	Frmwk.TRUEHD.IEC_MAT_Buf_Wr_Ptr 		= Frmwk.TRUEHD.IEC_MAT_Buf_heap;
	Frmwk.TRUEHD.IEC_MAT_Buf_Rd_Ptr 		= Frmwk.TRUEHD.IEC_MAT_Buf_heap;

	Frmwk.TRUEHD.TRUEHD_predac_Wr_Ptr 		= Frmwk.TRUEHD.TRUEHD_predac_heap;
	Frmwk.TRUEHD.TRUEHD_predac_Rd_Ptr 		= Frmwk.TRUEHD.TRUEHD_predac_heap;

	if ((Frmwk.TRUEHD.decoded_sampling_frequency == ASF48K) || (Frmwk.TRUEHD.decoded_sampling_frequency == ASF44K1))
	{
		Frmwk.TRUEHD.DecoderBlocksize 		= DECODERBLOCKSIZE_48K;
		Frmwk.TRUEHD.AuOut8channel 			= TRUEHD_AUOUT8CHANNEL_48K;
		Frmwk.TRUEHD.TRUEHD_predac_length 	= TRUEHD_OUTPUTBUFFERSIZE_48K;
		Frmwk.IOP.Next_DataValid_count 		= Frmwk.IOP.Predac.lengthhalf / (16 * DECODERBLOCKSIZE_48K);
		Frmwk.TRUEHD.DRC_init_For 			= 0; //DRC initialisation inside library for 48KHz or 44.1KHz Fs
	}
	else if ((Frmwk.TRUEHD.decoded_sampling_frequency == ASF96K) || (Frmwk.TRUEHD.decoded_sampling_frequency == ASF88K2))
	{
#ifdef EXT_DNMIX
		if(Frmwk.Speakers_presence_7_1 == 0x7)
		{
			Frmwk.TRUEHD.LFE_enable=1;
			ext_dnmix_flag=1;
			TrueHD_outchanconfigFromCmd = 0x7;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_7;
		}
		if(Frmwk.Speakers_presence_7_1 == 0xD)
		{
			Frmwk.TRUEHD.LFE_enable=1;
			ext_dnmix_flag=1;
			TrueHD_outchanconfigFromCmd = 0xD;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_7;
		}
		if(Frmwk.Speakers_presence_7_1 == 0x1D)
		{
			Frmwk.TRUEHD.LFE_enable=1;
			ext_dnmix_flag=1;
			TrueHD_outchanconfigFromCmd = 0x1D;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_21;
		}
#endif
		Frmwk.TRUEHD.DecoderBlocksize 		= DECODERBLOCKSIZE_96K;
		Frmwk.TRUEHD.AuOut8channel 			= TRUEHD_AUOUT8CHANNEL_96K;
		Frmwk.TRUEHD.TRUEHD_predac_length 	= TRUEHD_OUTPUTBUFFERSIZE_96K;
		Frmwk.IOP.Next_DataValid_count 		= Frmwk.IOP.Predac.lengthhalf / (16 * DECODERBLOCKSIZE_96K);
		Frmwk.TRUEHD.DRC_init_For 			= 1; //DRC initialisation inside library for 96KHz or 88.2KHz Fs
	}

	else if ((Frmwk.TRUEHD.decoded_sampling_frequency == ASF192K) || (Frmwk.TRUEHD.decoded_sampling_frequency == ASF176K4))
	{
#ifdef EXT_DNMIX
		if(Frmwk.Speakers_presence_7_1 == 0x7)
		{
			Frmwk.TRUEHD.LFE_enable=1;
			ext_dnmix_flag=1;
			TrueHD_outchanconfigFromCmd = 0x7;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_7;
		}
		if(Frmwk.Speakers_presence_7_1 == 0xD)
		{
			Frmwk.TRUEHD.LFE_enable=1;
			ext_dnmix_flag=1;
			TrueHD_outchanconfigFromCmd = 0xD;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_7;
		}
		if(Frmwk.Speakers_presence_7_1 == 0x1D)
		{
			Frmwk.TRUEHD.LFE_enable=1;
			ext_dnmix_flag=1;
			TrueHD_outchanconfigFromCmd = 0x1D;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_21;
		}
		if(Frmwk.TRUEHD.KERNEL_drc_enable==3)
		{
			Frmwk.TRUEHD.KERNEL_drc_enable=2;
		}
#endif
		Frmwk.TRUEHD.DecoderBlocksize 		= DECODERBLOCKSIZE_192K;
		Frmwk.TRUEHD.AuOut8channel 			= TRUEHD_AUOUT8CHANNEL_192K;
		Frmwk.TRUEHD.TRUEHD_predac_length 	= TRUEHD_OUTPUTBUFFERSIZE_192K;
		Frmwk.IOP.Next_DataValid_count 		= Frmwk.IOP.Predac.lengthhalf / (8 * DECODERBLOCKSIZE_192K);
		Frmwk.TRUEHD.DRC_init_For 			= 2; //DRC initialisation inside library for 192KHz or 176.4KHz Fs
	}

	Frmwk.IOP.LatencyDone 					= 0;
	Frmwk.TRUEHD.DecodedAU_Cnt 				= 0;
	Frmwk.TRUEHD.StreamState 				= IEC_UNLOCKED;
	Frmwk.TRUEHD.Stream_Locked 				= 0;
	Frmwk.TRUEHD.TrueHD_MS_Offset 			= 0;
	Frmwk.TRUEHD.metadataoffsetcheckFlag 	= 1;
	Frmwk.TRUEHD.metadataoffset 			= -1;

	Frmwk.Misc.Control.OutBufferEmptyFlag 	= 0;
	Frmwk.TRUEHD.True_HD_FIFO_Delay_Flag 	= 1;
	Frmwk.TRUEHD.True_HD_FIFO_Delay 		= 0;
	Frmwk.TRUEHD.evo_sc_counter_initflag 	= 1;
	Frmwk.TRUEHD.Prev_Output_Ch_Config 		= -1;
	Frmwk.TRUEHD.Prev_Force_Decoding_Mode 	= -1;

	Frmwk.TRUEHD.NeedMLPinitialise 			= 1;
	Frmwk.TRUEHD.TrueHD_Decoder_Error 		= 0;
	Frmwk.TRUEHD.TrueHDOption 				= 1;
	Frmwk.MAT.update_params 				= 1;
	Frmwk.TRUEHD.Object_decode_flag 		= 1;

	Frmwk.TRUEHD.connection_init_flag 		= 1;
	Frmwk.MAT.mat_dec_state 				= 0;
#ifdef DOLBY_MAT
	mat_dec_init(Frmwk.MAT.matpstate);
#endif
	//Frmwk.MAT.First_access_unit 			= 1;
#ifdef EXT_DNMIX
	centre_downmix_check_c1                = 0;
#endif
	datmos_speaker_legacy();
	if(((Frmwk.datmos_speaker_legacy_option>>12) & 0x00000001)==1 && (((Frmwk.datmos_speaker_legacy_option>>26) & 0x00000001)==0))
	{
	    graph_type_cmd  				= 0;
		Frmwk.TRUEHD.Legacymode 		= 1;
		Frmwk.Legacy_Mode_enable		= 1;
		Frmwk.Speakers_presence_7_1 	= (Frmwk.speakers_bitmask) & AR_SPEAKER_71_MASK;

		if(Frmwk.Speakers_presence_7_1 == AR_SPEAKER_61_MASK || Frmwk.Speakers_presence_7_1 == AR_SPEAKER_60_MASK)
		{
			Frmwk.b_mat_pcm_mode=1;
		}
		else
		{
			Frmwk.b_mat_pcm_mode=0;
		}
	}

}
#endif /* DOLBY_THD */
#if defined (DOLBY_THD) || defined(DOLBY_MAT)
/**************************************************************************************************
 *  Module Name        : Error_Reset_Variables
 *  Functionality      : Reset Datacanbeprocess now and HeaderplaceWritten variables when Error
 *  					 returned by the decoder.
 *  Input Parameters   : Error_Reset_Variables
 *  Output Parameters  : None
 *************************************************************************************************/
#pragma section("Seg_THD_Kernel_Code_L3")
void Error_Reset_Variables(void)
{
	Frmwk.IOP.datacanbeprocessednow = 0;
	Frmwk.Autdet.HeaderPlaceWritten = 0;
}
/**************************************************************************************************
 *  Module Name        : mat_dthd_configure
 *  Functionality      : Returns the output channel configurations for MAT and TrueHD streams when legacy enabled
 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/
#pragma section("Seg_MAT_Kernel_Code_L3")
int mat_dthd_configure(void)
{

	int ch_cnt 					= 0;
	int datmos_speaker_presence = Frmwk.Speakers_presence_7_1;
	int speakers_config1 		= 0;
#ifdef EXT_DNMIX
	if ((Frmwk.Speakers_presence_7_1 == 0x2D)||(Frmwk.Speakers_presence_7_1 == 0x2F)||(Frmwk.Speakers_presence_7_1 == 0x40D)||(Frmwk.Speakers_presence_7_1 == 0x10D)||(Frmwk.Speakers_presence_7_1 == 0x8D))
	{
		TrueHD_outchanconfigFromCmd = 0;
		Frmwk.TRUEHD.LFE_enable=((Frmwk.Speakers_presence_7_1 >> 2) & 0x1);

		if(Frmwk.Speakers_presence_7_1 == 0x2D)//
		{
			TrueHD_outchanconfigFromCmd = 0x2D;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_21;
		}
		if(Frmwk.Speakers_presence_7_1 == 0x2F)///
		{
			TrueHD_outchanconfigFromCmd = 0x2F;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_21;
		}
		if(Frmwk.Speakers_presence_7_1 == 0x40D)///
		{
			TrueHD_outchanconfigFromCmd = 0x40D;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_28;
		}
		if(Frmwk.Speakers_presence_7_1 == 0x10D)///
		{
			TrueHD_outchanconfigFromCmd = 0x10D;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_19;
		}
		if(Frmwk.Speakers_presence_7_1 == 0x8D)///
		{
			TrueHD_outchanconfigFromCmd = 0x8D;
			Frmwk.TRUEHD.Output_Ch_Config = DTHDI_DEC_CH_CFG_18;
		}
	}

	else
	{
		if(ext_dnmix_flag==0)
		{
#endif
			/* In direct decode mode there is only decoder, so if no sub speaker is available the LFE channel is dropped */
			if(( Frmwk.TRUEHD.Legacymode==1)  || (Frmwk.core_config == 1))
			{
				int center = ((datmos_speaker_presence >> 1) & 0x1);	    //( (speaker_presence[DATMOS_SPEAKER_ID_C] == DATMOS_SPEAKER_PRESENCE_OFF) ? 0 : 1 );

				if( Frmwk.TRUEHD.Legacymode==1)
				{
					Frmwk.TRUEHD.LFE_enable = ((datmos_speaker_presence >> 2) & 0x1);	//( (speaker_presence[DATMOS_SPEAKER_ID_SUB] == DATMOS_SPEAKER_PRESENCE_OFF) ? 0 : 1 );

					if(datmos_speaker_presence == AR_SPEAKER_61_MASK || datmos_speaker_presence == AR_SPEAKER_60_MASK)
					{
						datmos_speaker_presence=AR_SPEAKER_71_MASK;
					}

					if (((datmos_speaker_presence >> 4) & 0x1) != 0)
					{
						speakers_config1 = DTHDI_DEC_CH_CFG_21;
						if (!center)
						{
							Frmwk.TRUEHD.LFE_enable = 1;
						}
					}
					else if (((datmos_speaker_presence >> 3) & 0x1) != 0)
					{
						speakers_config1 = (center) ? DTHDI_DEC_CH_CFG_7 : DTHDI_DEC_CH_CFG_6;
					}
					else
					{
						speakers_config1 = (center) ? DTHDI_DEC_CH_CFG_3 : DTHDI_DEC_CH_CFG_2;
					}
				}
				else
				{
					speakers_config1	= AR_SPEAKER_51_MASK;
					Frmwk.TRUEHD.LFE_enable = 1;
				}
			}
			else
			{
				speakers_config1 	= DTHDI_DEC_CH_CFG_RAW;
				Frmwk.TRUEHD.LFE_enable 	= 1;
			}
			Frmwk.TRUEHD.Output_Ch_Config	= speakers_config1;
			datmos_speaker_legacy();
		if(((Frmwk.datmos_speaker_legacy_option>>12) & 0x00000001)==1 && (((Frmwk.datmos_speaker_legacy_option>>26) & 0x00000001)==0))
		{
			graph_type_cmd  				= 0;
			Frmwk.MAT.Legacy_Decode 		= 1;
			Frmwk.Legacy_Mode_enable		= 1;
			Frmwk.Speakers_presence_7_1 	= (Frmwk.speakers_bitmask) & AR_SPEAKER_71_MASK;
			Frmwk.b_mat_pcm_mode 			= 1;
			return 0;
		}
	#endif 
#ifdef EXT_DNMIX
		}
	}
#endif
	Frmwk.TRUEHD.Object_decode_flag = (Frmwk.core_config) ? 0 : 1;
	//	Frmwk.TRUEHD.Output_Ch_Config	= speakers_config1;

	return 0;

}

#pragma section("Seg_MAT_Kernel_Code_L3")
void MAT_PCM_Variable_Init()
{
	Frmwk.IOP.LatencyDone 		= 0;
	Frmwk.MAT.Decoder_Error 	= 0;
#ifdef DOLBY_MAT
	mat_dec_init(Frmwk.MAT.matpstate);
#endif
	Frmwk.MAT.No_of_Channels 	= 32;
	Frmwk.MAT.update_params 	= 1;
}

/**************************************************************************************************
 *  Module Name        : MAT_PCM_Predac_Allocation
 *  Functionality      : MAT PCM PACK Predac Memory allocation and Length and length half definitions
 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/
#pragma section("Seg_MAT_Kernel_Code_L3")
void MAT_PCM_Predac_Allocation()
{
	int size2,sampleblock,Predac_Int_size;
	if((Frmwk.MAT.decoded_sampling_frequency == MAT_48k) || (Frmwk.MAT.decoded_sampling_frequency == MAT_44k))
	{
		size2 						= PREDAC_LENGTH_MATPCM_48K;
		Frmwk.MAT.channel_modifier 	= 25;
		Frmwk.MAT.No_of_Channels 	= 32;
	}

	if(Frmwk.MemoryAllotMAT)
	{
		Frmwk.MemoryAllotMAT		= 0;
	}
}

#if defined (DOLBY_DAP) || defined (DOLBY_OAR) || defined (DOLBY_DMX)
/**************************************************************************************************
 *  Module Name        : Init_Var_Fs
 *  Functionality      : Variables which is need to be initialized to restart the
 *  					system process for decoder fs switching case should be placed here
						In this framework, Latency process & system process for decoder are initiated
						This function will be called in GENERAL_DECODING_COMMAND command Fs switching case

 *  Input Parameters   : None
 *  Output Parameters  : None
 *************************************************************************************************/
#pragma section("Seg_Dolby_Kernel_Code_L3")
void Init_Var_PP()
{
#ifdef DOLBY_DAP
	Frmwk.DAP_krnl.DAP_Init_Done 				= 0;
	Frmwk.DAP_krnl.DMX_ChannelMapping 			= 0;
	Frmwk.DAP_krnl.DAP_Process_Error 			= 0;
	Frmwk.DAP_krnl.DAP_ON_OFF 					= 1;
	Frmwk.DAP_krnl.DAP_first_frame 				= 1;
	Frmwk.FADER_Frmwk.fader_active 				= 0;
	Frmwk.DAP_krnl.DAP_prev_nchannels_in 		= 0;
	Frmwk.DAP_krnl.DAP_Init_Skip				= 0;
	Frmwk.DAP_krnl.DolbyUpmixer_Done_temp		= 0;
#endif

#ifdef DOLBY_OAR
	Frmwk.OAR_Frmwk.OARiInitFlag 			= 1;
	Frmwk.OAR_Frmwk.OAR_b_enable_limiter	= 1;
	Frmwk.OAR_Frmwk.Do_OARi_OAR_Process 	= 0;
	Frmwk.OAR_Frmwk.OAR_Done_temp 			= 0;
	Sync_detected=0;
#endif

#ifdef DOLBY_DMX
	Frmwk.dmx_Frmwk.dmx_init_done 			= 0;
	Frmwk.dmx_Frmwk.dmx_params_b_bypass 	= 0;
	Frmwk.DAP_krnl.Prev_DMX_ChannelMapping 	= 0;
#endif

#ifdef AURO_3D
	Auro_Processing_done=0;
#endif

}
#endif
#if defined (DOLBY_OAR) || defined (DOLBY_DAP)
#pragma default_section(SWITCH,"Seg_DAP_Kernel_Data_L3")
#pragma section("Seg_DAP_Kernel_Code_L3")
void Dolby_Command_handling()
{
	Frmwk.b_mat_pcm_mode	= 0;
	Frmwk.DAP_krnl.DAP_upmixer_On_Off		= Frmwk.DAP_krnl.DAP_upmixer;
	Frmwk.DAP_krnl.DAP_previous_virtuali 	= -1;

	datmos_ht_speaker_presence_remap_kernel();
	datmos_ht_core_config_check_kernel();
#ifdef EXT_DNMIX
	speakers_bitmask_Cs = (Frmwk.speakers_bitmask) & 0x1FBF;
#endif

	ar_speaker_mask 					= Frmwk.speakers_bitmask;
#ifdef AURO_3D
	graph_type_cmd 					= datmos_ht_graph_type_configure(Frmwk.Legacy_Mode_enable,Frmwk.tuning_mode_enable,Frmwk.DAP_krnl.DAP_Tuning_ON_OFF);
	Frmwk.graph_type  = graph_type_cmd;
#else
	Frmwk.graph_type 					= datmos_ht_graph_type_configure(Frmwk.Legacy_Mode_enable,Frmwk.tuning_mode_enable,Frmwk.DAP_krnl.DAP_Tuning_ON_OFF);
#endif
	if(Frmwk.graph_type == DATMOS_HT_GRAPH_TYPE_EXTENDED)
	{
		Frmwk.DAP_OAR_Reinit = 1;
	}
	/* Error handling for tuning tool enabled with extended graph type cases */
	if(Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 1 && Frmwk.graph_type == DATMOS_HT_GRAPH_TYPE_EXTENDED)
	{
		Frmwk.DAP_krnl.DAP_Tuning_ON_OFF = 0;
		Frmwk.Legacy_Mode_enable = 0;
	}
	Frmwk.DAP_krnl.Direct_Decode 		= Frmwk.Legacy_Mode_enable;
#if defined (DOLBY_DDP)||defined (DOLBY_DD)
	Frmwk.DDPlus.Legacy_Decoding_Mode	= Frmwk.Legacy_Mode_enable;
#endif
#if defined (DOLBY_THD) || defined (DOLBY_MAT)
	Frmwk.TRUEHD.legacy_mode_cmd 		= Frmwk.Legacy_Mode_enable;
	Frmwk.MAT.Legacy_Decode 			= Frmwk.Legacy_Mode_enable;

	if(Frmwk.TRUEHD.Prev_Legacymode != Frmwk.TRUEHD.legacy_mode_cmd )
	{
		Frmwk.TRUEHD.Prev_Legacymode =  Frmwk.TRUEHD.legacy_mode_cmd;
		Frmwk.InitDoneForStreamType = 0xF;
	}
#endif
	Frmwk.DAP_krnl.DAP_Speakers 			= Frmwk.speakers_bitmask;
	Frmwk.dmx_Frmwk.dmx_params_speakers		= Frmwk.speakers_bitmask;
	Frmwk.speakers_bitmask_OAR				= Frmwk.speakers_bitmask;
	/** Handling of error decision start **/
	if(Frmwk.tuning_mode_enable == 1)
	{
#if defined (DOLBY_THD) || defined (DOLBY_MAT)
		Frmwk.MAT.DRC_Mode					= 0;		/*	DRC cannot be enabled in tuning mode				*/
#endif
		Frmwk.DAP_krnl.Direct_Decode 		= 0;		/*	Direct decoding cannot be enabled in tuning mode	*/
		Frmwk.DAP_krnl.DAP_virtuali 		= 0;		/*	Virtualizer has to be disabled in tuning mode		*/
		Frmwk.DAP_krnl.DAP_Audio_Profile 	= 0;		/*	Audio profile cannot be used in tuning mode		*/
	}

	if (Frmwk.DAP_krnl.DAP_virtuali == DATMOS_VIRTUALIZER_MODE_HEADPHONE && Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 0)
	{
		Frmwk.DAP_krnl.DAP_Speakers 					= AR_SPEAKER_20_MASK;			/*For Headphone virtualization speaker should be LR only applicable*/
		Frmwk.dmx_Frmwk.dmx_params_speakers				= AR_SPEAKER_20_MASK;
		Frmwk.DAP_krnl.virtualizer_front_angle			= 0;
		Frmwk.DAP_krnl.virtualizer_height_angle			= 0;							/*For Headphone virtualization speaker angle not applicable - should be disable*/
		Frmwk.DAP_krnl.virtualizer_surround_angle		= 0;
		Frmwk.DAP_krnl.virtualizer_rear_surround_angle	= 0;
	}
	if(Frmwk.DAP_krnl.DAP_Audio_Profile > 3 && Frmwk.DAP_krnl.DAP_Audio_Profile <= 11 && Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 0) /** This profile could be only used with "Tuning tool file" **/
	{
		Frmwk.DAP_krnl.DAP_Audio_Profile = 0;								/*Default Audio profile OFF*/
	}

	if(Frmwk.DAP_krnl.DAP_virtuali == DATMOS_VIRTUALIZER_MODE_SPEAKER && Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 0)
	{
		if((Frmwk.DAP_krnl.virtualizer_surround_angle) && (((Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LS_RS) & 0x1) == DATMOS_SPEAKER_PRESENCE_OFF))
		{
			Frmwk.DAP_krnl.virtualizer_surround_angle = 0;					/*Speaker angle value for surround speakers has been provided but surround speakers are missing from the speaker layout*/
		}
		if((Frmwk.DAP_krnl.virtualizer_rear_surround_angle) && (((Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LRS_RRS) & 0x1) == DATMOS_SPEAKER_PRESENCE_OFF))
		{
			Frmwk.DAP_krnl.virtualizer_rear_surround_angle = 0;				/*Speaker angle value for rear surround speakers has been provided but surround speakers are missing from the speaker layout*/
		}
	}
	if((Frmwk.DAP_krnl.DAP_virtuali == DATMOS_VIRTUALIZER_MODE_SPEAKER
			&& Frmwk.DAP_krnl.virtualizer_height_angle) && (Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 0))
	{
		if(((Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_SH) & 0x1) == DATMOS_SPEAKER_PRESENCE_ON)
		{
			Frmwk.DAP_krnl.virtualizer_height_angle = 0;					/*Value of the height virtualization speaker angle cannot be applied if the Single height speaker is present in the speaker layout*/
		}
		else if ((((Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LTF_RTF) & 0x1) == DATMOS_SPEAKER_PRESENCE_OFF) &&
				(((Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LTM_RTM) & 0x1) == DATMOS_SPEAKER_PRESENCE_OFF))
		{
			Frmwk.DAP_krnl.virtualizer_height_angle = 0;					/*Speaker angle value for height speakers has been provided but height speakers are missing from the speaker layout*/
		}
	}

	if((Frmwk.DAP_krnl.center_spread_enable == 1) && (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_C & 0x1) == DATMOS_SPEAKER_PRESENCE_OFF)
	{
		Frmwk.DAP_krnl.center_spread_enable = 0;							/*Center spreading can only be enabled if Center speaker is present*/
	}

	if(Frmwk.graph_type == DATMOS_HT_GRAPH_TYPE_EXTENDED)  					/* Channel gains cannot be used in extended graph*/
	{
		Frmwk.DAP_krnl.Frontgain 		= 0;
		Frmwk.DAP_krnl.lfegain			= 0;
		Frmwk.DAP_krnl.surrgain			= 0;
		Frmwk.DAP_krnl.heightgain		= 0;
		Frmwk.DAP_krnl.rearsurrgain		= 0;
		Frmwk.DAP_krnl.rearheightgain	= 0;
		Frmwk.DAP_krnl.Centergain		= 0;
	}
	if((Frmwk.graph_type == DATMOS_HT_GRAPH_TYPE_EXTENDED) && (Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 0))
	{
		Frmwk.DAP_krnl.DAP_height_filter 	= 0;							/*Audio profile, virtualization and height cue filter is not allowed when graph type is extended*/
		Frmwk.DAP_krnl.DAP_virtuali 		= 0;
		Frmwk.DAP_krnl.DAP_Audio_Profile 	= 0;
	}

	const unsigned int heights = datmos_ht_height_speaker_count_get();
	/* The Single height speaker can be used in speaker layouts: 2.x.1, 3.x.1, 4.x.1 or 5.x.1.*/
	if ( (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_SH & 0x1) == DATMOS_SPEAKER_PRESENCE_ON)
	{
		/* Only Single Height speaker alone is supported
		 * Speaker layout cannot contain any extended speakers
		 */
		if (heights > 1
				|| ((Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LRS_RRS & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LS1_RS1 & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LS2_RS2 & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LRS1_RRS1 & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LRS2_RRS2 & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LCS_RCS & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_CS & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LSC_RSC & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LC_RC & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF
						|| (Frmwk.speakers_bitmask >> DATMOS_SPEAKER_ID_LW_RW & 0x1)
						!= DATMOS_SPEAKER_PRESENCE_OFF))
		{

			Frmwk.DAP_krnl.DAP_Speakers 					= AR_SPEAKER_511_MASK;			/* The Single height speaker can be used in speaker layouts: 2.x.1, 3.x.1, 4.x.1 or 5.x.1.*/
			Frmwk.dmx_Frmwk.dmx_params_speakers				= AR_SPEAKER_51_MASK;			/* Here, speaker configuration mapped to worst case of 5.1 for dmx and 5.x.1 for DAP */
        	Frmwk.speakers_bitmask 			 				= AR_SPEAKER_511_MASK;         /* Speaker config handled for channel reorder */
        	Frmwk.speakers_bitmask_OAR						= AR_SPEAKER_511_MASK;         /* Speaker bitmask of OAR handled for Single Height cases */
        	ar_speaker_mask 				 				= Frmwk.speakers_bitmask;     /* ar speaker mask handled for Single Height cases */
        	graph_type_cmd                     			= DATMOS_HT_GRAPH_TYPE_REGULAR;
		}
	}

	if(Frmwk.DAP_krnl.DAP_Audio_Profile != 0)												/* If Audio profile is enabled, DRC must be disabled */
	{
#if defined (DOLBY_THD) || defined (DOLBY_MAT)
		Frmwk.TRUEHD.KERNEL_drc_enable 	= 0;
		Frmwk.MAT.DRC_Mode  		    = 0;
#endif
#if defined (DOLBY_DDP)||defined (DOLBY_DD)
		Frmwk.DDPlus.dynscalehigh		= 0;
		Frmwk.DDPlus.dynscalelow		= 0;
#endif
	}
#if defined (DOLBY_THD) || defined (DOLBY_MAT)
	if(Frmwk.TRUEHD.Loudness_enable == 0 || Frmwk.MAT.Loudness_Management == 0)				/* If Loudness management is disabled, then DRC and Audio Profile must also be disabled */
	{
		Frmwk.TRUEHD.KERNEL_drc_enable   = 0;
		Frmwk.MAT.DRC_Mode			     = 0;
		Frmwk.DAP_krnl.DAP_Audio_Profile = 0;
#if defined (DOLBY_DDP)||defined (DOLBY_DD)
		Frmwk.DDPlus.dynscalehigh	   	 = 0;
		Frmwk.DDPlus.dynscalelow		 = 0;
#endif
	}
#endif
	/** Handling of error decision end **/
	if(Frmwk.Legacy_Mode_enable)
	{
#if defined(EXT_DNMIX) || defined(EXT_DNMIX_DDP)
		if ((Frmwk.speakers_bitmask == 0x40D) || (Frmwk.speakers_bitmask == 0x10D) || (Frmwk.speakers_bitmask == 0x8D) || (Frmwk.speakers_bitmask == 0x409))
		{
			Frmwk.Speakers_presence_7_1 = Frmwk.speakers_bitmask;
		}
		else if (Cs_enable ==1)
		{
			Frmwk.Speakers_presence_7_1 = (speakers_bitmask_Cs & AR_SPEAKER_71_MASK) |  0x20 ;
		}
		else
#endif
		{
			Frmwk.Speakers_presence_7_1 			= (Frmwk.speakers_bitmask) & AR_SPEAKER_71_MASK;
		}
		Frmwk.OAR_Frmwk.Speaker_Output_Config 	= Frmwk.Speakers_presence_7_1;
		Frmwk.dmx_Frmwk.dmx_params_speakers		= Frmwk.Speakers_presence_7_1;

#ifdef DOLBY_OAR
		if(Frmwk.OAR_Frmwk.Speaker_Output_Config!=Frmwk.OAR_Frmwk.Prev_Speaker_Output_Config)
		{
			Frmwk.OAR_Frmwk.OARiInitFlag 		= 1;
			Frmwk.OAR_Frmwk.OAR_b_enable_limiter= 1;

			InitOARiModule();

			Frmwk.OAR_Frmwk.Prev_Speaker_Output_Config = Frmwk.OAR_Frmwk.Speaker_Output_Config;
		}
#endif /* DOLBY_OAR */
		return;
	}

	/*Single Height Channel re-mapping to LRTM for OAR*/
	if(((Frmwk.speakers_bitmask>>19)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
	{
		Frmwk.speakers_bitmask_OAR &= 0x11fff;
		Frmwk.speakers_bitmask_OAR |= AR_SPEAKER_LTM_RTM_MASK;
	}

	if (DATMOS_HT_GRAPH_TYPE_EXTENDED != Frmwk.graph_type)
	{

		if(Frmwk.DAP_krnl.DAP_virtuali == DATMOS_VIRTUALIZER_MODE_SPEAKER)
		{
			surr_speakers_present 		= (Frmwk.speakers_bitmask_OAR & AR_SPEAKER_LS_RS_MASK);//(*Frmwk.speakers_bitmask>>3)&1;
			rear_surr_speakers_present 	= (Frmwk.speakers_bitmask_OAR & AR_SPEAKER_LRS_RRS_MASK);//(*Frmwk.speakers_bitmask>>4)&1;
			height_speakers_present 	= (Frmwk.speakers_bitmask_OAR & AR_SPEAKER_HEIGHTS_MASK);//((*Frmwk.speakers_bitmask>>9)&1) | ((*Frmwk.speakers_bitmask>>10)&1) | ((*Frmwk.speakers_bitmask>>11)&1);

			/* 6.x VH, 6.x VH+SB, 6.x.2 SB, 6.x.4 SB, 7.x VH, 7.x VH+SB, 7.x.2 SB, 7.x.4 SB */
			if (rear_surr_speakers_present)
			{
				Frmwk.speakers_bitmask_OAR  = AR_SPEAKER_714_MASK;
			}
			/* 4.x VH, 5.x VH, 4.x.2, 5.x.2 4.x.4, 5.x.4 */
			else if (surr_speakers_present)
			{
				/* 4.x.4, 5.x.4 */
				if (Frmwk.speakers_bitmask_OAR  & AR_SPEAKER_LTR_RTR_MASK)
				{
					Frmwk.speakers_bitmask_OAR  = AR_SPEAKER_514_MASK;
				}
				/* 4.x VH, 5.x VH, 4.x.2, 5.x.2 */
				else
				{
					Frmwk.speakers_bitmask_OAR = height_speakers_present ? AR_SPEAKER_512_MASK : AR_SPEAKER_514_MASK;
				}
			}
			/* 2.0 VH, 2.x.2, , 3.x VH, 3.x.2 */
			else
			{
				Frmwk.speakers_bitmask_OAR  = AR_SPEAKER_512_MASK;
			}
		}
		/* If Headphone virtualization is enabled set OAR to 7.1.2 */
		else if (Frmwk.DAP_krnl.DAP_virtuali == DATMOS_VIRTUALIZER_MODE_HEADPHONE)
		{
			Frmwk.speakers_bitmask_OAR = AR_SPEAKER_712_MASK;
		}
		else
		{
			if (Frmwk.speakers_bitmask_OAR != AR_SPEAKER_20_MASK)
				Frmwk.speakers_bitmask_OAR |= AR_SPEAKER_LFE_MASK;

			switch (Frmwk.speakers_bitmask_OAR)
			{
			case AR_SPEAKER_20_MASK:
				Frmwk.speakers_bitmask_OAR = AR_SPEAKER_20_MASK;
				break;
			case AR_SPEAKER_21_MASK:
			case AR_SPEAKER_31_MASK:
			case AR_SPEAKER_41_MASK:
			case AR_SPEAKER_51_MASK:
				Frmwk.speakers_bitmask_OAR = AR_SPEAKER_51_MASK;
				break;
			case AR_SPEAKER_61_MASK:
			case AR_SPEAKER_71_MASK:
				Frmwk.speakers_bitmask_OAR = AR_SPEAKER_71_MASK;
				break;
			case AR_SPEAKER_212_MASK:
			case AR_SPEAKER_312_MASK:
			case AR_SPEAKER_412_MASK:
			case AR_SPEAKER_512_MASK:
				Frmwk.speakers_bitmask_OAR = AR_SPEAKER_512_MASK;
				break;
			case AR_SPEAKER_414_MASK:
			case AR_SPEAKER_514_MASK:
				Frmwk.speakers_bitmask_OAR = AR_SPEAKER_514_MASK;
				break;
			case AR_SPEAKER_612_MASK:
			case AR_SPEAKER_712_MASK:
				Frmwk.speakers_bitmask_OAR = AR_SPEAKER_712_MASK;
				break;
			case AR_SPEAKER_614_MASK:
			case AR_SPEAKER_714_MASK:
				Frmwk.speakers_bitmask_OAR = AR_SPEAKER_714_MASK;
				break;
			default:
				break;
			}
		}

	}

#ifdef DOLBY_OAR
	Frmwk.OAR_Frmwk.Speaker_Output_Config 		=	Frmwk.speakers_bitmask_OAR; 	//Bitfield that specifies the required speakers

	if(Frmwk.OAR_Frmwk.Speaker_Output_Config!=Frmwk.OAR_Frmwk.Prev_Speaker_Output_Config)
	{
		Frmwk.OAR_Frmwk.OARiInitFlag 		= 1;
		Frmwk.OAR_Frmwk.OAR_b_enable_limiter= 1;

		InitOARiModule();

		Frmwk.OAR_Frmwk.Prev_Speaker_Output_Config = Frmwk.OAR_Frmwk.Speaker_Output_Config;
	}

	if (3 == Frmwk.graph_type)
	{
		Frmwk.OAR_Frmwk.Extended_graph			= 1;
		Frmwk.OAR_Frmwk.Upmix					= 1;	// *Upmix_ON_OFF_Status;
		Frmwk.OAR_Frmwk.OARiInitFlag 			= 1;
	}
	else
	{
		Frmwk.OAR_Frmwk.Extended_graph			= 0;
	}
#endif
	
}

/******************************************************************************
 *  Module Name        : datmos_ht_speaker_presence_remap_kernel
 *  Functionality      : Remap requested DOLBY ATMOS enabled speaker feeds to discrete height speaker feeds

 ******************************************************************************/
#pragma section("Seg_DAP_Kernel_Code_L3")
void datmos_ht_speaker_presence_remap_kernel ()
{

	const unsigned int heights 		= datmos_ht_height_speaker_count_get();
	const unsigned int daes_count 	=  datmos_ht_daes_count();

	/*The height cue filter can only be enabled for Dolby Atmos enabled speaker pairs*/
	if((Frmwk.DAP_krnl.DAP_height_filter == 1) && (daes_count == 0))
		Frmwk.DAP_krnl.DAP_height_filter = 0;

	/* Check if corresponding floor speaker is present */
	if (((((Frmwk.speakers_bitmask>>20)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
			&&  (((Frmwk.speakers_bitmask>>0)&0x1) == DATMOS_SPEAKER_PRESENCE_OFF))
			||  ((((Frmwk.speakers_bitmask>>21)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
					&&  (((Frmwk.speakers_bitmask>>3)&0x1) == DATMOS_SPEAKER_PRESENCE_OFF))
					||  ((((Frmwk.speakers_bitmask>>22)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
							&&  (((Frmwk.speakers_bitmask>>4)&0x1) == DATMOS_SPEAKER_PRESENCE_OFF)))
	{
		Frmwk.cmd_result = 1;
		return;
	}

	/*
	 * The integration code should detect and reject the following cases of
	 * wrong speaker layouts:
	 * - one pair of upfiring speakers and LRtm,
	 * - two pairs of upfiring speakers and (LRtf or LRtr),
	 * - three pairs of upfiring speakers and (LRtf or LRtm or LRtr).
	 */

	if (2 == daes_count)
	{
		Frmwk.speakers_bitmask |= (1 << 10);
	}

	else if (4 == daes_count)
	{
		Frmwk.speakers_bitmask |= (1 << 9);
		Frmwk.speakers_bitmask |= (1 << 11);
	}

	else if (6 == daes_count)
	{
		Frmwk.speakers_bitmask |= (1 << 9);
		Frmwk.speakers_bitmask |= (1 << 10);
		Frmwk.speakers_bitmask |= (1 << 11);
	}

	/* Remove upfiring speakers from layout */
	Frmwk.speakers_bitmask 		= (Frmwk.speakers_bitmask) & 0x91FBF;

	/*
	 * If only one height speaker pair is available and we have 2.x.2/3.x.2
	 * remap it to Ltm/Rtm
	 */
	if(((Frmwk.speakers_bitmask>>0)&0x1)==1
			&& ((Frmwk.speakers_bitmask>>3)&0x1)==0
			&& 2 == heights)//lrtr=0
	{
		Frmwk.speakers_bitmask &= ~(1<<8);
		Frmwk.speakers_bitmask &= ~(1<<9);
		Frmwk.speakers_bitmask &= ~(1<<11);
		Frmwk.speakers_bitmask &= ~(1<<12);
		Frmwk.speakers_bitmask |= (1<<10);
	}

}

/******************************************************************************
 *  Module Name        : datmos_ht_daes_count
 *  Functionality      : Determine if a room configuration consists of 5.1 or fewer speakers

 ******************************************************************************/
#pragma section("Seg_DAP_Kernel_Code_L3")
unsigned int
datmos_ht_daes_count()
{
	unsigned int daes_count = 0;

	if (((Frmwk.speakers_bitmask>>20)&0x1)!=0)
	{
		daes_count += 2;
	}
	if (((Frmwk.speakers_bitmask>>21)&0x1)!=0)
	{
		daes_count += 2;
	}
	if (((Frmwk.speakers_bitmask>>22)&0x1)!=0)
	{
		daes_count += 2;
	}

	return daes_count;
}


/******************************************************************************
 *  Module Name        : datmos_ht_height_speaker_count_get
 *  Functionality      : Calculating the number of height speaker present in the user speaker option

 ******************************************************************************/
#pragma section("Seg_DAP_Kernel_Code_L3")
unsigned int datmos_ht_height_speaker_count_get()
{
	unsigned int spkrs_count = 0;
	if (((	Frmwk.speakers_bitmask>>9)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
	{
		spkrs_count += 2;
	}
	if (((	Frmwk.speakers_bitmask>>11)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
	{
		spkrs_count += 2;
	}
	if (((	Frmwk.speakers_bitmask>>10)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
	{
		spkrs_count += 2;
	}
	if (((	Frmwk.speakers_bitmask>>8)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
	{
		spkrs_count += 2;
	}
	if (((	Frmwk.speakers_bitmask>>12)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
	{
		spkrs_count += 2;
	}
	if (((	Frmwk.speakers_bitmask>>19)&0x1) == DATMOS_SPEAKER_PRESENCE_ON)
	{
		spkrs_count += 1;
	}
	return spkrs_count;
}
#endif /* (DOLBY_OAR) || (DOLBY_DAP) */
#ifdef DOLBY_LIB
/******************************************************************************
 *  Module Name        : datmos_ht_core_config_check
 *  Functionality      : Determine if a room configuration consists of 5.1 or fewer speakers

 ******************************************************************************/
#pragma section("Seg_Dolby_Kernel_NW_Code_L3",NW)
void datmos_ht_core_config_check_kernel()
{
	/* Check if virtualizer is disabled and Lrs/Rrs, as well as all of the
	 * speakers that only have Ls/Rs as prerequisites, and all height speakers
	 */
	if( (Frmwk.DAP_krnl.DAP_virtuali == 0)				/** virtualizer disable	**/
			&& (((Frmwk.speakers_bitmask >> 4) & 0x1) == 0)		/** 4	= lrs,rrs		**/
			&& (((Frmwk.speakers_bitmask >> 7) & 0x1) == 0)		/** 7	= lw,rw 		**/
			&& (((Frmwk.speakers_bitmask >> 5) & 0x1) == 0)		/** 5	= cs 			**/
			&& (((Frmwk.speakers_bitmask >> 6) & 0x1) == 0)		/** 6	= lc,rc 		**/
			&& (((Frmwk.speakers_bitmask >> 13) & 0x1) == 0)	/** 13	= lsc,rsc 		**/
			&& (((Frmwk.speakers_bitmask >> 9) & 0x1) == 0)		/** 9	= ltf,trf 		**/
			&& (((Frmwk.speakers_bitmask >> 10) & 0x1) == 0)	/** 10	= ltm,rtm 		**/
			&& (((Frmwk.speakers_bitmask >> 11) & 0x1) == 0)	/** 11	= ltr,rtr 		**/
			&& (((Frmwk.speakers_bitmask >> 12) & 0x1) == 0)	/** 12	= lrh,rrh 		**/
			&& (((Frmwk.speakers_bitmask >> 8) & 0x1) == 0)		/** 8	= lfh,rfh 		**/
			&& (((Frmwk.speakers_bitmask >> 19) & 0x1) == 0) )	/** 19	= sh 			**/
	{
		Frmwk.core_config = 1;
	}
	else
	{
		Frmwk.core_config = 0;
	}
}
/******************************************************************************
 *  Module Name        : Memory_Pointer_Allocation
 *  Functionality      : L2 memory pointer mapping

 ******************************************************************************/
#pragma section("Seg_Dolby_Kernel_Code_L3")
void Memory_Pointer_Allocation()
{
	/* L2 buffer pointer mapping */
	libraray_l2_data 				= L2_POINTER_OFFSET1;
	Predac_buffer_Int_pp	   		= L2_POINTER_OFFSET3;
#ifdef DTSX_DAP
	if(DTS_DAPEnable == 1)
	{
		Predac_buffer_Int_pp	   		= (int*)(L2_dm_start_Addr + 0xC2918);//0x20122918;//(int*)(L2_dm_start_Addr + 182024);
	}
#endif	
	Predac_buffer_Int_pp_rdptr 		= (int)Predac_buffer_Int_pp;
	Predac_buffer_Int_pp_wrptr 		= (int)Predac_buffer_Int_pp;

}
#if (defined (DOLBY_THD) && defined (DOLBY_THD_DS))
/******************************************************************************
 *  Module Name        : Memory_Pointer_Allocation
 *  Functionality      : L2 memory pointer mapping

 ******************************************************************************/
#pragma section("Seg_Dolby_Kernel_Code_L3")
void Memory_Pointer_Allocation_DS()
{
	/* L1 Block0 and Block2 buffer pointer mapping */
	leftinput_delays_heap_buffer	= L1_BLOCK0_POINTER_OFFSET4;
	rightinput_delays_heap_buffer	= L1_BLOCK0_POINTER_OFFSET5;
	centerinput_delays_heap_buffer	= L1_BLOCK0_POINTER_OFFSET6;
	lfeinput_delays_heap_buffer		= L1_BLOCK0_POINTER_OFFSET7;
	Ls_input_delays_heap_buffer		= L1_BLOCK0_POINTER_OFFSET8;
	Rs_input_delays_heap_buffer		= L1_BLOCK0_POINTER_OFFSET9;
	Lsr_input_delays_heap_buffer	= L1_BLOCK0_POINTER_OFFSET10;
	Rsr_input_delays_heap_buffer	= L1_BLOCK0_POINTER_OFFSET11;
	DS_Coef_192to48_Ptr_Add 		= L1_BLOCK2_POINTER_OFFSET4;
	DS_Coef_96to48_Ptr_Add 			= L1_BLOCK2_POINTER_OFFSET5;
	DS_Coef_192to96_Ptr_Add			= L1_BLOCK2_POINTER_OFFSET5;

}
#endif
/******************************************************************************
 *  Module Name        : dpf_node_get_channel_format_ar_mask_kernel
 *  Functionality      : Define the channel count of ground,height and LFE speakers

 ******************************************************************************/
#pragma section("Seg_Dolby_Kernel_NW_Code_L3",NW)
void dpf_node_get_channel_format_ar_mask_kernel(dpf_node_channel_format *fmt)
{
	int idx, heights = 0, grounds = 0;
	int _lfe = 0;

	for (idx = 0; idx <= AR_SPEAKER_MASK_MAX_INDEX; ++idx)
	{
		unsigned long mask = 1 << idx;
		if (ar_speaker_mask & mask & AR_SPEAKER_HEIGHTS_MASK)
		{
			heights = AR_SPEAKER_IS_SINGLE(mask) ? heights + 1 : heights + 2;
		}
		else if (ar_speaker_mask & mask & AR_SPEAKER_LFE_MASK)
		{
			_lfe = 1;
		}
		else if (ar_speaker_mask & mask)
		{
			grounds = AR_SPEAKER_IS_SINGLE(mask) ? grounds + 1 : grounds + 2;
		}
	}

	fmt->ground_channel_num = grounds;
	fmt->height_channel_num = heights;
	fmt->channel_num = grounds + heights + _lfe;
	fmt->_lfe= _lfe;
}
/******************************************************************************
 *  Module Name        : datmos_ht_graph_type_configure
 *  Functionality      : Determine the graph type based on speaker configuration and tuning mode

 ******************************************************************************/
#pragma section("Seg_Dolby_Kernel_NW_Code_L3",NW)
int datmos_ht_graph_type_configure(int Direct_decode, int tuning_mode_enable, int DAP_Tuning_ON_OFF)
{
	int result = DATMOS_HT_GRAPH_TYPE_UNKNOWN;
	dpf_node_channel_format ch_fmt;
	if (tuning_mode_enable == 1)
		return DATMOS_HT_GRAPH_TYPE_TUNING;

	dpf_node_get_channel_format_ar_mask_kernel(&ch_fmt);
	if ((ar_speaker_mask & AR_SPEAKER_EXTENDED_MASK) ||
			(4 < ch_fmt.height_channel_num))
	{
		result = DATMOS_HT_GRAPH_TYPE_EXTENDED;
	}
	else if (ar_speaker_mask & AR_SPEAKER_LS_RS_MASK)
	{
		if (((2 >= ch_fmt.height_channel_num) &&
				((ar_speaker_mask & AR_SPEAKER_LTM_RTM_MASK) || (ar_speaker_mask & AR_SPEAKER_SH_MASK))))
		{
			result = DATMOS_HT_GRAPH_TYPE_REGULAR;
		}
		else if ((4 == ch_fmt.height_channel_num) &&
				(ar_speaker_mask & AR_SPEAKER_LTF_RTF_MASK) &&
				(ar_speaker_mask & AR_SPEAKER_LTR_RTR_MASK))
		{
			result = DATMOS_HT_GRAPH_TYPE_REGULAR;
		}
		else if (0 == ch_fmt.height_channel_num)
		{
			result = DATMOS_HT_GRAPH_TYPE_REGULAR;
		}
		else
		{
			result = DATMOS_HT_GRAPH_TYPE_EXTENDED;
		}
	}

	else
	{
		result = DATMOS_HT_GRAPH_TYPE_REGULAR;
	}

	if(Direct_decode == 1 && DAP_Tuning_ON_OFF == 1)
	{
		result = DATMOS_HT_GRAPH_TYPE_REGULAR;
	}
	/* Error handling for tuning tool enabled with above 7.1.4 speaker config cases */
	if(DAP_Tuning_ON_OFF == 1 && ((ar_speaker_mask & AR_SPEAKER_EXTENDED_MASK) || (4 < ch_fmt.height_channel_num)))
	{
		result = DATMOS_HT_GRAPH_TYPE_EXTENDED;
	}
	if(Direct_decode == 1 && DAP_Tuning_ON_OFF == 0)
	{
		result = DATMOS_HT_GRAPH_TYPE_DIRECTDEC;
	}

	return result;
}

/******************************************************************************
 *  Module Name        : datmos_ht_graph_type_configure
 *  Functionality      : Determine the graph type based on speaker configuration and tuning mode

 ******************************************************************************/
#pragma section("Seg_Dolby_Kernel_NW_Code_L3",NW)
int Dolby_Legacy_CustPP_ChannelMask(unsigned long long  in_channels_mask)
{
	switch(in_channels_mask)
	{
	case C                       :           /*DDP_MODE: 1        */
		return Frmwk.Customer_pp.ChannelMask = 0x0002;
	case L                       :          /*Single L channel    */
		return Frmwk.Customer_pp.ChannelMask = 0x0001;
	case C_LFE                   :          /*DDP_MODE: 1  + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0006;
	case L_R                     :           /*DDP_MODE: 2        *//*TRUHD_MODE: 2       */
		return Frmwk.Customer_pp.ChannelMask = 0x0001;
	case L_R_LFE:                            /*DDP_MODE: 2  + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0005;
	case L_R_C_LFE               :           /*DDP_MODE: 3  + LFE *//*TRUHD_MODE: 3  + LFE*/
		return Frmwk.Customer_pp.ChannelMask = 0x0007;
	case L_R_LFE_CS              :           /*DDP_MODE: 4  + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0025;
	case L_R_C_LFE_CS            :           /*DDP_MODE: 5  + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0027;
	case L_R_LFE_LS_RS           :           /*DDP_MODE: 6  + LFE *//*TRUHD_MODE: 6  + LFE*/
		return Frmwk.Customer_pp.ChannelMask = 0x0015;
	case L_R_C_LFE_LS_RS         :           /*DDP_MODE: 7  + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0017;
	case L_R_C_LFE_CVH           :           /*DDP_MODE: 8  + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0017;									//have to update
	case L_R_LFE_LS_RS_TS        :           /*DDP_MODE: 9  + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x4015;
	case L_R_C_LFE_LS_RS_TS      :          /*DDP_MODE: 10 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x4017;
	case L_R_C_LFE_LS_RS_CVH     :           /*DDP_MODE: 11 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x4017;									//have to update
	case L_R_C_LFE_LC_RC         :           /*DDP_MODE: 12 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x4017;									//have to update
	case L_R_C_LFE_LFH_RFH             :
		return Frmwk.Customer_pp.ChannelMask = 0x0107;
	case L_R_C_LFE_LC_RC_CS      :
		return Frmwk.Customer_pp.ChannelMask = 0x0107;									//have to update
	case L_R_C_LFE_LC_RC_TS      :
		return Frmwk.Customer_pp.ChannelMask = 0x0107;									//have to update
	case L_R_LFE_LS_RS_LW_RW     :           /*DDP_MODE: 13 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0095;
	case L_R_LFE_LS_RS_LFH_RFH   :           /*DDP_MODE: 14 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0115;
	case L_R_LFE_LS_RS_LSD_RSD   :           /*DDP_MODE: 15 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0115;												//have to update
	case L_R_LFE_LS_RS_LRS_RRS   :           /*DDP_MODE: 16 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0055;
	case L_R_LFE_LS_RS_LC_RC   :
		return Frmwk.Customer_pp.ChannelMask = 0x0055;												//have to update
	case L_R_C_LFE_LS_RS_LC_RC   :           /*DDP_MODE: 17 + LFE *//*TRUHD_MODE: 17 + LFE*/
		return Frmwk.Customer_pp.ChannelMask = 0x0055;												//have to update
	case L_R_C_LFE_LS_RS_LW_RW   :           /*DDP_MODE: 18 + LFE *//*TRUHD_MODE: 18 + LFE*/
		return Frmwk.Customer_pp.ChannelMask = 0x0097;
	case L_R_C_LFE_LS_RS_LFH_RFH :           /*DDP_MODE: 19 + LFE *//*TRUHD_MODE: 19 + LFE*/
		return Frmwk.Customer_pp.ChannelMask = 0x0117;
	case L_R_C_LFE_LS_RS_LSD_RSD :           /*DDP_MODE: 20 + LFE *//*TRUHD_MODE: 20 + LFE*/
		return Frmwk.Customer_pp.ChannelMask = 0x0117;												//have to update
	case L_R_C_LFE_LS_RS_LRS_RRS :           /*DDP_MODE: 21 + LFE *//*TRUHD_MODE: 21 + LFE*/
		return Frmwk.Customer_pp.ChannelMask = 0x0057;
	case L_R_C_LFE_LS_RS_TS_CVH  :           /*DDP_MODE: 22 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0057;												//have to update
	case L_R_LFE_LS_RS_CS        :           /*DDP_MODE: 23 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0035;
	case L_R_C_LFE_LS_RS_CS      :           /*DDP_MODE: 24 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x0037;
	case L_R_C_LFE_LRS_RRS_CS      :
		return Frmwk.Customer_pp.ChannelMask = 0x0067;
	case L_R_C_LFE_LRS_RRS_TS      :
		return Frmwk.Customer_pp.ChannelMask = 0x4047;
	case L_R_LFE_LS_RS_CS_TS     :           /*DDP_MODE: 25 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x4065;
	case L_R_C_LFE_LS_RS_CS_CVH  :           /*DDP_MODE: 26 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x4065;												//have to update
	case L_R_C_LFE_LS_RS_CS_TS   :           /*DDP_MODE: 27 + LFE */
		return Frmwk.Customer_pp.ChannelMask = 0x4037;
	case L_R_C_LFE_LS_RS_LTM_RTM:            /* Pass through of 5.1.2  */
		return Frmwk.Customer_pp.ChannelMask = 0x0417;
	case L_R_C_LFE_LS_RS_LTF_RTF_LTR_RTR:    /* Pass through of 5.1.4  */
		return Frmwk.Customer_pp.ChannelMask = 0x0A17;
	case L_R_C_LFE_LS_RS_LRS_RRS_LTM_RTM:    /* Pass through of 7.1.2  */
		return Frmwk.Customer_pp.ChannelMask = 0x0457;
	case L_R_C_LFE_LS_RS_LRS_RRS_LTF_RTF_LTR_RTR:  /* Pass through of 7.1.4  */
		return Frmwk.Customer_pp.ChannelMask = 0x0A57;
	case L_R_C                   :           /*DDP_MODE:  3       *//*TRUHD_MODE: 3       */
		return Frmwk.Customer_pp.ChannelMask = 0x0003;
	case L_R_CS                   :          /*DDP_MODE:  4       */
		return Frmwk.Customer_pp.ChannelMask = 0x0003;
	case L_R_C_CS                 :          /*DDP_MODE:  5       */
		return Frmwk.Customer_pp.ChannelMask = 0x0023;
	case L_R_LS_RS               :           /*DDP_MODE:  6       *//*TRUHD_MODE: 6       */
		return Frmwk.Customer_pp.ChannelMask = 0x0011;
	case L_R_LRS_RRS             :
		return Frmwk.Customer_pp.ChannelMask = 0x0051;
	case L_R_C_LS_RS             :           /*DDP_MODE:  7       */
		return Frmwk.Customer_pp.ChannelMask = 0x0013;
	case L_R_C_CVH               :           /*DDP_MODE:  8       */
		return Frmwk.Customer_pp.ChannelMask = 0x0013;													//have to update
	case L_R_LS_RS_TS            :           /*DDP_MODE:  9       */
		return Frmwk.Customer_pp.ChannelMask = 0x4011;
	case L_R_C_LS_RS_TS          :           /*DDP_MODE: 10       */
		return Frmwk.Customer_pp.ChannelMask = 0x4013;
	case L_R_C_LS_RS_CVH         :           /*DDP_MODE: 11       */
		return Frmwk.Customer_pp.ChannelMask = 0x4013;													//have to update
	case L_R_C_LC_RC             :           /*DDP_MODE: 12       */
		return Frmwk.Customer_pp.ChannelMask = 0x0003;													//have to update
	case L_R_C_LFH_RFH             :
		return Frmwk.Customer_pp.ChannelMask = 0x0103;
	case L_R_LS_RS_LW_RW             :           /*DDP_MODE: 13       */
		return Frmwk.Customer_pp.ChannelMask = 0x0091;
	case L_R_LS_RS_LFH_RFH           :           /*DDP_MODE: 14       */
		return Frmwk.Customer_pp.ChannelMask = 0x0111;
	case L_R_LS_RS_LSD_RSD           :           /*DDP_MODE: 15       */
		return Frmwk.Customer_pp.ChannelMask = 0x0111;													//have to update
	case L_R_LS_RS_LRS_RRS           :           /*DDP_MODE: 16       */
		return Frmwk.Customer_pp.ChannelMask = 0x0051;
	case L_R_C_LS_RS_LC_RC           :           /*DDP_MODE: 17       *//*TRUHD_MODE: 17      */
		return Frmwk.Customer_pp.ChannelMask = 0x0051;													//have to update
	case L_R_C_LS_RS_LC_RC_CVH     :
		return Frmwk.Customer_pp.ChannelMask = 0x0051;													//have to update
	case L_R_C_LS_RS_LW_RW           :           /*DDP_MODE: 18       *//*TRUHD_MODE: 18      */
		return Frmwk.Customer_pp.ChannelMask = 0x0093;
	case L_R_C_LS_RS_LFH_RFH        :           /*DDP_MODE: 19       *//*TRUHD_MODE: 19      */
		return Frmwk.Customer_pp.ChannelMask = 0x0113;
	case L_R_C_LS_RS_LSD_RSD        :           /*DDP_MODE: 20       *//*TRUHD_MODE: 20      */
		return Frmwk.Customer_pp.ChannelMask = 0x0113;													//have to update
	case L_R_C_LS_RS_LRS_RRS        :           /*DDP_MODE: 21       *//*TRUHD_MODE: 21      */
		return Frmwk.Customer_pp.ChannelMask = 0x0053;
	case L_R_C_LS_RS_TS_CVH         :           /*DDP_MODE: 22       */
		return Frmwk.Customer_pp.ChannelMask = 0x0053;													//have to update
	case L_R_LS_RS_CS               :           /*DDP_MODE: 23       */
		return Frmwk.Customer_pp.ChannelMask = 0x0031;
	case L_R_C_LS_RS_CS             :           /*DDP_MODE: 24       */
		return Frmwk.Customer_pp.ChannelMask = 0x0033;
	case L_R_LS_RS_CS_TS            :           /*DDP_MODE: 25       */
		return Frmwk.Customer_pp.ChannelMask = 0x4031;
	case L_R_C_LS_RS_CS_CVH         :           /*DDP_MODE: 26       */
		return Frmwk.Customer_pp.ChannelMask = 0x4031;													//have to update
	case L_R_C_LS_RS_CS_TS          :           /*DDP_MODE: 27       */
		return Frmwk.Customer_pp.ChannelMask = 0x4033;
	case L_R_C_LFE_LS_RS_LFE2       :              /* 5.2                */
		return Frmwk.Customer_pp.ChannelMask = 0x4033;													//have to update
	case L_R_LFE_LS_RS_LRS_RRS_LFE2 :              /* 7.2 without C      */
		return Frmwk.Customer_pp.ChannelMask = 0x4033;													//have to update
	case L_R_LFE_LS_RS_CS_LFE2        :              /* L, R, LFE, LS, RS, CS, LFE2      */
		return Frmwk.Customer_pp.ChannelMask = 0x4033;													//have to update
	case L_R_C_LFE_LS_RS_LRS_RRS_LFE2 :              /* 7.2             */
		return Frmwk.Customer_pp.ChannelMask = 0x4033;													//have to update
	case L_R_LFE_LS_RS_LC_RC_CVH:
		return Frmwk.Customer_pp.ChannelMask = 0x4033;													//have to update
	default:
		return Frmwk.Customer_pp.ChannelMask = 0x0;
	}
}

#endif /* DOLBY_LIB */

#ifdef eARC_ENABLE
#pragma section("Seg_Kernal_Code_L3")
void eARC_PCG_Clock_Divider(int sample_fs_micro,int Output_SampleRate)
{
	if(Frmwk.autodetect_mode == AUTODETECT3)
	{
		SRU(HIGH,DAI1_PBEN12_I);
		SRU(DAI1_PB07_O,PCG0_EXTCLKD_I);     // MCLK to PCG-D

		SRU(PCG0_CLKD_O, DAI1_PB12_I);
		SRU(DAI1_PB12_O,PCG0_EXTCLKC_I);     // PCG-D to PCG-C

		ADI_PCG_CLK_INFO gClkInfo_D;
		gClkInfo_D.eClkInput 		= ADI_PCG_CLK_EXT;			/* Clock Source */
		gClkInfo_D.nDiv 			= 4;						/* Clock Divisor */
		gClkInfo_D.bExternalTrigger = false;					/* External Trigger */
		gClkInfo_D.bHwTriggerCtl= false;

		ADI_PCG_FS_INFO gFsInfo_D;
		gFsInfo_D.eClkInput = ADI_PCG_FS_EXT;                     /* Clock Source */
		gFsInfo_D.nDiv = 4;      				      /* Frame Sync Divisor */
		gFsInfo_D.nPulseWidth = (gFsInfo_D.nDiv)/2u;                         /* Pulse Width */
		gFsInfo_D.nPhase = gClkInfo_D.nDiv/2;                              /* Phase */
		gFsInfo_D.bExternalTrigger = true;                        /* External Trigger */
		gFsInfo_D.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */

		adi_pcg_Init(ADI_PCG_DEV_D,&gClkInfo_D,&gFsInfo_D);
	}
	Clock_Div_Value= 128*Freq_Table[sample_fs_micro]/Freq_Table[Output_SampleRate];
}
#endif /* eARC_ENABLE */

#ifdef I2S_TDM_MODE_ENABLE
void TX_Buf_Ptr_Allocation()
{
	#ifdef BEO_Framework
	if((I2S_TDM_MODE == I2S_MODE) || (I2S_TDM_MODE == ASRC_TDM_MODE))
	{
		Frmwk.Tx.dac_buf_LCRSw0_ptr 			  = TX_SP2A_BUFFER_LCRSW0;
		Frmwk.Tx.dac_buf_LCRSw1_ptr				  = TX_SP2A_BUFFER_LCRSW1;
		Frmwk.Tx.dac_buf_LsLsrRsRsr0_ptr		  = TX_SP2B_BUFFER_LsLsrRsRsr0;
		Frmwk.Tx.dac_buf_LsLsrRsRsr1_ptr		  = TX_SP2B_BUFFER_LsLsrRsRsr1;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set0_ptr = TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set1_ptr = TX_SP3A_BUFFER_Addch1ch3ch2ch4_set1;
		Frmwk.Tx.dac_buf_addch5ch7ch6ch8_set0_ptr = TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0;
		Frmwk.Tx.dac_buf_addch5ch7ch6ch8_set1_ptr = TX_SP3B_BUFFER_Addch5ch7ch6ch8_set1;
	}
	#else
	if((I2S_TDM_MODE == I2S_MODE) || (I2S_TDM_MODE == ASRC_MODE)||(I2S_TDM_MODE == ASRC_TDM_MODE))
	{
		Frmwk.Tx.dac_buf_LCRSw0_ptr 			  		= TX_SP4A_BUFFER_LCRSW0;
		Frmwk.Tx.dac_buf_LCRSw1_ptr				  		= TX_SP4A_BUFFER_LCRSW1;
		Frmwk.Tx.dac_buf_LsLsrRsRsr0_ptr		  		= TX_SP4B_BUFFER_LsLsrRsRsr0;
		Frmwk.Tx.dac_buf_LsLsrRsRsr1_ptr		  		= TX_SP4B_BUFFER_LsLsrRsRsr1;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set0_ptr 		= TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set1_ptr 		= TX_SP3A_BUFFER_Addch1ch3ch2ch4_set1;
		Frmwk.Tx.dac_buf_addch5ch7ch6ch8_set0_ptr 		= TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0;
		Frmwk.Tx.dac_buf_addch5ch7ch6ch8_set1_ptr 		= TX_SP3B_BUFFER_Addch5ch7ch6ch8_set1;
		if(I2S_TDM_MODE == I2S_MODE)
		{
		Frmwk.Tx.dac_buf_addch9ch11ch10ch12_set0_ptr 	= TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0;
		Frmwk.Tx.dac_buf_addch9ch11ch10ch12_set1_ptr	= TX_SP6A_BUFFER_Addch9ch11ch10ch12_set1;
		Frmwk.Tx.dac_buf_addch13ch15ch14ch16_set0_ptr 	= TX_SP2A_BUFFER_Addch13ch15ch14ch16_set0;
		Frmwk.Tx.dac_buf_addch13ch15ch14ch16_set1_ptr	= TX_SP2A_BUFFER_Addch13ch15ch14ch16_set1;
		}
	}
		#endif /* BEO_Framework */
	else if(I2S_TDM_MODE == TDM_MODE)
	{
		Frmwk.Tx.dac_buf_LCRSw0_ptr 				= TX_SP4A_BUFFER_LCRSW0;
		Frmwk.Tx.dac_buf_LCRSw1_ptr					= TX_SP4B_BUFFER_LsLsrRsRsr0;

		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set0_ptr 	= TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0;
		Frmwk.Tx.dac_buf_addch1ch3ch2ch4_set1_ptr 	= TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0;

		Frmwk.Tx.dac_buf_addch9ch11ch10ch12_set0_ptr = TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0;
		Frmwk.Tx.dac_buf_addch9ch11ch10ch12_set1_ptr = TX_SP2A_BUFFER_Addch13ch15ch14ch16_set0;

		TX_SP4A_BUFFER_LCRSW0_BUF 					= &TX_SP4A_BUFFER_LCRSW0[0];
		TX_SP4A_BUFFER_LsLsrRsRsr0_BUF				= &TX_SP4B_BUFFER_LsLsrRsRsr0[0];
		TX_SP3A_BUFFER_Addch1ch3Addch2ch4_set0_BUF	= &TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0[0];
		TX_SP3A_BUFFER_Addch5ch7Addch6ch8_set0_BUF 	= &TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0[0];
		TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0_BUF	= &TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0[0];
		TX_SP6A_BUFFER_Addch13ch15ch14ch16_set0_BUF	= &TX_SP2A_BUFFER_Addch13ch15ch14ch16_set0[0];
	}
}
#endif 
