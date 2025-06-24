/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	2159SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Def_Struct.h
*  Description      :   All the Struture Variables included
******************************************************************************/
#ifndef DEF_STRUCT_H_
#define DEF_STRUCT_H_

#include "Commn.h"

extern volatile struct kernel Frmwk;

struct Transmitter
{
	int	*dac_buf_LCRSw0_ptr;
	int	*dac_buf_LCRSw1_ptr;
	int	*dac_buf_LsLsrRsRsr0_ptr;
	int	*dac_buf_LsLsrRsRsr1_ptr;

	int	*dac_buf_addch1ch3ch2ch4_set0_ptr;
	int	*dac_buf_addch1ch3ch2ch4_set1_ptr;

	int	*dac_buf_addch5ch7ch6ch8_set0_ptr;
	int	*dac_buf_addch5ch7ch6ch8_set1_ptr;

	int	*dac_buf_addch9ch11ch10ch12_set0_ptr;
	int	*dac_buf_addch9ch11ch10ch12_set1_ptr;

	int	*dac_buf_addch13ch15ch14ch16_set0_ptr;
	int	*dac_buf_addch13ch15ch14ch16_set1_ptr;

	int buf_zero_data;
	int Latency_data;
	int TX_prev_i2;
	int Tx_LatencyFlag;
};

struct Receiver
{
	int	*DummyInAutbuf0m_ptr;
	int	*DummyInAutbuf1m_ptr;
	
	int *DummyInAutbuf0_ptr;
	int *DummyInAutbuf1_ptr;
	int	*DummyInAutbuf2_ptr;
	int	*DummyInAutbuf3_ptr;
	int	*DummyInAutbuf4_ptr;
	int	*DummyInAutbuf5_ptr;
	int	*DummyInAutbuf6_ptr;
	int	*DummyInAutbuf7_ptr;
	
	int *INPUTsamples_ptr;	
	int SingleI2S_prev_b2;
	int MCPCM_prev_b2;
	int prev_b2_adc;
#ifdef DSD2PCM_DEC
	int *DSD2PCMInAutbuf_LR0_ptr;
	int *DSD2PCMInAutbuf_LR1_ptr;
	int	*DSD2PCMInAutbuf_CSW0_ptr;
	int	*DSD2PCMInAutbuf_CSW1_ptr;
	int	*DSD2PCMInAutbuf_LsRs0_ptr;
	int	*DSD2PCMInAutbuf_LsRs1_ptr;
#endif	

};

struct Host
{
	/*************** Don't change the order*************/
	int COMMAND_BYTE;
	int PARAMETER_1;
	int PARAMETER_2;
	int PARAMETER_3;
	int PARAMETER_4;
	int PARAMETER_5;
	int PARAMETER_6;
	int PARAMETER_7;
	int PARAMETER_8;
	int PARAMETER_9;
	int PARAMETER_10;
	int PARAMETER_11;
	int PARAMETER_12;
	int PARAMETER_13;
	int PARAMETER_14;
	int PARAMETER_15;
	int PARAMETER_16;
	int PARAMETER_17;
	int PARAMETER_18;
	int PARAMETER_19;
	int PARAMETER_20;
	int PARAMETER_21;
	int PARAMETER_22;
	int PARAMETER_23;
	int PARAMETER_24;
	int PARAMETER_25;
	int PARAMETER_26;
	int PARAMETER_27;
	int PARAMETER_28;
	int PARAMETER_29;
	int PARAMETER_30;
	int PARAMETER_31;
	int STATUS_BYTE1;
	int STATUS_BYTE2;
	int STATUS_BYTE3;
	int STATUS_BYTE4;
	int STATUS_BYTE5;
	int STATUS_BYTE6;
	int STATUS_BYTE7;
	int STATUS_BYTE8;
	int STATUS_BYTE9;
	int STATUS_BYTE10;
	int STATUS_BYTE11;
	int STATUS_BYTE12;
	int STATUS_BYTE13;
	int STATUS_BYTE14;
	int STATUS_BYTE15;
	int STATUS_BYTE16;
	int RESERVED_BYTE1;
	int RESERVED_BYTE2;
	int RESERVED_BYTE3;
	int RESERVED_BYTE4;
	int RESERVED_BYTE5;
	int RESERVED_BYTE6;
	int RESERVED_BYTE7;
	int RESERVED_BYTE8;
	int RESERVED_BYTE9;
	int RESERVED_BYTE10;
	int RESERVED_BYTE11;
	int RESERVED_BYTE12;
	int RESERVED_BYTE13;
	int RESERVED_BYTE14;
	int RESERVED_BYTE15;
	int INTR_DESC_LOCN;

	/*************** END ****************************/
	
	int	PREV_STATUS_BYTE1;
	int PREV_STATUS_BYTE2;
	int PREV_STATUS_BYTE3;
	int PREV_STATUS_BYTE4;
	int PREV_STATUS_BYTE5;
	int PREV_STATUS_BYTE6;
	int PREV_STATUS_BYTE7;
	int PREV_STATUS_BYTE8;
	int PREV_STATUS_BYTE9;
	int PREV_STATUS_BYTE10;
	int PREV_STATUS_BYTE11;
	int PREV_STATUS_BYTE12;
	int PREV_STATUS_BYTE13;
	int PREV_STATUS_BYTE14;
	int PREV_STATUS_BYTE15;
	int PREV_STATUS_BYTE16;
	int PREV_RESERVED_BYTE1;
	int PREV_RESERVED_BYTE2;
	int PREV_RESERVED_BYTE3;
	int PREV_RESERVED_BYTE4;
	int PREV_RESERVED_BYTE5;
	int PREV_RESERVED_BYTE8;
	
	int STATUS_BYTE4T;
	int STATUS_BYTE5T;
	int STATUS_BYTE1T;
	int SPIDummyReadFlg;
	int DirectRead_flag;

