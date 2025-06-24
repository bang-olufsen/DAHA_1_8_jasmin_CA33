/*****************************************************************************
 *
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
 *
 *  Project          :  	21593SDK
 *  Organization     :  	Jasmin Infotech Private Limited,Chennai
 *  File Name        :		Main_Core1.c
 *  Description      :
 ******************************************************************************/
#pragma default_section(CODE,"Seg_Main_Code")
#pragma default_section(ALLDATA,"Seg_Main_Data")
#pragma default_section(SWITCH,"Seg_Main_Data")
#include "../Include/Main_Core1.h"
#include "../../../system/adi_initialize.h"
#include "../Include/Function_Prototype.h"
#include "../Include/Extern_Core1.h"

/**************************************************************************************************
 * If you want to use command program arguments, then place them in the following string. 
 *************************************************************************************************/

//char __argv_string[] = "";
int SPDIF_Enable_check = 1;

/**************************************************************************************************
 *			Global Functions Declaration Section
 *************************************************************************************************/
void ConfigSoftSwitches_EV_21593_SOM(void);
/*	main function Started Here	*/
void main()
{
	adi_initComponents();
#ifdef __ADSPSC598_FAMILY__
	*pREG_DDRPFB0_CTL0 &= ~BITM_DDRPFB_CTL0_PREFETCH_EN;

	*pREG_DDRPFB0_CTL1 &= ~BITM_DDRPFB_CTL1_SMART_FEATURE_EN;
#endif
#ifndef CORE1_TX
	adi_core_enable(ADI_CORE_SHARC1);
#endif
#ifdef MELODY9
	ConfigSoftSwitches_EV_21593_SOM();
#endif

	Enable_Cache();               // Enable Cache function
	System_Initialization();
#ifdef LED_TOGGLE
	Initialize_Led();
	Led1_Set_Routine();
#endif
	Set_Priority();
	/* Enabling the global gate bit */
	if (SPI_Device == 1)
	{
		adi_int_InstallHandler (INTR_SPI1_RXDMA, SPI0_RxCore_Handler, 0, true);
	}
	else
	{
		adi_int_InstallHandler (INTR_SPI0_RXDMA, SPI0_RxCore_Handler, 0, true);
	}

	adi_sport_GlobalEnable(true);
#ifdef DOLBY_OAR
	OARI_Init_Call();					// OAR init call for default speaker configuration to avoid MIPS overshoot
#endif
	asm("bit clr FLAGS 0x00000001;");
	SendInitializationDone();

	#ifdef BEO_Framework
	Stop_Command();

	Frmwk.Spi.PARAMETER_1 = 0x0030;
	Tx_Rx_Mode_Command();

	Frmwk.Spi.PARAMETER_1 = 0x0010;
	Frmwk.Spi.PARAMETER_2 = 0x0020; // 48k,DAP = off
	Frmwk.Spi.PARAMETER_3 = 0x0010;
	General_Decoding_Command();

	SportInitialize_Command();
	Resume_Command();
	Play_Command();

	#endif /* BEO_Framework */
	//Frmwk.autodetect_mode = FORCEPCM3;
	while(1)
	{
		Frmwk.Spi.STATUS_BYTE1 = (Frmwk.Spi.STATUS_BYTE1&0xFFE0)|(Frmwk.Autdet.MSGR_Save&0x1F);
		if((Frmwk.Spi.serialflash_flag==0)&&(Frmwk.Spi.serialflash_cmd_flag==0)
				&&(Frmwk.Spi.download_flag==0)
				&&(Frmwk.Spi.DirectWrite_flag==0)
				&&(Frmwk.Spi.DirectRead_flag==0))
		{
			Status_Comparison();	// Valid only when NO SPECIAL COMMANDS
		}
#ifdef SPDIF_MODULE
		Spdif_Lock_check_fn();
		if(SPDIF_Enable_check == 1)
		{
			Resume_Command();
			Play_Command();
			SPDIF_Enable_check = 0;
		}
//		spdif_status_valid_output_muted = 0;
#endif
#ifdef	SPI_COMMAND
		if((Frmwk.Spi.COMMAND_BYTE&0xFF)!=0)
		{
			//Decoder & Post processing commands from HOST will be processed here
			CommandProcessing();
			Frmwk.Spi.COMMAND_BYTE = 0;
			SendIRQInterrupt();
		}
#else
		Frmwk.run_flag=1;
#endif
#ifdef DSD2PCM_TESTING 
		Frmwk.run_flag        = 1;   //Modified for DSD2PCM
		Frmwk.autodetect_mode = 4;   //Modified for DSD2PCM
#endif 
		*datacanbeprocessnow = Frmwk.IOP.datacanbeprocessednow;
		if(Frmwk.run_flag)
		{
			PlayForgnd();
			if((Frmwk.ADI_DecoderError == NO_ERROR)||(Frmwk.ADI_DecoderError == DECODER_ERROR))
			{
				Status_Update();
				NOP1;
			}
		}
		if(Frmwk.stop_flag)
		{
			Frmwk.run_flag  = 0;
			Frmwk.stop_flag = 0;
		}
	}
}

/******************************************************************************
 *  Module Name        : CommandProcessing
 *  Functionality      : CommandProcessing Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 *****************************************************************************/
#ifdef COMMAND_PROCESSING
#pragma section("Seg_Cmd_Code")
void CommandProcessing(void)
{
	Frmwk.cmd_result = 0;					        // No Error
	if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x2)        // PLAY COMMAND
	{
		Play_Command();
	}
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x3)	// STOP COMMAND
	{
		Stop_Command();
	}
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x4)	// MUTE COMMAND
	{
		Mute_Command();
	}
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x5)	// RESUME COMMAND
	{
		Resume_Command();
	}
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x6)	// SPORTINIT COMMAND
	{
		SportInitialize_Command();
	}
