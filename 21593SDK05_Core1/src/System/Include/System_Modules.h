/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	System_Modules.h
*  Description      :
******************************************************************************/
#ifndef SYSTEM_INCLUDE_SYSTEM_MODULES_H_
#define SYSTEM_INCLUDE_SYSTEM_MODULES_H_

#include "Commn.h"
#include "Extern_Core1.h"
#include <math.h>
#include <stdio.h>
#include "HostDefines.h"
#include "Codeid.h"
#include <services/pcg/adi_pcg.h>
#include "Def_Struct.h"

#include "ar_speaker.h"

#ifdef I2S_TDM_MODE_ENABLE
int *TX_SP4A_BUFFER_LCRSW0_BUF;
int *TX_SP4A_BUFFER_LsLsrRsRsr0_BUF;
int *TX_SP3A_BUFFER_Addch1ch3Addch2ch4_set0_BUF;
int *TX_SP3A_BUFFER_Addch5ch7Addch6ch8_set0_BUF;
int *TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0_BUF;
int *TX_SP6A_BUFFER_Addch13ch15ch14ch16_set0_BUF;
#endif

#ifdef PCM_DEC
#pragma section("seg_PCM_data")
int LPCMDelayBuffer[LPCMDelayBuffer_size];//Lpcm delay for 96k and 192k(16384+(256*2*4))
#endif

int Freq_Table[11]={ 32000,
					 44100,
					 48000,
					 48000,
					 64000,
					 88200,
					 96000,
					 96000,
					 128000,
					 176400,
					 192000};

int Freq_Table_SRU[11] =   {48000,48000,48000,48000,96000,96000,96000,96000,192000,192000,192000};

#ifdef DOLBY_LIB
#pragma section("Seg_AddPredac_Bw")
	int AddPredac_buffer_Int[61440];		//40960		// 40*32*8*4//1280*8*4

#pragma align 32
#pragma	section("Seg_Dolby_Library_Data_L3")
char joc_phse[29984];
#pragma align 32
#ifdef DOLBY_L2_BUFFER_POINTER
#pragma section("Seg_Dolby_Library_Data_L3")
	char *libraray_l2_data; //char buffer [169392] is  assigned as a pointer and mapped in L2
#else
#pragma section("Seg_Dolby_Library_Data_L3")
char libraray_l2_data[169392];
#endif/* DOLBY_L2_BUFFER_POINTER */

	#pragma align 32
#pragma	section("Seg_Dolby_Library_Data_L3")
	char TRUEHD_predac_heap_buf[122880];		//1280*16*4 //160*32*6*4 TRUEHD_predac_heap_buf[81920];

	/*==============DDP Decoder output channel configuration=================================================*/
#pragma	section("Seg_DDP_Kernel_Data_L3")
	typedef enum
	{
			UDC_OUTPUT_CHAN_ID_L_R                  = 2,    /**< UDC Output Mode: Stereo       */
			UDC_OUTPUT_CHAN_ID_L_R_C                = 3,    /**< UDC Output Mode: 3/0          */
			UDC_OUTPUT_CHAN_ID_L_R_LS_RS            = 6,    /**< UDC Output Mode: 2/2          */
			UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS          = 7,    /**< UDC Output Mode: 3/2          */
			UDC_OUTPUT_CHAN_ID_L_R_LS_RS_LRS_RRS    = 16,   /**< UDC Output Mode: 2/2/2        */
			UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS_LRS_RRS  = 21,   /**< UDC Output Mode: 3/2/2        */
			UDC_OUTPUT_CHAN_ID_L_R_C_LS_RS_LRS_RRS_LTS_RTS  = 28,   /**< UDC Output Mode: 3/2/2 (L,R,Ls,Rs,Ltm,Rtm)	**/
			UDC_OUTPUT_RAW                          = -1,   /**< UDC OUtput Mode: Raw output   */
	} udc_output_mode;


#pragma		section("Seg_Dolby_Kernel_Data_L3")
		int DAP_Enable;

#if defined (DOLBY_DAP)||defined (DOLBY_OAR)
#pragma		section("Seg_Dolby_Kernel_Data_L3")
		int surr_speakers_present		= 0;
#pragma		section("Seg_Dolby_Kernel_Data_L3")
		int rear_surr_speakers_present	= 0;
#pragma		section("Seg_Dolby_Kernel_Data_L3")
		int height_speakers_present		= 0;

#pragma		section("Seg_Dolby_Kernel_Data_L3")
		typedef enum {
		  DATMOS_VIRTUALIZER_MODE_DISABLE,
		  DATMOS_VIRTUALIZER_MODE_SPEAKER,
		  DATMOS_VIRTUALIZER_MODE_HEADPHONE,
		  DATMOS_VIRTUALIZER_MODE_DEFAULT = DATMOS_VIRTUALIZER_MODE_DISABLE,
		} datmos_ht_virtualizer_mode;

#endif /* DOLBY_DAP || DOLBY_OAR  */ 

#pragma	section("Seg_Dolby_Kernel_Data_L3")
	unsigned long ar_speaker_mask;
