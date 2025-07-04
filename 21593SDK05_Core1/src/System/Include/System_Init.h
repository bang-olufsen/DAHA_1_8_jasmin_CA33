/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	System_Init.h
*  Description      :
******************************************************************************/
#ifndef SYSTEM_INCLUDE_SYSTEM_INIT_H_
#define SYSTEM_INCLUDE_SYSTEM_INIT_H_

#include <stdint.h>
#include <sys/platform.h>
#include <sys/adi_core.h>
#include <stdio.h>
#include <math.h>
#include <cdef21593.h>
#include "sru.h"
#include <sys/cache.h>
#include "Codeid.h"
#include "Commn.h"
#include "Extern_Core1.h"
#ifdef SPDIF_MODULE
#include <drivers/spdif/adi_spdif_rx_v1.h>
#endif
#ifdef __ADSPSC598_FAMILY__
#include <cdefSC598.h>
#else
#include <cdef21593.h>
#endif
#include <drivers/sport/adi_sport.h>
#include <services/dma/adi_dma.h>
#include <services/spu/adi_spu.h>
#include <services/pcg/adi_pcg.h>
#include <drivers/asrc/adi_asrc.h>
#include <drivers/sport/adi_sport.h>
#include "Def_Struct.h"
#include "TMU_ReadTemperature.h"

/**********************************************defines Declared**********************************************/

#define SMSIZE 4
#define DMSIZE 4
#define BUFF_SIZE 1024


#ifdef AURO_3D
static ADI_DMA_2D_MEM_TRANSFER Src_2DMemXfer;
static ADI_DMA_2D_MEM_TRANSFER Dest_2DMemXfer;
ADI_DMA_RESULT      eResult1;
#endif

#define SPORT0A_DMA_SPU_ID 63
#define SPORT0B_DMA_SPU_ID 64
#ifdef DSD2PCM_DEC
#define SPORT1A_DMA_SPU_ID 65
#endif
#define SPORT2A_DMA_SPU_ID 67
#ifdef BEO_Framework
#define SPORT2B_DMA_SPU_ID 68
#endif /*  BEO_Framework */
#define SPORT3A_DMA_SPU_ID 69
#define SPORT3B_DMA_SPU_ID 70
#define SPORT4A_DMA_SPU_ID 71
#define SPORT4B_DMA_SPU_ID 72

#ifdef SPDIF_MODULE
#define SPORT5A_DMA_SPU_ID 73
#endif
#define SPORT6A_DMA_SPU_ID 75


#ifdef __ADSPSC598_FAMILY__                 //SC_598_MDMA
#define MDMA0_SRC_SPU_ID  147
#define MDMA0_DST_SPU_ID  148
#define MDMA1_SRC_SPU_ID  149
#define MDMA1_DST_SPU_ID  150
#define MDMA3_SPU_ID	  136 //MAX BW MDMA
#else
#define MDMA0_SRC_SPU_ID  146
#define MDMA0_DST_SPU_ID  147
#define MDMA1_SRC_SPU_ID  148
#define MDMA1_DST_SPU_ID  149
#define MDMA3_SPU_ID	  135 //MAX BW MDMA
#endif

#define SPI0_TXDMA_SPU_ID  93
#define SPI0_RXDMA_SPU_ID  94
#define SPI1_TXDMA_SPU_ID  95
#define SPI1_RXDMA_SPU_ID  96
/**************************************************************************************************
 * 	Global Variable Declaration and Extern Section
 **************************************************************************************************/
extern int *run_flag;
extern int mdma_done;
extern int SPI_Device;

#ifdef I2S_TDM_MODE_ENABLE
extern int I2S_TDM_MODE;
extern int prev_I2S_TDM_Mode;
extern int *TX_SP4A_BUFFER_LCRSW0_BUF;
extern int *TX_SP4A_BUFFER_LsLsrRsRsr0_BUF;
extern int *TX_SP3A_BUFFER_Addch1ch3Addch2ch4_set0_BUF;
extern int *TX_SP3A_BUFFER_Addch5ch7Addch6ch8_set0_BUF;
extern int *TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0_BUF;
extern int *TX_SP6A_BUFFER_Addch13ch15ch14ch16_set0_BUF;
#endif

