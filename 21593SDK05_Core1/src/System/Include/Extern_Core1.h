/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Extern_Core1.h
*  Description      :   Extern variables & modules for framework & ISR can be included here
******************************************************************************/
#ifndef EXTERN_CORE1_H_
#define EXTERN_CORE1_H_

#include "commn.h"
extern int Center_Downmix_Flag;
extern int ext_dnmix_flag;
extern int AuroEngine_Enable_cmd;

extern int PP_flag;

extern int check;

extern int MSIZE;

extern int PSIZE;

extern int iEdge;
extern int gClock;

extern int lateFS;
extern int lowFS;
extern int dataIndFS;
extern int edgedetFS;
extern int FSR;

extern int LSBfirst;
extern int MSBfirst;
extern int dataType;
extern int packEnable;

extern int *predac_wr_ptr_c2;
extern int *predac_wr_ptr_c1;
extern int *predac_rd_ptr_c1;
extern int *Frmwk_SampleBlock_c1;
extern int *Frmwk_Outputsamplerate_c1;
extern int *Frmwk_nchannels_in_c1;
extern int *SampleBlock_Core2;
extern int *Frmwk_nchannels_in_c1_MPCM;
extern int Frame_DD_Error;
#pragma word_addressed
extern int InAutobuf[(((INAUTOBUFSIZEBY2 * 4)+INAUTOBUFSIZEBY2)/4)*4];
#pragma word_addressed
extern int Spi_size[SPI_BUFFER_SIZE*4];
extern int Prev_Clock_Div_Value;
extern int Clock_Div_Value;
extern int PCG_Sample_ratio;
extern int Freq_Table[];

#ifdef BEO_Framework
extern int FS_Div_Value;
extern int ASRC_Samplerate;
#endif /* BEO_Framework */
extern int EXT_Downmix_Flag;
#ifdef DEFAULT_CH_CONFIG
	extern int Command_Processing;
#endif
/************************************Downsampling*************************************/
#ifdef DOWNSAMPLING
extern int down_samp_flag;
extern int down_samp_flag_cmd;
extern int Do_Downsampling_process;
extern int DnSamp192to48;
extern int DnSamp192to48_flag;
extern int Previous_DS_Mode;
#endif
/**********************************************RECEIVER DMA BUFFER**********************************************/

extern int   RX_SP5A_BUFFER_SPDIF0[COUNT_2CH];

extern int   RX_SP5A_BUFFER_SPDIF1[COUNT_2CH];

extern int   RX_SP0A_BUFFER_LCRSW0[COUNT_4CH];

extern int   RX_SP0A_BUFFER_LCRSW1[COUNT_4CH];

extern int   RX_SP0B_BUFFER_LsLsrRsRsr0[COUNT_4CH];

extern int   RX_SP0B_BUFFER_LsLsrRsRsr1[COUNT_4CH];

#ifdef DSD2PCM_DEC 
extern int   RX_SP1A_BUFFER_DSD2PCM0[COUNT_4CH];

extern int   RX_SP1A_BUFFER_DSD2PCM1[COUNT_4CH];
#endif

extern int RX_Intermediate_BUFFER[COUNT_4CH*2];
/**********************************************TRANSMITTER DMA BUFFER**********************************************/
#ifdef BEO_Framework
extern int  TX_SP2A_BUFFER_LCRSW0[COUNT_4CH];

extern int  TX_SP2A_BUFFER_LCRSW1[COUNT_4CH];

extern int  TX_SP2B_BUFFER_LsLsrRsRsr0[COUNT_4CH];

extern int  TX_SP2B_BUFFER_LsLsrRsRsr1[COUNT_4CH];
#endif /* BEO_Framework */

extern int   TX_SP4A_BUFFER_LCRSW0[COUNT_4CH];

extern int   TX_SP4A_BUFFER_LCRSW1[COUNT_4CH];

extern int   TX_SP4B_BUFFER_LsLsrRsRsr0[COUNT_4CH];

extern int   TX_SP4B_BUFFER_LsLsrRsRsr1[COUNT_4CH];

extern int   TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0[COUNT_4CH];

extern int   TX_SP3A_BUFFER_Addch1ch3ch2ch4_set1[COUNT_4CH];