#pragma	section("Seg_Dolby_Kernel_Data_L3")
	const uint8_t outputmap_channels[UDC_OUTPUTMAP_LENGTH] =
	{
			DPF_CHANNEL_LEFT,                /**< 0x8000 - single                    */
			DPF_CHANNEL_CENTER,              /**< 0x4000 - single                    */
			DPF_CHANNEL_RIGHT,               /**< 0x2000 - single                    */
			DPF_CHANNEL_SIDE_LEFT,           /**< 0x1000 - single                    */
			DPF_CHANNEL_SIDE_RIGHT,          /**< 0x0800 - single                    */
			DPF_CHANNEL_CENTER_LEFT,         /**< 0x0400 - paired                    */
			DPF_CHANNEL_BACK_LEFT,           /**< 0x0200 - paired                    */
			DPF_CHANNEL_BACK_CENTER,         /**< 0x0100 - single                    */
			DPF_CHANNEL_TOP_SURROUND,        /**< 0x0080 - single                    */
			DPF_CHANNEL_SIDE_LEFT,           /**< 0x0040 - paired, "direct surround" */
			DPF_CHANNEL_LEFT_WIDE,           /**< 0x0020 - paired                    */
			DPF_CHANNEL_LEFT_FRONT_HEIGHT,   /**< 0x0010 - paired                    */
			DPF_CHANNEL_CENTER_FRONT_HEIGHT, /**< 0x0008 - single                    */
			DPF_CHANNEL_LEFT_TOP_MIDDLE,     /**< 0x0004 - paired                    */
			DPF_CHANNEL_LFE,                 /**< 0x0002 - single, "LFE2"            */
			DPF_CHANNEL_LFE                  /**< 0x0001 - single                    */
	};
#pragma	section("Seg_Dolby_Kernel_Data_L3")
	const uint8_t outputmap_pairs[UDC_OUTPUTMAP_LENGTH] =
	{
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_CENTER_RIGHT,
		DPF_CHANNEL_BACK_RIGHT,
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_SIDE_RIGHT,
		DPF_CHANNEL_RIGHT_WIDE,
		DPF_CHANNEL_RIGHT_FRONT_HEIGHT,
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_RIGHT_TOP_MIDDLE,
		DPF_CHANNEL_UNUSED,
		DPF_CHANNEL_UNUSED,
	};

	#define CHANBIT(A)                      (((unsigned)0x8000) >> (A))
	#define CHAN_EXISTS_IN_OUTMAP(A,B)		((CHANBIT(A)) & (B))
	#define IS_OUTMAP_PAIR(A)				((CHANBIT(A)) & ((unsigned short)0x0674))

	#if defined (DOLBY_THD) || defined (DOLBY_MAT)
#pragma	section("Seg_MAT_Data_L3")
	char p_mat_dec_static_mem[143655];//150000

#pragma	section("Seg_MAT_Data_L3")
	char p_mat_dec_dynamic_mem[30000];

#pragma	section("Seg_MAT_Data_L3")
	int mat_pstate_structure[8912];

#pragma	section("Seg_MAT_Data_L3")
	int mat_input_buffer[7680];


#pragma	section("Seg_MAT_Kernel_Data_L3")
	int mat_output_buffer[1000];

#pragma	section("Seg_MAT_Data_L3")
	int THD_done=0;

#pragma	section("Seg_MAT_Data_L3")
	char metadata_payload_pstate[128][4096];

#pragma	section("Seg_MAT_Data_L3")
	int IEC_MAT_Buf[TRUEHD_INPUTBUFFERSIZE];


#pragma	section("Seg_MAT_Data_L3")
	unsigned char evo_payload[0x4000];


#pragma	section("Seg_THD_Kernel_Data_L3")
	char TrueHDLibvar[800];

#pragma	section("Seg_THD_Kernel_Data_L3")
	char TrueHDLibstruct[1024];

#pragma	section("Seg_THD_Kernel_Data_L3")//seg_lib_data_l2
	char TrueHDLibEvolutionStruct[74344];


	#ifndef DOLBY_L2_BUFFER_POINTER
	#pragma section("Seg_THD_Kernel_Data_L3")
	char evo_buf[12630];
	#endif/* DOLBY_L2_BUFFER_POINTER */
	/*section("Seg_THD_Data_L2")
	char evo_buf[12630];*/
	/*Check the PM data bus access*/
#pragma	section("Seg_THD_Data_L3")
	int pm Smooth_a[3]={0x5470b33d,0x5470b33d,0x82a3859a};

#pragma	section("Seg_THD_Data_L3")
	int pm Smooth_b[3]={0x2a7057cd,0x2a7057cd,0x815382be};

#pragma	section("Seg_THD_Data_L3")
	int pm Smooth_c[3]={0x1546475e,0x1546475e,0x80aa323b};

#pragma	section("Seg_THD_Data_L3")
	int pm Smoothing_filter[3];

#pragma	section("Seg_THD_Data_L3")
	short pm mat_coef_A_B_Buf[4][16][8];

#pragma	section("Seg_THD_Data_L3")
	int   pm mat_coef_C_Buf[4][16][16];

#pragma	section("Seg_THD_Data_L3")
	int   pm del_coef_C_Buf[4][16][16];

#pragma	section("Seg_THD_Data_L3")
	int   pm mat_coef_c;

#pragma	section("Seg_THD_Data_L3")
	int   pm del_coef_c;

#pragma	section("Seg_THD_Data_L3")
	short pm dither_coef_1;