#ifdef DSD2PCM_DEC
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x7)   // DSD2PCM COMMAND
	{
		DSD2PCM_LOAD_COMMAND();
	}
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x8)   // Load Autodetect Mode
	{
		Load_Autodetect_Mode();
	}
#endif

	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x0E)	// PCM Zero count
	{
		Special_Function_Command();
	}

	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x0F)	//Tx_Rx_Mode_Command
	{
		Tx_Rx_Mode_Command();
	}

	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x10)	// GENERAL COMMAND
	{
		General_Decoding_Command();
	}
#ifdef AAC_DEC
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x23)	// AAC OPTIONS COMMAND
	{	
		AACOptions_Command();
	}
#endif

#ifdef PCM_DEC
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x24)
	{
		PCMOPTIONS_COMMAND();
	}
#endif

#if defined (DOLBY_DDP) || defined (DOLBY_DD)
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x30)	// DOLBY DIGITAL PLUS COMMAND
	{
		DolbyDigitalPlus_Command();
	}
#endif

#ifdef DOLBY_THD
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x32)	// DOLBY TRUEHD COMMAND
	{
		DolbyTrueHD_Command();
	}
#endif
#ifdef DOLBY_MAT
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x33)	// DOLBY MATPCM COMMAND
	{
		MATPCM_Command();
	}
#endif

#ifdef MCPCM_DECODER
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x35)
	{
		MPCM_Input_command();
	}
#endif

#ifdef CHANNEL_REORDER
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x41) // CHANREORDER COMMAND
	{
		ChannelReorder_command();
	}
#endif
#if defined (DOLBY_OAR) || defined (DOLBY_DAP)
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x42)
	{
		DAP_OARI_Command();
	}
#endif
#ifdef MPEGH_DECODER
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x46)//for mpegh command line process
	{
		MPEGH_OPTIONS_COMMAND();
	}
#endif
#ifdef CUSTOMER_PP
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) == 0x51)	// CUSTOMER EXAMPLE COMMAND
	{
		CUSTOMER_PP_COMMAND();
	}
#endif
#ifndef CORE1_TX
	else if((Frmwk.Spi.COMMAND_BYTE&0xFF) > 0x60)	// Core2  Command Processing
	{
		CommandProcessing_Core2();
	}
#endif
}
#endif /*	End of #ifdef COMMAND_PROCESSING	*/
/******************************************************************************
 *  Module Name        : Play_Command
 *  Functionality      : Play_Command Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 *****************************************************************************/
#pragma section("Seg_Cmd_Code")
void Play_Command(void)
{
	if(Frmwk.run_flag==0)
	{
		Frmwk.Autdet.HeaderPlaceWritten = 0;
		Frmwk.run_flag  = 1;
		Frmwk.stop_flag = 0;
		Init_Var();
		Frmwk.Spi.STATUS_BYTE1 &= 0x7FFF;		// STATUS INVALID
	}
	*run_flag = Frmwk.run_flag;
}
/******************************************************************************
 *  Module Name        : Stop_Command
 *  Functionality      : Stop_Command Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 *****************************************************************************/
#pragma section("Seg_Cmd_Code")
void Stop_Command(void)
{
	Frmwk.stop_flag = 1;
	Frmwk.run_flag  = 0;
	Frmwk.Spi.STATUS_BYTE1 &= 0x7FFF;			// STATUS INVALID
	*run_flag = Frmwk.run_flag;
}