	int header_count;
	int header_address;
	int destination_address;
	int destination_count;
	int temp_write_count;
	int temp_write_address;
	int DataRead;
	int special_cmd_result;
	int FlagToggle;
	int serialflash_flag;
	int download_status;
	int download_flag;
	int DirectWrite_flag;
	int DataWrite;
	int MicroWriteFlg;
	int loader_address;
	int serialflash_cmd_flag;
	int SpiTxBuffer;
	int COMMAND_SAVE_LOCATION;
	int SPIReceiveTempBufPtr;
	int SPIReceiveTempBuf;
	int SPIReceivebufsize;
	int spictl_8bit;		
	int spictl_16bit;	
	int spictl_32bit;	
	int spictl_32bit_read;
	int spival1;
	int spival2;
};

 struct Autodet  
{
	int	MSGR_Save;
	int	mpegstreamdetected;
	int PcmHeaderWritten;
	int autodetectcount;
	int autodetect3;
	int	*InAutbuf_ptr;	      // [INAUTOBUFSIZE*2];
	int	StreamDetectEnable;   // = 1;
	int	BreakCount;
	int PauseCount;	          // = 0
	int	LongPause;	          // = 0
	int	SmallPause ;         // = 0
	int	HIGHTOLOWBRDOLBY;    //	= 0
	int	AlignFlg;           // = 0
	int	HeaderAddress;
	int	HeaderAddWritten;   // = 0
	int HeaderPlaceWritten;	// = 0
	int	BurstSyncFound;    // = 0
	int	TransferNeeded;    // = 0
	int	No_Of_DWords_In_Present_Burst;	  // = 384
	
	int	FormatStream;
	int	PrevPc;
	
	int	CompareWord;
	int PcmZeroCount,PcmCount,MayBePcm;
	int	MayBeDTS,streamdetected,GoForchk;
	int	DTSSampleCount;
	int	StreamBlockOffset;
	int	StreamBlockCount,StreamBlockCountMax,PcmDetected;
	int	DTSDataLength,InitHeaderWritten;
	int	DataCanBeCopied;
	int	DTSDataLengthDouble;

	int PcValue;
	int PdValue;
	
	int dtssynclsb;
	int dtssyncmsb;
	int BurstSyncFoundHalf;
	int BurstSyncFoundHalfPCM;
	int BurstPcFound;
    int empty;
	int	flag_receiver2;
	int FrameSizeWMAPRO;
	int MSGR4;
	int MAYBEPCMCOUNT_var;
	int save_MAYBEPCM;
	int MaybePcm_count;
	int PrevFrameDTS;
	int PrevPcClearCount;
	int dolbyblockcountmax;
	int dtsblockcountmax0;
	int dtsblockcountmax1;
	int dtsblockcountmax2;
	int dtsblockcountmax3;
	int dtsblockcountmax4;
	int mpegl1blockcountmax;
	int mpegl2blockcountmax;
	int aacblockcountmax;
	int ddplusblockcountmax;
	int truehdblockcountmax;
	int dtshdblockcountmax;
	int dtshdhr2kblockcountmax;
	int dtshdhr1kblockcountmax;
	int dtshdhr512blockcountmax;
	int dtslbrblockcountmax;
	int wmablockcountmax0;
	int wmablockcountmax1;
	int wmablockcountmax2;
	int wmablockcountmax3;
	int blockcountmax;
	int unformatdtsblockcountmax0;
	int unformatdtsblockcountmax1;
	int unformatdtsblockcountmax2;
	int unformatdtsblockcountmax3;
	int unformatdtsblockcountmax4;
	int mpeghblockcountmax;

	int aacblockcountmax_hrls;
	int aacblockcountmax_qrls;
	int aacblockcountmax_drhs;

	int aacblockcountmax_latmloas0;
	int aacblockcountmax_latmloas1;
	int aacblockcountmax_latmloas2;
	int aacblockcountmax_latmloas3;
	int AAC_DataLen;

	int pc_value;
};

 struct Alglist
 {
 	int alg_input_list[102];
 	int alg_output_list[50];
 };
#ifdef DOLBY_DAP
struct DAP_Xml_Alglist
{
	int alg_xml_input_list[102];
	int alg_xml_output_list[5];
};
#endif

struct saveunsave
{
	int prolbufsave_tx[75];
	int prolbufsave_rx[45];
	int prolbufsave_spi[20];
	int SveforSetSync[6];
	int saveint[90];
	int savestack[70];
	int save_creg[20];
	int save_rxisr;

};


struct Control_tag
{
     int ForcePcm;
     int XPcm;
     int ReceiveReqFlag;
     int TransmitReqFlag;
     int OutBufferEmptyFlag;
     int InAutobufsizeby2;
     int OutAutobufsizeby2;
     int InAutobufsizeby2_DSD;
     int InAutobufsizeDSD2PCMby2;
     int Bufzerocount;
};

struct Packbuf
{
	int heap;
	int rd_ptr;
	int wr_ptr;
	int length;
	int lengthhalf;
};

struct Customer_post_processing
{
    int ChannelMask;
	int Volume;
	int Data_Format;
};

struct Predacbuf
{
	int heap;
	int rd_ptr;
	int wr_ptr;
	int wr_ptr_c2;
	int wr_ptr_dec;
	int wr_ptr_pp;
	int length;
	int lengthhalf;
	int rd_ptr_PP;
};

struct AddPreDacbuf
{
	int heap;
	int rd_ptr;
	int wr_ptr;
	int length;
	int lengthhalf;
	int lengthperch;
};


struct IOProcess
{
	
	struct Packbuf Pack;
	struct Predacbuf Predac;
	struct AddPreDacbuf AddPreDac;
	int	   NextDataValid;
	int    ThirdDataValid;
	int    ThirdDacCount;
	int    ThirdDacAddPreDac;
	int    ThirdDacAdd;
	int    DataValid;	
	int    NextDacCount;
	int	   DacCount;	 
	int    NextDacAdd;
	int    NextDacAddPreDac;
	int    CopyToDacCounter;
	int    datacanbeprocessednow;
	int    CopyToLatencyCnt;
	int    LatencyCnt;
	int    FIFO_LatencyCnt;
	int    LatencyFlag;
	int    LatencyDone;	
	int    LatencyComplete;
	int    FIFOLatencyFlag;
	int    FIFOLatencyCnt;
	int    FIFOTx_LatencyFlag;
	int    Next_DataValid_count;
};

