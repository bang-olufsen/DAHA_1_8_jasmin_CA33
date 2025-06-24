/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Main_Core2.h
*  Description      :
******************************************************************************/

#pragma default_section(ALLDATA,"Seg_Kernal_Data")

#ifndef __MAIN_CORE2_H__
#define __MAIN_CORE2_H__

#include <sys/platform.h>
#include <sys/adi_core.h>
#include "adi_initialize.h"
#include "Init_Struct.h"
#include "Commn.h"
#include "Extern_Core2.h"
enum
{
    RESULT_SUCCESS = 0u,            /* Successfully completed the requested operation */
    RESULT_FAILURE,                 /* Failed to completed the requested operation */
    RESULT_NEED_MORE_DATA           /* Requires more data to proceed with the requested operation */
};



int Sampling_freq;
int Stream_Type_frm_Core1;
int pre_dac_ptr_sync;
int addpredac_ptr_sync;



#define NOP asm("nop;");
#define NOP10 asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");


extern int *Latency_predac_wr_ptr_c1;
extern int *core2_sync_bit;
extern int *stream_type;
extern int *Next_dac_count;
extern int *core2_command_processing_status_done;
extern int *predac_heap;
extern int *datacanbeprocessnow;
extern int *predac_wr_ptr_c1;
extern int *predac_wr_ptr_c2;
extern int *Predac_length;
extern int *addpredac_rd_ptr;
extern int *addpredac_wr_ptr;
extern int *addpredac_heap;
extern int *addpredac_length;
extern int *Predac_length_half;
extern int *addpredac_lengthhalf;
extern int *SampleBlock_Core2;
extern int *run_flag;

extern int *c1_predac_rd_ptr;
extern int *c1_predac_wr_ptr;

extern int *Frmwk_Legacy_Decoding_Mode_c1;

extern int *Frmwk_Decoded_ChAssignment_FromHost_c1;
extern int *Frmwk_Outputsamplerate_c1;

extern int *Init_Start_Command_c1;

extern int *Upmix_ON_OFF_Status;

extern int *core2_dcpn_done;

extern int *PARAMETER_1_C2;
extern int *PARAMETER_2_C2;
extern int *PARAMETER_3_C2;
extern int *PARAMETER_4_C2;
extern int *PARAMETER_5_C2;
extern int *PARAMETER_6_C2;
extern int *PARAMETER_7_C2;
extern int *PARAMETER_8_C2;
extern int *PARAMETER_9_C2;
extern int *PARAMETER_10_C2;
extern int *PARAMETER_11_C2;
extern int *PARAMETER_12_C2;
extern int *PARAMETER_13_C2;
extern int *PARAMETER_14_C2;
extern int *PARAMETER_15_C2;
extern int *PARAMETER_16_C2;
extern int *PARAMETER_17_C2;
extern int *PARAMETER_18_C2;
extern int *PARAMETER_19_C2;
extern int *PARAMETER_20_C2;
extern int *PARAMETER_21_C2;
extern int *PARAMETER_22_C2;
extern int *PARAMETER_23_C2;
extern int *PARAMETER_24_C2;
extern int *PARAMETER_25_C2;
extern int *PARAMETER_26_C2;
extern int *PARAMETER_27_C2;
extern int *PARAMETER_28_C2;
extern int *PARAMETER_29_C2;
extern int *PARAMETER_30_C2;
extern int *PARAMETER_31_C2;

extern int *COMMAND_BYTE_C2;


#endif /* __MAIN_CORE2_H__ */
