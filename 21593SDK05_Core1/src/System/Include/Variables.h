/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Variables.h
*  Description      :
******************************************************************************/
#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "Commn.h"


/************************************Downsampling*************************************/
	int DnSamp192to48 = 0;
	int down_samp_flag = 0;
	int C_SW_Swap = 1;
#ifdef DOWNSAMPLING
	int DnSamp192to48_flag = 0;
	int down_samp_flag_cmd = 0;
	int Do_Downsampling_process;
	int Previous_DS_Mode;
	
#pragma	section("seg_DS_kernal_data")
	int Predac_int[256*2];

#pragma	section("seg_DS_kernal_data")
	float LR_int[1024*2];
#pragma	section("seg_DS_kernal_data")
	float C_SW_int[1024*2];
#pragma	section("seg_DS_kernal_data")
	float LS_RS_int[1024*2];
#pragma	section("seg_DS_kernal_data")
	float LSR_RSR_int[1024*2];
	
#pragma	section("seg_DS_kernal_data")
	float LR_out[256*2];
#pragma	section("seg_DS_kernal_data")
	float C_SW_out[256*2];
#pragma	section("seg_DS_kernal_data")
	float LS_RS_out[256*2];
#pragma	section("seg_DS_kernal_data")
	float LSR_RSR_out[256*2];
	
	#ifdef DOWNSAMPLING_DTSX
#pragma		section("seg_DTSX_DS_kernal_data")
		float Add1_2chnl[1024*2];
#pragma		section("seg_DTSX_DS_kernal_data")
		float Add3_4chnl[1024*2];
#pragma		section("seg_DTSX_DS_kernal_data")
		float Add5_6chnl[1024*2];
#pragma		section("seg_DTSX_DS_kernal_data")
		float Add7_8chnl[1024*2];
#pragma		section("seg_DTSX_DS_kernal_data")
		float Add1_2chnlout[256*2];
#pragma		section("seg_DTSX_DS_kernal_data")
		float Add3_4chnlout[256*2];
#pragma		section("seg_DTSX_DS_kernal_data")
		float Add5_6chnlout[256*2];
#pragma		section("seg_DTSX_DS_kernal_data")
		float Add7_8chnlout[256*2];
	#endif //DOWNSAMPLING_DTSX

	int LR_ptr_int=0,cs_ptr_int=0,LsRs_ptr_int=0,LtRt_ptr_int=0;
	
	int dn_blkcnt_temp;

	int leftinput_delays_heap;
	int leftinput_delays_ptr;
	int rightinput_delays_heap;
	int lp_cfs_heap_ptr;
	int Ls_input_delays_heap;
	int Ls_input_delays_ptr;
	int Lsr_input_delays_heap;
	int Lsr_input_delays_ptr;
	int centerinput_delays_heap;
	int centerinput_delays_ptr;
	int lfeinput_delays_heap;
	int Rs_input_delays_heap;
	int Rsr_input_delays_heap;

	#ifdef DOWNSAMPLING_DTSX
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_1_input_delays_heap;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_1_input_delays_ptr;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_3_input_delays_heap;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_3_input_delays_ptr;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_5_input_delays_heap;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_5_input_delays_ptr;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_7_input_delays_heap;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_7_input_delays_ptr;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_2_input_delays_heap;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_4_input_delays_heap;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_6_input_delays_heap;
#pragma		section("seg_DTSX_DS_kernal_data")
		int add_8_input_delays_heap;
	#endif //DOWNSAMPLING_DTSX

	#if defined (DOLBY_THD_DS) || defined (DOWNSAMPLING) 
#pragma		section("Seg_DS_Kernel_Data_L3")
		float *DS_Coef_192to48_Ptr_Add;
#pragma		section("Seg_DS_Kernel_Data_L3")
		float *DS_Coef_96to48_Ptr_Add;
#pragma		section("Seg_DS_Kernel_Data_L3")
		float *DS_Coef_192to96_Ptr_Add;
#pragma		section("Seg_Dolby_Library_Data_L3")
		int leftinput_delays_heap_buffer;
#pragma		section("Seg_Dolby_Library_Data_L3")
		int rightinput_delays_heap_buffer;