/******************************************************************************
 *  Module Name        : MUTE_COMMAND
 *  Functionality      : Mute command processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void Mute_Command(void)
{
	Frmwk.Mute_flag_from_HOST = 1;
}

/******************************************************************************
 *  Module Name        : RESUME_COMMAND
 *  Functionality      : Resume command processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void Resume_Command(void)
{
	Frmwk.Mute_flag_from_HOST = 0;
#ifdef SPDIF_MODULE
	if(SPDIF_Enable == 1)
	{
		spdif_status_valid_output_muted = 0;
	}
#endif
}

/******************************************************************************
 *  Module Name        : General_Decoding_Command
 *  Functionality      : General Decoding Command processing(autodetect_mode,
 *  					 sampling_fs_micro,DRC cut and boost)
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void Special_Function_Command(void)
{
	Frmwk.cmd_temp_read    	= (Frmwk.Spi.PARAMETER_1)&0x7F;
	PcmZeroCountMax = (Frmwk.cmd_temp_read+1)*24000;

	Frmwk.cmd_temp_read = (Frmwk.Spi.PARAMETER_1 >> 13) & 0x3;

	if(Frmwk.cmd_temp_read == 2)
	{
		Custom_Clock_Ratio = 256;
	}
	else
	{
		Custom_Clock_Ratio = 128;
	}

	Custom_MCLK_Mode_cmd = (Frmwk.Spi.PARAMETER_1 >> 12) & 0x1;

#ifdef TMU
	TMU_Enable   = (Frmwk.Spi.PARAMETER_1>>7)&0x1;
#endif

}

#pragma section("Seg_Cmd_Code")
void Tx_Rx_Mode_Command(void)
{
#ifdef eARC_ENABLE
	eARC_Mode    	= (Frmwk.Spi.PARAMETER_1 & 0x1);

	Frmwk.cmd_temp_read = (Frmwk.Spi.PARAMETER_1 >> 1) & 0x3;

	if(Frmwk.cmd_temp_read == 2)
	{
		eARC_Clock_Ratio = 256;
	}
	else if(Frmwk.cmd_temp_read == 3)
	{
		eARC_Clock_Ratio = 512;
	}
	else
	{
		eARC_Clock_Ratio = 128;
	}
#endif
#ifdef I2S_TDM_MODE_ENABLE
	I2S_TDM_MODE = (Frmwk.Spi.PARAMETER_1 >>4) & 0x3;
#ifdef ASRC_ENABLE
	if((I2S_TDM_MODE == ASRC_MODE)||(I2S_TDM_MODE == ASRC_TDM_MODE))
	{
		ASRC_Samplerate = (Frmwk.Spi.PARAMETER_1 >> 6) & 0x3;

		if(ASRC_Samplerate == 0)
		{
			FS_Div_Value = Mclk_48Khz;
		}
		else if(ASRC_Samplerate == 1)
		{
			FS_Div_Value = Mclk_96Khz;
		}
		else if(ASRC_Samplerate == 2)
		{
			FS_Div_Value = Mclk_192Khz;
		}
		else
		{
			FS_Div_Value = Mclk_48Khz;
		}
	}

	else
	{
		ASRC_Samplerate = 0;
		FS_Div_Value = Mclk_48Khz;
	}
#endif
	if(prev_I2S_TDM_Mode != I2S_TDM_MODE)
	{
		SPORT_Recongifuration();
		//prev_I2S_TDM_Mode = I2S_TDM_MODE;
	}
#endif

}
/******************************************************************************
 *  Module Name        : General_Decoding_Command
 *  Functionality      : General Decoding Command processing(autodetect_mode,
 *  					 sampling_fs_micro,DRC cut and boost)
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void General_Decoding_Command(void)
{
	int InAutobuf_temp_ptr;
	Frmwk.autodetect_mode = (Frmwk.Spi.PARAMETER_1>>8)&0xF;


	Frmwk.LPCM_delay_index      = (Frmwk.Spi.PARAMETER_1>>2)&0xF;
	Frmwk.SampleDropCountIndex  = (Frmwk.Spi.PARAMETER_1>>2)&0xF;

	if(Frmwk.SampleDropCountIndex==1)
	{
		Frmwk.SampleDropCount = 2048;
	}
	else if(Frmwk.SampleDropCountIndex==2)
	{
		Frmwk.SampleDropCount = 4096;
	}
	else if(Frmwk.SampleDropCountIndex==3)
	{
		Frmwk.SampleDropCount = 12288;
	}
	else if((Frmwk.SampleDropCountIndex==4) || (Frmwk.SampleDropCountIndex==0) || (Frmwk.SampleDropCountIndex>4))
	{
		Frmwk.SampleDropCount = 16384;
	}

	Frmwk.cmd_temp_read			= (Frmwk.Spi.PARAMETER_2>>4)&0xF;
	//values 3, 7 & greater than 10 of bit 4 - 7 is set as reserved
	if((Frmwk.cmd_temp_read == 3)||(Frmwk.cmd_temp_read == 7)||(Frmwk.cmd_temp_read>10))
	{
		Frmwk.cmd_temp_read=2;
	}
	Frmwk.sampling_fs_micro				= Frmwk.cmd_temp_read;
#ifdef SPDIF_MODULE
	SPDIF_Enable = (Frmwk.Spi.PARAMETER_3>>4)&0x00000001;

	if(SPDIF_Enable == 1)
	{
		Spdif_parameter1 		= Frmwk.Spi.PARAMETER_1;
		Spdif_parameter2 		= Frmwk.Spi.PARAMETER_2;
		Spdif_parameter3 		= Frmwk.Spi.PARAMETER_3;
		Frmwk.sampling_fs_micro = Spdif_Input_fs_micro;
	}
#endif

	if(Frmwk.prev_sampling_fs_micro != Frmwk.sampling_fs_micro)
	{
		Init_Var_Fs();
		Frmwk.prev_sampling_fs_micro = Frmwk.sampling_fs_micro;
	}
	Frmwk.Post_decoding_option_command = (Frmwk.Spi.PARAMETER_2)&0x3;
#ifdef CUSTOMIZATION
	if(Frmwk.SampleDropCountIndex==2)
		Frmwk.Autdet.MaybePcm_count = 2048;
	else if(Frmwk.SampleDropCountIndex==3)
		Frmwk.Autdet.MaybePcm_count = 4096;
	else if(Frmwk.SampleDropCountIndex==4)
		Frmwk.Autdet.MaybePcm_count = 8192;
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
		Frmwk.AACDecoderEnable = 0;
#endif
#ifdef MPEGH_DECODER
		Frmwk.MPEGH_DecoderEnable = 0;
#endif
		break;

	case FORCEPCM2:
		Frmwk.Misc.Control.ForcePcm = 1;
		Frmwk.LPCMDelaySize_host = 0;
		Frmwk.PCMEnable = 1;
		Frmwk.MCLPCMEnable = 0;
		Frmwk.ADCEnable = 0;
		Frmwk.Autdet.autodetect3 = 0;
#ifdef AAC_DEC
		Frmwk.AACDecoderEnable		= 0;
#endif
		Frmwk.LBRDecoderEnable		= 0;
		Frmwk.DTSXDecoderEnable	    = 0;
#if defined (DOLBY_DDP) || defined (DOLBY_DD)		
		Frmwk.DOLBYDecoderEnable	= 0;
		Frmwk.DDPLUSDecoderEnable	= 0;
#endif		
#if defined (DOLBY_THD) || defined (DOLBY_MAT)
		Frmwk.TRUEHDDecoderEnable	= 0;
#endif		
#ifdef MPEGH_DECODER
		Frmwk.MPEGH_DecoderEnable   = 0;
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
		Frmwk.Rx.INPUTsamples_ptr =  (int*)InAutobuf_temp_ptr;
		// Frmwk.Rx.INPUTsamples_ptr = InAutobuf;
		Frmwk.Autdet.InAutbuf_ptr 	= Frmwk.Rx.INPUTsamples_ptr + (Frmwk.Misc.Control.InAutobufsizeby2*4);	
#ifdef AAC_DEC
		Frmwk.AACDecoderEnable      = 0;
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
		Frmwk.PCMEnable = 1;
		Frmwk.MCLPCMEnable = 0;
		Frmwk.ADCEnable = 1;
		Frmwk.Autdet.autodetect3 = 0;
		break;

#ifdef CUSTOMIZATION
	case CUSTOMAUTODETECT1:
		Frmwk.Misc.Control.ForcePcm = 0;
		Frmwk.LPCMDelaySize_host = 0;
		Frmwk.PCMEnable = 1;
		Frmwk.MCLPCMEnable = 0;
		Frmwk.ADCEnable = 0;
		Frmwk.Autdet.autodetect3 = 0;
		break;
#endif
	default:
		break;
	}

#ifdef DOWNSAMPLING
	Frmwk.DS_Mode					= (Frmwk.Spi.PARAMETER_3>>5)&0x3;

	down_samp_flag_cmd = 0;
	DnSamp192to48      = 0;
	down_samp_flag     = 0;
	DnSamp192to48_flag = 0;

#ifdef DOWNSAMPLING_DTSX
	Frmwk.DTSX.DTSX_DS_Enable = 0;
#endif

	if(Frmwk.DS_Mode==0x2)//Invalid command
	{
		Frmwk.DS_Mode = 0;
	}
	if(Frmwk.DS_Mode != Previous_DS_Mode)
	{
		Frmwk.init_ds_processing 	= 1;
		Frmwk.InitDoneForStreamType = INVALID;
		Frmwk.InitDoneForFS         = INVALID;
		Frmwk.MemoryAllotMCLPCM     = 0;
		Previous_DS_Mode            = Frmwk.DS_Mode;
	}

	if(Frmwk.DS_Mode == 0x1)// 1/2 Downsampling
	{
		DnSamp192to48 = 0;
		down_samp_flag_cmd = 1;

#ifdef DOWNSAMPLING_DTSX
		Frmwk.DTSX.DTSX_DS_Enable = 1;
#endif

	}
	else if(Frmwk.DS_Mode==0x3)// 1/4 Downsampling
	{
		DnSamp192to48 = 1;
		down_samp_flag_cmd = 1;
	}
#endif

}

#ifdef AAC_DEC
/******************************************************************************
 *  Module Name        : AACOptions_Command
 *  Functionality      : Updates the AAC parameters from the form the Host.
 *  Input Parameters   : Frmwk.Spi.PARAMETER
 *  Output Parameters  : DualMono_Repro_Mode, doARIBDownmix, AAC_Target_Loudness_Cmd, AAC_Output_channel_config_from_user
 ******************************************************************************/

