/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Decoder_Core2.h
*  Description      :
******************************************************************************/
#pragma default_section(ALLDATA,"Seg_Kernal_Data")

#ifndef DECODER_CORE2_H_
#define DECODER_CORE2_H_

#include "Def_Struct.h"
#include <platform_include.h>
#include <sys/cache.h>
#include <stdio.h>
#include <services/dma/adi_dma.h>
#include <services/spu/adi_spu.h>

#include "Commn.h"
#include "Extern_Core2.h"

int fram_cnt;

section("seg_kernal_data_align32")
int Predac_buffer_Int_c2[BUFF_MAX_SIZE];


#ifdef MDMA_COPY
/* Memory to handle DMA Stream */
static uint8_t MemDmaStreamMem2[ADI_DMA_STREAM_REQ_MEMORY];

/* DMA Stream Handle */
ADI_DMA_STREAM_HANDLE   hMemDmaStream2;

/* Source DMA Handle */
static ADI_DMA_CHANNEL_HANDLE  hSrcDmaChannel2;

/* Destination DMA Handle */
static ADI_DMA_CHANNEL_HANDLE  hDestDmaChannel2;

static bool bMemCopyInProgress_check;

void MDMA_init(void);
void MDMA_Copy(int, int, int);

#endif


extern int Sampling_freq;

int BufSize;
int SrcBuf;
int DstBuf;

#ifdef MDMA_COPY
void MDMA_init(void);
void MDMA_Copy(int BuffSize, int SrcBuff, int DstBuff);
#endif

void Predac_buffer_Int_to_Predac_buffer(void);
void pre_dac_ptr_update_rd_c2(void);
void  Pre_Dac_Ptr_Update(void);
void FreeMemoryAll(void);
void Init_Var(void);
void MCPCMDecoder(void);
void shared_memory_var_update(void);
void Control_DataVariable_Update(void);

void Init_Var_Fs();
void Init_Var();
void FreeMemoryAll();
int Free_AllotMemoryPackDac (int , int , int );
void Autodetect_MemoryAlloc();
void CustomerPP_gain_control(int *CustPPInputList);
void pack_t0_int();
void Pack_rd_ptr_upadate_c2();
void int_t0_predac();
void Pre_Dac_Ptr_Update();
void PreDac_Buffer_Int_Rearrange();

int mdma_done;

int Predac_Length_Ptr;
int No_Sample_Processing = NO_OF_SAMPLE_PROCESSING;

#ifdef CUSTOMER_PP
int CustPPInputList[20];
void Customer_Post_Processing(void);
#endif


#ifdef ADI_VIRTUAL
section("seg_Input_buffer")
int Input_buffer[256*8]; //2048
section("seg_Output_buffer")
int *Input_buffer_ptr = Input_buffer;
section("seg_Output_buffer")
int Output_buffer[256*2]; //512
section("seg_Output_buffer")
int *Output_buffer_ptr = Output_buffer;

int loopcount_value=0;
int alg_input_list[10];
#endif

/*Dont Use this section for any other Buffers.It is for shared memory*/
section("Seg_Shared_Mem")
int   Shared_mem_reserved[500];

/*Kernal Data share variable from 0 to 50*/
int *sampling_frequency		 				=&Shared_mem_reserved[0];
int *Auto_detection_mode	 				=&Shared_mem_reserved[1];
int *Next_dac_count          				=&Shared_mem_reserved[2];
int *NextDataValid_ptr		 				=&Shared_mem_reserved[3];
int *core2_sync_bit			 				=&Shared_mem_reserved[4];
int *stream_type			 				=&Shared_mem_reserved[5];
int *datacanbeprocessnow 				 	=&Shared_mem_reserved[7];
int *core2_dcpn_done						=&Shared_mem_reserved[8];
int *Frmwk_SampleBlock_c1			     	=&Shared_mem_reserved[9];
int *Frmwk_Outputsamplerate_c1				=&Shared_mem_reserved[10];
int *Frmwk_nchannels_in_c1					=&Shared_mem_reserved[11];
int *Init_Start_Command_c1					=&Shared_mem_reserved[12];
int *Frmwk_nchannels_in_c1_MPCM				=&Shared_mem_reserved[13];
int *Stream_Profile							=&Shared_mem_reserved[14];
int *SampleBlock_Core2						=&Shared_mem_reserved[15];
int *run_flag                               =&Shared_mem_reserved[16];

