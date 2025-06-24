/***************************************************************************
 *
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
 *
 *  Project          :   21593SDK
 *  Organization     :   Jasmin Infotech Private Limited,Chennai
 *  File Name        :	 Extern_SPI.h
 *  Description      :   Extern variables & modules for framework & ISR can be included here
 ******************************************************************************/

#ifndef EXTERN_H
#define EXTERN_H
/*****************************************************************************
	Framework Modules
 *****************************************************************************/
.extern Tag_Location32;
.extern FLAG_TOGGLE_ROUTINE;
.extern	saveforCEnv;
.extern	unsaveforCEnv;
.extern	saveforCEnvNoMode1;
.extern	unsaveforCEnvNoMode1;
.extern saveforCEnv_lib;
.extern unsaveforCEnv_lib;
.extern SerialPortInitTx;
.extern LoadCPRegistersTx;
.extern serialflashAddrRoutine;

.extern C_SW_Swap.;
.extern ReadHeader;
.extern DirectReadRoutine;
.extern SPIConfigure;
.extern _AddCh_Routing;
.extern _PCM_Ovly_Req_Flag;
.extern _CopySamplesFrmIntToExtPreDac;
.extern _CopySamplesFrmIntToExtAddPreDac;
.extern SerialPortInit;
.extern Save_AllRegisters;
.extern Unsave_AllRegisters;

.extern _Center_flag;
.extern _save_mode;

/*****************************************************************************
	ISR Modules
 *****************************************************************************/
.extern save_lbrm_reg_tx;
.extern unsave_lbrm_reg_tx;
.extern Check_DAI_Finished_asm;
.extern ExitSPIReceiveInterrupt;
.extern save_lbrm_reg_spi;
.extern unsave_lbrm_reg_spi;
.extern _SPIReceive;
.extern SetSync_Rx;
.extern _receiver2;
.extern transmitter;
.extern save_lbrm_reg_rx;
.extern unsave_lbrm_reg_rx;
.extern _receiver1;

/************************************************************************/


.extern _Predac_heap;
.extern _Predac_length;


.extern _bypass;
.extern  _high;


.extern save_all_reg;
.extern _Fidelity_Code;

.extern _Pack_buffer_Int_ptr;
.extern CRC_ERROR;

.extern SPORT_CONFIGURE_CFN_Label_DSD2PCM;
.extern Status14Val;
.extern _AddPredac_heap_Ext;
.extern _AddPredac_length_Ext;
.extern _AddPredac_lengthhalf_Ext;
.extern _AddPredac_wr_ptr_Ext;
.extern _AddPredac_rd_ptr_Ext;
.extern _BRStatus;
.extern _Predac_heap_Ext;
.extern _Predac_length_Ext;
.extern _Predac_lengthhalf_Ext;
.extern _Predac_rd_ptr_Ext;
.extern _Predac_wr_ptr_Ext;
.extern _Run_AddrConversion;
.extern _error_frame;
.extern lfe_on;
.extern mAMODE;
.extern profile;
.extern save_all_reg;
.extern save_cregAAC;
.extern Check_EPDMA;
.extern Check_EPDMARx1;
.extern tempbuffer_to_copylfe;
.extern copylfe_to_tempbuffer;

.extern AllocateMemoryDssEs;
.extern FreeMemoryDssEs;
.extern PlayForgnd_DSD2PCM;
.extern DSD2PCMDecoder;
.extern Deemphasis;
.extern copy_to_pre_dac_dummy;
.extern CopyPack2Work;


.extern Init_Struct;
.extern SystemInitialisation;
.extern SystemInitialisation_DSD2PCM;
//.extern _Autodetect_MemoryAlloc;

.extern _Reinitialise_Kernel;

.extern Unsave_AllRegisters;
.extern Save_AllRegisters;
.extern Init_Var;


.extern _OffsetCumBlockLength_Kernel;
.extern _Predac_heap_Ext;
.extern _Predac_length_Ext;
.extern _Predac_lengthhalf_Ext;
.extern _Predac_rd_ptr_Ext;
.extern _Predac_wr_ptr_Ext;
.extern _RWorkBuf;
.extern _WorkBuffer;

.extern _channels;

.extern _Init_Kernel_Code;
.extern _ControlParams_Int;
.extern _Zeropad_tx_id_Tx;


.extern _mat_input_buffer;
.extern EP0InterruptOccured;

.extern _SystemInitDoneFlag;


.extern _SPI_Disable;
.extern _SPI_SRU_change;


.extern _AudioExtFlag;
.extern _SilentDetect_Process;
.extern _SilentDetect_Process_MPCM;
.extern _SilentDetect_Process_DSD2PCM;

.extern _RestorerOrMdax;
.extern _Init_Mdax;

.extern _ControlParams_rd_ptr_Ext;
.extern _ControlParams_wr_ptr_Ext;
.extern _ControlParams_length_Ext;
.extern _ControlParams_heap_Ext;
.extern SampleCount;


.extern _FourI2S_Routing_Rx;
.extern _CustomAutoPCMZero;
.extern _CustomAutoInitPCMZero;


#endif