#pragma section("seg_AAC_Command")
void AACOptions_Command (void)
{
	Frmwk.AAC.DualMono_Repro_Mode 		    		= (Frmwk.Spi.PARAMETER_1)&0x3;
	Frmwk.AAC.doARIBDownmix 						= (Frmwk.Spi.PARAMETER_1>>2)&0x1;
	Frmwk.AAC.AAC_Target_Loudness_Cmd   			= (Frmwk.Spi.PARAMETER_1>>9)&0x3;
	Frmwk.AAC.AAC_Output_channel_config_from_user	= (Frmwk.Spi.PARAMETER_2)&0xFFFB;
	AAC_Parameter_2 = Frmwk.Spi.PARAMETER_2;

}
#endif

/******************************************************************************
 *  Module Name        : SportInitialize_Command
 *  Functionality      : Sport initialization command processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void SportInitialize_Command(void)
{
	Frmwk.Spi.STATUS_BYTE1 &= 0x7FFF;
	Frmwk.Autdet.AlignFlg = 0;
	Frmwk.Autdet.MSGR_Save	= SYNCSIGUNKNOWN;
	Frmwk.Autdet.MSGR4 = 0xF;

	SPORT_Recongifuration();

	Init_Var();
	Init_Var_Fs();
}
/******************************************************************************
 *  Module Name        : SendIRQInterrupt
 *  Functionality      : SendIRQInterrupt Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
void SendIRQInterrupt(void)
{
	Frmwk.Spi.INTR_DESC_LOCN &=0xfff9;

	if((Frmwk.cmd_result==0)&&(Frmwk.Spi.special_cmd_result == 0))
	{
		Frmwk.Spi.INTR_DESC_LOCN |= SIGNATURE_COMMAND_SUCCESSFUL;
	}
	else if((Frmwk.cmd_result == 1)||(Frmwk.Spi.special_cmd_result == 1))
	{
		Frmwk.Spi.INTR_DESC_LOCN |= SIGNATURE_COMMAND_ERROR;
	}

	if(Frmwk.cmd_result!=2)
	{
		Flag_Toggle();
	}

	Frmwk.cmd_result = 0;
	Frmwk.Spi.special_cmd_result = 0;
}

/******************************************************************************
 *  Module Name        : PCMOPTIONS_COMMAND
 *  Functionality      : PCMOPTIONS_COMMAND Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void PCMOPTIONS_COMMAND(void)
{
#ifdef DE_EMPHASIS_PP
	Frmwk.pcm_deemphasis_enable     = (Frmwk.Spi.PARAMETER_1>>10)&0x1;			
#endif
#ifdef NOISEGEN
	Frmwk.NoiseGenEnable      		= (Frmwk.Spi.PARAMETER_1>>14)&0x1;
	Frmwk.NoiseGen.thx_boost		= (Frmwk.Spi.PARAMETER_1>>4)&0x1;

	Frmwk.cmd_temp_read             = (Frmwk.Spi.PARAMETER_2>>14)&0x3;

	if(Frmwk.cmd_temp_read == 3)
	{
		Frmwk.cmd_result = 1;
		return;
	}

	Frmwk.NoiseGen.noise_type = Frmwk.cmd_temp_read;

	Frmwk.NoiseGen.noise_chan_select_pattern = Frmwk.Spi.PARAMETER_2&0x3F; //L,R,Ls,Rs,C,Lfe
	Frmwk.NoiseGen.sb_noise_ocfg             = (Frmwk.Spi.PARAMETER_2>>6)&0x3; //SBL,SBR
	Frmwk.NoiseGen.Addch_noise_ocfg			 = (Frmwk.Spi.PARAMETER_2>>8)&0x3F; //LTF,RTF,LTR,RTR,  LRH, RRH

	Frmwk.NoiseGen.Addch_noise_ocfg_18ch    = (Frmwk.Spi.PARAMETER_3)&0xF; //LFH, RFH

	Frmwk.NoiseGen.Addch_noise_ocfg    =     (Frmwk.NoiseGen.Addch_noise_ocfg_18ch <<6) | Frmwk.NoiseGen.Addch_noise_ocfg;
	Frmwk.init_noise_gen = 1;
#endif

}
/******************************************************************************
 *  Module Name        : MPCM_Input_command
 *  Functionality      : MPCM_Input_command Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void MPCM_Input_command(void)
{
	Frmwk.lfepresent=(Frmwk.Spi.PARAMETER_1>> 3)&0x1;
	Frmwk.inputChannelConfig=(Frmwk.Spi.PARAMETER_1)&0x7;

	if(Frmwk.inputChannelConfig==0)
	{
		Frmwk.inputChannelConfig			 = 2;
	}
	else if(Frmwk.inputChannelConfig==1)
	{
		Frmwk.inputChannelConfig			 = 1;
	}
	else if(Frmwk.inputChannelConfig==2)
	{
		Frmwk.inputChannelConfig			 = 3;
	}
	else if(Frmwk.inputChannelConfig==3)
	{
		Frmwk.inputChannelConfig			 = 4;
	}
	else if(Frmwk.inputChannelConfig==4)
	{
		Frmwk.inputChannelConfig			 = 5;
	}
	else if(Frmwk.inputChannelConfig==5)
	{
		Frmwk.inputChannelConfig			 = 6;
	}
	else if(Frmwk.inputChannelConfig==6)
	{
		Frmwk.inputChannelConfig			 = 7;
	}

}

/******************************************************************************
 *  Module Name        : CommandProcessing_Core2
 *  Functionality      : Core2 Command Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void CommandProcessing_Core2(void)
{
	volatile int *src_ptr;
	int *dst_ptr;
	dst_ptr = PARAMETER_1_C2;
	src_ptr = &(Frmwk.Spi.PARAMETER_1);

	for(int i=0;i<31;i++)
	{
		*dst_ptr++ = *src_ptr++;
	}
	*COMMAND_BYTE_C2 = Frmwk.Spi.COMMAND_BYTE;
#ifndef CORE1_TX
	Wait_Core1(core2_command_processing_status_done,0);
	*core2_command_processing_status_done = 0;
#endif

}

#ifdef CHANNEL_REORDER
/******************************************************************************
 *  Module Name        : ChannelReorder_command
 *  Functionality      : Channel reorder commands for the Assign Lines
 *  Input Parameters	  : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("seg_ChannelReOrder_Kernel_Code")
void ChannelReorder_command(void)
{
#ifdef DEFAULT_CH_CONFIG
	Command_Processing = 1;
#endif
	Frmwk.ChannelReorder_AssignLines	= (Frmwk.Spi.PARAMETER_1)&0xFFFF;		// Assign Lines (1,2,3,4) values bit[15:0]
	Frmwk.ChannelReorder_AssignLines   |= ((Frmwk.Spi.PARAMETER_2)&0xF) << 16;	// Assign Lines (5) values bit[3:0]

}
#endif
#ifdef MPEGH_DECODER
/******************************************************************************
 *  Module Name        : MPEGH_OPTIONS_COMMAND
 *  Functionality      : Updates the MPEGH parameters from the form the Host.
 *  Input Parameters   : Frmwk.Spi.PARAMETER
 *  Output Parameters  : Target_Loudness,Target_layout_Mask for MPEGH Decoder
 ******************************************************************************/
