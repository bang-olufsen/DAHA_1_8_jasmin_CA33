/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Function_Prototype.h
*  Description      :   Function prototypes for various functions can be included here
******************************************************************************/

#include <stdint.h>
#include <drivers/spi/adi_spi_2156x.h>
#include "Def_Struct.h"
#include "Commn.h"
#ifndef _Function_Prototype_H_
#define _Function_Prototype_H_

/*****************************************************************************
	Framework Modules
*****************************************************************************/
    void SPIReceive(void);

	void FreeMemoryAll(void);
	void SendInitializationDone(void);
	void Status_Update(void);
	void Status_Comparison(void);
	void SPORT_Recongifuration(void);
	void SendIRQInterrupt(void);

	void CommandProcessing(void);
	void Play_Command(void);
	void Stop_Command(void);
	void Mute_Command(void);
	void Resume_Command(void);
	void Special_Function_Command(void);
	void General_Decoding_Command(void);
	void SportInitialize_Command(void);
	void MPCM_Input_command(void);
	
	void CommandProcessing_Core2(void);

	void Flag_Toggle(void);
	void Set_Global_Interrupt(void);
	void Clear_Global_Interrupt(void);
	void Init_Var_Fs(void);

	void PlayForgnd_DSD2PCM(void);
	void Kernal_Default_Init_DSD2PCM(void);
	void Load_Autodetect_Mode(void);
	void DSD2PCM_LOAD_COMMAND(void);
	void Tx_Rx_Mode_Command(void);
	void DSD2PCM_COMMAND(void);
	void TX_Buf_Ptr_Allocation(void);
	void eARC_PCG_Clock_Divider(int, int);
	void DAP_OARI_Command_Default(void);
	void FloatToFixConversion_INT(void);
	void Copy_PredacExt_To_Auro_InBuff(int *, int);
	void AAC_DAP_Input_Channel_Reorder(void);
	void Pre_Dac_rdptr_Update_PP(void);
	void Dolby_NeuralX_Wrapper(void);
	void Copy_PredacExt_AuroBuff_THD(void);
	void floattofixConversion_Auro(void);
	int Dolby_Legacy_CustPP_ChannelMask(unsigned long long);
	void DownMix_TrueHD_Cust(void);
	void DownMix_DDplus_Cust(void);
	void Pack_TO_Predac_MCPCM_Auro(void);
	void CopyLPCMToPredac_Auro(void);
	void CopyZeroesToPredac_Auro(void);
	void AllocateMemoryKernel_DSD2PCM(void);
	void Kernal_Default_Init_DSD2PCM();
	int Downmix_normalization_Routine(int a,int b);
	//void Channel_Reorder_lib(int *,int);
	void Init_struct_DSD(void);
#ifdef CUSTOMER_PP
	void PreDac_Int_To_Cust_PP_Buffer(void);
	void Cust_PP_To_PreDac_Int_Buffer(void);
	void FixToFloatConversion(void);
	void FloatToFixConversion(void);
	void CustomerPP_Gain_Control(int *);
	void Customer_PP_kernel(void);
	void CUSTOMER_PP_COMMAND(void);
#endif
	void EXTMDMA_enable(int, int, int);

	int PlayForgnd(void);
	void Init_Var(void);
	void PackUpdate(void);
	void Pre_Dac_Ptr_Update(void);
	void Pre_FIFO_Ptr_Update(void);
	void AddPredac_Ptr_Update(void);
	void MCPCMDecoder(void);
#ifdef PCM_DEC	
	void PCMDecoder(void);
	void PCMOPTIONS_COMMAND(void);
	void AllocateMemoryPCMDelay(int);
	void ClearLPCMDelay(void);
	void CopyINTLPCMtoDelayBuf(void);
	void CopyLPCMToPredac(void);
#endif

	void Pack_TO_Predac_MCPCM(void);
	void Predac_Buffer_Int_To_Predac_Buffer_Ext(void);
	void Predac_Buffer_Ext_To_Predac_Buffer_Int_DMA(int,int,int);
	void Control_Data_Update(void);
	void PostProcessing_Routine(void);
	void Free_AllotMemoryPackDac( int, int, int);
	void SRU_Reconfigure(int,int);

#ifdef LED_TOGGLE
	void Led1_Set_Routine(void);
	void Led2_Set_Routine(void);
	void Led2_Clr_Routine(void);
	void Led_Toggle_Routine(void);