#pragma section("Seg_Tx_Dma_Bw")
uint32_t uiTapList[32];
#pragma section("Seg_Ex_Ds_Bw")
int FSTemp_spt;
#pragma section("Seg_Ex_Ds_Bw")
int Frame_Sync=0;

/*************************TRANSMITTER DESCRIPTION LIST STRUCTURE***********************/
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_1_SP4A;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_2_SP4A;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_3_SP4B;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_4_SP4B;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_5_SP3A;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_6_SP3A;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_7_SP3B;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_8_SP3B;
#pragma  section("Seg_List_Bw")
  	ADI_PDMA_DESC_LIST iDESC_LIST_9_SP6A;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_10_SP6A;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_11_SP2A;
#pragma  section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_12_SP2A;
  #ifdef BEO_Framework
#pragma section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_13_SP2B;
#pragma section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iDESC_LIST_14_SP2B;
  #endif /* BEO_Framework */


#pragma  section("Seg_List_Bw")
    static uint8_t SPORTMemory4A[ADI_SPORT_MEMORY_SIZE];
#pragma  section("Seg_List_Bw")
    static uint8_t SPORTMemory4B[ADI_SPORT_MEMORY_SIZE];
#pragma  section("Seg_List_Bw")
    static uint8_t SPORTMemory3A[ADI_SPORT_MEMORY_SIZE];
#pragma  section("Seg_List_Bw")
    static uint8_t SPORTMemory3B[ADI_SPORT_MEMORY_SIZE];
#pragma  section("Seg_List_Bw")
    static uint8_t SPORTMemory2A[ADI_SPORT_MEMORY_SIZE];
	  #ifdef BEO_Framework
#pragma section("Seg_List_Bw")
    static uint8_t SPORTMemory2B[ADI_SPORT_MEMORY_SIZE];
   #endif /*  BEO_Framework */
#pragma  section("Seg_List_Bw")
    static uint8_t SPORTMemory6A[ADI_SPORT_MEMORY_SIZE];

#ifdef SPDIF_MODULE
 /* Memory required for SPDIF driver */
#pragma section("Seg_List_Bw")
    static uint8_t SpdifRxMemory[ADI_SPORT_MEMORY_SIZE];
#pragma section("Seg_List_Bw")
	static uint8_t SPORTMemory5A[ADI_SPORT_MEMORY_SIZE];

  /****************RECEIVER DESCRIPTION LIST STRUCTURE*************************/
#pragma section("Seg_List_Bw")
    ADI_PDMA_DESC_LIST iSRC_LIST_1_SP5A;
#pragma section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iSRC_LIST_2_SP5A;
#endif
#pragma section("Seg_List_Bw")
    ADI_PDMA_DESC_LIST iSRC_LIST_1_SP0A;
#pragma section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iSRC_LIST_2_SP0A;
#pragma section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iSRC_LIST_3_SP0B;
#pragma section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iSRC_LIST_4_SP0B;
#ifdef DSD2PCM_DEC
#pragma section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iSRC_LIST_5_SP1A;
#pragma section("Seg_List_Bw")
	ADI_PDMA_DESC_LIST iSRC_LIST_6_SP1A;
#endif

#pragma section("Seg_List_Bw")
	static uint8_t SPORTMemory0A[ADI_SPORT_MEMORY_SIZE];
#pragma section("Seg_List_Bw")
	static uint8_t SPORTMemory0B[ADI_SPORT_MEMORY_SIZE];
#ifdef DSD2PCM_DEC
#pragma section("Seg_List_Bw")
	static uint8_t SPORTMemory1A[ADI_SPORT_MEMORY_SIZE];
#endif

/****************DMA Variable Declaration and Initialization Section *************************/

/* Memory to handle DMA Stream */
static uint8_t MemDmaStreamMem[ADI_DMA_STREAM_REQ_MEMORY];

/* DMA Stream Handle */
ADI_DMA_STREAM_HANDLE   hMemDmaStream;

/* Source DMA Handle */
static ADI_DMA_CHANNEL_HANDLE  hSrcDmaChannel;