#pragma section("Seg_MPEGH_Kernel_Code")
void MPEGH_OPTIONS_COMMAND(void)
{
	Frmwk.MPEGH.Target_layout_Mask = (((Frmwk.Spi.PARAMETER_1>>0) & 0xFFFF) | (1<<2));  //LFE hard coded with incoming command
	Frmwk.MPEGH.Target_Loudness    = (Frmwk.Spi.PARAMETER_2>>0) & 0xF;
	Get_MPEGH_CICP_Target_Index();
	Frmwk.InitDoneForStreamType = 0;
}
#endif

/******************************************************************************
 *  Module Name        : DolbyDigitalPlus_Command
 *  Functionality      : This module is responsible for handling the dynamic parameters of DDP decoder
 *  					 It will verify that all required options are present and are valid

 ******************************************************************************/
#if defined (DOLBY_DDP)|| defined (DOLBY_DD)
#pragma section("Seg_DDP_Kernel_Code_L3")
void DolbyDigitalPlus_Command(void)
{

	Frmwk.DDPlus.dynscalehigh			= (Frmwk.Spi.PARAMETER_1>>8)&0xF;
	Frmwk.DDPlus.dynscalehigh			= Frmwk.DDPlus.dynscalehigh*10;
	Frmwk.DDPlus.dynscalelow			= (Frmwk.Spi.PARAMETER_1>>4)&0xF;
	Frmwk.DDPlus.dynscalelow			= Frmwk.DDPlus.dynscalelow *10;

	Frmwk.DDPlus.InitDecoder			= 0;
#ifdef DOLBY_CERTIFICATION
	Frmwk.DDPlus.outchanconfig		    = (Frmwk.Spi.PARAMETER_2)& 0x1F; 					 //Bit 0:4 DDPlus Output Channel Configuration - Applicable only for CIDK REALTIME
	Frmwk.DDPlus.DDP_Length             = (Frmwk.Spi.PARAMETER_1>>12)&0x3;      // DDP_Packlength_selection
	if(Frmwk.DDPlus.DDP_Length == 0)
	{
		Frmwk.DDPlus.Pack_length_DDP = 2048;
	}
	else if(Frmwk.DDPlus.DDP_Length == 1)
	{
		Frmwk.DDPlus.Pack_length_DDP = 3840;
	}
	else if(Frmwk.DDPlus.DDP_Length == 2)
	{
		Frmwk.DDPlus.Pack_length_DDP = 4096;
	}
	else if(Frmwk.DDPlus.DDP_Length == 3)
	{
		Frmwk.DDPlus.Pack_length_DDP = 6144;
	}
	else
	{
		Frmwk.DDPlus.Pack_length_DDP = 2048;
	}
#endif /* DOLBY_CERTIFICATION */

}
#endif