extern int   TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0[COUNT_4CH];

extern int   TX_SP3B_BUFFER_Addch5ch7ch6ch8_set1[COUNT_4CH];

extern int   TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0[COUNT_4CH];

extern int   TX_SP6A_BUFFER_Addch9ch11ch10ch12_set1[COUNT_4CH];

extern int   TX_SP2A_BUFFER_Addch13ch15ch14ch16_set0[COUNT_4CH];

extern int   TX_SP2A_BUFFER_Addch13ch15ch14ch16_set1[COUNT_4CH];

/*************************************************DECODER BUFFERS***********************************************/
extern int Pack_buffer_ext[PACK_BUFFER_MAX_SIZE];

//extern int Predac_buffer_Ext[(/*1280*NUMMAXCHAN*FIVE_HALF*/)];
extern int Predac_buffer_Ext[(SAMPLEBLOCK_TRUEHD_192K*NUMMAXCHAN*FOUR_HALF)];

extern int Predac_buffer_Int[NO_OF_SAMPLE_PROCESSING*PREDAC_INT_NUMCHAN];

extern int TX_EXT_DMA_BUFFER[NO_OF_TX_SAMPLE_COUNT*NUMMAXCHAN];

extern int Intr_count;
#ifdef DOLBY_LIB
extern int AddPredac_buffer_Int[];

#if defined (DOLBY_DDP) || defined (DOLBY_DD)
#ifdef DOLBY_L2_BUFFER_POINTER
extern char *libraray_l2_data;
#else
extern char libraray_l2_data[169392];
#endif/* DOLBY_L2_BUFFER_POINTER */
extern char joc_phse[29984];
extern char TRUEHD_predac_heap_buf[122880];
#endif/* DOLBY_DDP || DOLBY_DD  */
#endif

/*************************************************Customer_PP BUFFERS***********************************************/
extern int CustPPInputList[20];

#ifdef CUSTOMER_PP
	#ifdef FLOAT
		extern float CustomerPP_Buffer[];
	#else
		extern int CustomerPP_Buffer[];
	#endif
#endif

extern int Prev_OutputSampleRate;
extern int *datacanbeprocessnow;
extern int *core2_dcpn_done;
extern int	*Predac_length;
extern int	*Predac_length_half;
extern int	*predac_heap;
extern int	*predac_wr_ptr;
extern int	*Latency_predac_wr_ptr_c1;
extern int	*Init_Start_Command_c1;

extern int	*addpredac_heap;
extern int	*addpredac_wr_ptr;
extern int	*addpredac_rd_ptr;
extern int	*addpredac_length;
extern int Ext_Buffer_Data_Size;
extern int Ext_Buffer_Data[EXT_BUFFER_DATA_SIZE];
extern int Mclk_192Khz;
extern int Mclk_96Khz;
extern int Mclk_48Khz;

#ifdef CHANNEL_REORDER
	extern int Channel_PP_InputList[15];
	extern int ChanReorder_InBufPtr_LIB;
	extern int ChanReorder_OutBufPtr_LIB;
#endif
extern int PP_process_cnt;

#ifdef AAC_DEC
	extern int AAC_Output_channel_config_cicp;
	extern int AAC_ChannelReorder_Enable;
	extern int LshRsh_Ts_Flag_AAC;
    extern int AAC_Ch_Ts_flag;
    extern int AAC_Parameter_2;
#endif

#ifdef NOISEGEN
	extern int Noisegen_structure_Buffer[900]; 
#endif

#ifdef CUSTOMIZATION
	extern int CustomAutoPCMZero;
	extern int InitDoneForAutodetectMode;