#ifdef MPEGH_DECODER
struct MPEGH_Tag
{
int ChannelReorder_AssignLines;
int Target_layout_Mask;
int CICP_Target_Layout;
int Target_Loudness;
int FreeMemoryAllot;
};
#endif
struct Miscelleny
{
	struct saveunsave Protect;
	struct Alglist List;
	struct Control_tag Control;
	#ifdef DOLBY_DAP
		struct DAP_Xml_Alglist Xml_List;
	#endif
};

#ifdef DE_EMPHASIS_PP
struct Deemph_Tag
{
	int sample_blk;
	int samp_fs;
	int predac_length;
	int predac_heap;
	int predac_wr_ptr;
	int input_d1;
	int input_d2;
	int output_d1;
	int output_d2;
	int savestack_ptr;
};
#endif
#ifdef AAC_DEC
struct AAC_Tag
{
	int DualMono_Repro_Mode;
	int doARIBDownmix;
	int error_frame;
	int CRC_ERROR;
	int AAC_Dec_init;
	int AAC_Output_Channel_Config;
	int AAC_Target_Loudness;
	int Framecount_AAC;
	int Arib_Downmix;
	int BitRate;
	int BRStatus;
	int Avg_Frame_Length;
	int Profile;
	int ID;
	int Num_Channels;
	int MPEG4;
	int Stream_Transport_Type;
	int Prev_Stream_Transport_Type;
	int Predac_Length_AAC;
	int Predac_LengthHalf_AAC;
	int LC;
	int AAC_DataLen_ker;
	int FrameLength;
	int FrameSize_768_flag;
	int transportType;
	int Memory_Allot;
	int Prev_DataLen;
	int Prev_SampleRate;
	int Dual_Mono_On;
	int LFEPres;
	int LFEPresIn_Op;
    int Prev_framesize_AAC;
    int BR_Frame_Counter;
    int Frame_Length_Total;
    int New_Stream;
    int OLD_BITRATE;
    int AAC_Output_channel_config_from_user;
    int AAC_Target_Loudness_Cmd;
    int mAMODE;
    int Prev_Amode;
    int FreeMemoryAllot;
};
#endif

#ifdef NOISEGEN
struct noise_lib
{
	int *pink_outbuf_temp_heap;
	int *random_heap;
	int *pcmout_buf_heap;
	int *xvectL_heap;
	int *yvectL_heap;
	int *xvectC_heap;
	int *yvectC_heap;
	int *xvectR_heap;
	int *yvectR_heap;
	int *xvectLs_heap;
	int *yvectLs_heap;
	int *xvectRs_heap;
	int *yvectRs_heap;
	int *xvectSBL_heap;
	int *yvectSBL_heap;
	int *xvectSBR_heap;
	int *yvectSBR_heap;
	int *pink_o_ptr;
	int THXflag_pink;
	int pink_outbuf;
	int pk_blkcnt;
	int *pink_input_list_ptr;
	int pk_ocfg;
	int ooff_pnk_test;
	int omod_pnk_test;
	int optr_pnk_test;
	int saver14_pnk;	
	int saver15_pnk;
	int *filt_addr_bpf;
	int *filt_addr_lpf;
	int *filt_addr_hpf;
	int pk_blkcnt1;
	//int pk_gain;
	int pk_scl;
	int pink_samprate;
	int nshape;
	int chanstatpk[12];
	//int pocfg;
	int ochancfgpk;
	int boost;
	int thxboostallowed;
	int *random_ptr;
	int wht;
	int wht1;
	int y1,y2,y3,y4,y5;
	int y1d1;
	int y2d1;
	int y3d1;
	int y4d1;
	int y5d1;
	int pink;
	int pink1;
	int pink2;
	int pink_d1;
	int pink_d2;
	int pink1_d1;
	int pink1_d2;
	int pink1_in_d1;
	int pink1_in_d2;
	int pink2_d1;
	int pink2_d2;
	int *xptrL;
	int *yptrL;
	int *xptrC;
	int *yptrC;
	int *xptrR;
	int *yptrR;
	int *xptrLs;
	int *yptrLs;
	int *xptrRs;
	int *yptrRs;
	int *xvect1LFE;//[2];
	int *yvect1LFE;//[2];
	int *xvect2LFE;//[2];
	int *yvect2LFE;//[2];
	int *xyvectLFE_hpf;//[2];
	int shp_flt[5];//*shp_flt;//
	int *xptr1LFE;
	int *yptr1LFE;
	int *xptr2LFE;
	int *yptr2LFE;
	int *xptrSBL;
	int *yptrSBL;
	int *xptrSBR;
	int *yptrSBR;
    int  savestack_ptr;
    int Input_list_ptr; 
};

struct NoiesGen_Tag
{
   struct noise_lib *noise_heap;
   int * noise_dummyptr;
   int sb_noise_ocfg;
   int noise_ocfg;
   int thx_boost;
   int thx_noise; 
   int noise_chan_select_pattern;
   int noise_type;
   int Addch_noise_ocfg;
   int Addch_noise_ocfg_18ch;
   int *Noise_temp_ptr;
};
#endif
#if defined (DOLBY_THD) || defined (DOLBY_MAT)
struct TrueHD
{
    int  IEC_MAT_Buf_Rd_Ptr;
    int  IEC_MAT_Buf_Wr_Ptr;
    int  TRUEHD_sampling_frequency;
	int  savestack_ptr;
    int  Input_list_ptr;
    int  Output_list_ptr;
  	int FIFO_State;
  	int StreamState;
  	int Mat_Frame_Error;
   	int mlpStatus;
   	int TrueHD_MS_Offset;
   	int Fifo_Rd_ptr;
    int DECODERBLOCKSIZE;
    int MatState;
    int Stream_Locked;
    int MLPCOUNTER;
    int PeakT;

};
struct TrueHD_Tag
{
  struct TrueHD *LibTrueHDPtr;
  struct dthd_dec_state *pstate;
  	 
  int   kerneldrc_boost;
  int   kerneldrc_cut;
  int   Force_Decoding_Mode;
  int   Output_Ch_Config;
  int   KERNEL_drc_enable;
  int   Loudness_enable;
  int   LFE_enable;
  int   evo_sc_counter_initflag;
  int   Legacymode;
  int   Dialnormenable;
  int   Prev_Legacymode;