/******************************************************************************
 *  Module Name        : TrueHDandMLP_Command
 *  Functionality      : This module is responsible for handling the dynamic parameters of TrueHD decoder
 *  					 It will verify that all required options are present and are valid
 *
 ******************************************************************************/
#ifdef DOLBY_THD
#pragma section("Seg_THD_Kernel_Code_L3")
void DolbyTrueHD_Command(void)
{
	
	Frmwk.TRUEHD.Loudness_enable		= (Frmwk.Spi.PARAMETER_1>>13)&0x1;  				// Bit 13 Loudness management

	if((((Frmwk.Spi.PARAMETER_1>>9)&0xF) > 0xA) || (((Frmwk.Spi.PARAMETER_1>>5)&0xF) > 0xA)) // Bit 5:8 LDRC ,9:12 HDRC
	{
		Frmwk.cmd_result = 1;
		return;
	}
	Frmwk.TRUEHD.kerneldrc_boost		= (Frmwk.Spi.PARAMETER_1>>9)&0xF;
	Frmwk.TRUEHD.kerneldrc_boost		= Frmwk.TRUEHD.kerneldrc_boost*10;
	Frmwk.TRUEHD.kerneldrc_cut			= (Frmwk.Spi.PARAMETER_1>>5)&0xF;
	Frmwk.TRUEHD.kerneldrc_cut			= Frmwk.TRUEHD.kerneldrc_cut*10;

	Frmwk.cmd_temp_read					= Frmwk.Spi.PARAMETER_1 &0x7;      					 //Bit 0:2 Kernel DRC Enable
#ifdef CIDK_Enable_Dec
	if(Frmwk.cmd_temp_read > 3)
	{
		Frmwk.cmd_result = 1;
		return;
	}
#else
	if(Frmwk.cmd_temp_read > 3)
	{
		Frmwk.cmd_result = 1;
		return;
	}
#endif /* CIDK_Enable_Dec */
	Frmwk.TRUEHD.KERNEL_drc_enable 		= Frmwk.cmd_temp_read;
#ifdef DOLBY_CERTIFICATION
	Frmwk.TRUEHD.Output_Ch_Config   	= (Frmwk.Spi.PARAMETER_2)&0x001F;					// Bit 0:4 TrueHD Output Channel Configuration
#endif
	Frmwk.TRUEHD.TrueHDOption 			= 1;

}
#endif /* DOLBY_THD */
/******************************************************************************
 *  Module Name        : MATPCM_Command
 *  Functionality      : This module is responsible for handling the dynamic parameters of MAT decoder
 *  					 It will verify that all required options are present and are valid
 *
 ******************************************************************************/
#ifdef DOLBY_MAT
#pragma section("Seg_MAT_Kernel_Code_L3")
void MATPCM_Command(void)
{
	
	Frmwk.MAT.Loudness_Management		= (Frmwk.Spi.PARAMETER_1>>13)&0x1;  				 //bit13 Loudness management

	Frmwk.MAT.kerneldrc_cut				= (Frmwk.Spi.PARAMETER_1>>4)&0xF;
	Frmwk.MAT.kerneldrc_cut				= Frmwk.MAT.kerneldrc_cut*10;
	Frmwk.MAT.kerneldrc_boost			= (Frmwk.Spi.PARAMETER_1>>8)&0xF;
	Frmwk.MAT.kerneldrc_boost			= Frmwk.MAT.kerneldrc_boost*10;

	Frmwk.cmd_temp_read					= (Frmwk.Spi.PARAMETER_1>>1)&0x3; 					   // Bit 1:2 DRC mode
	if((Frmwk.cmd_temp_read != 0) && (Frmwk.cmd_temp_read != 2) && (Frmwk.cmd_temp_read != 3))
	{
		Frmwk.cmd_result = 1;
		return;
	}
	Frmwk.MAT.DRC_Mode					= Frmwk.cmd_temp_read;
	Frmwk.MAT.update_params				= 1;
}
#endif /* DOLBY_MAT */
/******************************************************************************
 *  Module Name        : DAP_OARI_Command
 *  Functionality      : This module is responsible for handling the dynamic parameters of DAP and OAR post decoder
 *  					 It will verify that all required options are present and are valid
 *
 ******************************************************************************/
