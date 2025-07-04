/***************************************************************************
*
*  (C)Copyright Analog Devices Inc., India.
*  All rights reserved. Reproduction in whole or part is prohibited without 
*  the written permission of the copyright owner.
*
*  Project          :  	Audio_RAMFramework
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Main.h
*  Description      :   All the global variables for framework can be included here
******************************************************************************/

#ifndef _MAIN_H_
#define _MAIN_H_

//#include "Commn.h"

//#ifdef DSD2PCM_DEC

.segment/bw seg_DSD_LibData;
.var predacwrptr.;	.global predacwrptr.;
.var Predac_length_Ext.;					.global Predac_length_Ext.;
.var Up_sampling2.;							.global Up_sampling2.;
.var DSD_Error_Kernel.;						.global DSD_Error_Kernel.;
.var OffsetCumBlockLength_Kernel. = 512;	.global OffsetCumBlockLength_Kernel.;   //256
.var OUT_DSD_GAIN_Kernel. = 1;				.global OUT_DSD_GAIN_Kernel.;	//Default gain ON
.var OUT_FORMAT_Kernel. = 3;				.global OUT_FORMAT_Kernel.;	//Default
.var DSD2PCM_IN_DSD_TYPE_Kernel. = 1;		.global DSD2PCM_IN_DSD_TYPE_Kernel. ;	//Default 128Fs
.var Prev_DSD2PCM_IN_DSD_TYPE_Kernel. = -1;	.global Prev_DSD2PCM_IN_DSD_TYPE_Kernel. ;
.var Reinitialise_Kernel.;					.global Reinitialise_Kernel.;
.var Prev_Upsampling.=-1;					.global Prev_Upsampling.;
.var OUT_DSD_GAIN.;							.global OUT_DSD_GAIN.;	//Default gain ON
.var OUT_FORMAT.;							.global OUT_FORMAT.;	//Default
.var DSD2PCM_OUT_FS. = 0;					.global DSD2PCM_OUT_FS.;//Default Fs , 1 * Fs
.var DSD2PCM_OUT_WORDWIDTH. = 2; 			.global DSD2PCM_OUT_WORDWIDTH.;	//Default o/p word width, 24 bits
.var DSD2PCM_OUT_DITHER. = 1;				.global DSD2PCM_OUT_DITHER.;	//Default Dither ON
.var Reinitialise.;							.global Reinitialise.;
.var OffsetCumBlockLength.;					.global OffsetCumBlockLength.;	//Value for 1 * FS
.var DSD2PCM_OUT_FS_LIB.;					.global DSD2PCM_OUT_FS_LIB.;
.var DSD2PCM_IN_DSD_TYPE.;				.global DSD2PCM_IN_DSD_TYPE.;
.var sampling_fs_micro_DSD_sru.;			.global sampling_fs_micro_DSD_sru.;
.var OutputSampleRate_DSD_sru.;				.global OutputSampleRate_DSD_sru.;
.var Input_Source. = 0 ;			.global Input_Source. ;
.var Prev_Input_Source.;			.global Prev_Input_Source. ;

.segment/bw seg_DSD_LibData;
.var NumInputChannel.;			.global NumInputChannel.;
.var LFE_Present. = 0;			.global	LFE_Present.;
.endseg;

.segment/bw seg_DSD_LibData;

#ifdef DSD_PCM_Passthrough
	.var WorkBuffer.[128*6];
#else
	.var WorkBuffer.[256*6*2];
#endif
.global WorkBuffer.;

//.var predacwrptr.[10000];	.global predacwrptr.;
.var LWorkBuf.[1024*3];	.global LWorkBuf.;
.var RWorkBuf.[1024*3];	.global RWorkBuf.;
.var WorkBuffer_Lib.;	.global WorkBuffer_Lib.;
.var LWorkBuf_Lib.;		.global LWorkBuf_Lib.;
.var RWorkBuf_Lib.;		.global RWorkBuf_Lib.;
.var DSD_Error.;		.global DSD_Error.;
.var iDone.;			.global iDone.;
.var Up_sampling2_Lib.;	.global Up_sampling2_Lib.;


.endseg;

//#endif
#endif

