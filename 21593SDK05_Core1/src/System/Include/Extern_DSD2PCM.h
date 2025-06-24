/***************************************************************************
*
*  (C)Copyright Analog Devices Inc., India.
*  All rights reserved. Reproduction in whole or part is prohibited without 
*  the written permission of the copyright owner.
*
*  Project          :  	Audio_RAMFramework
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Extern.h
*  Description      :   Extern variables & modules for framework & ISR can be included here
******************************************************************************/

#ifndef EXTERN_H
#define EXTERN_H

/*****************************************************************************
	Framework Modules
*****************************************************************************/	
.extern FLAG_TOGGLE_ROUTINE;
.extern	saveforCEnv;
.extern	unsaveforCEnv;
.extern	saveforCEnvNoMode1;
.extern	unsaveforCEnvNoMode1;
.extern saveforCEnv_lib;
.extern unsaveforCEnv_lib;
.extern SerialPortInitTx;
.extern LoadCPRegistersTx;
.extern serialflashAddrRoutine;
.extern Tag_Location32;
.extern ReadHeader;
.extern DirectReadRoutine;
.extern SPIConfigure;
.extern _AddCh_Routing;
.extern _CopySamplesFrmIntToExtPreDac;
.extern _CopySamplesFrmIntToExtAddPreDac;
.extern SerialPortInit;
.extern Save_AllRegisters;
.extern Unsave_AllRegisters;

.extern _Center_flag;
.extern Center_flag_ddp_dmx.;
.extern Center_downmix_ddp.;
.extern Cs_downmix_ddp.;
.extern _save_mode;
.extern Center_Downmix_Flag.;
.extern TrueHD_Downmix_Norm.;
//MCPCM downmix
.extern MCPCMDownmixing;
.extern MCPCMOutputChLayout;
.extern PrevMCPCMInputChConfig;
.extern MCPCMInputChConfig;
.extern PrevMCPCMOutputChLayout;
.extern MCPCMNormValue;
.extern MCPCMDownmixCoeffInit;
.extern InitMCPCMDownmixDone;
.extern _MCPCMDownmixingProcess;


/*****************************************************************************
	ISR Modules
*****************************************************************************/	
.extern save_lbrm_reg_tx;
.extern unsave_lbrm_reg_tx;
.extern Check_DAI_Finished_asm;
.extern ExitSPIReceiveInterrupt;
.extern save_lbrm_reg_spi;
.extern unsave_lbrm_reg_spi;
.extern SPIReceive;
.extern SetSync_Rx;
.extern _receiver2;
.extern transmitter;
.extern save_lbrm_reg_rx;
.extern unsave_lbrm_reg_rx;
.extern _receiver1;
.extern _Background_overlay_ISR;
.extern Check_Audio_Mute;
.extern MakeFlag3PortHigh;
.extern DSD2PCM_Receiver;
/***************************************************************************************************/
.extern seginitbuf;
.extern _Heap_Segment_Ptr;
.extern unformatdtsblockcountROM;
.extern dtshd8kblockcountmax_ROM;
.extern dtshd4kblockcountmax_ROM;

/************************************************************************/
.extern MCPCM_Downmixing;
.extern DSD2PCM_Downmixing;
.extern Silent_detection;
.extern OutputSampleRateLib;
.extern CustomerSpecificPostProcessing3;
.extern MusicEnhancerProcess;
.extern SW_Delay_Neo6;
.extern Frmwk_OutputSampleRateLib;
.extern Dummy_ALT_PP2Label;
.extern Post_PointerTemp;
.extern Post_pointerLib;
.extern Predac_heapLib;
.extern Predac_lengthLib;
.extern SampleBlockLib;
.extern BlockStart;
.extern _buf;
.extern _processBlock;
.extern BlockCounter;
.extern freq_table;
.extern DataOvly_asm;
.extern _Predac_heap;
.extern _Predac_length;
//MEnc

.extern _bypass;

.extern save_all_reg;

.extern Status14Val;
.extern _AddPredac_heap_Ext;
.extern _AddPredac_length_Ext;
.extern _AddPredac_lengthhalf_Ext;
.extern _AddPredac_wr_ptr_Ext;
.extern _AddPredac_rd_ptr_Ext;
.extern _BRStatus;

