/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Customer_PP.h
*  Description      :
******************************************************************************/
#include "../src/System/Include/Commn.h"
#include <builtins.h>
/*B&O Change Start */
#include "version.h"
/*B&O Change End */

section("Seg_CustomerPP_Data")
int CustPPInputList[20];
#ifdef CUSTOMER_PP
section("Seg_CustomerPP_Data")
#ifdef FLOAT
float CustomerPP_Buffer[NO_OF_SAMPLE_PROCESSING*CUSTOMER_PP_CHANNELS];
#else
int CustomerPP_Buffer[NO_OF_SAMPLE_PROCESSING*CUSTOMER_PP_CHANNELS];
#endif
int CustPPInputList[20];

/*B&O Change Start */
// Version Format
// V1.V2.V3.V4
// Note: V4 should be FIXED to the "DSP_Version_Info" variable (updated by Jasmin <.dlb>)
int DSP_Version_Info;	// (4 in this version)
int BO_Version_Info = (1<<12)*V1 + (1<<8)*V2 + (1<<4)*V3 + V4;
/*B&O Change End */


#endif
