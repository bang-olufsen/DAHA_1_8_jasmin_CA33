/***************************************************************************
*
 *  (C)Copyright Analog Devices Inc., India.
*  All rights reserved. Reproduction in whole or part is prohibited without
*  the written permission of the copyright owner.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Buff_Ptr_Defines.h
*  Description      :	Macro define Section for Dolby buffer pointers
******************************************************************************/
#include "Commn.h"
/*============== Dolby Decoder L1_BLOCK_0_BUFFER_POINTER offset Definitions==========================================*/
#define L1_BLOCK0_POINTER_OFFSET1		 (int*)L1_Block0_Start_Addr
#define L1_BLOCK0_POINTER_OFFSET2		 (int)L1_Block0_Start_Addr +50848
#define L1_BLOCK0_POINTER_OFFSET3		 (int)L1_Block0_Start_Addr +58528
#define L1_BLOCK0_POINTER_OFFSET4		 (int)L1_Block0_Start_Addr +60448
#define L1_BLOCK0_POINTER_OFFSET5		 (int)L1_Block0_Start_Addr +60708
#define L1_BLOCK0_POINTER_OFFSET6		 (int)L1_Block0_Start_Addr +60968
#define L1_BLOCK0_POINTER_OFFSET7		 (int)L1_Block0_Start_Addr +61228
#define L1_BLOCK0_POINTER_OFFSET8		 (int)L1_Block0_Start_Addr +61488
#define L1_BLOCK0_POINTER_OFFSET9		 (int)L1_Block0_Start_Addr +61748
#define L1_BLOCK0_POINTER_OFFSET10		 (int)L1_Block0_Start_Addr +62008
#define L1_BLOCK0_POINTER_OFFSET11		 (int)L1_Block0_Start_Addr +62268
/*==============================================================================*/
/*============== Dolby Decoder L1_BLOCK_2_BUFFER_POINTER offset Definitions==========================================*/
#define L1_BLOCK2_POINTER_OFFSET1		 (int*)(L1_Block2_Start_Addr)
#define L1_BLOCK2_POINTER_OFFSET2		 (int*)(L1_Block2_Start_Addr + 1528)
#define L1_BLOCK2_POINTER_OFFSET3		 (int*)(L1_Block2_Start_Addr + 10480)
#define L1_BLOCK2_POINTER_OFFSET4		 (float*)(L1_Block2_Start_Addr + 12432)
#define L1_BLOCK2_POINTER_OFFSET5		 (float*)(L1_Block2_Start_Addr + 12948)
#define L1_BLOCK2_POINTER_OFFSET6		 (int) (L1_Block2_Start_Addr + 13472)
/*==============================================================================*/
/*============== Dolby Decoder L2_BUFFER_POINTER offset Definitions==========================================*/
#ifdef DOLBY_L2_BUFFER_POINTER
#define L2_POINTER_OFFSET1		   (char*)L2_dm_start_Addr
#define L2_POINTER_OFFSET2    	   (int)(L2_dm_start_Addr + 169392)
#define	L2_POINTER_OFFSET3		   (int*)(L2_dm_start_Addr + 182024)
#define	L2_POINTER_OFFSET4		   (int*)(L2_dm_start_Addr + 304904)
#define	L2_POINTER_OFFSET5		   (int*)(L2_dm_start_Addr + 333576)
#define	L2_POINTER_OFFSET6		   (int*)(L2_dm_start_Addr + 419592)
#define	L2_POINTER_OFFSET7		   (int*)(L2_dm_start_Addr + 423408)
#define	L2_POINTER_OFFSET8		   (int*)(L2_dm_start_Addr + 502440)
#define	L2_POINTER_OFFSET9		   (int*)(L2_dm_start_Addr + 503960)
#define	L2_POINTER_OFFSET10		   (int*)(L2_dm_start_Addr + 504576)
#define	L2_POINTER_OFFSET11		   (int*)(L2_dm_start_Addr + 524256)
#define	L2_POINTER_OFFSET12		   (int*)(L2_dm_start_Addr + 526200)
#define	L2_POINTER_OFFSET13		   (int*)(L2_dm_start_Addr + 527872)
#define L2_POINTER_OFFSET14		   (int*)(L2_dm_start_Addr + 531120)
#define L2_POINTER_OFFSET15		   (int*)(L2_dm_start_Addr + 565016)
#define L2_POINTER_OFFSET16	       (int*)(L2_dm_start_Addr + 565036)
#define L2_POINTER_OFFSET17		   (int*)(L2_dm_start_Addr + 572224)
#define L2_POINTER_OFFSET18		   (int*)(L2_dm_start_Addr + 684792)
#define L2_POINTER_OFFSET19		   (int*)(L2_dm_start_Addr + 703608)
#define L2_POINTER_OFFSET20 	   (unsigned char*)(L2_dm_start_Addr + 712064)
#endif/* DOLBY_L2_BUFFER_POINTER */
/*==============================================================================*/