#pragma section("Seg_THD_Data_L3")
	short pm Filt_A_Coeff[4][16][8];
	#pragma section("Seg_THD_Data_L3")
	short pm Filt_B_Coeff[4][16][4];
	#pragma section("Seg_THD_Data_L3")
	short pm	*Filter_coeff_A;


	/*#pragma align 32
	section("Seg_THD_Data_L1")
	char L1_block0_lib_Memory[32000];	//42872//31647 for TrueHD*/

	/******************************************************************************
	 * 						Macro define Section
	 *****************************************************************************/
	#define AR_SPEAKER_L_R_INDEX       (0)  /**< L/R       (2 speakers) */
	#define AR_SPEAKER_C_INDEX         (1)  /**< C         (1 speaker)  */
	#define AR_SPEAKER_LFE_INDEX       (2)  /**< LFE       (1 speaker)  */
	#define AR_SPEAKER_LS_RS_INDEX     (3)  /**< Ls/Rs     (2 speakers) */
	#define AR_SPEAKER_LRS_RRS_INDEX   (4)  /**< Lrs/Rrs   (2 speakers) */

	#define AR_SPEAKER_CS_INDEX        (5)  /**< Cs        (1 speaker)  */
	#define AR_SPEAKER_LC_RC_INDEX     (6)  /**< Lc/Rc     (2 speakers) */
	#define AR_SPEAKER_LW_RW_INDEX     (7)  /**< Lw/Rw     (2 speakers) */

	#define AR_SPEAKER_LFH_RFH_INDEX   (8)  /**< Lfh/Rfh   (2 speakers) */
	#define AR_SPEAKER_LTF_RTF_INDEX   (9)  /**< Ltf/Rtf   (2 speakers) */
	#define AR_SPEAKER_LTM_RTM_INDEX   (10) /**< Ltm/Rtm   (2 speakers) */
	#define AR_SPEAKER_LTR_RTR_INDEX   (11) /**< Ltr/Rtr   (2 speakers) */
	#define AR_SPEAKER_LRH_RRH_INDEX   (12) /**< Lrh/Rrh   (2 speakers) */

	#define AR_SPEAKER_LSC_RSC_INDEX   (13) /**< Lsc/Rsc   (2 speakers) */
	#define AR_SPEAKER_LS1_RS1_INDEX   (14) /**< Ls1/Rs2   (2 speakers) */
	#define AR_SPEAKER_LS2_RS2_INDEX   (15) /**< Ls2/Rs2   (2 speakers) */
	#define AR_SPEAKER_LRS1_RRS1_INDEX (16) /**< Lrs1/Rrs1 (2 speakers) */
	#define AR_SPEAKER_LRS2_RRS2_INDEX (17) /**< Lrs2/Rrs2 (2 speakers) */
	#define AR_SPEAKER_LCS_RCS_INDEX   (18) /**< Lcs/Rcs   (2 speakers) */
	/** @} */

	/** @brief Limit of speaker mask indices */
	//#define AR_SPEAKER_MASK_MAX_INDEX (AR_SPEAKER_LCS_RCS_INDEX)


	/* Decoder channel assignment bit positions                                                       */
	#define DTHDI_DEC_BIT_POS_L                 (0)    /* Main (Left/Right): 2 Channels               */
	#define DTHDI_DEC_BIT_POS_R                 (1)    /* Main (Left/Right): 2 Channels               */
	#define DTHDI_DEC_BIT_POS_C                 (2)    /* Centre: 1 Channel                           */
	#define DTHDI_DEC_BIT_POS_LFE               (3)    /* LFE: 1 Channel                              */
	#define DTHDI_DEC_BIT_POS_LS                (4)    /* Surrounds (Ls/Rs): 2 Channels               */
	#define DTHDI_DEC_BIT_POS_RS                (5)    /* Surrounds (Ls/Rs): 2 Channels               */
	#define DTHDI_DEC_BIT_POS_LVH               (6)    /* Front Highs (Lvh/Rvh): 2 Channels           */
	#define DTHDI_DEC_BIT_POS_RVH               (7)    /* Front Highs (Lvh/Rvh): 2 Channels           */
	#define DTHDI_DEC_BIT_POS_LC                (8)    /* Inner Fronts (Lc/Rc): 2 Channels            */
	#define DTHDI_DEC_BIT_POS_RC                (9)    /* Inner Fronts (Lc/Rc): 2 Channels            */
	#define DTHDI_DEC_BIT_POS_LRS               (10)   /* Rears (Lrs/Rrs): 2 Channels                 */
	#define DTHDI_DEC_BIT_POS_RRS               (11)   /* Rears (Lrs/Rrs): 2 Channels                 */
	#define DTHDI_DEC_BIT_POS_CS                (12)   /* Centre Surround (Cs): 1 Channel             */
	#define DTHDI_DEC_BIT_POS_TS                (13)   /* Top (Ts): 1 Channel                         */
	#define DTHDI_DEC_BIT_POS_LSD               (14)   /* Surround Directs (Lsd/Rsd): 2 Channels      */
	#define DTHDI_DEC_BIT_POS_RSD               (15)   /* Surround Directs (Lsd/Rsd): 2 Channels      */
	#define DTHDI_DEC_BIT_POS_LW                (16)   /* Front Wide (Lw/Rw): 2 Channels              */
	#define DTHDI_DEC_BIT_POS_RW                (17)   /* Front Wide (Lw/Rw): 2 Channels              */
	#define DTHDI_DEC_BIT_POS_CVH               (18)   /* Centre Front High (Cvh): 1 Channel          */
	#define DTHDI_DEC_BIT_POS_LFE2              (19)   /* LFE2: 1 Channel                             */
	#define DTHDI_DEC_BIT_POS_LTS               (20)   /* Top Surrounds (Lts/Rts): 2 Channels         */
	#define DTHDI_DEC_BIT_POS_RTS               (21)   /* Top Surrounds (Lts/Rts): 2 Channels         */
	#define DTHDI_DEC_BIT_POS_S                 (22)   /* Mono Surround (S): 1 Channel                */
	#define DTHDI_DEC_BIT_POS_LRH               (23)   /* Rear Highs (Lrh/Rrh): 2 Channels            */
	#define DTHDI_DEC_BIT_POS_RRH               (24)   /* Rear Highs (Lrh/Rrh): 2 Channels            */
	#define DTHDI_DEC_BIT_POS_X1                (25)   /* Tactile 1 (X1): 1 Channel                   */
	#define DTHDI_DEC_BIT_POS_X2                (26)   /* Tactile 2 (X2): 1 Channel                   */
	#define DTHDI_DEC_BIT_POS_OBJ               (27)   /* Object                                      */
	#define DTHDI_DEC_BIT_POS_SFIELD            (28)   /* Spatial format audio                        */
	#define DTHDI_DEC_BIT_POS_COUNT             (29)   /* Channel assignment bit position count       */

	/**************************************************************************************************
	 *  Decoder channel assignment flags (ORed together to create channel configurations)
	 * Note that these channel assignments require a 32-bit integer to contain them
	 **************************************************************************************************/
	#define DTHDI_DEC_CHAN_ASSIGN_NOT_PRESENT   (0)
	#define DTHDI_DEC_CHAN_ASSIGN_L             (1 << DTHDI_DEC_BIT_POS_L)
	#define DTHDI_DEC_CHAN_ASSIGN_R             (1 << DTHDI_DEC_BIT_POS_R)
	#define DTHDI_DEC_CHAN_ASSIGN_C             (1 << DTHDI_DEC_BIT_POS_C)
	#define DTHDI_DEC_CHAN_ASSIGN_LFE           (1 << DTHDI_DEC_BIT_POS_LFE)
	#define DTHDI_DEC_CHAN_ASSIGN_LS            (1 << DTHDI_DEC_BIT_POS_LS)
	#define DTHDI_DEC_CHAN_ASSIGN_RS            (1 << DTHDI_DEC_BIT_POS_RS)
	#define DTHDI_DEC_CHAN_ASSIGN_LVH           (1 << DTHDI_DEC_BIT_POS_LVH)
	#define DTHDI_DEC_CHAN_ASSIGN_RVH           (1 << DTHDI_DEC_BIT_POS_RVH)
	#define DTHDI_DEC_CHAN_ASSIGN_LC            (1 << DTHDI_DEC_BIT_POS_LC)
	#define DTHDI_DEC_CHAN_ASSIGN_RC            (1 << DTHDI_DEC_BIT_POS_RC)
	#define DTHDI_DEC_CHAN_ASSIGN_LRS           (1 << DTHDI_DEC_BIT_POS_LRS)
	#define DTHDI_DEC_CHAN_ASSIGN_RRS           (1 << DTHDI_DEC_BIT_POS_RRS)
	#define DTHDI_DEC_CHAN_ASSIGN_CS            (1 << DTHDI_DEC_BIT_POS_CS)
	#define DTHDI_DEC_CHAN_ASSIGN_TS            (1 << DTHDI_DEC_BIT_POS_TS)
	#define DTHDI_DEC_CHAN_ASSIGN_LSD           (1 << DTHDI_DEC_BIT_POS_LSD)
	#define DTHDI_DEC_CHAN_ASSIGN_RSD           (1 << DTHDI_DEC_BIT_POS_RSD)
	#define DTHDI_DEC_CHAN_ASSIGN_LW            (1 << DTHDI_DEC_BIT_POS_LW)
	#define DTHDI_DEC_CHAN_ASSIGN_RW            (1 << DTHDI_DEC_BIT_POS_RW)
	#define DTHDI_DEC_CHAN_ASSIGN_CVH           (1 << DTHDI_DEC_BIT_POS_CVH)
	#define DTHDI_DEC_CHAN_ASSIGN_LFE2          (1 << DTHDI_DEC_BIT_POS_LFE2)
	#define DTHDI_DEC_CHAN_ASSIGN_LTS           (1 << DTHDI_DEC_BIT_POS_LTS)
	#define DTHDI_DEC_CHAN_ASSIGN_RTS           (1 << DTHDI_DEC_BIT_POS_RTS)
	#define DTHDI_DEC_CHAN_ASSIGN_S             (1 << DTHDI_DEC_BIT_POS_S)
	#define DTHDI_DEC_CHAN_ASSIGN_LRH           (1 << DTHDI_DEC_BIT_POS_LRH)
	#define DTHDI_DEC_CHAN_ASSIGN_RRH           (1 << DTHDI_DEC_BIT_POS_RRH)
	#define DTHDI_DEC_CHAN_ASSIGN_X1            (1 << DTHDI_DEC_BIT_POS_X1)
	#define DTHDI_DEC_CHAN_ASSIGN_X2            (1 << DTHDI_DEC_BIT_POS_X2)
	#define DTHDI_DEC_CHAN_ASSIGN_OBJ           (1 << DTHDI_DEC_BIT_POS_OBJ)
	#define DTHDI_DEC_CHAN_ASSIGN_SFIELD        (1 << DTHDI_DEC_BIT_POS_SFIELD)


	/* Decoder channel assignment flags for speakers that must occur in pairs                         */
	/* Main (Left/Right): 2 Channels                                                                  */
	#define DTHDI_DEC_CHAN_ASSIGN_L_R       ((DTHDI_DEC_CHAN_ASSIGN_L)   | (DTHDI_DEC_CHAN_ASSIGN_R)  )

	/* Surrounds (Ls/Rs): 2 Channels                                                                  */
	#define DTHDI_DEC_CHAN_ASSIGN_LS_RS     ((DTHDI_DEC_CHAN_ASSIGN_LS)  | (DTHDI_DEC_CHAN_ASSIGN_RS) )

	/* Front Highs (Lvh/Rvh): 2 Channels                                                              */
	#define DTHDI_DEC_CHAN_ASSIGN_LVH_RVH   ((DTHDI_DEC_CHAN_ASSIGN_LVH) | (DTHDI_DEC_CHAN_ASSIGN_RVH))

	/* Inner Fronts (Lc/Rc): 2 Channels                                                               */
	#define DTHDI_DEC_CHAN_ASSIGN_LC_RC     ((DTHDI_DEC_CHAN_ASSIGN_LC)  | (DTHDI_DEC_CHAN_ASSIGN_RC) )

	/* Rears (Lrs/Rrs): 2 Channels                                                                    */
	#define DTHDI_DEC_CHAN_ASSIGN_LRS_RRS   ((DTHDI_DEC_CHAN_ASSIGN_LRS) | (DTHDI_DEC_CHAN_ASSIGN_RRS))

	/* Surround Directs (Lsd/Rsd): 2 Channels                                                         */
	#define DTHDI_DEC_CHAN_ASSIGN_LSD_RSD   ((DTHDI_DEC_CHAN_ASSIGN_LSD) | (DTHDI_DEC_CHAN_ASSIGN_RSD))

	/* Front Wide (Lw/Rw): 2 Channels                                                                 */
	#define DTHDI_DEC_CHAN_ASSIGN_LW_RW     ((DTHDI_DEC_CHAN_ASSIGN_LW)  | (DTHDI_DEC_CHAN_ASSIGN_RW) )

	/* Top Surrounds (Lts/Rts): 2 Channels                                                            */
	#define DTHDI_DEC_CHAN_ASSIGN_LTS_RTS   ((DTHDI_DEC_CHAN_ASSIGN_LTS) | (DTHDI_DEC_CHAN_ASSIGN_RTS))


	/* API macros to set and remove a single channel assignment in a channel configuration            */
	#define DTHDI_SET_CHAN_ASSIGN_FLAG(ch_cfg, chan_assign)     ((ch_cfg) | (chan_assign)   )
	#define DTHDI_CLEAR_CHAN_ASSIGN_FLAG(ch_cfg, chan_assign)   ((ch_cfg) & (~(chan_assign)))

	/* API Decoder PCM Output Channel Configuration IDs                                               */

	/* Channel configuration 1 = 1/0   (C)                                                            */
	#define DTHDI_DEC_CH_CFG_1                  (   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            )

	/* Channel configuration 2 = 2/0   (L, R)                                                         */
	#define DTHDI_DEC_CH_CFG_2                  (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            )

	/* Channel configuration 3 = 3/0   (L, R, C, LFE)                                                 */
	#define DTHDI_DEC_CH_CFG_3                  (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            )

	/* Channel configuration 6 = 2/2   (L, R, LFE, Ls, Rs)                                            */
	#define DTHDI_DEC_CH_CFG_6                  (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            )

	/* Channel configuration 7 = 3/2   (L, R, C, LFE, Ls, Rs)                                         */
	#define DTHDI_DEC_CH_CFG_7                  (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            )

	/* Channel configuration 8 = 3/0/1 (L, R, C, LFE, Cvh)                                            */
	#define DTHDI_DEC_CH_CFG_8                  (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_CVH)                        \
	                                            )

	/* Channel configuration 9 = 2/2/1 (L, R, LFE, Ls, Rs, Ts)                                        */
	#define DTHDI_DEC_CH_CFG_9                  (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_TS)                         \
	                                            )

	/* Channel configuration 10 = 3/2/1 (L, R, C, LFE, Ls, Rs, Ts)                                    */
	#define DTHDI_DEC_CH_CFG_10                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_TS)                         \
	                                            )

	/* Channel configuration 11 = 3/2/1 (L, R, CLFE, Ls, Rs, Cvh)                                     */
	#define DTHDI_DEC_CH_CFG_11                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_CVH)                        \
	                                            )

	/* Channel configuration 12 = 3/0/2 (L, R, C, LFE, Lc, Rc)                                        */
	#define DTHDI_DEC_CH_CFG_12                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LC_RC)                      \
	                                            )

	/* Channel configuration 13 = 2/2/2 (L, R, LFE, Ls, Rs, Lw, Rw)                                   */
	#define DTHDI_DEC_CH_CFG_13                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LW_RW)                      \
	                                            )

	/* Channel configuration 14 = 2/2/2 (L, R, LFE, Ls, Rs, Lvh, Rvh)                                 */
	#define DTHDI_DEC_CH_CFG_14                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LVH_RVH)                    \
	                                            )

	/* Channel configuration 15 = 2/2/2 (L, R, LFE, Ls, Rs, Lsd, Rsd)                                 */
	#define DTHDI_DEC_CH_CFG_15                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LSD_RSD)                    \
	                                            )

	/* Channel configuration 16 = 2/2/2 (L, R, LFE, Ls, Rs, Lrs, Rrs)                                 */
	#define DTHDI_DEC_CH_CFG_16                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LRS_RRS)                    \
	                                            )

	/* Channel configuration 17 = 3/2/2 (L, R, C, LFE, Ls, Rs, Lc, Rc)                                */
	#define DTHDI_DEC_CH_CFG_17                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LC_RC)                      \
	                                            )

	/* Channel configuration 18 = 3/2/2 (L, R, C, LFE, Ls, Rs, Lw, Rw)                                */
	#define DTHDI_DEC_CH_CFG_18                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LW_RW)                      \
	                                            )

	/* Channel configuration 19 = 3/2/2 (L, R, C, LFE, Ls, Rs, Lvh, Rvh)                              */
	#define DTHDI_DEC_CH_CFG_19                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LVH_RVH)                    \
	                                            )

	/* Channel configuration 20 = 3/2/2 (L, R, C, LFE, Ls, Rs, Lsd, Rsd)                              */
	#define DTHDI_DEC_CH_CFG_20                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LSD_RSD)                    \
	                                            )

	/* Channel configuration 21 = 3/2/2 (L, R, C, LFE, Ls, Rs, Lrs, Rrs)                              */
	#define DTHDI_DEC_CH_CFG_21                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LRS_RRS)                    \
	                                            )

	/* Channel configuration 22 = 3/2/2 (L, R, C, LFE, Ls, Rs, Ts, Cvh)                               */
	#define DTHDI_DEC_CH_CFG_22                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_TS)                         \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_CVH)                        \
	                                            )

	/* Channel configuration 28 = 3/2/2 (L, R, C, LFE, Ls, Rs, Lts, Rts)                              */
	#define DTHDI_DEC_CH_CFG_28                 (   (DTHDI_DEC_CHAN_ASSIGN_L_R)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_C)                          \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LFE)                        \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LS_RS)                      \
	                                            |   (DTHDI_DEC_CHAN_ASSIGN_LTS_RTS)                    \
	                                            )

	/* Decode the 8-channel presentation with the channel configuration defined by the bitstream      */
	/* This special output configuration decodes all available output channels; check return values   */
	/* from dthdi_dec_process_au to determine the channel assignment of the output PCM                */
	#define DTHDI_DEC_CH_CFG_RAW                ((1 << DTHDI_DEC_BIT_POS_COUNT) - 1)

	/* Dolby TrueHD PCM output buffer channel location indexes.                                       */
	/* These values represent the index into the output PCM buffer of each decoded PCM channel.       */
	/* E.g., after a call to dthdi_dec_process_au, the left channel audio of the nth output is in     */
	/*          a_pcmout_op[n].p_output_buffer->ppdata[DTHDI_DEC_OUTPUT_CHAN_INDEX_L]                 */
	/* X1 and X2 refer to the first and second occurence(s) of "extension channels", those whose bit  */
	/* position in the output channel configuration bitfield exceeds DTHDI_DEC_BIT_POS_RS             */
	/* Note: fixed channel locations are only applicable to 2-, 6- and 8-channel presentation outputs */

	#endif /* DOLBY_THD */
	