#endif
	void Led2_Toggle_Routine(void);
	void Customer_PP_Status_Update(void);

	void System_Initialization(void);
	void Spdif_Rx_Stop(void);
	void Initialize_Led(void);

	void SPI1_GPIO_Init(void);
	void SH_SPI1_Master_Config(void);
	void SPI1_Init_DIT(uint32_t Fs);
	void Optical_Write(uint32_t );
	void SPI_Disable(void);
	void SPI_Delay(int i);
	void Init_SPI0(void);
	void ReInit_SPI0(void);
	void SPI0_RxCore_Handler (uint32_t, void *);
	void SPICS_Delay(void);

	void Set_Priority(void);
	void Kernal_Default_Init(void);
	void Enable_Cache(void);
	void SPI_Init(void);
	void DAI_Init(void);
	void SPORT_Init(void);
	void PCG_Init(void);
	void SRC_Init(void);
	void EXTMDMA_Init(void);
	int Init_Struct(void);
	void SpdifRxInit(void);
	void Default_Command_Config(void);

	int FlagsConfigure(void);
	void Init_PORTs(void);

	void AllocateMemoryKernel(void);
	void Wait_Core1(int*, int);

	void SPU_Init(void);

	int adi_sec_SetPriority(uint32_t, uint32_t);
	int adi_dai_init(uint8_t);
	void Rx_DMA_HANDLER(int, void *);
	void Tx_DMA_HANDLER(int, void *);
	//void memset(void*, int,size_t);
	void PCG_Clock_Divider(int, int);
	void Enable_SPI0(void);
	void PCG_Config(void);
	//void Channel_Reorder_lib(int *);
	void Copy_CustomerPP_Buffer_To_PrdacExt(void);
	void Copy_PredacExt_To_PredacInt(void);
	void PreDac_Core1_Data_Copy(void);

#ifdef AAC_DEC
	void AACOptions_Command (void);
	int AACDecoder_Framework(void);
	void Pre_Dac_Ptr_Update_PP(void);
	void Predac_Dec_Ptr_Update(void);
#endif

#ifdef MPEGH_DECODER
	int  MPEGH_Kernel(void);
	void MPEGHDecoder(int nInputChannels, int nOutChannels);
	int  MPEGH_Framework(void);
	void Extract_Channel_reorder_parameters(void);
	void copychannelstoBuffer_asm(int *LR_Chan_Ptr,int Copy_Single_Channel,int Predac_count);
	void Copy_zeros_to_FIFO(void);
	void copy_mpegh_to_predac_asm(int*a,int*b,int n);
	void MPEGH_Channel_Reorder_Kernel(void);
	void find_channelPointer_MPEGH_asm(void);
	void MPEGH_OPTIONS_COMMAND(void);
	void Get_MPEGH_CICP_Target_Index(void);
	void MPEGH_Default_Command_config(void);
	void Predac_Buffer_Int_To_Predac_Buffer_Ext_MPEGH(void);
	void Copy_PredacExt_To_PredacInt_Mpegh(void);
	void Pre_Dac_Ptr_Update_flexible(int);
#endif
#ifdef NOISEGEN
	void NoiseProcess(void);
	void AllocateMemoryNoise(void);
	int pack_noiseocfg(void);
	int pink_init(int,void *ptr);
	int pink_noise_start(int,void *ptr);
	int Noise_Temp_buffer_to_Predac_buffer();
	int Additional_Channel_Noise_Copy(int,int,void *ptr);
	int Copy_Noise_Temp_buffer_to_Predac_buffer_Int_pp_noisegen(void);
	void fixtofloatConversion_Predacbuf_Noisegen(void);
#endif

#ifdef DE_EMPHASIS_PP
	int deemp_init(void *ptr);
	void Deemphasis_Wrapper(void);
	void Deemphasis(int,void *ptr);
#endif
#ifdef CHANNEL_REORDER
	void ChannelReorder_command(void);
#endif

	void customautodetect1(void);
	void CopyZeroesToPredac(void);

#ifdef DOWNSAMPLING
	void CopyLPCMToPack(void);
	void Pack_TO_Predac_Downsam(void);
	void Down_Samp_Processing(void);
	void Pack_To_Int_MCPCM(void);
	void Down_Samp_Processing_8ch(void);
	void Int_Predac_MCPCM(void);
	void Predac_Int_TO_Predac(void);
#endif
	