#endif
extern int SrcBuf,DstBuf,BufSize,BufSize_remain;
extern int Input_Channel_Config_Mask;
extern int Mpegh_LFE_Present;
extern int L2_dm_start_Addr_MPEGH;
/************************************************* Auro Variables ***************************************************/
#ifdef AURO_3D
extern int Auro_TargetDevice;
extern int	Auro_Output_ch_count;
//extern int dap_cqmf_analysis_buf[7560];
extern int Noisegen_Temp_Buffer[4096];
extern int AuroEng_ListeningMode ;
extern int Au_LFE_Enable;
extern int AuMt_Preset;
extern int AuMt_Strength;
extern int Au_Input_Config;
extern int Au_Output_Config;
extern int AuroEngine_Enable;
extern int	Prev_Au_Output_Config;
extern int AURO_DS_Enabled;
extern int Auro_Encoded_Stream;
extern int Auro_carrier_status;
extern int Au_encodeConf_info;
extern int AU_Init_Done ;
extern int ChanReorder_inputConfig_Auro;
extern int Au_Outputbuffer[256*16];
extern int Auro_Ds_flag;
extern int InputSampleRate_Auro;
extern int OutputSampleRate_Auro;
extern int Prev_sample_rate;
extern int AURO_DS_CMD_FROM_HOST;
extern int Prev_Auro_Enable;
extern int AuroProcess;

extern int Auro_Processing_done;
extern int Au_Virtualization_Mode;
extern int Auro_Virtualization_Status;
extern int DTS_AuroEnable;
extern int DTSX_DecoderMask_Temp_Auro;
extern int DTSX_PrevStreamType;
extern int DTSx_DS_On_Cmd_Auro;
extern int DTSX_Commands_Temp_Auro[4];
extern int obj_mat_auro_flag;
extern int MAT_Detected;
extern int MAT_AuroUpmixer;
extern int Dolby_AuroEnable;
extern int graph_type_cmd;
extern int headroom_to_set_dB;
extern int Auro_Virt_Disable_Flag;
extern int Headroom_status;
extern int Au_Eng_Done;
extern int Auro_DS_Buffer[4096];
extern int *Auro_IP_Ptr ;
extern int Auro_Loop_Count;
extern int* Auro_OP_Ptr;
extern int index_count;
extern int AuroDTS_IP_Ptr;
extern int Auro_IP_Stride;
extern int Au_Room_Preset;
extern float Au_Headsize_range;
extern int Au_HRTF_Preset;
extern int Headphone_Quality;
extern int BM_Active;
extern int BM_Boost_input_LFE;
extern int BM_Low_Pass_Order;
extern int BM_High_Pass_Order;
extern int BM_Low_Pass_Cutoff_Freq;
extern int BM_High_Pass_Cutoff_Freq;
extern int SB_Side_Crossover_Freq_Valid;
extern int SB_Up_Crossover_Freq_Valid;
extern int SB_Side_Crossover_Freq_Value;
extern int SB_Up_Crossover_Freq_Value;
#endif
/************************************************* Dolby Variables ***************************************************/
#ifdef DOLBY_LIB
	extern int Predac_buffer_Int[];
	extern int L2_dm_start_Addr;
	extern int L1_Block0_Start_Addr;
	extern int L1_Block2_Start_Addr;
#if defined (DOLBY_OAR) || defined(DOLBY_DMX) || defined(DOLBY_DAP) 
		extern char lfract_OAR_output_buffer[];
#endif
#ifdef DOLBY_L2_BUFFER_POINTER
		extern int *Predac_buffer_Int_pp;
#else
extern int Predac_buffer_Int_pp[30720];
#endif /* DOLBY_L2_BUFFER_POINTER */
		extern int Predac_buffer_Int_pp_rdptr;
		extern int Predac_buffer_Int_pp_wrptr;
extern int DAP_Enable;
#ifdef DOLBY_OAR
		extern int Sync_detected;
	#endif /* DOLBY_OAR */
	#ifdef DOLBY_DAP
		extern int dap_rcl_struct_buf;
	#endif /* DOLBY_DAP */
#if defined (DOLBY_DMX) || defined(DOLBY_DAP)
		extern char *out_channel_map;
	#endif /* DOLBY_DMX */
#ifdef DOLBY_THD_DA
extern int THD_Info_Ret;
extern int THD_Obj_Flag;
#endif /* DOLBY_THD_DA */
#if defined (DOLBY_THD) || defined (DOLBY_MAT)
		extern int Do_Downsampling_process;
		extern int mode1_value;
		extern char metadata_payload_pstate[128][4096];
		extern unsigned char evo_payload[0x4000];
		extern int consumed_bytes;
		extern int endian_mips;
		extern int first_md_present;
	#endif /* DOLBY_MAT */
	extern unsigned long ar_speaker_mask;
	#if defined (DOLBY_MAT) || defined(DOLBY_DDP)
		extern int prev_stream_decoder_assign;
		extern int prev_stream_profile_mat;
	#endif /* (DOLBY_MAT) || (DOLBY_DDP) */
		extern int down_samp_flag;	//Need to conform
