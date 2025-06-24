/*****************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Codeid.h
*  Description      :   Used to identify which code module is currently running
*                       on Sharc processor. This is used by auto stream detect routine
	                    to identify whether the stream detected is the valid stream for the
	                    code module running on the processor currently
******************************************************************************/

/******************************************************************************
 * THISCODEID is used to identify which code module is currently
	running on Sharc processor. This is used by auto stream detect routine
	to identify whether the stream detected is the valid stream for the
	code module running on the processor currently
 *******************************************************************************/
#ifndef CODEID_H_
#define CODEID_H_

#include "..\src\system\Include\Commn.h"

#define DTSSYNCSIG1SHUFFLED	    0x7ffe
#define DTSSYNCSIG2SHUFFLED	    0x1fff
#define IEC958SHUFFLEDSIG	    0xf872

#define SYNCSIGPCMZERO	     0x00     // detection under progress 
#define SYNCSIGPCM	     	 0x01
#define SYNCSIGDOLBY	     0x02
#define SYNCSIGDTSLDCD	     0x03
#define SYNCSIGDTSDVD	     0x04
//#ifdef AAC_DEC
	#define SYNCSIGAAC       0x08
//#endif
#define SYNCSIGMPEGH         0x19
#define SYNCSIGWMAPRO		 0x09
#define SYNCSIGDDPLUS        0x0A
#define SYNCSIGTRUEHD		 0x0B
#define SYNCSIGDTSMA		 0x0C
#define SYNCSIGDTSHR    	 0x0D
#define SYNCSIGDTSLBR		 0x0E
#define SYNCSIGUNKNOWN	     0x0f    // detection under progress

#define FORCEPCM2            3
#define CUSTOMAUTODETECT1    0xA

//#ifdef MPEG4_AAC
#define AACSTREAMLENGTH        1024*2
/*MPEG-4 AAC*/
#define AACSTREAMLENGTH_HRLS		2048*2
#define AACSTREAMLENGTH_QRLS		4096*2
#define AACSTREAMLENGTH_DRLS		512*2
#define AACSTREAMLENGTH_LATM_LOAS0 	960*2
#define AACSTREAMLENGTH_LATM_LOAS1 	1920*2
#define AACSTREAMLENGTH_LATM_LOAS2 	1024*2
#define AACSTREAMLENGTH_LATM_LOAS3 	2048*2

#define AACBLOCKCOUNTMAX_HRLS   		64
#define AACBLOCKCOUNTMAX_QRLS   		128
#define AACBLOCKCOUNTMAX_DRHS   		16
#define AACBLOCKCOUNTMAX_LATM_LOAS0 	30
#define AACBLOCKCOUNTMAX_LATM_LOAS1		60
#define AACBLOCKCOUNTMAX_LATM_LOAS2  	32
#define AACBLOCKCOUNTMAX_LATM_LOAS3		64
//#endif

#define DTSSTREAM1LENGTH		0x400
#define DTSSTREAM2LENGTH		0x800
#define DTSSTREAM3LENGTH		0x1000
#define WMA0STREAMLENGTH		0x2000
#define WMA1STREAMLENGTH		0x1000
#define WMA2STREAMLENGTH		0x800
#define WMA3STREAMLENGTH		0x400
#define DTSHDHR2KFRAMELENGTH    0x4000
#define DTSHDHR1KFRAMELENGTH    0x2000
#define DTSHDHR512KFRAMELENGTH  0x1000
#define DTSHDSTREAMLENGTH		0x4000
#define DTSLBRSTREAMLENGTH		0x2000
#define TRUEHDSTREAMLENGTH		0x7800
#define DDPLUS0STREAMLENGTH     0x3000
#define DOLBYSTREAMLENGTH       3068//DOLBYSTREAMLENGTH =1536*2 - 4
#define MPEGL1STREAMLENGTH	 768
#define MPEGL2STREAMLENGTH	 2304
#define MPEGHSTREAMLENGTH 		0x8000


#define DOLBYBLOCKCOUNTMAX      48
#define DTSBLOCKCOUNTMAX0		8
#define DTSBLOCKCOUNTMAX1		16
#define DTSBLOCKCOUNTMAX2		32
#define DTSBLOCKCOUNTMAX3		64
#define DTSBLOCKCOUNTMAX4		128
#define MPEGHBLOCKCOUNTMAX      128*4
#define MPEGL1BLOCKCOUNTMAX     24
#define MPEGL2BLOCKCOUNTMAX     36
//#ifdef AAC_DEC
#define AACBLOCKCOUNTMAX        32
//#endif
#define DDPLUSBLOCKCOUNTMAX0     192
#define TRUEHDBLOCKCOUNTMAX0	 480
#define DTSHDBLOCKCOUNTMAX0		 256
#define DTSHDHR2KBLOCKCOUNTMAX0  256
#define DTSHDHR1KBLOCKCOUNTMAX0  128
#define DTSHDHR512KBLOCKCOUNTMAX0 64
#define DTSLBRBLOCKCOUNTMAX0	 128
#define WMABLOCKCOUNTMAX0		 128
#define WMABLOCKCOUNTMAX1		 64
#define WMABLOCKCOUNTMAX2		 32
#define WMABLOCKCOUNTMAX3		 16
#define BLOCKCOUNTMAX	        380*4	// 0.5 Sec at 48 Khz
#define UNFORMATDTSBLOCKCOUNTMAX0  8
#define UNFORMATDTSBLOCKCOUNTMAX1  16
#define UNFORMATDTSBLOCKCOUNTMAX2  32
#define UNFORMATDTSBLOCKCOUNTMAX3  64
#define UNFORMATDTSBLOCKCOUNTMAX4  128

#define SBPD_AUTO1 			0
#define SBPD_AUTO2 			1
#define SBPD_FORCE_OFF		2
#define SBPD_FORCE_EX		3
#define SBPD_FORCE_ES		4

//#define PCM_ID		      	 0x1234
//#define HALFSECVAL           5   // 4096 * 5 at 48 Khz is 0.426 sec 
#define PCMCOUNTMAX	      	 4096
#define MAYBEPCMCOUNT	     4096-1024
#define PREVPCCLEARCOUNTMAX  30720


#endif /* End of #ifndef CODEID_H_	*/