#ifdef EXT_DNMIX
	extern int Cs_enable;
	extern int speakers_bitmask_Cs;
	extern int ext_dnmix_flag;
	extern int TrueHD_outchanconfigFromCmd;
	extern int centre_downmix_check_c1;
#endif

#ifdef EXT_DNMIX_DDP
	extern int DDPlus_outchanconfigFromCmd;
	extern int DDplus_OutChanConfig_Tx;
	extern int Center_flag_ddp_dmx;
	extern int Center_downmix_ddp;
	extern int Cs_downmix_ddp;
#endif	

	extern int Custom_Clock_Ratio;
	extern int Custom_MCLK_Mode;
#ifdef eARC_ENABLE
	extern int eARC_Mode;
	extern int eARC_Clock_Ratio;
#endif

	typedef struct dpf_node_channel_format_s
	{
	    int ground_channel_num;  /**< number of ground channels */
	    int height_channel_num;  /**< number of height channels */
	    int channel_num;         /**< ground + height + lfe     */
	    int _lfe;                 /**< is lfe channel present    */

	} dpf_node_channel_format;

#define CHAN_TO_BIT(A)     (1ULL << (A))
#define _DPF_CHANNELS_UNUSED 39
#define LSD_CHANNEL        (_DPF_CHANNELS_UNUSED + 0)
#define RSD_CHANNEL        (_DPF_CHANNELS_UNUSED + 1)
#define LFE2_CHANNEL       (_DPF_CHANNELS_UNUSED + 2)

