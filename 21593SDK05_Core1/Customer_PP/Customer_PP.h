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

section("Seg_CustomerPP_Data")
int CustPPInputList[20];
#ifdef CUSTOMER_PP
section("Seg_CustomerPP_Data")
#ifdef FLOAT
        float CustomerPP_Buffer[NO_OF_SAMPLE_PROCESSING*CUSTOMER_PP_CHANNELS];
#else
         int CustomerPP_Buffer[NO_OF_SAMPLE_PROCESSING*CUSTOMER_PP_CHANNELS];
#endif
#endif