#pragma		section("Seg_Dolby_Library_Data_L3")
		int centerinput_delays_heap_buffer;
#pragma		section("Seg_Dolby_Library_Data_L3")
		int  lfeinput_delays_heap_buffer;
#pragma		section("Seg_Dolby_Library_Data_L3")
		int Ls_input_delays_heap_buffer;
#pragma		section("Seg_Dolby_Library_Data_L3")
		int Rs_input_delays_heap_buffer;
#pragma		section("Seg_Dolby_Library_Data_L3")
		int Lsr_input_delays_heap_buffer;
#pragma		section("Seg_Dolby_Library_Data_L3")
		int Rsr_input_delays_heap_buffer;
	#endif /* (DOLBY_THD_DS) || (DOWNSAMPLING) */

#endif

/**********************************Main*******************************************/
int BufSize = NO_OF_SAMPLE_PROCESSING*NUMMAXCHAN;
int No_of_Predac_Channel = NO_OF_PREDAC_CHANNEL;
/*PCG Related Variables*/
int Prev_Clock_Div_Value;
int Clock_Div_Value = MCLK_48KHZ;
int PCG_Sample_ratio;
#pragma section("Seg_Ex_Ds_Bw")
int *PACK_WR_PTR;
#pragma section("Seg_Ex_Ds_Bw")
int PP_flag = 1;

#pragma section("Seg_Ex_Ds_Bw")
int RX_receiver_Count=0;
#pragma section("Seg_Ex_Ds_Bw")
int check=0;
#pragma section("Seg_Ex_Ds_Bw")
int buff_zero=0;
#pragma section("Seg_Ex_Ds_Bw")
int DataValid;
#pragma section("Seg_Ex_Ds_Bw")
int SingleI2S_prev_b2;
#pragma section("Seg_Ex_Ds_Bw")
int flag_receiver2;
#pragma section("Seg_Ex_Ds_Bw")
int Read_count = 0;

/************************INTERMEDIATE BUFFER FOR COPYTING DATA FROM DMA BUFFER TO DECODER**********************/

#pragma section("seg_dmda_nw2")

int save_buffer[INAUTOBUFSIZEBY2*4];

/**********************************************RECEIVER DMA BUFFER**********************************************/

#pragma section("Seg_Rx_Dma_Bw")
int   RX_SP5A_BUFFER_SPDIF0[COUNT_2CH];
#pragma section("Seg_Rx_Dma_Bw")
int   RX_SP5A_BUFFER_SPDIF1[COUNT_2CH];

#pragma section("Seg_Rx_Dma_Bw")
int   RX_SP0A_BUFFER_LCRSW0[COUNT_4CH];
#pragma section("Seg_Rx_Dma_Bw")
int   RX_SP0A_BUFFER_LCRSW1[COUNT_4CH];
#pragma section("Seg_Rx_Dma_Bw")
int   RX_SP0B_BUFFER_LsLsrRsRsr0[COUNT_4CH];
#pragma section("Seg_Rx_Dma_Bw")
int   RX_SP0B_BUFFER_LsLsrRsRsr1[COUNT_4CH];

#ifdef DSD2PCM_DEC
#pragma section("Seg_Rx_Dma_Bw")
int   RX_SP1A_BUFFER_DSD2PCM0[COUNT_4CH];
#pragma section("Seg_Rx_Dma_Bw")
int   RX_SP1A_BUFFER_DSD2PCM1[COUNT_4CH];
#endif