#if defined (DOLBY_OAR) || defined (DOLBY_DAP)
#pragma section("Seg_DAP_Kernel_Code_L3")
void DAP_OARI_Command(void)
{
	if(((Frmwk.Spi.PARAMETER_1>>2)&0x1) || ((Frmwk.Spi.PARAMETER_1>>6)&0x1))
	{
		Frmwk.cmd_result = 1;
		return;
	}
	Frmwk.speakers_bitmask					= (Frmwk.Spi.PARAMETER_1)&0x1FBB;				/* Speaker output Configuration */
	Frmwk.LFE_Enable						= (Frmwk.Spi.PARAMETER_1>>15)&1;
	/*When tuning mode is enabled, speakers parameter is invalid*/
	/*If tuning tool configuration file is enabled,Xml speaker configuration & Host speaker configuration should be same*/
	Frmwk.speakers_bitmask					= Frmwk.speakers_bitmask | Frmwk.LFE_Enable<<2;	/* LFE bit masking */
	Frmwk.speakers_bitmask					= Frmwk.speakers_bitmask | ((Frmwk.Spi.PARAMETER_2 & 0x0079) << 16); /* Lrrs1,SH and Dolby enabled speaker masking  */
#ifdef EXT_DNMIX
	Cs_enable = ((Frmwk.Spi.PARAMETER_1)>>5)&0x1;
	if(Cs_enable)	//No Need of if condition
	{
		Frmwk.speakers_bitmask = Frmwk.speakers_bitmask | Cs_enable<<5;
	}
#endif
	/*Tuning mode can only be used for MAT input*/
	/*DAP Parameters-2*/
	Frmwk.tuning_mode_enable				= (Frmwk.Spi.PARAMETER_2>>7)&1;
	Frmwk.DAP_krnl.DAP_Tuning_ON_OFF		= (Frmwk.Spi.PARAMETER_2>>8)&1; 				/* To enable XML Tuning for DAP ,Applicable only for Realtime*/
	if(Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 1)
		Frmwk.DAP_krnl.DAP_Audio_Profile	= (Frmwk.Spi.PARAMETER_2>>9)&0xF;				/* Tuning tool configuration audio profile mode bit 12:9 */
	else
		Frmwk.DAP_krnl.DAP_Audio_Profile	= (Frmwk.Spi.PARAMETER_3>>6)&0x3;				/* DAP audio profile mode bit 7:6 */
	/*DAP Parameters-3*/
	Frmwk.Legacy_Mode_enable				= (Frmwk.Spi.PARAMETER_3>>12)&0x1;				/* Legacy mode */
	Frmwk.DAP_krnl.DAP_vlamp				= (Frmwk.Spi.PARAMETER_3>>11)&0x1;				/* DAP vlamp bit 11 */
	/*The height cue filter cannot be used with (Tuning Tool Xml) file*/
	Frmwk.DAP_krnl.DAP_height_filter		= (Frmwk.Spi.PARAMETER_3>>9)&0x1;        		/* DAP Height cue filter bit 9 */
	Frmwk.DAP_krnl.center_spread_enable		= (Frmwk.Spi.PARAMETER_3>>8)&0x1;         		/* DAP Center spread bit 8 */

	Frmwk.DAP_krnl.DAP_upmixer				= (Frmwk.Spi.PARAMETER_3>>5)&0x1;         		/* DAP Upmixer bit 5 */
	Frmwk.cmd_temp_read						= (Frmwk.Spi.PARAMETER_3>>3)&0x3;         		/* DAP virtual mode bit 4:3 */

#ifdef DOLBY_CERTIFICATION

	if( (Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 1) && (Frmwk.DAP_krnl.DAP_Tuning_file_ID == 2))
	{
		Frmwk.DAP_krnl.DAP_Tuning_3way = 1;
		Frmwk.DAP_krnl.DAP_Tuning_2way  = 0;
		ChanReorder_AssignLines_Harmony= 0xA41;
		Frmwk.DAP_krnl.DAP_Tuning_init=0;
	}
	else if( (Frmwk.DAP_krnl.DAP_Tuning_ON_OFF == 1) && (Frmwk.DAP_krnl.DAP_Tuning_file_ID == 1))
	{
		Frmwk.DAP_krnl.DAP_Tuning_3way = 0;
		Frmwk.DAP_krnl.DAP_Tuning_2way = 1;
		ChanReorder_AssignLines_Harmony= 0x6;
		Frmwk.DAP_krnl.DAP_Tuning_init=0;
	}
	else
	{
		Frmwk.DAP_krnl.DAP_Tuning_2way = 0;
		Frmwk.DAP_krnl.DAP_Tuning_3way = 0;
		Frmwk.DAP_krnl.DAP_Tuning_init=0;
	}
#endif

	if(Frmwk.cmd_temp_read == 3)
	{
		Frmwk.cmd_result = 1;
		return;
	}
	Frmwk.DAP_krnl.DAP_virtuali				   = Frmwk.cmd_temp_read;         					/* DAP virtual mode bit 4:3 */

	Frmwk.cmd_temp_read						   = (Frmwk.Spi.PARAMETER_4>>11)&0x1F;				/* Height angle */
	if(Frmwk.cmd_temp_read > 30)
	{
		Frmwk.cmd_result = 1;
		return;
	}
	Frmwk.DAP_krnl.virtualizer_height_angle	   = Frmwk.cmd_temp_read;				/* DAP Surround Virtualizer-height angle bit 0 */
	Frmwk.cmd_temp_read					       = (Frmwk.Spi.PARAMETER_4>>6)&0x1F;
	if(Frmwk.cmd_temp_read > 30)
	{
		Frmwk.cmd_result = 1;
		return;
	}
	Frmwk.DAP_krnl.virtualizer_surround_angle = Frmwk.cmd_temp_read;				/* DAP Surround Virtualizer-surround angle bit 0 */
	Frmwk.cmd_temp_read						  = (Frmwk.Spi.PARAMETER_4>>1)&0x1F;
	if(Frmwk.cmd_temp_read > 30)
	{
		Frmwk.cmd_result = 1;
		return;
	}
	Frmwk.DAP_krnl.virtualizer_front_angle	 = Frmwk.cmd_temp_read;				/* DAP Surround Virtualizer-front angle bit 0 */

	Frmwk.cmd_temp_read						 = (Frmwk.Spi.PARAMETER_5)&0x1F;    /* DAP Rear surround angle */
	if(Frmwk.cmd_temp_read > 30)
	{
		Frmwk.cmd_result = 1;
		return;
	}
	Frmwk.DAP_krnl.virtualizer_rear_surround_angle	= Frmwk.cmd_temp_read;
#ifdef DOLBY_DAP
	Frmwk.DAP_krnl.datmosmusicapp					= (Frmwk.Spi.PARAMETER_5 >>15)& 0x1;		   /* Enable/Disable Datmos music */

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_5 >> 5)&0x3FF)-(0x1E0);/* DAP Front gain */

	Frmwk.DAP_krnl.Frontgain						= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_6 )&0x3FF)-(0x1E0);    /* DAP Lfe gain */

	Frmwk.DAP_krnl.lfegain							= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_7 )&0x3FF)-(0x1E0);    /* DAP surround gain  */

	Frmwk.DAP_krnl.surrgain							= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_8 )&0x3FF)-(0x1E0);    /* DAP Height gain */

	Frmwk.DAP_krnl.heightgain						= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_9 )&0x3FF)-(0x1E0);    /* DAP Rear surround gain */

	Frmwk.DAP_krnl.rearsurrgain						= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_10 )&0x3FF)-(0x1E0);    /* DAP Rear height gain */

	Frmwk.DAP_krnl.rearheightgain					= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_11 )&0x3FF)-(0x1E0);    /* DAP Center gain */

	Frmwk.DAP_krnl.Centergain						= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_12 )&0xFFF)-(0x820);    /* DAP Post-gain */

	Frmwk.DAP_krnl.postgain							= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_13 )&0xFFF)-(0x820);    /* DAP  Pre-gain */

	Frmwk.DAP_krnl.pregain							= Frmwk.gain_temp;

	Frmwk.gain_temp						 			= ((Frmwk.Spi.PARAMETER_14 )&0xFFF)-(0x820);    /* DAP System gain */

	Frmwk.DAP_krnl.system_gain						= Frmwk.gain_temp;

	#endif /* DOLBY_DAP */
	Frmwk.DAP_krnl.DAP_Init_Done					= 0;

	Dolby_Command_handling();
