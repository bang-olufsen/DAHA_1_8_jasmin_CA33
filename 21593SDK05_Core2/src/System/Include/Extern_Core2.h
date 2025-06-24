/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Extern_C.h
*  Description      :   Extern framework & ISR variables for C environment can be included here
******************************************************************************/


/*****************************************************************************
	OARi & OAR Variables
*****************************************************************************/
#ifndef EXTERN_CORE2_H
#define EXTERN_CORE2_H
#include "Commn.h"

extern int DecoderBlockSize;

/*****************************************************************************/
extern int Predac_buffer_Int_c2[];

extern int *addpredac_heap;
extern int *addpredac_rd_ptr;
extern int *addpredac_length;
extern int *addpredac_wr_ptr;

extern int pre_dac_ptr_sync;
extern int addpredac_ptr_sync;
extern int Stream_Type_frm_Core1;
extern int *Stream_Profile;
extern int No_Sample_Processing;

#ifdef CUSTOMER_PP
extern int CustPPInputList[];
#endif

#ifdef ADI_VIRTUAL
extern int Input_buffer[(256*8)];
extern int Output_buffer[(256*2)];
extern int *Input_buffer_ptr;
extern int *Output_buffer_ptr;
#endif
#endif /* EXTERN_CORE2_H_ */