/**
 * Macro that will create channels mask for provided input.
 * Each input parameter represents particualr channel.
 * For example:
 *   CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
 *   equals to 2^0 + 2^1 + 2^2 = 7  which is L/R/C configuration.
 *   ! ONLY Values {0, 1} are valid input for the macro.
 */
#define CH_MASK(c0,  c1,  c2,  c3,  c4,  c5,  c6,  c7,  c8,  c9,            \
				c10, c11, c12, c13, c14, c15, c16, c17, c18, c19,           \
				c20, c21, c22, c23, c24, c25, c26, c27, c28, c29,           \
				c30, c31, c32, c33, c34, c35, c36, c37, c38, c39)           \
				(                                                           \
				(c0 ) * CHAN_TO_BIT( DPF_CHANNEL_LEFT                 )  |  \
				(c1 ) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT                )  |  \
				(c2 ) * CHAN_TO_BIT( DPF_CHANNEL_CENTER               )  |  \
				(c3 ) * CHAN_TO_BIT( DPF_CHANNEL_LFE                  )  |  \
				(c4 ) * CHAN_TO_BIT( DPF_CHANNEL_BACK_LEFT            )  |  \
				(c5 ) * CHAN_TO_BIT( DPF_CHANNEL_BACK_RIGHT           )  |  \
				(c6 ) * CHAN_TO_BIT( DPF_CHANNEL_CENTER_LEFT          )  |  \
				(c7 ) * CHAN_TO_BIT( DPF_CHANNEL_CENTER_RIGHT         )  |  \
				(c8 ) * CHAN_TO_BIT( DPF_CHANNEL_BACK_CENTER          )  |  \
				(c9 ) * CHAN_TO_BIT( DPF_CHANNEL_SIDE_LEFT            )  |  \
				(c10) * CHAN_TO_BIT( DPF_CHANNEL_SIDE_RIGHT           )  |  \
				(c11) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_WIDE            )  |  \
				(c12) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_WIDE           )  |  \
				(c13) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_SCREEN          )  |  \
				(c14) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_SCREEN         )  |  \
				(c15) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_SUR_1           )  |  \
				(c16) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_SUR_1          )  |  \
				(c17) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_SUR_2           )  |  \
				(c18) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_SUR_2          )  |  \
				(c19) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_REAR_SUR_1      )  |  \
				(c20) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_REAR_SUR_1     )  |  \
				(c21) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_REAR_SUR_2      )  |  \
				(c22) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_REAR_SUR_2     )  |  \
				(c23) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_CENTER_SUR      )  |  \
				(c24) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_CENTER_SUR     )  |  \
				(c25) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_FRONT_HEIGHT    )  |  \
				(c26) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_FRONT_HEIGHT   )  |  \
				(c27) * CHAN_TO_BIT( DPF_CHANNEL_CENTER_FRONT_HEIGHT  )  |  \
				(c28) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_TOP_FRONT       )  |  \
				(c29) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_TOP_FRONT      )  |  \
				(c30) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_TOP_MIDDLE      )  |  \
				(c31) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_TOP_MIDDLE     )  |  \
				(c32) * CHAN_TO_BIT( DPF_CHANNEL_TOP_SURROUND         )  |  \
				(c33) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_TOP_REAR        )  |  \
				(c34) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_TOP_REAR       )  |  \
				(c35) * CHAN_TO_BIT( DPF_CHANNEL_LEFT_REAR_HEIGHT     )  |  \
				(c36) * CHAN_TO_BIT( DPF_CHANNEL_RIGHT_REAR_HEIGHT    )  |  \
				(c37) * CHAN_TO_BIT( LSD_CHANNEL                      )  |  \
				(c38) * CHAN_TO_BIT( RSD_CHANNEL                      )  |  \
				(c39) * CHAN_TO_BIT( LFE2_CHANNEL                     )  )