/*Predac(51 to 75)  details share variable from 51 to 75 */
int *predac_heap			 				=&Shared_mem_reserved[51];
int *Predac_length           				=&Shared_mem_reserved[52];
int *Predac_length_half      				=&Shared_mem_reserved[53];
int *Latency_predac_wr_ptr_c1				=&Shared_mem_reserved[54];
int *predac_wr_ptr_c1		 				=&Shared_mem_reserved[55];
int *predac_wr_ptr           				=&Shared_mem_reserved[56];
int *predac_wr_ptr_c2		 				=&Shared_mem_reserved[57];
int *predac_rd_ptr_c1                       =&Shared_mem_reserved[58];

/*Addpredac(76 to 100) details share variable from 76 to 100*/
int *addpredac_heap			 				=&Shared_mem_reserved[76];
int *addpredac_length			 			=&Shared_mem_reserved[77];
int *addpredac_lengthhalf    				=&Shared_mem_reserved[78];
int *addpredac_wr_ptr		 				=&Shared_mem_reserved[79];
int *addpredac_rd_ptr		 				=&Shared_mem_reserved[80];

/****Core2 Post processing variable  will use from 101 to 125****/
int *core2_command_processing_status_done 	 =&Shared_mem_reserved[101];
int *Decoder_Speaker_config                  =&Shared_mem_reserved[102];

/****CommandProcessing variable will use from 126 to 159****/
int *COMMAND_BYTE_C2						=&Shared_mem_reserved[126];
int *PARAMETER_1_C2 						=&Shared_mem_reserved[127];
int *PARAMETER_2_C2 						=&Shared_mem_reserved[128];
int *PARAMETER_3_C2 						=&Shared_mem_reserved[129];
int *PARAMETER_4_C2							=&Shared_mem_reserved[130];
int *PARAMETER_5_C2 						=&Shared_mem_reserved[131];
int *PARAMETER_6_C2 						=&Shared_mem_reserved[132];
int *PARAMETER_7_C2 						=&Shared_mem_reserved[133];
int *PARAMETER_8_C2							=&Shared_mem_reserved[134];
int *PARAMETER_9_C2 						=&Shared_mem_reserved[135];
int *PARAMETER_10_C2 						=&Shared_mem_reserved[136];
int *PARAMETER_11_C2 						=&Shared_mem_reserved[137];
int *PARAMETER_12_C2						=&Shared_mem_reserved[138];
int *PARAMETER_13_C2 						=&Shared_mem_reserved[139];
int *PARAMETER_14_C2 						=&Shared_mem_reserved[140];
int *PARAMETER_15_C2 						=&Shared_mem_reserved[141];
int *PARAMETER_16_C2						=&Shared_mem_reserved[142];
int *PARAMETER_17_C2 						=&Shared_mem_reserved[143];
int *PARAMETER_18_C2 						=&Shared_mem_reserved[144];
int *PARAMETER_19_C2 						=&Shared_mem_reserved[145];
int *PARAMETER_20_C2						=&Shared_mem_reserved[146];
int *PARAMETER_21_C2 						=&Shared_mem_reserved[147];
int *PARAMETER_22_C2 						=&Shared_mem_reserved[148];
int *PARAMETER_23_C2 						=&Shared_mem_reserved[149];
int *PARAMETER_24_C2						=&Shared_mem_reserved[150];
int *PARAMETER_25_C2 						=&Shared_mem_reserved[151];
int *PARAMETER_26_C2 						=&Shared_mem_reserved[152];
int *PARAMETER_27_C2 						=&Shared_mem_reserved[153];
int *PARAMETER_28_C2						=&Shared_mem_reserved[154];
int *PARAMETER_29_C2 						=&Shared_mem_reserved[155];
int *PARAMETER_30_C2 						=&Shared_mem_reserved[156];
int *PARAMETER_31_C2 						=&Shared_mem_reserved[157];

/****Resevered for the Customer will use from 160 to 250****/



#endif /* DECODER_CORE2_H_ */