#pragma section("Seg_Rx_Dma_Bw")
int RX_Intermediate_BUFFER[COUNT_4CH*2];
/**********************************************TRANSMITTER DMA BUFFER**********************************************/
#ifdef BEO_Framework
#pragma section("Seg_Tx_Dma_Bw")  // L1 Memory Location
int  TX_SP2A_BUFFER_LCRSW0[COUNT_4CH];
#pragma section("Seg_Tx_Dma_Bw") // L1 Memory Location
int  TX_SP2A_BUFFER_LCRSW1[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw") // L1 Memory Location
int   TX_SP2B_BUFFER_LsLsrRsRsr0[COUNT_4CH];
#pragma section("Seg_Tx_Dma_Bw") // L1 Memory Location
int   TX_SP2B_BUFFER_LsLsrRsRsr1[COUNT_4CH];
#endif

#pragma section("Seg_Tx_Dma_Bw")  // L1 Memory Location
int  TX_SP4A_BUFFER_LCRSW0[COUNT_4CH];
#pragma section("Seg_Tx_Dma_Bw") // L1 Memory Location
int  TX_SP4A_BUFFER_LCRSW1[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw") // L1 Memory Location
int   TX_SP4B_BUFFER_LsLsrRsRsr0[COUNT_4CH];
#pragma section("Seg_Tx_Dma_Bw") // L1 Memory Location
int   TX_SP4B_BUFFER_LsLsrRsRsr1[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw")
int   TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw")
int   TX_SP3A_BUFFER_Addch1ch3ch2ch4_set1[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw")
int   TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw")
int   TX_SP3B_BUFFER_Addch5ch7ch6ch8_set1[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw")
int   TX_SP6A_BUFFER_Addch9ch11ch10ch12_set0[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw")
int   TX_SP6A_BUFFER_Addch9ch11ch10ch12_set1[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw")
int   TX_SP2A_BUFFER_Addch13ch15ch14ch16_set0[COUNT_4CH];

#pragma section("Seg_Tx_Dma_Bw")
int   TX_SP2A_BUFFER_Addch13ch15ch14ch16_set1[COUNT_4CH];


#pragma section("Seg_Tx_Dma_Bw")
int   TX_EXT_DMA_BUFFER[NO_OF_TX_SAMPLE_COUNT * NUMMAXCHAN];

/*************************************************DECODER BUFFERS***********************************************/

#pragma section("Seg_Pack_Bw")
int Pack_buffer_ext[PACK_BUFFER_MAX_SIZE];

#pragma section("Seg_Predac_Bw")
int Predac_buffer_Ext[(SAMPLEBLOCK_TRUEHD_192K*NUMMAXCHAN*FOUR_HALF)];  /* Predac declared for maximum decoding size  */
//int Predac_buffer_Ext[(1280*NUMMAXCHAN*FIVE_HALF)];

#pragma section("Seg_Internal_Predac")
int Predac_buffer_Int[NO_OF_SAMPLE_PROCESSING*PREDAC_INT_NUMCHAN];

#pragma section("Seg_Predac_Bw")
int Intr_count = INVALID;


#ifdef SPDIF_MODULE
#pragma section("seg_spdif_data")
int SPDIF_Enable = 0;
#pragma section("seg_spdif_data")
int Prev_SPDIF_Enable = 0;
#pragma section("seg_spdif_data")
int Spdif_prev_sampling_frequency = -1;
#pragma section("seg_spdif_data")
int Spdif_Input_fs_micro = 2;
#pragma section("seg_spdif_data")
int Spdif_Rx_Fs;
#pragma section("seg_spdif_data")
int Prev_Spdif_Rx_Fs;
#pragma section("seg_spdif_data")
bool SPDIF_Input_locked;
#pragma section("seg_spdif_data")
int Spdif_Rx_Div = 0;
#pragma section("seg_spdif_data")
int Spdif_I2S_Switch_Occured = 1;
#pragma section("seg_spdif_data")
int Spdif_Input_locked_DAC_Mute = 0;
#pragma section("seg_spdif_data")
int Spdif_unlock_interrupt_occured = 0;
#pragma section("seg_spdif_data")
int SPDIF_testcount = 1000000;
#pragma section("seg_spdif_data")
int Spdif_Command_arg = 0;
#pragma section("seg_spdif_data")
int spdif_status_valid_output_muted = 0;
#pragma section("seg_spdif_data")
int Spdif_fs_table[12] = {32000,44100,48000,48000,64000,88200,96000,96000,128000,176400,192000};
#pragma section("seg_spdif_data")
int Spdif_parameter1;
#pragma section("seg_spdif_data")
int Spdif_parameter2;
#pragma section("seg_spdif_data")
int Spdif_parameter3;
#endif
#endif /* VARIABLES_H_ */
