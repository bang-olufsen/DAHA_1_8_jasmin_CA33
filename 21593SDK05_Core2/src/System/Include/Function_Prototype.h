/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Function_Prototypes.h
*  Description      :   Function_Prototypes are added.
******************************************************************************/
#ifndef SYSTEM_INCLUDE_FUNCTION_PROTOTYPE_H_
#define SYSTEM_INCLUDE_FUNCTION_PROTOTYPE_H_

#ifdef MDMA_COPY
void MDMA_init(void);
void MDMA_Copy(int BuffSize, int SrcBuff, int DstBuff);
#endif

void Predac_buffer_Int_to_Predac_buffer(void);
void Pre_Dac_Ptr_Update_Rd_C2(void);
void Pre_Dac_Ptr_Update(void);
void FreeMemoryAll(void);
void Init_Var(void);
void MCPCMDecoder(void);
void Shared_Memory_Var_Update(void);
void Control_DataVariable_Update(void);

#ifdef CUSTOMER_PP_C2
void Customer_Post_Processing(void);
#endif

void Init_Var_Fs();
void Init_Var();
void FreeMemoryAll();
int Free_AllotMemoryPackDac (int , int , int );
void Autodetect_MemoryAlloc();
void CustomerPP_Gain_Control(int *);
void Pre_Dac_Ptr_Update();
void PreDac_Buffer_Int_Rearrange();

void Command_Update(void);
void CommandProcessing(void);
void CUSTOMER_PP_COMMAND(void);
int PlayForgnd(void);
void Init_Struct(void);
void Enable_Cache(void);

void fixtofloatConversion_IntC2(void);
void floattofixConversion_IntC2(void);

#endif /* SYSTEM_INCLUDE_FUNCTION_PROTOTYPE_H_ */
