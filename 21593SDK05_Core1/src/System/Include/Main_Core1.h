/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Main_Core1.h
*  Description      :
******************************************************************************/

#ifndef __MAIN_CORE1_H__
#define __MAIN_CORE1_H__

/* Add your custom header content here */
#include <stdint.h>
#include <sys/platform.h>
#include <sys/adi_core.h>
#include <stdio.h>
#include <cdef21593.h>
#include "Init_Struct.h"
#include <sys/cache.h>
#include <drivers\sport\adi_sport.h>
#include <drivers/spdif/adi_spdif_rx_v1.h>
#include <services/dma/adi_dma.h>

#include <math.h>
#include "Codeid.h"
#include "HostDefines.h"
#include "sru.h"
#include "Commn.h"
#include "Variables.h"
#include "Function_Prototype.h"
#include "Extern_Core1.h"
#include "Common_macros__extern_definations.h"

/*
#ifdef AURO_3D
#include "Kernal\Chan_Id.h"
#endif
*/

#ifdef __ADSPSC598_FAMILY__
#include <sys/ADSP-SC598.h>
#include <cdefSC598.h>
#else
#include <cdef21593.h>
#endif


int PcmZeroCountMax = 96000;
int Ext_Buffer_Data_Size;
int *Ext_Buff_Ptr_copy = &Ext_Buffer_Data[0];
int frame_count_VX;
int FsFrameCnt;
int frame_count;	//Need to conform	
int SPI_Device = SPI_DEVICE;
int AuroEngine_Enable_cmd = 0;

#ifdef I2S_TDM_MODE_ENABLE
#ifdef BEO_Framework
int I2S_TDM_MODE = ASRC_TDM_MODE;
int prev_I2S_TDM_Mode = ASRC_TDM_MODE;
#else
int I2S_TDM_MODE = I2S_MODE;
int prev_I2S_TDM_Mode = I2S_MODE;
#endif
#endif
#ifdef AURO_3D
int Auro_TargetDevice=0;
int	Auro_Output_ch_count=0;
#endif
#ifdef BEO_Framework
int FS_Div_Value = 0;
int ASRC_Samplerate = 0;
#endif /* BEO_Framework */

#ifdef EXT_DNMIX
int Cs_enable;
int speakers_bitmask_Cs;
#endif

int Custom_Clock_Ratio = 128;
int Custom_MCLK_Mode_cmd = 0;
#ifdef eARC_ENABLE
	int eARC_Mode = 0;
	int eARC_Clock_Ratio = 128;
#endif
#ifdef DEFAULT_CH_CONFIG
	int Command_Processing = 0;
#endif
#ifdef AURO_3D
	typedef enum
	{
	    AU_channel_Id_Left = 0,
		AU_channel_Id_Right = 1,
		AU_channel_Id_Center = 2,
		AU_channel_Id_LFE = 3,
		AU_channel_Id_LeftSurround = 4,
		AU_channel_Id_RightSurround = 5,
		AU_channel_Id_CenterSurround = 6,
		AU_channel_Id_LeftBack = 7,
		AU_channel_Id_RightBack = 8,
		AU_channel_Id_HeightLeft = 9,
		AU_channel_Id_HeightRight = 10,
		AU_channel_Id_HeightCenter = 11,
		AU_channel_Id_Top = 12,
		AU_channel_Id_HeightLeftSurround = 13,
		AU_channel_Id_HeightRightSurround = 14,
		AU_channel_Id_HeightCenterSurround = 15,
		AU_channel_Id_HeightLeftBack = 16,
		AU_channel_Id_HeightRightBack = 17,
		AU_channel_Id_LeftCenter = 18,
		AU_channel_Id_RightCenter = 19,
		AU_channel_Id_LFE2 = 20,
		AU_channel_Id_BottomLeft = 21,
		AU_channel_Id_BottomRight = 22,
		AU_channel_Id_BottomCenter = 23,
		AU_channel_Id_BottomLeftSurround = 24,
		AU_channel_Id_BottomRightSurround = 25,
		AU_channel_Id_LeftWide = 26,
		AU_channel_Id_RightWide = 27,
		AU_channel_Id_TopLeft = 28,
		AU_channel_Id_TopRight = 29,
		AU_channel_Id_Mono = 30,
		AU_channel_Id__End = 31,
		AU_channel_Id__Undefined = AU_channel_Id__End,
	} AU_channel_Id_t;
#endif
/******************************************************************************
 * Global Variables Extern Section
 *****************************************************************************/

extern int down_samp_flag;

extern int *datacanbeprocessnow;
extern int *run_flag;
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
extern int *core2_command_processing_status_done;

extern int TMU_Enable;

#endif /* __MAIN_CORE1__H__ */