#ifdef DTSX_DECODER
	void DTSX_Internal_Memory_Ptr_alloc(void);
	void convCustPPchmask(unsigned int *);
#endif

#ifdef DTS_VIRTUALX
	void PreDac_Core1_Data_Copy(void);
	int Predac_int_frm_LibPP(int *, int);
	int DTSX_Predac_int_To_Predac_Buffer_Ext(int *, int);
#endif

#if defined (DOLBY_DDP) || defined (DOLBY_DD)
	void DolbyDigitalPlus_Command(void);
	int  DDPlusDecoder(void);
	void Clear_Decoder_Buffer(void);
	int ddp_dec_configure(void);
	void dpf_blob_reorder(int,int,int,int);
	void Copy_PredacInt_PredacExt_DDP_CIDK(void);
	void Pre_Dac_Ptr_Update_DDP_CIDK(void);
	#endif /* (DOLBY_DDP) || (DOLBY_DD) */
	void  SET_TIMER(void);
	void  CALCULATE_MIPS(int *);
	void Clear_Input_Buffer(void);
	void datmos_ht_core_config_check_kernel(void);
	void datmos_ht_speaker_presence_remap_kernel(void);
	int datmos_ht_graph_type_configure(int, int, int);
	void Memory_Pointer_Allocation(void);
	void Pre_Dac_Ptr_Update_PP(void);
	void fc_fade_out_in(void);
	void Init_Var_PP(void);
	int set_output_config(int, uint8_t *); 
	void Copy_Cust_PP_To_PredacExt(void);
	void fixtofloatConversion_Predacbuf(void);
	unsigned int datmos_ht_height_speaker_count_get(void);
	unsigned int datmos_ht_daes_count(void);
	#if defined (DOLBY_OAR) || defined (DOLBY_DAP) || defined (DOLBY_THD) || defined (DOLBY_MAT) || defined (DOLBY_DDP) || defined(DOLBY_DD)
	void InitOARiModule(void);
	void OAR_DAP_Processing(void);
	void OARI_Param_output_update(void);
	void AllocateMemory_OARi(void);
	void dpf_node_oar_activate(volatile int *,volatile int *);
	void fadeout_process(int, int, float *, int (*)[], int);
	void fadein_process(int, int, float *, int, int);
	void OARI_Init_Call(void);
	static int  min(int, int);
	#endif /* DOLBY_OAR */
	void Control_DataVariable_Update(void);
	void Predac_Addpredac_align_ch_ch_MAT(void);
	void Predac_Addpredac_align_ch_obj_DDP(void);
	void OARi_Processing(void);
	void Predac_Addpredac_align_ch_obj(void);
	void Predac_Addpredac_align_obj_ch(void);
	void obj_obj_switch_reset_DDP(void);
	void obj_obj_switch_reset_DDP(void);
	void obj_obj_switch_reset(void);
	void Copy_PredacExt_PredacInt_THD(void);
	void Copy_PredacExt_PredacInt(void);
	void Copy_PredacExt_PredacInt_pcm(void);
	void Copy_PredacExt_PredacInt16(void);
	unsigned int dpf_node_build_channel_map_dwx(unsigned long,uint8_t * );
	#if defined (DOLBY_OAR) || defined (DOLBY_DAP)
	void Dolby_Audio_Processing(void);
	void DAP_Param_Init(void);
	void DAP_Xml_Param_Inputlist(int *,int *,int ,int ,int ,int );
	void DAP_OARI_Command(void);
	void Dolby_Command_handling(void);

	void dpf_node_datmos_dap_activate(volatile int *,volatile int *,volatile int *,int *datmos_dap_state_buf, int *dap_rcl_struct_buf,int *dap_datmos_ht_state_buf,int *xml_buf,int *profile_buff);

	#endif /* (DOLBY_OAR) || defined (DOLBY_DAP) */
	void prepare_fade_array(float *);
	#if defined (DOLBY_DDP) || defined (DOLBY_DD)
	int DolbyDigitalDecoder(int *InputList , int *OutputList);
	void set_output_config_DDP(int legacy_mode,int *joc_dmx_out_order,int outmap,int outchanconfig,int outlfe,int jocd_out_mode,int joc_mode);
	void set_output_config_DDP_Legacy(int legacy_mode,int *joc_dmx_out_order,int outmap,int outchanconfig,int outlfe,int jocd_out_mode,int joc_mode);
	void AddPredac_Ptr_Update_DDP(void);
	#endif  /* DOLBY_DDP */
	#ifdef DOLBY_DMX
	//int set_output_config(int outputmap, int *ch_map);
	void Downmixer_Processing(void);
	void dpf_node_dmx_activate(int *Alginputlist);
	#endif /* DOLBY_DMX */
	#if defined (DOLBY_THD) || defined (DOLBY_MAT)
	void Pre_Dac_Ptr_Update_THD_CIDK(void);
	void MLP_Initialise(volatile int *, struct TrueHD *);
	void Error_Reset_Variables(void);
	void InitilaAuExtract(volatile int *,volatile int *, struct TrueHD *);
	void DolbyTrueHD_Command(void);
	void DTHD_Dec_Set_Params(void *ptr, int *, int *);
	void TrueHDDecoderLib(int *, int *, void *ptr);
	void CALCULATE_MIPS_thd(int *);
	void PredacPtrUpdate_TRUEHD(void);
	void TrueHDAddpre_Dac_Ptr_Update(void);
	void AllocateMemoryTrueHD(void);
	void DTHD_Dec_Init(void *ptr, struct TrueHD_Tag);
	int TrueHDDecoder(void);
	void TrueHD_Variable_Init(void);
	void LatencyProcess(void);
	void TrueHD_FIFO_Latency(void);
	void dpf_blob_reorder_thd(int, unsigned int *, int, int, int);
	void PredacPtrUpdate_TRUEHD(void);
	void TrueHDAddpre_Dac_Ptr_Update(void);
	void PredacPtrUpdate_TRUEHD(void);

	#if defined (DOLBY_THD) || defined (DOLBY_MAT)
	void MATPCM_Command(void);
	void mat_dec_init(void *ptr);
	int MAT_Decoder_Init(void *ptr, struct MAT_Tag);
	void MATDec_Set_Params(struct MAT_Tag, void *ptr);
	void MAT_PCM_Variable_Init(void);
	void MAT_PCM_Predac_Allocation(void);
	void Copy_Pre_Dac_lib_Pre_Dac_Ext_MAT(void);
	void Copy_Pre_Dac_lib_Pre_Dac_Ext_MAT_16ch(void);
	int mat_dthd_configure(void);
	void COPY_MAT_TO_IN_BUF(void *, void *, void*);
	void Endian_Change_ForMAT(volatile int *, volatile int *, struct TrueHD *);
	void Find_MAT_Stream_Profile(int *, int *);
	void MATDecoder_Lib(int *Input_list_ptr, int *Output_list_ptr, void *ptr);
	void Endian_Change_ForMAT_PCM(volatile int *, volatile int *, struct TrueHD *);
	void fixtofloatConversion_Predacbuf_MAT(void);
	void Pre_Dac_Ptr_Update_MAT_lib(void);
	void MATPCMAddpre_Dac_Ptr_Update(void);
	void UPDATE_PACK_RD_PTR(int , int *, int *);
	void UPDATE_PACK_RD_PTR1(int, int *, int *);
	void fill_zero_predac(void);
	#ifdef DOLBY_THD_DA
	int dthd_bitstream_extraction_data(void);
	#endif /* DOLBY_THD_DA */
	#endif /* (DOLBY_THD) || defined (DOLBY_MAT) */
	#if defined (DOWNSAMPLING_PCM ) || defined (DOWNSAMPLING_MCPCM) || defined (DOLBY_THD_DS)
	void Pack_TO_ExtPredac_MCPCM(void);
	void Init_ds_buffers(int);
	#endif /* (DOWNSAMPLING_PCM ) || (DOWNSAMPLING_MCPCM) || (DOLBY_THD_DS) */
	#ifdef DOLBY_THD_DA
	int dthd_bitstream_extraction_data(void);
	#endif /* DOLBY_THD_DA */
	void datmos_speaker_legacy(void);

#ifdef TMU
    void TMU_Init(void);
    void TMU_Monitoring(void);
#endif
	#ifdef DOLBY_MIPS
	void  SET_TIMER(void);
	void  CALCULATE_MIPS(int *);
	void  Free_MIPS_Calc(void);
	#endif /* DOLBY_MIPS */
#endif
#ifdef SPDIF_MODULE
void Spdif_Rx_ISR(int, void *);
void Spdif_Rx_Fs_conversion(int);
void Spdif_Lock_check_fn();
void Spdif_Input_lock_check();
#endif
void _Flag_Toggle(void);
	#endif /* FUNCTION_PROTOTYPE_H_ */