  int	analog_db_gain;
  int	NormalDrcPresent;
  int	Channel_assignment_type;
  int   TrueHD_Channel_Assignment;
  int   dthd_atmos_present;
  int   Special96k_ATMOS_Mode;
  int 	TrueHD_Decoder_CRCError;
  int   StreamState;
  int   Mat_Frame_Error;
  int   Stream_Locked;
  int   prev_sampling_frequency;
  int   decoded_sampling_frequency;

  int   IEC_MAT_Buf_heap;
  int   IEC_MAT_Buf_Wr_Ptr;
  int   IEC_MAT_Buf_Rd_Ptr;
  int   TRUEHD_predac_heap;
  int   TRUEHD_predac_Wr_Ptr;
  int   TRUEHD_predac_Rd_Ptr;
  int   TRUEHD_predac_length;
  int   DecoderBlocksize;
  int   Prev_Output_Ch_Config;
  int   Prev_Force_Decoding_Mode;

  int   Decoding_Mode;
  int   DialNorm_Stream;
  int   Decoder_Ch_Modifier;
  int   TrueHD_Decoder_Error;
  int   decoder_6_ch_assign;
  int   decoder_8_ch_assign;
  int   decoder_16_ch_assign;
  int   decoder_errorTRUEHD;
  int   PP_flag;
  int   fbafbbdetector;

  int   Sampling_Update;
  int   TrueHD_MS_Offset;
  int   Delay_TrueHd;
  int   True_HD_FIFO_Delay;
  int   True_HD_FIFO_Delay_Flag;
  int   DecodedAU_Cnt;
  int   TrueHD_DEC_AU_Cnt;
  int   Downmix_Norm;
  int   DRC_init_For;
  int   NeedMLPinitialise;

  int AuOut8channel;
  int decoder_ch_assign;
  int PPlatency;
  int Fifolatencyfactor;
  int connection_init_flag;
  int Au_Len;
  int IEC_MAT_BUF_FLAG;
  int MLP_INPUT_Buf_heap;
  int INPUT_Buf_Rd_Ptr;
  int decinstancemem;

  int presentationmem;
  int outputstatemem;
  int drcmem;
  int dvlimmem;
  int delaybufmem;
  int scratchbufmem;
  int ss_mem;
  int timing_state_mem;
  int pres_mgr_prams_mem;
  int dec_output_mem;

  int au_decoder_instance_mem;
  int evolutionmem;
  int extra_data;
  int evo_buf;
  int TrueHDOption;
  int First_access_unit;
  int Decoded_ch_cfg;
  int evolutionflag;	
  int metadatapresentflag;
  int metadataoffsetcheckFlag;
  int metadataoffset;

  int legacy_mode_cmd;
  int Num_chs_rearrange;
  int Ch_order_req;
  int Object_decode_flag;
  int MDcnt;
  int Prev_MDcnt;
  int a_channel_assign;
  int lfeonstatus;
  int THD_96k_Channel_Decoding;
};
struct MAT_Tag
{
  struct mat_dthd_dec_node_state *matpstate;	
  
  int mat_static_memory_requirements;
  int mat_dynamic_memory_requirements;
  int a_metadatapayload_pstate;
  int a_metadatapayload;
  int a_mat_inputbuffer;
  int a_mat_outputbuffer;
  int Stream_Profile;
  int Stream_Profile_prev;
  int channel_modifier;
  int channel_offset;
  int decoder_init;
  
  int Legacy_Decode; //Command
  int Loudness_Management;
  int output_Mode;
  int LFE_Output_Channels;
  int DRC_Mode;
  int kerneldrc_cut;
  int kerneldrc_boost;
  int update_params;
  int Dialnormenable;
  
  int Ex_encoded; //status
  int LtRt_Present;
  int LFE_Present;
  int decoded_sampling_frequency;
  int Lfe_10dB_Boost;
  int MAT_Stream_Profile_Info;
  int PCM_Channel_Assignment;
  int Downmix_Norm;
  int Dialogue_Normalisation;
  int Decoder_Error;	
  int prev_sampling_frequency; 
  int No_of_Channels;
  int decoder_errorMAT;
  int mat_dec_state;
  int First_access_unit;
  int Decoder_cnt_MAT;
  int End_of_sequence;
  int Chunk_Ready;
  int Predac_buffer_heap;
  int Predac_buffer_wr_ptr;
  int Predac_buffer_rd_ptr;
  int Predac_buffer_length;
};
#endif /* (DOLBY_THD) || defined (DOLBY_MAT) */