#endif /* DOLBY_LIB */

#ifdef DOLBY_THD_DS
	extern float lp_cfs128_1to4or4to1[129];
	extern float lp_cfs128_1to2or2to1[129];
	extern float *DS_Coef_192to48_Ptr_Add;
	extern float *DS_Coef_96to48_Ptr_Add;
	extern float *DS_Coef_192to96_Ptr_Add;
	/*extern int leftinput_delays_heap_buffer1;
	extern int rightinput_delays_heap_buffer1;
	extern int centerinput_delays_heap_buffer1;
	extern int  lfeinput_delays_heap_buffer1;
	extern int Ls_input_delays_heap_buffer1;
	extern int Rs_input_delays_heap_buffer1;
	extern int Lsr_input_delays_heap_buffer1;
	extern int Rsr_input_delays_heap_buffer1;
*/
	extern int leftinput_delays_heap_buffer;
	extern int rightinput_delays_heap_buffer;
	extern int centerinput_delays_heap_buffer;
	extern int  lfeinput_delays_heap_buffer;
	extern int Ls_input_delays_heap_buffer;
	extern int Rs_input_delays_heap_buffer;
	extern int Lsr_input_delays_heap_buffer;
	extern int Rsr_input_delays_heap_buffer;
#endif

#ifdef DOLBY_LIB
	extern unsigned long ar_speaker_mask;
#endif

#ifdef DTSX_DECODER
extern unsigned int		InputParameter[129*4];  //192
extern unsigned int		OutputParameter[226*4]; // 412
extern unsigned int		InputParameter[];
extern unsigned int		OutputParameter[];
extern int Freq_TableDtsx[];
extern int channel_config_table[];
extern int channel_assgn_Table[];
//extern int Pack_buffer_Int[];
//extern int Pack_buffer_Int_ptr;

extern int *IntAddrblock0_ptr;
extern int DTSX_SamplingFrequencyDecoded;

#ifdef DTS_VIRTUALX
extern int DTSX_Commands_Temp[];
//extern int DTSX_Command_Init;
#endif //DTS_VIRTUALX
 /***  DTSX_CHANREORDER ***/
#ifdef DTSX_CHANREORDER

	extern int DTSX_DecoderMask;
	extern int ChanReorder_inputConfig;
	extern int ChannelReorder_ASLReroute;
	extern int ChannelReorder_DTSX;
	extern int Freq_Table_kernel[];
	extern int Reorder_Samples;
	extern int Predac_int_ptr_dtsx;
	extern int Int_Block0_start_addr;
	extern int L2_Core1data_start_addr;
	extern int No_of_DTSX_predac_Channels;
#endif //DTSX_CHANREORDER

extern int shiftsamplescount;
#endif//DTSX_DECODER

#ifdef EXT_DNMIX
	extern int centre_downmix_check_flag;
#endif
#ifdef EXT_DNMIX_DDP
	extern int centre_downmix_check_flag_ddp;
	extern int LFE_disable_ddp_c2;
#endif


/*****************************************************************************
							VirtualX Variables
*****************************************************************************/
extern int No_of_output_channels;
extern int FFT_DM_start;
extern int FFT_PM_start;
#ifdef DTS_VIRTUALX
	/***  DTS VirtualX***/


	extern int DTSVX_Predac_Align[256*12];
	extern int ChannelReorder_DTSVX;
	extern unsigned int DecoderMask_DTSVX;

#endif