/* Destination DMA Handle */
static ADI_DMA_CHANNEL_HANDLE  hDestDmaChannel;

/* Memory to handle DMA Stream */
static uint8_t MemDmaStreamMem1[ADI_DMA_STREAM_REQ_MEMORY];

/* DMA Stream Handle */
ADI_DMA_STREAM_HANDLE   hMemDmaStream1;

/* Source DMA Handle */
static ADI_DMA_CHANNEL_HANDLE  hSrcDmaChannel1;

/* Destination DMA Handle */
static ADI_DMA_CHANNEL_HANDLE  hDestDmaChannel1;


/* Memory to handle DMA Stream */
static uint8_t MemDmaStreamMem2[ADI_DMA_STREAM_REQ_MEMORY];

/* DMA Stream Handle */
ADI_DMA_STREAM_HANDLE   hMemDmaStream2;

/* Source DMA Handle */
static ADI_DMA_CHANNEL_HANDLE  hSrcDmaChannel2;

/* Destination DMA Handle */
static ADI_DMA_CHANNEL_HANDLE  hDestDmaChannel2;
/****************ASRC Variable Declaration and Initialization Section *************************/

uint8_t gAsrcMem0[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE  hAsrc0    = NULL;

uint8_t gAsrcMem1[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE  hAsrc1    = NULL;

uint8_t gAsrcMem2[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE  hAsrc2    = NULL;

uint8_t gAsrcMem3[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE  hAsrc3    = NULL;

#ifdef BEO_Framework
uint8_t gAsrcMem4[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE  hAsrc4    = NULL;
uint8_t gAsrcMem5[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE  hAsrc5    = NULL;
uint8_t gAsrcMem6[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE  hAsrc6    = NULL;
uint8_t gAsrcMem7[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE  hAsrc7    = NULL;
#endif /* BEO_Framework */
/****************SPORT Variable Declaration and Initialization Section *************************/
#ifdef SPDIF_MODULE
ADI_SPORT_HANDLE hSPORT5ARx;
ADI_SPDIF_RX_HANDLE hSpdifRx;
#endif
ADI_SPORT_HANDLE hSPORT0ARx;
ADI_SPORT_HANDLE hSPORT0BRx;
#ifdef DSD2PCM_DEC
ADI_SPORT_HANDLE hSPORT1ARx;
#endif

ADI_SPORT_HANDLE hSPORT4ATx;
ADI_SPORT_HANDLE hSPORT4BTx;
ADI_SPORT_HANDLE hSPORT3ATx;
ADI_SPORT_HANDLE hSPORT3BTx;
ADI_SPORT_HANDLE hSPORT2ATx;
#ifdef BEO_Framework
ADI_SPORT_HANDLE hSPORT2BTx;
#endif /* BEO_Framework */
ADI_SPORT_HANDLE hSPORT6ATx;


ADI_SPORT_RESULT Result;


/* Global SPORT Array Handle */
static ADI_SPORT_HANDLE SportTxDai1Array[3];
#ifdef BEO_Framework
static ADI_SPORT_HANDLE SportTxDai0Array[4];
#else
static ADI_SPORT_HANDLE SportTxDai0Array[3];
#endif /* BEO_Framework */

#ifdef DSD2PCM_DEC
static ADI_SPORT_HANDLE SportRxDai0Array[3];
#else
static ADI_SPORT_HANDLE SportRxDai0Array[2];
#endif
#ifdef SPDIF_MODULE
static ADI_SPORT_HANDLE SportRxDai1Array[1];
#endif
/*GLobal sport group handle */
ADI_GLOBAL_SPORT_HANDLE hDai1Group0Tx;
ADI_GLOBAL_SPORT_HANDLE hDai0Group0Tx;
ADI_GLOBAL_SPORT_HANDLE hDai0Group1Rx;
#ifdef SPDIF_MODULE
ADI_GLOBAL_SPORT_HANDLE hDai1Group1Rx;
#endif
extern int Mclk_192Khz;
extern int Mclk_96Khz;
extern int Mclk_48Khz;

#ifdef ASRC_ENABLE
int ASRC_Enable = 0;
int ASRC_Samplerate = 0;
int FS_Div_Value = 0;
#endif
#endif