.extern _Predac_lengthhalf_Ext;
.extern _Predac_rd_ptr_Ext;
.extern _Predac_wr_ptr_Ext;
.extern _Run_AddrConversion;
.extern _error_frame;
.extern lfe_on;
.extern mAMODE;
.extern profile;
.extern save_all_reg;
.extern save_cregAAC;
.extern Check_EPDMA;
.extern Check_EPDMARx1;
.extern tempbuffer_to_copylfe;
.extern copylfe_to_tempbuffer;

.extern PlayForgnd_DSD2PCM;
.extern DSD2PCMDecoder;
.extern Deemphasis;
.extern copy_to_pre_dac_dummy;
.extern CopyPack2Work;
.extern Silent_detection;

.extern Init_struct;
.extern SystemInitialisation;
.extern SystemInitialisation_DSD2PCM;
.extern _Autodetect_MemoryAlloc;
.extern _DSD2PCM_MemoryAlloc;
.extern _DSD_Coeff;
.extern _DSD_Data;
.extern _DSD_Framework_and_Code;
.extern _DSD_KernelData_Data;

.extern UpdateWorkBuffer;
.extern Unsave_AllRegisters;
.extern Save_AllRegisters;
.extern Init_Var;

.extern DSD2PCM_IN_DSD_TYPE_Kernel.;
.extern LWorkBuf;
.extern OffsetCumBlockLength_Kernel.;
.extern predac_buf.;
.extern predacwrptr.;

.extern _Predac_lengthhalf_Ext;
.extern _Predac_rd_ptr_Ext;
.extern _Predac_wr_ptr_Ext;
.extern RWorkBuf;
.extern _WorkBuffer;
.extern DSD_Error_Kernel.;
.extern _channels;

.extern _Init_Kernel_Code;
.extern _ControlParams_Int;
.extern _Zeropad_tx_id_Tx;
.extern _Renderer_Info_Tx;
.extern _Tx_Samples_Tx;



/*****************************************************************************
	Downsampling
*****************************************************************************/

.extern DS_Sample_Count;
.extern _DnSamp192to48;
.extern _Do_Downsampling_process;
.extern kernel_downsampling_MCPCM;

.extern DOWNSAMP_96;
.extern DS_INFO;
.extern _Decimation_Ratio;
.extern _FIRSRC;
.extern DS_Input_Samples;
.extern SixteenCh_DS;

.extern previous_sampling_fs_micro;
.extern _Pack_buffer_Int;
.extern _Pack_buffer_ext;

.extern _mat_input_buffer;
.extern EP0InterruptOccured;

.extern _NumInputChannel;

.extern _bitratetab;

.extern _Au_Encoded_Stream;
.extern _offset_address;
.extern _Background_overlay;

.extern _Tx_Samples;
.extern _ControlParams_rd_ptr_Ext;
.extern _ControlParams_wr_ptr_Ext;
.extern _ControlParams_length_Ext;
.extern _ControlParams_heap_Ext;
.extern SampleCount;

.extern _DTSHD_Data3;
.extern _SixteenCh_DS;
.extern _DS_Start_Add_Heap_Ext;
.extern _DS_Data_Ovl_Done;

.extern _MEnc_Data1;
.extern _MEnc_DS_Data2;
.extern _Memory_Allocate_Code;

.extern _UpdateIOP;
.extern Init_struct_DSD;
.extern _Au_carrier_status;
.extern _Au_decodeConf_status;
.extern _Sample_Block;

.extern _DTSHD_RemappingON_Tx;
.extern _DTSHD_Hifront_Tx;
.extern _DTSHD_WideCh_Tx;
.extern _FourI2S_Routing_Rx;
.extern CustomAutoPCMZero.;
.extern CustomAutoInitPCMZero.;

.extern _MAT_Downsampling_Process;		
.extern _DS_BlockCount_CoreProcess;	
.extern _DS_Output_Samples;	
.extern _PCM128_SampleProcessing;		

.extern deemcoeffs;		//DEEMPHASIS
.extern samp_rate_tab;	//DEEMPHASIS
.extern samp_rate_adjust;

//.extern lp_cfs_1to2or2to1;	//DOWNSAMPLING
//.extern lp_cfs_1to4or4to1;	//DOWNSAMPLING
.extern	LFE_Present;

.extern Cust_PP_InputList;
.extern Status_Update_Dts;
.extern Input_Source;
#endif