/*****************************************************************************
							DSD_PCM Variables
*****************************************************************************/
#ifdef DSD2PCM_DEC
extern int process_selection_DSD2PCM;
extern int InitDoneForAutodetectMode;
extern int LWorkBuf_Lib;
extern int RWorkBuf_Lib;
extern int WorkBuffer_Lib;
extern int OffsetCumBlockLength;
extern int OUT_DSD_GAIN;
extern int OUT_FORMAT;
extern int Up_sampling2_Lib;
extern int Reinitialise;
extern int DSD_Error;
extern int iDone;
extern int Predac_length_Ext;
extern int Prev_Upsampling;
extern int Up_sampling2;
extern int Prev_DSD2PCM_IN_DSD_TYPE_Kernel;
extern int DSD2PCM_IN_DSD_TYPE_Kernel;
extern int OffsetCumBlockLength_Kernel;
extern int LWorkBuf[];
extern int RWorkBuf[];
extern int WorkBuffer[];
extern int OUT_DSD_GAIN_Kernel;
extern int OUT_FORMAT_Kernel;
extern int Reinitialise_Kernel;
extern int Prev_DSD2PCM_OUT_FS;
extern int OUT_DSD_GAIN;
extern int OUT_FORMAT;
extern int DSD2PCM_OUT_FS;
extern int DSD2PCM_OUT_WORDWIDTH;
extern int DSD2PCM_OUT_DITHER;
extern int Reinitialise;
extern int OffsetCumBlockLength;
extern int DSD2PCM_IN_DSD_TYPE;
extern int DSD2PCM_OUT_FS_LIB;
extern int DSD_Error_Kernel;
extern int NumInputChannel;
extern int LFE_Present;
extern int FSTemp_spt;

extern int AddPredac_rd_ptr_Ext;
extern int AddPredac_wr_ptr_Ext;
extern int AddPredac_heap_Ext;
extern int Predac_rd_ptr_Ext;
extern int Predac_wr_ptr_Ext;
extern int Predac_heap_Ext;
extern int AddPredac_lengthperch_Ext;
extern int AddPredac_lengthhalf_Ext;
extern int AddPredac_length_Ext;
extern int Predac_lengthhalf_Ext;
extern int Predac_length_Ext;
extern int ControlParams_wr_ptr_Ext;
extern int ControlParams_rd_ptr_Ext;
extern int ControlParams_length_Ext;
extern int ControlParams_heap_Ext;
extern int CustomAutoPCMZero;
extern int *predac_wr_ptr_c1;
extern int *predac_rd_ptr_c1;
extern int DSD2PCM_Initialisation;
#endif
/*****************************************************************************
							Cross upmixer Variables
*****************************************************************************/
#ifdef DOLBY_NEURALX
extern int Dolby_NeuralX_Enable;
#endif

#ifdef DTSX_DAP
extern int DTS_DAPEnable;
extern int DTSX_DecoderMask_DAP;
extern int DTSX_Commands_Temp_DTSx_DAP[4];
extern int mono_chnl_Modifier;
#endif

#ifdef DOLBY_NEURALX
extern int Cross_Upmix_b2_Start;
#endif

extern int Prev_Channel_Assign;
extern int Prev_Dolby_NeuralX_Enable;

#ifdef I2S_TDM_MODE_ENABLE
extern int I2S_TDM_MODE;
#ifdef ASRC_ENABLE
extern int ASRC_Enable;
extern int ASRC_Samplerate;
extern int FS_Div_Value;
#endif
extern int DTSX_Max_User_Obj_Gain_SB14;
#ifdef SPDIF_MODULE
extern int SPDIF_Enable;
extern int Prev_SPDIF_Enable;
extern int Spdif_I2S_Switch_Occured;
extern int Spdif_prev_sampling_frequency;
extern int Spdif_Input_fs_micro;
extern int Prev_Spdif_Rx_Fs;
extern int Lock_interrupt_occured;
extern int Spdif_Rx_Fs;
extern int Spdif_Rx_Div;
extern int spdif_status_valid_output_muted;
extern int Spdif_unlock_interrupt_occured;
extern int Spdif_Input_locked_DAC_Mute;
extern bool SPDIF_Input_locked;
extern int Spdif_Command_arg;
extern int SPDIF_testcount;
extern int Spdif_parameter1;
extern int Spdif_parameter2;
extern int Spdif_parameter3;
extern int Spdif_fs_table[12];
#endif
#endif
#endif /* EXTERN_CORE1_H_ */

