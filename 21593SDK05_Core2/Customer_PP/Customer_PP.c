/*****************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Customer_PP.c
*  Description      :

******************************************************************************/
#include <System/Include/Def_Struct.h>
#include "Customer_PP.h"
#include "..\src\System\Include\Extern_Core2.h"

#pragma default_section(CODE,"Seg_CustomerPP_Code")
#pragma default_section(DATA,"Seg_CustomerPP_Data")
extern int loopcount_value;
extern int  alg_input_list[];

void Customer_Post_Processing(void)
{

	PreDac_Int_To_Cust_PP_Buffer();

#ifdef FLOAT
	Frmwk.Customer_pp.Data_Format = FLOAT_PP;
#endif

	if(Frmwk.Customer_pp.Data_Format == 1)
    {
	    fixtofloatConversion();
	}

	CustPPInputList[0] = (int)CustomerPP_Buffer;
	CustPPInputList[1] = Frmwk.SampleBlock*CUSTOMER_PP_CHANNELS;
	CustPPInputList[2] = Frmwk.SampleBlock ;
	CustPPInputList[3] = CUSTOMER_PP_CHANNELS;
	CustPPInputList[4] = Frmwk.Customer_pp.Data_Format;
	CustPPInputList[5] = Frmwk.Customer_pp.ChannelMask;
	CustPPInputList[6] = Frmwk.StreamType;
	CustPPInputList[7] = Frmwk.OutputSampleRate;
	CustPPInputList[8] = Frmwk.Customer_pp.Volume;

	CustomerPP_Gain_Control(CustPPInputList);

	if(Frmwk.Customer_pp.Data_Format == 1)
	{
		floattofixConversion();
	}

    Cust_PP_To_PreDac_Int_Buffer();

}


/******************************************************************************
*  Module Name        : CustomerPP_gain_control
*  Functionality      : CustPPInputList contains the parameter for
   *CustomerPPProcessBufferPtr;
	CustomerPPProcessBufferSize;
	Blocksize;
	Number_of_Channels;
	DataFormat;
	ChannelMask;
	StreamType;
	SamplingFrequency;,
*						DB_VALUE is used to set the dB level.
*  Input Parameters	  : Customer_PP_IO_buffer
*  Output Parameters  : None
******************************************************************************/
void CustomerPP_Gain_Control(int *CustPPInputList)
{
  #ifdef FLOAT
	 float *CustomerPPProcessBufferPtr;
	 float DB_VALUE;
  #else
	 int *CustomerPPProcessBufferPtr;
	 int DB_VALUE;
  #endif

	int CustomerPPProcessBufferSize;
	int Blocksize;
	int Number_of_Channels;
	int DataFormat;
	int ChannelMask;
	int StreamType;
	int SamplingFrequency;
	int Volume;

	#ifdef FLOAT
		CustomerPPProcessBufferPtr  = (float*)CustPPInputList[0];
	#else
		CustomerPPProcessBufferPtr  = (int*)CustPPInputList[0];
	#endif
	CustomerPPProcessBufferSize = CustPPInputList[1];
	Blocksize                   = CustPPInputList[2];
	Number_of_Channels          = CustPPInputList[3];
	DataFormat                  = CustPPInputList[4];
	ChannelMask                 = CustPPInputList[5];
	StreamType                  = CustPPInputList[6];
	SamplingFrequency           = CustPPInputList[7];
	Volume                      = CustPPInputList[8];

  if(DataFormat == 1)
  {

	switch(Volume)
	{
	  case 0:
		  DB_VALUE = 1.0;     // 0 db
		  break;

	  case 1:
	  	  DB_VALUE = 0.891;   // -1 db
	  	  break;

	  case 2:
	  	  DB_VALUE = 0.707;   //  -3 db
	  	  break;

	  case 3:
	  	  DB_VALUE = 0.501;   //  -6 db
	  	  break;

	  default:
	  	  break;
	}

	for(int i=0;i<(Blocksize*Number_of_Channels);i=(i+Number_of_Channels))
	{
		CustomerPPProcessBufferPtr[i] = ((CustomerPPProcessBufferPtr[i] * DB_VALUE));  //L channel
		CustomerPPProcessBufferPtr[i+1] = (CustomerPPProcessBufferPtr[i+1] * DB_VALUE);  //R channel
	}
  }
  else
  {
	acc80 Temp_val;
	switch(Volume)
	{
	  case 0:
	  	  DB_VALUE = 0x80000000;     // 0 db
	  	  break;

	  case 1:
	  	  DB_VALUE = 0x720C49BA;   // -1 db
	  	  break;

	  case 2:
	  	  DB_VALUE = 0x5A7EF9DB;   //  -3 db
	  	  break;

	  case 3:
	  	  DB_VALUE = 0x4020C49C;   //  -6 db
	  	  break;

	  default:
	  	  	  break;
	}

	for(int i=0;i<(Blocksize*Number_of_Channels);i=(i+Number_of_Channels))
	{
		Temp_val = A_mul_ssf (CustomerPPProcessBufferPtr[i], DB_VALUE);
		CustomerPPProcessBufferPtr[i] = sat_sf (Temp_val);
		Temp_val = A_mul_ssf (CustomerPPProcessBufferPtr[i+1], DB_VALUE);
		CustomerPPProcessBufferPtr[i+1] = sat_sf (Temp_val);
    }
  }
}

#ifdef CUSTOMER_PP
void CUSTOMER_PP_COMMAND(void)
{
	Frmwk.Customer_pp.Volume		= 	(Frmwk.Spi.PARAMETER_1)&0x3;
}
#endif