#ifdef DOLBY_CERTIFICATION
	if(Frmwk.CIDK_Enable_PP == 1)
	{

		Frmwk.DAP_krnl.surround_boost							= (Frmwk.Spi.PARAMETER_16>>1)&0x3F;
		Frmwk.DAP_krnl.dialog_enhancer_enable					= (Frmwk.Spi.PARAMETER_16)&0x1;
		Frmwk.DAP_krnl.volume_leveler_enable					= (Frmwk.Spi.PARAMETER_15>>4)&0x1;
		Frmwk.DAP_krnl.ieq_enable								= (Frmwk.Spi.PARAMETER_15>>10)&0x1;
		Frmwk.DAP_krnl.ieq_amount								= (Frmwk.Spi.PARAMETER_15>>11)&0x1F;
		Frmwk.DAP_krnl.volume_leveler_amount					= (Frmwk.Spi.PARAMETER_15)&0xF;
		Frmwk.DAP_krnl.dialog_enhancer_amount					= (Frmwk.Spi.PARAMETER_16>>8)&0x1F;
		Frmwk.DAP_krnl.dialog_enhancer_ducking					= (Frmwk.Spi.PARAMETER_15>>5)&0x1F;

	}
	#endif /* DOLBY_CERTIFICATION */
}
#endif /* END of #if defined (DOLBY_OAR) || defined (DOLBY_DAP) */

#ifdef DSD2PCM_DEC
/******************************************************************************
 *  Module Name        : DSD2PCM_LOAD_COMMAND
 *  Functionality      :
 *  Input Parameters   :
 *  Output Parameters  : None
 *****************************************************************************/
#pragma section("Seg_Cmd_Code")
void DSD2PCM_LOAD_COMMAND()
{
	if(Frmwk.InitDoneForDSD2PCM == 0)
	{
		//while(Frmwk.IOP.DataValid==1);

		Init_struct_DSD();
		Kernal_Default_Init_DSD2PCM();

		Frmwk.DSD2PCMMode_Enable = 1;
		SPORT_Recongifuration();

		Frmwk.AutodetectMode_Enable = 0;
		Frmwk.InitDoneForDSD2PCM = 1;
		InitDoneForAutodetectMode = 0;
	}
}
#pragma section("Seg_Cmd_Code")
void Load_Autodetect_Mode()
{
	Frmwk.DSD2PCMMode_Enable    = 0;

	if(InitDoneForAutodetectMode == 0)
	{
		AllocateMemoryKernel();
		Free_AllotMemoryPackDac( Frmwk.pack_length_pcm, Frmwk.predac_length_pcm, 1);

#ifdef PCM_DEC
		Frmwk.LPCMDelaySize = Frmwk.LPCMDelaySize_host+(Frmwk.SampleBlock*2);	//(4096samples*2ch*32bit)
		Frmwk.PrevLPCMDelaySize_host = Frmwk.LPCMDelaySize_host;

		AllocateMemoryPCMDelay(Frmwk.LPCMDelaySize);
#endif

		SportInitialize_Command();

	}
	else
	{
		Init_Struct();
		SportInitialize_Command();
	}
	Frmwk.DSD2PCMMode_Enable    = 0;
	Frmwk.AutodetectMode_Enable = 1;
	Frmwk.InitDoneForDSD2PCM    = 0;
	InitDoneForAutodetectMode   = 1;
	Frmwk.InitDoneForStreamType = -1;
}
#endif