#if defined (DOLBY_DDP) || defined (DOLBY_DD)
struct DDPlus_Tag
{
    int dialnormonoff;
    int outchanconfig;
	int dualmode;  //----------------- don't change order
	int compmode;
	int stereomode;
	int inputmode;
	int runningmode;
	int dynscalelow;
	int dynscalehigh;
	int outlfe;
	int *p_dechdlPtr;
	int *Fbptr1;
	int InitDecoder;
	int *udcexecBufferPtr;
	int FramenumberDDP;
	int stream_type;
	int ex_flag_ddp;
	int dsurmod;
	int error;
	int *outparams;
    int pcmscale;
    int mdctbandlimit;
    int *limiter;
    int lfeonstatus;
    int cmixlev;
    int surmixlev;
    int dialnormstatus;
    int Acmod;
    int Normvalue;
    int framesizcod;
    int crcerr;
    int nooflfe;
    int Legacy_Decoding_Mode;
    int bse_chanmap;
	int jocd_out_mode;
	int joc_mode;
	int Prev_Dec_Fs;
	int prevddpsamplerate;
	int prevjocd_out_mode;
	int previousoutputmap;
	int DDP_Length;
	int Pack_length_DDP;
	int Pack_length_DD;
};
#endif /* (DOLBY_DDP) || defined (DOLBY_DD) */
#ifdef DOLBY_LIB
struct DAP_struct
{
	int DAP_Init_Done;
	//DAP_SIDK
	int DAP_height_filter;
	int DAP_Bass_cut_off;
	int DAP_virtuali;
	int DAP_upmixer_disable;
	int DAP_Audio_Profile;
	int DAP_upmixer;
	//int DAP_vmcall;
	//int DAP_LFE_Enable;
	int DAP_Speakers;
	int DAP_ON_OFF;
	int DAP_vlamp;
	int DAP_Tuning_Mode;
	//DAP_SIDK --params_end
	int DMX_ChannelMapping;
	int Prev_DMX_ChannelMapping;
	int DMX_ON_OFF;
	int ObjectAudioEnable;
	char dap_in_channel_map[12];
	int DAP_upmixer_On_Off;
	//int DAP_upmixer_On_Off_staus;
	int DAP_Process_Error;
	int DAP_Speakers_from_lib;
	int DAP_first_frame;
	int dap_OutChannel_count;
	int DAP_Init_Skip;
	int DAP_No_Of_Samples_Processing;
	int DAP_nchannels_in;
	int DAP_nchannels_out;
	int DAP_prev_nchannels_in;
	int DAP_input_ptr;
	int Direct_Decode;
	int virtualizer_front_angle;
	int virtualizer_height_angle;
	int virtualizer_surround_angle;
	int virtualizer_rear_surround_angle;
	int center_spread_enable;
	int DAP_previous_virtuali;
	int Prev_virt_front_angle;
	int Prev_virt_surround_angle;
	int Prev_virt_height_angle;
	int Prev_virt_rear_surround_angle;
	//DAP_CIDK
	int virtualizer_rear_height_angle;
	int Regulator_Enable;
	int Height_channels;
	int regulator_relaxation_amount;
	//int virtualizer_surround_speaker_angle;
	int volume_modeler_calibration;
	//int virtualizer_height_speaker_angle;
	int regulator_timbre_preservation;
	int Volume_Leveler_Input_Target_Level;
	int Volume_Leveler_Output_Target_Level;
	int volmax_boost;
	int calibration_boost;
	int system_gain;
	int postgain;
	int pregain;
	//int ieq_bands;
	int ieq_amount;
	int ieq_enable;
	int volume_modeler_enable;
	int volume_leveler_amount;
	int volume_leveler_enable;
	int surround_boost;
	int dialog_enhancer_ducking;
	int dialog_enhancer_amount;
	int dialog_enhancer_enable;
	//int surround_decoder_center_spread_enable;
	int surround_decoder_enable;
	int mi_surround_compressor_steering_enable;
	int mi_dialog_enhancer_steering_enable;
	int mi_dv_leveler_steering_enable;
	int mi_ieq_steering_enable;
	int regulator_overdrive;
	int audio_optimizer_enable;
	int bass_extraction_cutoff_frequency;
	int bass_extraction_enable;
	int bass_enhancer_cutoff_frequency ;
	int bass_enhancer_enable;
	int process_optimizer_bands;
	int process_optimizer_enable;
	int graphic_equalizer_enable;
	int bass_enhancer_width;
	int bass_enhancer_boost;
	int regulator_speaker_dist_enable;
	int woofer_regulator_enable;
	int custom_woofer_channel_index;
	int virtualizer_start_band;
	int complex_equalizer_enable;
	int bass_extraction_lfe_trim;
	int mi_adaptive_virtualizer_steering_enable;
	int virtual_bass_mode;
	int virtual_bass_overall_gain;
	int virtual_bass_slope_gain;
	int allow_simple_config_to_override_serialized_config;
	int rear_height_filter_mode;
	int DAP_Tuning_ON_OFF;
	int DAP_Tuning_file_ID;
	int DAP_Tuning_2way;
	int DAP_Tuning_3way;
	int DAP_Tuning_init;
	int DolbyUpmixer_Done_temp;
	int Frontgain;
	int lfegain;
	int Centergain;
	int surrgain;
	int heightgain;
	int rearsurrgain;
	int rearheightgain;
	int datmosmusicapp;

};


/*Downmixer structure */
struct downmix_struct
{
	int dmx_params_b_bypass;
	int dmx_params_b_mat_pcm_mode;
	int dmx_params_speakers;
	char dmx_in_channel_map[12];
	char dmx_out_channel_map[12];
	int dmx_stride;
	int dmx_sample_rate;
	int dmx_init_done;
	int dmx_out_channel_cnt;
};


struct OARi_struct
{
	int *oari_nodestate;
	int Speaker_Output_Config;
	int Extended_graph;
	int Upmix;
	int LFE_Enable;
	int SampleRate;
	int prev_sampling_rate;
	int Prev_Speaker_Output_Config;
	int OARiInitFlag;
	int Do_OARi_OAR_Process;
	int Max_MD_Length;
	int Max_MD_Length_byte;
	int FirstObjectFrame;
	int oariMDCount;
	int UsedBytes;

	int RestoreCount;
	int OARiLoopCount;
	int OAR_Done_temp;
	int DecoderBlockSize;
	int OAR_b_enable_limiter;
	int bufsize;
	int headindex;
	int Bass_cut_off;
	int Stream_Type_FrmKernel;

	int block_size;
	int oari_speakers_bitmask;
	int RxedBlksize;

	int AudioInbufptr;
	int Outputbufptr;
	int MDInbufptr;
	int MDInbufbase;
	int MDInbuflen;
    unsigned int    max_objs;                   /**< Maximum number of objects (beds, dynamic, and ISF).     */
    unsigned int    max_input_block_size;       /**< Maximum size of PCM input block.                        */
    int             b_enable_limiter;           /**< Enables the limiter if set.                             */

    unsigned int    max_width_objects;          /**< The maximum number of objects with width to process.Any additional objects with width will be forced to zero width                                              */
    void            *state;        				/**< Pointer to node-specific state */
    int MAT_legacy_oar_flag;
    int SampleBlock_Rx;
    int prev_SampleBlock_Rx;
	int obj_chan_reset;
	int oar_reset_enable;
	int channel_distribution_flag;
	int b_eos;
	int OAR_Reset_Init;
};

struct FADER_struct
{
	int samples_processed;
    int max_fade_len;
    int fade_len;
    int fade_seg;
    int fade_init_done;
    int fader_active;
};
#endif /* DOLBY_LIB */

