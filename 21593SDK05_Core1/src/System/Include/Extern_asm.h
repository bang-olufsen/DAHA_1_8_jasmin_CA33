/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Extern_asm.h
*  Description      :   Extern variables & modules for framework & ISR can be included here
******************************************************************************/

#ifndef EXTERN_ASM_H
#define EXTERN_ASM_H

#include "..\src\system\Include\Commn.h"
/*****************************************************************************
	Framework Modules
*****************************************************************************/	

.extern AddPredac_heap_Ext.;
.extern AddPredac_length_Ext.;
.extern AddPredac_lengthhalf_Ext.;
.extern AddPredac_wr_ptr_Ext.;
.extern AddPredac_rd_ptr_Ext.;

.extern Predac_heap_Ext.;
//.extern Predac_length_Ext.;
.extern Predac_lengthhalf_Ext.;
.extern Predac_rd_ptr_Ext.;
.extern Predac_wr_ptr_Ext.;

.extern ControlParams_rd_ptr_Ext.;
.extern ControlParams_wr_ptr_Ext.;
.extern ControlParams_length_Ext.;
.extern ControlParams_heap_Ext.;

.extern No_of_Predac_Channel.;
.extern down_samp_flag.;
.extern DnSamp192to48_flag.;

.extern C_Chan_Ptr.;
.extern Ch_Chan_Ptr.;
.extern Cs_Chan_Ptr.;
.extern LR_Chan_Ptr.;
.extern Lfe_Chan_Ptr.;
.extern LfhRfh_Chan_Ptr.;
.extern LrhRrh_Chan_Ptr.;
.extern LsRs_Chan_Ptr.;
.extern LshRsh_Chan_Ptr.;
.extern LshRsh_Ts_Flag.;
.extern LsrRsr_Chan_Ptr.;
.extern LssRss_Chan_Ptr.;
.extern LtfRtf_Chan_Ptr.;
.extern LtmRtm_Chan_Ptr.;
.extern LtrRtr_Chan_Ptr.;
.extern LwRw_Chan_Ptr.;

.extern Ts_Chan_Ptr.;

#ifdef MPEGH_DECODER
	.extern mpegh_channel_cofig.;
	.extern Mpegh_LFE_Present.;
	.extern Input_Channel_Config_Mask.;
	.extern Default_Target_Layout_Enabled.;
	.extern Predac_FIFO_Base_Ptr.;
#endif



#ifdef DOWNSAMPLING
	.extern Predac_int.;
	.extern C_SW_int.;
	.extern C_SW_out.;
	.extern LR_int.;
	.extern LR_out.;
	.extern SR_RSR_int.;
	.extern LSR_RSR_out.;
	.extern LS_RS_int.;
	.extern LS_RS_out.;
	.extern ds_count.;
	.extern LR_ptr_int.;
	.extern cs_ptr_int.;
	.extern LsRs_ptr_int.;
	.extern LtRt_ptr_int.;

	.extern dn_blkcnt_temp.;
	.extern lp_cfs_heap_ptr.;
	.extern LSR_RSR_int.;
/*
	.extern leftinput_delays_heap_buffer1.;
	.extern rightinput_delays_heap_buffer1.;
	.extern centerinput_delays_heap_buffer1.;
	.extern lfeinput_delays_heap_buffer1.;
	.extern Ls_input_delays_heap_buffer1.;
	.extern Rs_input_delays_heap_buffer1.;
	.extern Lsr_input_delays_heap_buffer1.;
	.extern Rsr_input_delays_heap_buffer1.;
*/
	.extern leftinput_delays_heap.;
	.extern rightinput_delays_heap.;
	.extern centerinput_delays_heap.;
	.extern lfeinput_delays_heap.;
	.extern Ls_input_delays_heap.;
	.extern Rs_input_delays_heap.;
	.extern Lsr_input_delays_heap.;
	.extern Rsr_input_delays_heap.;
	.extern leftinput_delays_ptr.;
	.extern rightinput_delays_ptr.;
	.extern centerinput_delays_ptr.;
	.extern lfeinput_delays_ptr.;
	.extern Ls_input_delays_ptr.;
	.extern Rs_input_delays_ptr.;
	.extern Lsr_input_delays_ptr.;
	.extern Rsr_input_delays_ptr.;

	#ifdef DOWNSAMPLING_DTSX
		.extern Add1_2chnlout.;
		.extern Add3_4chnlout.;
		.extern Add5_6chnlout.;
		.extern Add7_8chnlout.;
		.extern Add1_2chnl.;
		.extern Add3_4chnl.;
		.extern Add5_6chnl.;
		.extern Add7_8chnl.;
		.extern add_1_input_delays_heap.;
		.extern add_1_input_delays_ptr.;
		.extern add_3_input_delays_heap.;
		.extern add_3_input_delays_ptr.;
		.extern add_5_input_delays_heap.;
		.extern add_5_input_delays_ptr.;
		.extern add_7_input_delays_heap.;
		.extern add_7_input_delays_ptr.;
		.extern add_2_input_delays_heap.;
		.extern add_4_input_delays_heap.;
		.extern add_6_input_delays_heap.;
		.extern add_8_input_delays_heap.;
	#endif //DOWNSAMPLING_DTSX
#endif
#ifdef DOLBY_THD_DA
.extern THD_Info_Ret.;
#endif /* DOLBY_THD_DA */
#endif  /*	EXTERN_ASM_H  */
