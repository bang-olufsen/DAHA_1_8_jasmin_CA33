/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Def_Struct.h
*  Description      :   All the Struture Variables inlcluded
******************************************************************************/

extern volatile struct kernel Frmwk;
struct Host
{
	/*************** Don't chage the order*************/
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
};

struct saveunsave
{
	int prolbufsave_tx[75];
	int prolbufsave_rx[45];
	int prolbufsave_spi[15];
	int SveforSetSync[6];
	int saveint[90];
	int savestack[65];
	int save_creg[20];
	int save_rxisr;
};

struct Alglist
{
	int alg_input_list[50];
	int alg_output_list[50];
};

struct Packbuf
{
	int heap;
	int rd_ptr_c2;
	int wr_ptr_c2;
	int length;
	int lengthhalf;
};

struct Customer_post_processing
{
	int CustomerPPProcessBufferPtr;
	int CustomerPPProcessBufferSize;
	int Blocksize;
	int Number_of_Channels;
	int Data_Format;
	int ChannelMask;
	int StreamType;
	int SamplingFrequency;
	int Volume;
};

struct Predacbuf
{
	int heap;
	int rd_ptr_c2;
	int wr_ptr_c2;
	int wr_ptr_c1;
	int length;
	int lengthhalf;
};

struct AddPreDacbuf
{
	int heap;
	int rd_ptr_c2;
	int wr_ptr_c2;
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
	int    NextDacCount;
	int	   DacCount;	 
	int    NextDacAdd;
	int    NextDacAddPreDac;
	int    CopyToDacCounter;
	int    datacanbeprocessednow;
	int    datacanbeprocessednow_core1;
};

struct Miscelleny
{
	struct saveunsave Protect;
	struct Alglist List;	
};

struct kernel
{
	int RAM_codeid;
	struct Customer_post_processing Customer_pp;
	struct Host Spi;
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
    int No_of_channel;
    int Max_No_of_channel;
    int	PCMEnable;
	int	MCLPCMEnable;
	int MCLPCM_ON;
	
    int MemoryAllotPcm;
    int MemoryAllotMCLPCM; 
    int MemoryAllotPack;
	int MemoryAllotDac;

	int Dual_Mono_Info;
	int cmd_temp_read;

	int pack_length_default;
	int ADI_DecoderError;
	
	int pack_length_pcm;
	int pack_length_mcpcm;
	int predac_length_pcm;
	int predac_length_mcpcm;
	int AddPreDac_length_pcm;		
	int AddPreDac_length_mcpcm;		

	int pack_length_lbr;
	int predac_length_lbr;
	int AddPreDac_length_lbr;
	int SampleDropCount;
	int SampleDropCountIndex;
	int autodetect_mode;
	int OutputSampleRate;
	int PrevOutputSampleRate;
	int sampling_fs_micro;
	int prev_sampling_fs_micro;
 	
	int AddPreDac_pointer;
	
	int InitDoneForAutodetectMode;
	int stereo_in;
	int down_mix;
	int AutodetectMode_Enable;
	int Stream_Type_ForMUTE;
	int Init_begin_core2;
    int Stream_Profile;
};