struct DTSX_Status_Var
{
	int Valid;
	int Es_Flag;
	int DialNorm;
	int DecoderError;
	int ExtensionError;
	int SamplingFrequencyDecoded_status;
	int SamplingFrequencyOriginal_status;
	int SamplingFrequencyOriginal;
	int SamplingFrequencyDecoded;
	int NumberofChannelsOriginal;
	int ChannelConfigurationOriginal;
	int ReplacementGrp_ChSet[3];
	int HeadPhoneStream;
	int LFE_Presence;
	int LFE_Count;//=0;
	int LtRtStream;
	int StreamType;
	int DRC_Presence;
	int Number_of_objects;
	int Parma_done;
	int Rendering_done;
	int Downmix_Normalization;
	int Dialog_Presence;
	int NeoX_Flag;
	int Type1_Flag;
	int IMAX_Done;
	int TruBass_Done;
	int DTSX_CoreFsize_Status;
	int DTS_AmbisonicStream;
	int Type1CC_State_Var;
};

struct DTSX_Tag
{
	struct DTSX_Status_Var Status;

	int OutputChannel_Confiq_command;
	int frame_count_ker;
	int Frame_Length_ker;
	int Offset;
    int nPrimaryFlags;
    int *ppcmoutput;
    int initdecoder;
    int numberofchannels;
    int DTSXcommandprocessingdone_c1;
    int DTSX_Commands[7];
    int InitConfigStructureDone;
	int VersionInfo_REF;
	int VersionBuild_REF;

	int dtsxframecount;
	int previous_Frame_Length_ker;
	int init_done_local;
	int NeuralX_enable;

	int DTSX_DS_Enable;
	int Prev_DTSX_DS_Enable;
	int IntAddrblock0_ptr_addr;

#ifdef DTSX_CHANREORDER
	int ChReorder_Done;
	int ChannelReorder_defaultconfig;
	int PP_InputList[13];
	int ChanReorder_AssignLines_1_2_3_4;
	int ChanReorder_AssignLines_5;
#endif

	int TruBass_init_done;
	int TBHDX_CommandProcessingDone;
	int InputParameter_ExtPPBuf[41];
	int TBasscommand_byte_buf[10];
	int TruBass_Enable;
	int TruBass_ChEnable;
	float TruBass_Dynamics;
	float TruBass_BassLvl;
	int TruBass_SpkrSize;
	int TruBass_SmallSpkrMask;
	int Trubas_Ext_Process_Value;
	int TruBass_Commands[4];
	int DTSX_External_PP;

	int dec_mode_ctrl_var_1;
	int dec_mode_ctrl_var_2;
	int dec_mode_ctrl_var_3;
	int dec_mode_ctrl_var_4;
	int nDecMode_value;

	float TempMips;
	int MipsIdx;
	int cycles;

	int Tone_dump_enable_var;
};

typedef struct
{
	/* SoundX */
	int SoundX_Enable;
	int SoundX_TBHDX_only_mode;
	int 	SoundX_Height_Discard;
	int SoundX_Input_Mode;
	int SoundX_Output_Mode;
	float SoundX_Input_Gain;
	float SoundX_Output_Gain;
	float SoundX_Height_Downmix_Coeff;
	/* Virtual Height */
	int Virtual_Height_Enable;
	int Virtual_Height_Surround_Enable;
	int	Virtual_Height_Tone_Adjustment;
	/* Height Upmix */
	int Height_Upmix_Enable;
	/* TSHD2 */
	int TSHD2_Horizontal_Enable;
	float TSHD2_Horizontal_Mix_Centre_to_Front;
	float TSHD2_Horizontal_Surround_Level;
	int TSHD2_Horizontal_Surround_Enable;
	/* TBHDX FRT */
	int TruBass_HDX_FRT_Processing_Enable;
	int TruBass_HDX_FRT_Processing_Mode;
	int TruBass_HDX_FRT_SpeakerSize;
	float TruBass_HDX_FRT_Dynamics;
	int TruBass_HDX_Front_High_Pass_Enable;
	int TruBass_HDX_FRT_HP_Order;
	float TruBass_HDX_FRT_Bass_Level;
	float TruBass_HDX_FRT_Extended_Bass;
	/* TBHDX CTR */
	int TruBass_HDX_CTR_Processing_Enable;
	int TruBass_HDX_CTR_SpeakerSize;
	float TruBass_HDX_CTR_Dynamics;
	int TruBass_HDX_Center_High_Pass_Enable;
	int TruBass_HDX_CTR_HP_Order;
	float TruBass_HDX_CTR_Bass_Level;
	float TruBass_HDX_CTR_Extended_Bass;
	/* Definition */
	int FRT_Definition_Enable;
	float FRT_Definition_Level;
	int REAR_Definition_Enable;
	float REAR_Definition_Level;
	int SUR_Definition_Enable;
	float SUR_Definition_Level;
	int CTR_Definition_Enable;
	float CTR_Definition_Level;
	/* Space HPF */
	int FRT_SpaceHPF_Enable;
	int FRT_SpaceHPF_Frequency;
	int REAR_SpaceHPF_Enable;
	int REAR_SpaceHPF_Frequency;
	int SUR_SpaceHPF_Enable;
	int SUR_SpaceHPF_Frequency;
	/* Dialog clarity */
	int Dialog_Clarity_Enable;
	float Dialog_Clarity_Control;
	/* TruSurroundM */
	int TruSurroundM_Enable;
	float 	TruSurroundM_LpR_To_Center_Mix;
	float 	TruSurroundM_Naturalness_Control;
	float 	TruSurroundM_Rear_Naturalness_Control;
	float 	TruSurroundM_Height_Naturalness_Control;
	float 	TruSurroundM_Center_Channel_Gain;
	float 	TruSurroundM_Front_Height_Channel_Gain;
	float 	TruSurroundM_Rear_Height_Channel_Gain;
	float 	TruSurroundM_Height_Mix_Coefficient;
	float 	TruSurroundM_Rear_Height_Mix_Coefficient;
	int 	TruSurroundM_Device_Layout;

	/* MBHL */
	int   	Mbhl_Enable;
	float 	Mbhl_Bypass_Gain;
	float 	Mbhl_Reference_Level;
	float 	Mbhl_Volume;
	float 	Mbhl_Output_Gain;
	int	 	Mbhl_Shuffle;
	float 	Mbhl_Shuffle_Level;
	int 	Mbhl_Anti_Clip_Enable;
	float 	Mbhl_Anti_Clip_Level;
	float 	Mbhl_Boost;
	float 	Mbhl_Threshold;
	float 	Mbhl_Slow_Offset;
	float 	Mbhl_Fast_Attack;
	int 	Mbhl_Fast_Release;
	int 	Mbhl_Slow_Attack;
	int 	Mbhl_Slow_Release;
	int 	Mbhl_Delay;
	int 	Mbhl_Envelope_Frequency;
	int	 	Mbhl_Mode;
	int		Mbhl_Cross_Low;
	int 	Mbhl_Cross_Mid;
	int 	Mbhl_Compressor_Attack;
	int 	Mbhl_Compressor_Low_Release;
	float 	Mbhl_Compressor_Low_Ratio;
	float 	Mbhl_Compressor_Low_Threshold;
	float 	Mbhl_Compressor_Low_Makeup;
	int 	Mbhl_Compressor_Mid_Release;
	float 	Mbhl_Compressor_Mid_Ratio;
	float 	Mbhl_Compressor_Mid_Threshold;
	float 	Mbhl_Compressor_Mid_Makeup;
	int 	Mbhl_Compressor_High_Release;
	float 	Mbhl_Compressor_High_Ratio;
	float 	Mbhl_Compressor_High_Threshold;
	float 	Mbhl_Compressor_High_Makeup;

	/* LOUDNESS */
	int 	Loudness_Enable;
	int 	Latency_Mode;
	unsigned int Target_Loudness;
	int 	Loudness_Preset;
	int 	Loudness_Control_Discard;

} DTSVX_Commands_t;