/* Indicate that there where errors in creating channels mask */
/**
 *  Defines for bit mask for particular input combination
 *  Those will be used in calculate_proper_downmix_mode and compared to mask calculated by get_speakers_mask
 *  to evaluate what is apropriate downmix table for current configuration
 */
			  /* CHANNELS                               L     C    Lrs    Lc    Cs    Rs    Rw   Rsc   Rs1   Rs2   Rrs1  Rrs2  Rcs   Rfh   Ltf   Ltm    Ts   Rtr   Rrh   Lsd   LFE2  */
			  /* CHANNELS                               |  R  | LFE | Rrs |  Rc |  Ls |  Lw | Lsc | Ls1 | Ls2 | Lrs1| Lrs2| Lcs | Lfh | Cvh | Rtf | Rtm | Ltr | Lrh | s| Rsd |    */
			  /* CHANNELS                               |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |     */
#define C                                       CH_MASK(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 1        */
#define L                                       CH_MASK(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*Single L channel   */
#define C_LFE                                   CH_MASK(0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 1  + LFE */
#define L_R                                     CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 2        *//*TRUHD_MODE: 2       */
#define L_R_LFE                                 CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 2  + LFE */
#define L_R_C_LFE                               CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 3  + LFE *//*TRUHD_MODE: 3  + LFE*/
#define L_R_LFE_CS                              CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 4  + LFE */
#define L_R_C_LFE_CS                            CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 5  + LFE */
#define L_R_LFE_LS_RS                           CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 6  + LFE *//*TRUHD_MODE: 6  + LFE*/
#define L_R_C_LFE_LS_RS                         CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 7  + LFE */
#define L_R_C_LFE_CVH                           CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 8  + LFE */
#define L_R_LFE_LS_RS_TS                        CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 9  + LFE */
#define L_R_C_LFE_LS_RS_TS                      CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 10 + LFE */
#define L_R_C_LFE_LS_RS_CVH                     CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 11 + LFE */
#define L_R_C_LFE_LFH_RFH                       CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define L_R_C_LFE_LC_RC                         CH_MASK(1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 12 + LFE */
#define L_R_C_LFE_LC_RC_CS                      CH_MASK(1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 12 + LFE */
#define L_R_C_LFE_LC_RC_TS                      CH_MASK(1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 12 + LFE */
#define L_R_LFE_LS_RS_LW_RW                     CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 13 + LFE */
#define L_R_LFE_LS_RS_LFH_RFH                   CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 14 + LFE */
#define L_R_LFE_LS_RS_LSD_RSD                   CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0)    /*DDP_MODE: 15 + LFE */
#define L_R_LFE_LS_RS_LRS_RRS                   CH_MASK(1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 16 + LFE */
#define L_R_LFE_LS_RS_LC_RC                     CH_MASK(1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define L_R_C_LFE_LS_RS_LC_RC                   CH_MASK(1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 17 + LFE *//*TRUHD_MODE: 17 + LFE*/
#define L_R_C_LFE_LS_RS_LW_RW                   CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 18 + LFE *//*TRUHD_MODE: 18 + LFE*/
#define L_R_C_LFE_LS_RS_LFH_RFH                 CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 19 + LFE *//*TRUHD_MODE: 19 + LFE*/
#define L_R_C_LFE_LS_RS_LSD_RSD                 CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0)    /*DDP_MODE: 20 + LFE *//*TRUHD_MODE: 20 + LFE*/
#define L_R_C_LFE_LS_RS_LRS_RRS                 CH_MASK(1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 21 + LFE *//*TRUHD_MODE: 21 + LFE*/
#define L_R_C_LFE_LS_RS_TS_CVH                  CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 22 + LFE */
#define L_R_LFE_LS_RS_CS                        CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 23 + LFE */
#define L_R_C_LFE_LS_RS_CS                      CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 24 + LFE */
#define L_R_C_LFE_LRS_RRS_CS                    CH_MASK(1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define L_R_C_LFE_LRS_RRS_TS                    CH_MASK(1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)
#define L_R_LFE_LS_RS_CS_TS                     CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 25 + LFE */
#define L_R_C_LFE_LS_RS_CS_CVH                  CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 26 + LFE */
#define L_R_C_LFE_LS_RS_CS_TS                   CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 27 + LFE */
#define L_R_C                                   CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE:  3       *//*TRUHD_MODE: 3       */
#define L_R_CS                                  CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE:  4       */
#define L_R_C_CS                                CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE:  5       */
#define L_R_LS_RS                               CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE:  6       *//*TRUHD_MODE: 6       */
#define L_R_LRS_RRS                             CH_MASK(1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define L_R_C_LS_RS                             CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE:  7       */
#define L_R_C_CVH                               CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE:  8       */
#define L_R_LS_RS_TS                            CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE:  9       */
#define L_R_C_LS_RS_TS                          CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 10       */
#define L_R_C_LS_RS_CVH                         CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 11       */
#define L_R_C_LC_RC                             CH_MASK(1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 12       */
#define L_R_C_LFH_RFH                           CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define L_R_LS_RS_LW_RW                         CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 13       */
#define L_R_LS_RS_LFH_RFH                       CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 14       */
#define L_R_LS_RS_LSD_RSD                       CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0)    /*DDP_MODE: 15       */
#define L_R_LS_RS_LRS_RRS                       CH_MASK(1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 16       */
#define L_R_C_LS_RS_LC_RC                       CH_MASK(1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 17       *//*TRUHD_MODE: 17      */
#define L_R_C_LS_RS_LC_RC_CVH                   CH_MASK(1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define L_R_C_LS_RS_LW_RW                       CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 18       *//*TRUHD_MODE: 18      */
#define L_R_C_LS_RS_LFH_RFH                     CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 19       *//*TRUHD_MODE: 19      */
#define L_R_C_LS_RS_LSD_RSD                     CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0)    /*DDP_MODE: 20       *//*TRUHD_MODE: 20      */
#define L_R_C_LS_RS_LRS_RRS                     CH_MASK(1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 21       *//*TRUHD_MODE: 21      */
#define L_R_C_LS_RS_TS_CVH                      CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 22       */
#define L_R_LS_RS_CS                            CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 23       */
#define L_R_C_LS_RS_CS                          CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 24       */
#define L_R_LS_RS_CS_TS                         CH_MASK(1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 25       */
#define L_R_C_LS_RS_CS_CVH                      CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 26       */
#define L_R_C_LS_RS_CS_TS                       CH_MASK(1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0)    /*DDP_MODE: 27       */
#define L_R_C_LFE_LS_RS_LTM_RTM                 CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0)    /* 5.1.2             */
#define L_R_C_LFE_LS_RS_LTF_RTF_LTR_RTR         CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0)    /* 5.1.4             */
#define L_R_C_LFE_LS_RS_LRS_RRS_LTM_RTM         CH_MASK(1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0)    /* 7.1.2             */
#define L_R_C_LFE_LS_RS_LRS_RRS_LTF_RTF_LTR_RTR CH_MASK(1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0)    /* 7.1.4             */
#define L_R_C_LFE_LS_RS_LFE2                    CH_MASK(1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)    /* 5.2               */
#define L_R_LFE_LS_RS_LRS_RRS_LFE2              CH_MASK(1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)    /* 7.2 without C     */
#define L_R_LFE_LS_RS_CS_LFE2                   CH_MASK(1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)    /* L, R, LFE, LS, RS, CS, LFE2 */
#define L_R_C_LFE_LS_RS_LRS_RRS_LFE2            CH_MASK(1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)    /* 7.2 */
#define L_R_LFE_LS_RS_LC_RC_CVH                 CH_MASK(1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)    /* 7.2 */
			  /* CHANNELS                               |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   */
			  /* CHANNELS                               L  |  C  | Lrs |  Lc |  Cs |  Rs |  Rw | Rsc | Rs1 | Rs2 | Rrs1| Rrs2| Rcs | Rfh | Ltf | Ltm |  Ts | Rtr | Rrh | Rsd |   */
			  /* CHANNELS                                  R    LFE   Rrs    Rc    Ls    Lw   Lsc   Ls1   Ls2   Lrs1  Lrs2  Lcs   Lfh   Cvh   Rtf   Rtm   Ltr   Lrh   Lsd   LFE2    */

#endif /* DOLBY_LIB */

int Mclk_192Khz = MCLK_192KHZ;
int Mclk_96Khz = MCLK_96KHZ;
int Mclk_48Khz = MCLK_48KHZ;

int Prev_Dolby_NeuralX_Enable = 0;

#endif /* SYSTEM_INCLUDE_SYSTEM_MODULES_H_ */
