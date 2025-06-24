
/*****************************************************************************
 *
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
 *
 *  Project          :  	21593SDK
 *  Organization     :  	Jasmin Infotech Private Limited,Chennai
 *  File Name        :		PostProcessing.c
 *  Description      :   	PostProcessing routines

 ******************************************************************************/
#pragma default_section(CODE,"Seg_Decoder_Code")

#include "../Include/Commn.h"
#include "../Include/Def_Struct.h"
#include "../Include/Extern_Core1.h"
#include "../Include/Function_Prototype.h"
#include "../Include/Codeid.h"
#ifdef DOLBY_LIB
#include "../Include/ar_speaker.h"
#endif

void PostProcessing_Routine()
{
	Control_DataVariable_Update();
	if( (Frmwk.StreamType_DTSX ==1)&& ((Frmwk.DTSX.Status.StreamType ==0x8)||(Frmwk.DTSX.Status.StreamType ==0x9)) )
	{
		DAP_Enable=0;
		DTS_DAPEnable=0;
	}

	if(DTS_AuroEnable == 0)
	{
		Control_Data_Update();
	}

	for(Frmwk.PP_Frmaecnt = 0;Frmwk.PP_Frmaecnt < Frmwk.PP_Framecnt_Loop;Frmwk.PP_Frmaecnt++)
	{
		Frmwk.IOP.Predac.wr_ptr_pp = Frmwk.IOP.Predac.wr_ptr + (Frmwk.PP_Frmaecnt * Frmwk.SampleBlock * NO_OF_PREDAC_CHANNEL *4) ;

#ifdef DOLBY_DAP
		if(DAP_Enable== 1)
		{
			if(Frmwk.OutputSampleRate<=2)
			{
#ifdef AAC_DEC
				if(Frmwk.StreamType == SYNCSIGAAC)
				{
				
					AAC_DAP_Input_Channel_Reorder();
				}
#endif
				if((Frmwk.DAP_OAR_Reinit == 1) && (DATMOS_HT_GRAPH_TYPE_EXTENDED == Frmwk.graph_type))
				{
#ifdef DOLBY_OAR
					Frmwk.OAR_Frmwk.SampleRate = (int) Freq_Table[Frmwk.OutputSampleRate];
					InitOARiModule();
#endif
					Frmwk.DAP_OAR_Reinit = 0;
				}
				else
					Frmwk.DAP_OAR_Reinit = 0;
#ifdef DTSX_DAP
				if(DTS_DAPEnable != 1)
#endif
				{
					fixtofloatConversion_Predacbuf();
				}

				OAR_DAP_Processing();
			}
			else
			{
				DAP_Enable = 0;
				Frmwk.DAP_krnl.DolbyUpmixer_Done_temp = 0;
			}
		}
#endif /* DOLBY_DAP */

#ifdef AURO_3D
		else if (AuroEngine_Enable == 1)
		{

			if ((Frmwk.StreamType ==1 || Frmwk.StreamType == 15)&&(Auro_Ds_flag ==1))
			{
				Auro_Loop_Count = 2;
			}
			else
			{
				Auro_Loop_Count = 1;
			}


			for (index_count =0; index_count< Auro_Loop_Count; index_count++)
			{
				for (int i=0; i<(sizeof(Noisegen_Temp_Buffer))/4; i++ )
				{
					Noisegen_Temp_Buffer[i]=0;
				}
				if ((Frmwk.StreamType ==1 || Frmwk.StreamType == 15)&&(Auro_Ds_flag ==1))
				{
					Auro_IP_Ptr = Auro_DS_Buffer + (index_count*BUFF_MAX_SIZE_IP_AURO);  // sample block * input ch
					Auro_IP_Stride =  0;
					Auro_OP_Ptr =  (int *) CustomerPP_Buffer + (index_count*BUFF_MAX_SIZE_AURO_HALF); // sample_block_Ds and Output ch
				}
				else if(DTS_AuroEnable == 1)
				{
					Auro_IP_Ptr =  (int *) AuroDTS_IP_Ptr;
					Auro_IP_Stride =  8;
				}
				else
				{
					Auro_IP_Ptr = (int *)Frmwk.IOP.Predac.wr_ptr_pp;
#ifdef FRAMEWORK_24CH
					Auro_IP_Stride = 16;  //24-8;
#else
					Auro_IP_Stride = 24; //32-8;
#endif
				}

				Copy_PredacExt_To_Auro_InBuff(Auro_IP_Ptr,Auro_IP_Stride);

			}
		}
		else
#endif
		{
			if(Frmwk.StreamType_DTSX == 0)
			{
				Frmwk.SampleBlock_PP = Frmwk.SampleBlock;
				Copy_PredacExt_To_PredacInt(); //Copies Predac External(256*NO_OF_PREDAC_CHANNEL) to internal buffer(256*16) as floating point data
			}


#ifdef AAC_DEC
			if((Frmwk.StreamType == SYNCSIGAAC) && (Frmwk.DTSX.NeuralX_enable != 1) && (Frmwk.DTSVX.DTS_VirtualX_Enable != 1) )
			{
				AAC_ChannelReorder_Enable = 1;

				Channel_PP_InputList[0] 	= Frmwk.AAC.AAC_Output_Channel_Config;
				Channel_PP_InputList[1]   	= Frmwk.ChannelReorder_AssignLines;
				Channel_PP_InputList[2]   	= (int)Predac_buffer_Int;
				Channel_PP_InputList[3]   	= (int)Predac_buffer_Int;
				Channel_PP_InputList[4]   	= BUFF_MAX_SIZE;
				Channel_PP_InputList[5]   	= (int)CustomerPP_Buffer;
				Channel_PP_InputList[6]   	= (int)CustomerPP_Buffer;
				Channel_PP_InputList[7]   	= PP_BUFF_MAX_SIZE;

				Channel_Reorder_lib(Channel_PP_InputList);

				AAC_ChannelReorder_Enable = 0;
			}
			else
#endif
#ifdef  CUSTOMER_PP
			{
				PreDac_Int_To_Cust_PP_Buffer();
			}

		}

		if(AuroEngine_Enable == 1 || Frmwk.DTSX.NeuralX_enable == 1 || Frmwk.DTSVX.DTS_VirtualX_Enable == 1 || Frmwk.StreamType_DTSX == 1)
		{
			FixToFloatConversion();
		}

		if(DAP_Enable == 0)
		{
#ifdef FLOAT
			Frmwk.Customer_pp.Data_Format = FLOAT_PP; //Floating Point Processing
#else
			Frmwk.Customer_pp.Data_Format = 0; //Fixed Point Processing
#endif


			if(Frmwk.Customer_pp.Data_Format != FLOAT_PP)
			{
				FloatToFixConversion();
			}

			Customer_PP_kernel();

			if(Frmwk.Customer_pp.Data_Format == FLOAT_PP)
			{
				FloatToFixConversion();
			}

			Cust_PP_To_PreDac_Int_Buffer(); //Copies the data from CustomerPP_buffer(256*CUSTOMER_PP_CHANNELS) to Predac_buffer_Int(256*32)
#else
			FloatToFixConversion();
#endif
			if(Frmwk.StreamType_DTSX == 0)
			{
				Led2_Toggle_Routine();
				PreDac_Core1_Data_Copy();
				Predac_Buffer_Int_To_Predac_Buffer_Ext(); //Copies the data from predac internal buffer(256*32) to predac external buffer (256*NO_OF_PREDAC_CHANNEL)
			}
		}
	}
}