struct DTS_VirtualX
{
	DTSVX_Commands_t DTSVX_Commands;
	int DTS_VirtualX_Enable;
	int InputCh_Config;
	int OutputCh_Config;
	int DTS_VirtualX_Init_Flag;
	int DTS_VirtualX_Status;
	int SampleBlock;
	int Input_Channels;
	int Output_Channels;
	int InputChMask;
	int OutputChMask;
	int Input_Sample_Rate;
	int Output_Sample_Rate;
	int ChanReorder_AssignLines_DTSVX;
	int VX_Process;
	int VX_InChannel_Count;
	int ChReorder_DTSVX_Done;
	int VirtualX_Enable;
	int DTSX_Commands_Temp[4];
	int DTSX_Command_Init;
	int DTSVX_enable_mode;
};

struct kernel
{
	int RAM_codeid;
#ifdef MPEGH_DECODER
	struct MPEGH_Tag MPEGH;
#endif
	struct Customer_post_processing Customer_pp;
	struct Autodet Autdet;
	struct Transmitter Tx;
	struct Receiver Rx;
	struct Host Spi;
#ifdef NOISEGEN
	struct NoiesGen_Tag  NoiseGen;
#endif

#ifdef DE_EMPHASIS_PP
	struct Deemph_Tag De_emphasis;
#endif

	struct IOProcess IOP;
	struct Miscelleny Misc;

	int Value;
    int run_flag;
	int stop_flag;
	int mute_flag;
	int decoder_error;
    int StreamType;
    int InitDoneForStreamType;
    int SampleBlock;
    int	PCMEnable;
	int	MCLPCMEnable;
	
#ifdef DE_EMPHASIS_PP
 	int init_deemphasis;
 	int pcm_deemphasis_enable;
#endif

	int MCLPCM_ON;
	int ADCEnable;
	
    int MemoryAllotPcm;
    int MemoryAllotMCLPCM; 
    int MemoryAllotPack;
	int MemoryAllotDac;
	int MemoryAllotEs;
	#if defined (DOLBY_DDP) || defined (DOLBY_DD)
	int Decoded_Fs;
	#endif
	int LPCM_delay_index;
	int LPCMDelaySize_host;
	int cmd_temp_read;
	int pack_length_pcm;
	int pack_length_mcpcm;
	int predac_length_pcm;
	int predac_length_mcpcm;
	int AddPreDac_length_mcpcm;
	int AddPreDac_length_pcm;

	int pack_length_dts;
	int pack_length_dtshdma;
	int pack_length_dtshdhr;
	int pack_length_ddp;
	int pack_length_dd;
    int pack_length_truehd;
    int pack_length_matpcm;
    int pack_length_mpegh;
	int predac_length_mpegh;

	int LBRDecoderEnable;
	int DTSXDecoderEnable;
	int TRUEHDDecoderEnable;
	int DDPLUSDecoderEnable;
	int DOLBYDecoderEnable;

	int SampleDropCount;
	int SampleDropCountIndex;
	int autodetect_mode;
	int OutputSampleRate;
	int PrevOutputSampleRate;
	int sampling_fs_micro;
	int prev_sampling_fs_micro;

    int ADI_DecoderError;
	int cmd_result;

	int sample_count_value;	
	int sample_count_value_save;
	int AddPreDac_pointer;
	
	int PackAllocateinProgress;
	int Mute_flag_from_HOST;
	int LPCMDelayBuffer_heap;
	int LPCMDelayBuffer_wr_ptr;
	int LPCMDelayBuffer_rd_ptr;
	int PrevLPCMDelaySize_host;
	int LPCMDelaySize;
	int lfesaveflag;
	int lfepresent;
	#ifdef NOISEGEN
	int temp_pointer;
	#endif
	int PostDecoderStereo;

	// AAC, LBR
	int loop_offset;
	int inputChannelConfig;
	int outputChannelConfig_c1;

	int InitDoneForFS;
	
	int AutodetectMode_Enable;
	int InitDoneForAutodetectMode;

	int Decoder_Channel_Assignment;

#ifdef DOWNSAMPLING
	int init_ds_processing;
	int DS_Mode;
	int SampleBlock_DS;
#endif
#ifdef NOISEGEN
	int heap_index;
	int pack_length_noise;
	int predac_length_noise;
	int AddPreDac_length_noise;
	int	MemoryAllotNoise;
	int	NoiseGenEnable;
	int init_noise_gen;
	int ClearLeftChannelNoise;
	int NoiseGen_Ch;
#endif
#ifdef  DSD2PCM_DEC
	int DSD2PCMMode_Enable;
	int Prev_DSD2PCMMode_Enable;
	int InitDoneForDSD2PCM;
	int pack_length_DSD2PCM;
	int predac_length_DSD2PCM;
	int addpredac_length_DSD2PCM;
#endif
	int Stream_Type_ForMUTE;
	int Bufzerocount;
	int No_of_DAC_channel;
	int Max_No_of_DAC_channel;
	int Tx_ChSel;
	int No_of_Channel;
	int internal_Tx_buff;
	int Post_decoding_option_command;
	int PP_Framecnt_Loop;
	int PP_Frmaecnt;
#ifdef AAC_DEC
	struct AAC_Tag AAC;
	int pack_length_aac;
	int AddPreDac_length_aac;
	int predac_length_aac;
	int AACDecoderEnable;
#endif
	int mpeg2support;
	int ChannelReorder_AssignLines;
#ifdef MPEGH_DECODER
	int MemoryAllotMPEGH;
	int Enable_Factor_MPEGH;
	int MPEGH_DecoderEnable;
#endif
	int Legacy_Decoding_Mode;   	//Needed for all PCM,MCPCM,DOLBY
	int No_of_Chan;
	int speakers_bitmask;
	/* Dolby libraries variables defines */
	#ifdef DOLBY_LIB
	int core_config;
	int ATMOS_Info;
	int Object_Audio;

	#ifdef DOLBY_DMX
	struct downmix_struct dmx_Frmwk;
	#endif
	int SampleBlock_PP;
	int graph_type;
	int Ch_ID_Check;
	int Legacy_Mode_enable;

	int LFE_Enable;
	int Speakers_presence_7_1;
	/* Dolby switching category variables */
	#if defined (DOLBY_DDP)||defined (DOLBY_MAT) ||defined (DOLBY_OAR) || defined (DOLBY_DAP)|| defined (DOLBY_DD) || defined (DOLBY_THD)
	int Ch_Ch_Switch;
	int Ch_Obj_Switch;
	int Obj_Ch_Switch;
	int Ch_Obj_Switch_Align_Pointer;
	int Ch_Obj_Addpredac_Align_Pointer;
	int DDP_ch_Obj_switch;
	int Ch_Ch_Switch_Align_Pointer;
	int PP_switch_confirm;
	int Obj_Ch_Switch_Align_Pointer;
	int End_of_Sequence_MAT_DDP;
	int Obj_Obj_Switch;
	int Obj_Obj_Predac_Align;
	int Obj_Ch_Addpredac_Align_Pointer;
	int Ch_to_Obj_MD_Content;
	int DDP_MD_Present;
	#endif /* (DOLBY_DDP) || defined (DOLBY_MAT) */
	int b_mat_pcm_mode;
	int mat_direct_mode;
	int datmos_speaker_legacy_option;
	int DAP_OAR_Reinit;
	int joc_dmx_out_order[16];
	int tuning_mode_enable;
	#endif /* DOLBY_LIB */

	/* DDP & DD variables */
	#if defined (DOLBY_DDP) || defined (DOLBY_DD)
	struct DDPlus_Tag DDPlus;
	
	//int pack_length_ddp;
	//int pack_length_dd;
	int predac_length_ddp;
	int AddPreDac_length_ddp;
	//int DOLBYDecoderEnable;
	//int DDPLUSDecoderEnable;
	#endif /* (DOLBY_DDP) || (DOLBY_DD) */
 	/* OAR variables */
	#ifdef DOLBY_LIB
	struct OARi_struct OAR_Frmwk;
	struct FADER_struct FADER_Frmwk;
	int speakers_bitmask_OAR;
	#endif
	/* DAP variables */
	#ifdef DOLBY_LIB
	struct DAP_struct DAP_krnl;
	#endif
	/* THD & MAT variables */
	#if defined (DOLBY_THD) || defined (DOLBY_MAT)	||	defined (DTSX_DECODER)
	int predac_length_truehd_48k;
	int predac_length_truehd_96k;
	int predac_length_truehd_192k;
	int predac_length_matpcm_48k;
	int predac_length_matpcm_96k;
	int predac_length_matpcm_192k;
	int MemoryAllotMAT;
	int MemoryAllotTrueHD;
	int Number_Of_Channels;
	int AddPreDac_length_truehd;
	int AddPreDac_length_matpcm;
	int decodersamplefreq;

	//int DS_Mode;
	int DS_Mode_THD;
	//int TRUEHDDecoderEnable;
	int AuDt_Enable;
	#endif /* (DOLBY_THD) || defined (DOLBY_MAT) */
	#ifdef DOLBY_DAP
	signed int gain_temp;
	#endif /* DOLBY_DAP */
	
	#ifdef DOLBY_LIB
	/* MAT variables */
	struct MAT_Tag MAT;
	/* THD variables */
	struct TrueHD_Tag TRUEHD;
	#endif
//	#if defined (DOWNSAMPLING_PCM) || defined (DOWNSAMPLING_MCPCM) || defined (DOLBY_THD_DS)
//	int DS_Mode;	//Need to conform
//	#endif

	#ifdef DOLBY_CERTIFICATION
	int CIDK_Enable_PP;
	int CIDK_Enable_Dec;
	#endif
	
	#ifdef DTSX_DECODER
		struct DTSX_Tag DTSX;
		//int Number_Of_Channels;
		int MemoryAllotDTS;
		//int pack_length_dtshdhr;
		int predac_length_dtshd;
		int addpredac_length_dtshd;
		int ChReorder_PassThrough;
		//int DTSXDecoderEnable;
		int McpcmNeuralX;
	#endif
	#ifdef DTS_VIRTUALX
	//DTS VirtualX
	struct DTS_VirtualX DTSVX;
	int StreamType_DTSX; 
	#endif
};

#endif  /*	DEF_STRUCT_H_  */

