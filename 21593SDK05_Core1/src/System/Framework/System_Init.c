/***************************************************************************
 *
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
 *
 *  Project          :  	21593SDK
 *  Organization     :  	Jasmin Infotech Private Limited,Chennai
 *  File Name        :	System_Init.c
 *  Description      :
 ******************************************************************************/
#pragma default_section(CODE,"Seg_System_Init_Code")
#pragma default_section(ALLDATA,"Seg_System_Init_Data")
#include "..\src\system\Include\System_Init.h"
#include "../Include/Function_Prototype.h"

/**************************************************************************************************
 *  Module Name        : System_Initialization
 *  Functionality      : call all system and hardware cfg functions (SPORT, DIA, SPI)
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
void System_Initialization(void)
{
#ifdef ASRC_ENABLE
	*pREG_PADS0_DAI0_IE=0xfffff; //PADS Configuration register	
	*pREG_PADS0_DAI1_IE=0xfffff; //PADS Configuration register	
#else
	*pREG_PADS0_DAI0_IE=0xfffff; //PADS Configuration register	//DAIO_PIN- 5
	*pREG_PADS0_DAI1_IE=0xfffff; //PADS Configuration register	//DAI1_PIN- 5,6
#endif
	Init_Struct();
#ifdef ASRC_ENABLE
    FS_Div_Value = Mclk_48Khz;
#endif
	SPI_Init();
	FlagsConfigure();
	Init_PORTs();
	Kernal_Default_Init();
	DAI_Init();
	Init_SPI0();
	Enable_SPI0();
#ifdef ASRC_ENABLE
	SRC_Init();
#endif
	PCG_Init();

#if defined (USE_MDMA_EXTCHANNEL) || defined (TX_NEW_LOGIC)
	EXTMDMA_Init();
#endif

	SPORT_Init();
	InitDoneForAutodetectMode = 1;

	Default_Command_Config();

#ifdef TMU
	TMU_Init();
#endif

#ifdef MPEGH_DECODER
	MPEGH_Default_Command_config();
#endif


#ifdef DSD2PCM_TESTING
	DSD2PCM_LOAD_COMMAND();
	DSD2PCM_COMMAND();
	Frmwk.sampling_fs_micro = 2;
	Frmwk.OutputSampleRate = 2;
#endif
}

/**************************************************************************************************
 *  Module Name        : Set Priority
 *  Functionality      : Set priority of SPI and SPORT DMA interrupts
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/

void Set_Priority(void)
{
	if (SPI_Device == 1)
	{
		adi_sec_SetPriority(INTR_SPI1_RXDMA,0);
	}
	else
	{
		adi_sec_SetPriority(INTR_SPI0_RXDMA,0);
	}
	adi_sec_SetPriority(INTR_DAI1_IRQH,1);
	adi_sec_SetPriority(INTR_SYS_MDMA0_DST,1);

	adi_sec_SetPriority(INTR_DAI1_GBL_SPORT_INT1,2);  // For SPDIF Receiver
	adi_sec_SetPriority(INTR_DAI0_GBL_SPORT_INT1 ,2);  // For HDMI Receiver

	adi_sec_SetPriority(INTR_DAI1_GBL_SPORT_INT0,2); // For Transmitter
	adi_sec_SetPriority(INTR_DAI0_GBL_SPORT_INT0,2); // For Transmitter
}

/**************************************************************************************************
 *  Module Name        : Default_Command_Config
 *  Functionality      : default kernel run flag set to 1
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
void Default_Command_Config(void)
{
	Frmwk.run_flag = 1;
	*run_flag      = 1;
}

#ifdef MPEGH_DECODER
#pragma section("seg_kernal_code_l3")
void MPEGH_Default_Command_config()
{
	Frmwk.MPEGH.ChannelReorder_AssignLines = -1;
	Frmwk.MPEGH.Target_layout_Mask  = MPEGH_DEFAULT_SPEAKER_MASK;
	Frmwk.MPEGH.CICP_Target_Layout  = MPEGH_DEFAULT_CICP_TARGET_INDEX; //7.1.4
	Frmwk.MPEGH.Target_Loudness     = MPEGH_DEFAULT_TARGET_LOUDNESS; // TV
}
#endif
/**************************************************************************************************
 *  Module Name        : Kernal_Default_Init
 *  Functionality      : Kernal_Default_Initialazation (Memory allocation, predac, pack & lpc delay buffer
 *  					 Security bit set as per Sport cfg)
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
void Kernal_Default_Init(void)
{
#ifdef DSD2PCM_TESTING
	Frmwk.autodetect_mode= FORCEPCM3;
	AllocateMemoryKernel();
	Free_AllotMemoryPackDac(Frmwk.pack_length_DSD2PCM, Frmwk.predac_length_DSD2PCM, Frmwk.addpredac_length_DSD2PCM);
#else	
	AllocateMemoryKernel();
	Free_AllotMemoryPackDac( Frmwk.pack_length_pcm, Frmwk.predac_length_pcm, 1);

#ifdef PCM_DEC
	Frmwk.LPCMDelaySize = Frmwk.LPCMDelaySize_host+(Frmwk.SampleBlock*2);	//(4096samples*2ch*32bit)
	Frmwk.PrevLPCMDelaySize_host = Frmwk.LPCMDelaySize_host;

	AllocateMemoryPCMDelay(Frmwk.LPCMDelaySize);
#endif
#endif 
	SPU_Init();
}

/**************************************************************************************************
 *  Module Name        : Enable_Cache
 *  Functionality      : Enable_Cache memory with size of
 *  					 PM cache = 0.25 Mbits
 *  					 DM cache = 1 Mbits
 *  					 I cache = 0.5 Mbits
 *  					 cache_able and non cache_able memory region by using Range register
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
#pragma section("seg_int_code")
void Enable_Cache(void)
{
	*pREG_SHL1C_CFG2 |= 0x3cc0;
	NOP10; NOP10; NOP10; NOP1; NOP1; NOP1;//33 NOPS

	// Non Cacheable region In L2 Memory (shared meemory)//(Pack buffer)
	*pREG_SHL1C_RANGE_START5 = 0x20146000;
	NOP10;NOP10;
	*pREG_SHL1C_RANGE_END5 =  0x2014DFFF;
	NOP10;NOP10;

	// Non Cacheable region In DDR0 (PREDAC and Add_Predac buffer)
	*pREG_SHL1C_RANGE_START6=0x80600000;
	NOP10;NOP10;

	*pREG_SHL1C_RANGE_END6=0x8097ffff;
	NOP10;NOP10;
}

/**************************************************************************************************
 *  Module Name        : SPI_Init
 *  Functionality      : SPI  receiver buffer initialization
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
void SPI_Init(void)
{
	Frmwk.Spi.SPIReceiveTempBuf  	= (int)&Spi_size;
	Frmwk.Spi.SPIReceiveTempBufPtr 	= (int)&Spi_size;
	Frmwk.Spi.SPIReceivebufsize 	= SPI_BUFFER_SIZE;
}

/**************************************************************************************************
 *  Module Name        : DAI_init
 *  Functionality      : Interface between process and hardware.Configured DAI pins for inputs & outputs
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
#pragma section("Seg_Kernal_Code")
void  DAI_Init(void)
{
	/****************************************************Receiver DAI configuration******************************************************************/
#ifdef SOUNDBAR
	SRU(LOW,DAI1_PBEN03_I);        //TX_I2S_BCLK
	SRU(LOW,DAI1_PBEN04_I);        //TX_I2S_LRCLK

#else
	SRU(HIGH,DAI1_PBEN03_I);        //TX_I2S_BCLK
	SRU(HIGH,DAI1_PBEN04_I);        //TX_I2S_LRCLK
#endif

	if(SPDIF_Enable == 1)
	{
		//SPDIF RX input to DAI0 pin 20
		SRU(LOW,DAI0_PBEN20_I);
		SRU(DAI0_PB20_O,SPDIF1_RX_I);

		//SPDIF clock, Fs, and data to SPORT5A
		SRU(SPDIF1_RX_FS_O,SPT5_AFS_I);
		SRU(SPDIF1_RX_CLK_O,SPT5_ACLK_I);
		SRU(SPDIF1_RX_DAT_O,SPT5_AD0_I);

		SRU(SPDIF1_RX_CLK_O,PCG0_EXTCLKC_I);     // BCLK to PCG C
	}
	else
	{
		SRU(LOW,DAI0_PBEN03_I);         //RX_I2S_BCLK
		SRU(LOW,DAI0_PBEN04_I);         //RX_I2S_LRCLK

		SRU(LOW,DAI0_PBEN09_I);
		SRU(LOW,DAI0_PBEN10_I);
		SRU(LOW,DAI0_PBEN11_I);
		SRU(LOW,DAI0_PBEN12_I);

		SRU(DAI0_PB03_O,SPT0_ACLK_I);
		SRU(DAI0_PB03_O,SPT0_BCLK_I);

		SRU(DAI0_PB04_O,SPT0_AFS_I);
		SRU(DAI0_PB04_O,SPT0_BFS_I);

		SRU(DAI0_PB09_O,SPT0_AD0_I);	//SPORT0A RX
		SRU(DAI0_PB10_O,SPT0_AD1_I);	//SPORT0A RX
		SRU(DAI0_PB11_O,SPT0_BD0_I);	//SPORT0B RX
		SRU(DAI0_PB12_O,SPT0_BD1_I);	//SPORT0B RX

		SRU(DAI0_PB03_O,PCG0_EXTCLKC_I);     //BCLK to PCG C
		SRU(DAI0_PB04_O,PCG0_SYNC_CLKC_I);
	}

#ifdef SOUNDBAR
	SRU(DAI1_PB03_O,PCG0_EXTCLKB_I);
	SRU(DAI1_PB04_O,PCG0_SYNC_CLKB_I);
#else
	SRU(LOW,DAI0_PBEN05_I);
	SRU(DAI0_PB05_O,PCG0_EXTCLKB_I);
	SRU(PCG0_INV_CLKB_O,DAI1_PB03_I);
	SRU(PCG0_FSB_O,DAI1_PB04_I);
#endif

	/****************************************************Transmitter DAI configuration******************************************************************/

#ifdef BEO_Framework
		ASRC_DAI_Init();
#endif
	/****************************************************PCG C DAI configuration******************************************************************/
	PCG_Init();

}

/**************************************************************************************************
 *  Module Name        : PrepareRxDescriptors
 *  Functionality      : Configuration SPORT Registers for Receiver & transmitter
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
static void PrepareRxDescriptors (ADI_PDMA_DESC_LIST* pDmaDescList1, ADI_PDMA_DESC_LIST* pDmaDescList2, void* Buf1, void* Buf2, uint8_t XCount, uint8_t XMod)
{
	pDmaDescList1->pStartAddr = (uint32_t*)((uint32_t)Buf1|MP_OFFSET);
	pDmaDescList1->pNxtDscp = pDmaDescList2;
	pDmaDescList1->XCount = XCount;
	pDmaDescList1->XModify = XMod;
	pDmaDescList1->Config = ENUM_DMA_CFG_XCNT_TRIG;

	pDmaDescList2->pStartAddr = (uint32_t*)((uint32_t)Buf2|MP_OFFSET);
	pDmaDescList2->pNxtDscp = pDmaDescList1;
	pDmaDescList2->XCount = XCount;
	pDmaDescList2->XModify = XMod;
	pDmaDescList2->Config = ENUM_DMA_CFG_XCNT_TRIG;
}

/**************************************************************************************************
 *  Module Name        : PrepareTxDescriptors
 *  Functionality      : Configuration SPORT Registers for Receiver & transmitter
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
static void PrepareTxDescriptors (ADI_PDMA_DESC_LIST* pDmaDescList1, ADI_PDMA_DESC_LIST* pDmaDescList2, void* Buf1, void* Buf2, uint16_t XCount, uint8_t XMod)
{
	pDmaDescList1->pStartAddr = (uint32_t*)((uint32_t)Buf1|MP_OFFSET);
	pDmaDescList1->pNxtDscp = pDmaDescList2;
	pDmaDescList1->XCount = XCount;
	pDmaDescList1->XModify = XMod;

	pDmaDescList2->pStartAddr = (uint32_t*)((uint32_t)Buf2|MP_OFFSET);
	pDmaDescList2->pNxtDscp = pDmaDescList1;
	pDmaDescList2->XCount = XCount;
	pDmaDescList2->XModify = XMod;
}

/**************************************************************************************************
 *  Module Name        : SPORT_Init
 *  Functionality      : Configuration SPORT Registers for Receiver & transmitter
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
void SPORT_Init(void)
{
	//ADI_SPORT_RESULT Result;
#ifdef SPDIF_MODULE
	if (SPDIF_Enable == 1)
	{
		SpdifRxInit();
		Result = adi_sport_Open(5,ADI_HALF_SPORT_A,ADI_SPORT_DIR_RX, ADI_SPORT_I2S_MODE, SPORTMemory5A,ADI_SPORT_MEMORY_SIZE,&hSPORT5ARx);
	}
	else
#endif
	{
		Result = adi_sport_Open(0,ADI_HALF_SPORT_A,ADI_SPORT_DIR_RX, ADI_SPORT_I2S_MODE, SPORTMemory0A,ADI_SPORT_MEMORY_SIZE,&hSPORT0ARx);
		Result = adi_sport_Open(0,ADI_HALF_SPORT_B,ADI_SPORT_DIR_RX, ADI_SPORT_I2S_MODE, SPORTMemory0B,ADI_SPORT_MEMORY_SIZE,&hSPORT0BRx);
	}
	#ifdef BEO_Framework

		Result = adi_sport_Open(2,ADI_HALF_SPORT_A,ADI_SPORT_DIR_TX, ADI_SPORT_I2S_MODE, SPORTMemory2A,ADI_SPORT_MEMORY_SIZE,&hSPORT2ATx);
		Result = adi_sport_Open(2,ADI_HALF_SPORT_B,ADI_SPORT_DIR_TX, ADI_SPORT_I2S_MODE, SPORTMemory2B,ADI_SPORT_MEMORY_SIZE,&hSPORT2BTx);
		Result = adi_sport_Open(3,ADI_HALF_SPORT_A,ADI_SPORT_DIR_TX, ADI_SPORT_I2S_MODE, SPORTMemory3A,ADI_SPORT_MEMORY_SIZE,&hSPORT3ATx);
		Result = adi_sport_Open(3,ADI_HALF_SPORT_B,ADI_SPORT_DIR_TX, ADI_SPORT_I2S_MODE, SPORTMemory3B,ADI_SPORT_MEMORY_SIZE,&hSPORT3BTx);

//		Result = adi_sport_ConfigData(hSPORT2ATx, ADI_SPORT_DTYPE_ZERO_FILL, 31, false, false, false);
//		Result = adi_sport_ConfigClock(hSPORT2ATx, 31, false, false, false);
//		Result = adi_sport_ConfigFrameSync(hSPORT2ATx, 31, false, false, false, bActiveHighFS, bLateFS, false);

	#endif /* BEO_Framework */
#ifdef SPDIF_MODULE
	if (SPDIF_Enable == 1)
	{
		PrepareRxDescriptors(&iSRC_LIST_1_SP5A, &iSRC_LIST_2_SP5A, &RX_SP0A_BUFFER_LCRSW0[0], &RX_SP0A_BUFFER_LCRSW1[0], 128, 4);
		iSRC_LIST_1_SP5A.Config |= ENUM_DMA_CFG_XCNT_INT;
		iSRC_LIST_2_SP5A.Config |= ENUM_DMA_CFG_XCNT_INT;
	}
	else
#endif
	{
		PrepareRxDescriptors(&iSRC_LIST_1_SP0A, &iSRC_LIST_2_SP0A, &RX_SP0A_BUFFER_LCRSW0[0], &RX_SP0A_BUFFER_LCRSW1[0], 128, 4);
		PrepareRxDescriptors(&iSRC_LIST_3_SP0B, &iSRC_LIST_4_SP0B, &RX_SP0B_BUFFER_LsLsrRsRsr0[0], &RX_SP0B_BUFFER_LsLsrRsRsr1[0], 128, 4);

		iSRC_LIST_1_SP0A.Config |= ENUM_DMA_CFG_XCNT_INT;
		iSRC_LIST_2_SP0A.Config |= ENUM_DMA_CFG_XCNT_INT;
		iSRC_LIST_3_SP0B.Config |= ENUM_DMA_CFG_XCNT_INT;
		iSRC_LIST_4_SP0B.Config |= ENUM_DMA_CFG_XCNT_INT;
	}
	#ifdef BEO_Framework
		PrepareTxDescriptors(&iDESC_LIST_11_SP2A, &iDESC_LIST_12_SP2A, &TX_SP2A_BUFFER_LCRSW0[0], &TX_SP2A_BUFFER_LCRSW1[0], 128, 4);
		PrepareTxDescriptors(&iDESC_LIST_13_SP2B, &iDESC_LIST_14_SP2B, &TX_SP2B_BUFFER_LsLsrRsRsr0[0], &TX_SP2B_BUFFER_LsLsrRsRsr1[0], 128, 4);
		PrepareTxDescriptors(&iDESC_LIST_5_SP3A, &iDESC_LIST_6_SP3A,&TX_SP3A_BUFFER_Addch1ch3ch2ch4_set0[0], &TX_SP3A_BUFFER_Addch1ch3ch2ch4_set1[0], 128, 4);
		PrepareTxDescriptors(&iDESC_LIST_7_SP3B, &iDESC_LIST_8_SP3B, &TX_SP3B_BUFFER_Addch5ch7ch6ch8_set0[0], &TX_SP3B_BUFFER_Addch5ch7ch6ch8_set1[0], 128, 4);

		iDESC_LIST_11_SP2A.Config  = ENUM_DMA_CFG_XCNT_INT;
		iDESC_LIST_12_SP2A.Config  = ENUM_DMA_CFG_XCNT_INT;
		iDESC_LIST_13_SP2B.Config  = ENUM_DMA_CFG_XCNT_INT;
		iDESC_LIST_14_SP2B.Config  = ENUM_DMA_CFG_XCNT_INT;
		iDESC_LIST_5_SP3A.Config  = ENUM_DMA_CFG_XCNT_INT;
		iDESC_LIST_6_SP3A.Config  = ENUM_DMA_CFG_XCNT_INT;
		iDESC_LIST_7_SP3B.Config  = ENUM_DMA_CFG_XCNT_INT;
		iDESC_LIST_8_SP3B.Config  = ENUM_DMA_CFG_XCNT_INT;
   	#endif /* BEO_Framework */
#ifdef SPDIF_MODULE
	if (SPDIF_Enable == 1)
	{
		Result = adi_sport_DMATransfer(hSPORT5ARx,&iSRC_LIST_1_SP5A,2,ADI_PDMA_DESCRIPTOR_LIST, ADI_SPORT_CHANNEL_PRIM_SEC);
	}
	else
#endif
	{
		Result = adi_sport_DMATransfer(hSPORT0ARx,&iSRC_LIST_1_SP0A,2,ADI_PDMA_DESCRIPTOR_LIST, ADI_SPORT_CHANNEL_PRIM_SEC);
		Result = adi_sport_DMATransfer(hSPORT0BRx,&iSRC_LIST_3_SP0B,2,ADI_PDMA_DESCRIPTOR_LIST, ADI_SPORT_CHANNEL_PRIM_SEC);
	}
	#ifdef BEO_Framework

		Result = adi_sport_DMATransfer(hSPORT2ATx,&iDESC_LIST_11_SP2A,2,ADI_PDMA_DESCRIPTOR_LIST, ADI_SPORT_CHANNEL_PRIM_SEC);
		Result = adi_sport_DMATransfer(hSPORT2BTx,&iDESC_LIST_13_SP2B,2,ADI_PDMA_DESCRIPTOR_LIST, ADI_SPORT_CHANNEL_PRIM_SEC);
		Result = adi_sport_DMATransfer(hSPORT3ATx,&iDESC_LIST_5_SP3A,2,ADI_PDMA_DESCRIPTOR_LIST, ADI_SPORT_CHANNEL_PRIM_SEC);
		Result = adi_sport_DMATransfer(hSPORT3BTx,&iDESC_LIST_7_SP3B,2,ADI_PDMA_DESCRIPTOR_LIST, ADI_SPORT_CHANNEL_PRIM_SEC);
	#endif /* BEO_Framework */
	/* This should be called only after setting up the DMA transfer */

	#ifdef BEO_Framework
		//For ASRC & ASRC_TDM mode
		SportTxDai0Array[0]= hSPORT2ATx;
		SportTxDai0Array[1]= hSPORT2BTx;
		SportTxDai0Array[2]= hSPORT3ATx;
		SportTxDai0Array[3]= hSPORT3BTx;

		/* Create DAI0 TX Group 0 */
		Result = adi_sport_CreateGlobalGroup(SportTxDai0Array,4u,&hDai0Group0Tx,false,true);
	#endif /*  BEO_Framework */

#ifdef SPDIF_MODULE
	if (SPDIF_Enable == 1)
	{
		SportRxDai1Array[0]= hSPORT5ARx;
		/* Create DAI1 RX Group 1 */
		Result = adi_sport_CreateGlobalGroup(SportRxDai1Array,1u,&hDai1Group1Rx,false,true);
		/* Register RX group callback */
		Result = adi_sport_GlobalRegisterCallback(hDai1Group1Rx, (ADI_CALLBACK)Rx_DMA_HANDLER, NULL);
	}
	else
#endif
	{
		SportRxDai0Array[0]= hSPORT0ARx;
		SportRxDai0Array[1]= hSPORT0BRx;

		Result = adi_sport_CreateGlobalGroup(SportRxDai0Array,2u,&hDai0Group1Rx,false,true);
		/* Register RX group callback */
		Result = adi_sport_GlobalRegisterCallback(hDai0Group1Rx, (ADI_CALLBACK)Rx_DMA_HANDLER, NULL);
	}



	#ifdef BEO_Framework
	if((I2S_TDM_MODE == I2S_MODE) || (I2S_TDM_MODE == ASRC_TDM_MODE))
	{
		/* Register TX group callback */
		Result = adi_sport_GlobalRegisterCallback(hDai0Group0Tx, (ADI_CALLBACK)Tx_DMA_HANDLER, NULL);
	}
	#endif /* BEO_Framework */

}

/******************************************************************************
 *  Module Name        : SPORT_Recongifuration
 *  Functionality      : SPORT_Recongifuration Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
void SPORT_Recongifuration(void)
{
#ifdef SPDIF_MODULE
	if (Prev_SPDIF_Enable == 1)
	{
		Spdif_Rx_Stop();
	}
#endif
	adi_sport_GlobalEnable(false);

	/* Destroy global groups */
	Clear_Global_Interrupt();

	spdif_status_valid_output_muted = 0;

	#ifdef BEO_Framework
	adi_sport_GlobalRegisterCallback(hDai0Group0Tx, NULL, NULL);
	adi_sport_DestroyGlobalGroup(hDai0Group0Tx);
	#endif /* BEO_Framework */

	#ifdef BEO_Framework
		adi_sport_Close(hSPORT2ATx);
		adi_sport_Close(hSPORT2BTx);
		adi_sport_Close(hSPORT3ATx);
		adi_sport_Close(hSPORT3BTx);
	#endif/* BEO_Framework */

	prev_I2S_TDM_Mode = I2S_TDM_MODE;

#ifdef SPDIF_MODULE
	if (Prev_SPDIF_Enable == 1)
	{
		adi_sport_GlobalRegisterCallback(hDai1Group1Rx, NULL, NULL);
		adi_sport_DestroyGlobalGroup(hDai1Group1Rx);
		adi_sport_Close(hSPORT5ARx);
		Prev_SPDIF_Enable=0;
	}
	else
#endif
	{
		adi_sport_GlobalRegisterCallback(hDai0Group1Rx, NULL, NULL);
		adi_sport_DestroyGlobalGroup(hDai0Group1Rx);
		adi_sport_Close(hSPORT0ARx);
		adi_sport_Close(hSPORT0BRx);
	}

#ifdef I2S_TDM_MODE_ENABLE
	TX_Buf_Ptr_Allocation();
#endif
	#ifdef BEO_Framework
		adi_pcg_Init(ADI_PCG_DEV_B,0,0);
		adi_pcg_Init(ADI_PCG_DEV_C,0,0);
		SRC_Init();
	#endif /* BEO_Framework */	


	DAI_Init();
	SPORT_Init();

	/* Set global enable bit */
	adi_sport_GlobalEnable(true);
	Set_Global_Interrupt();
}

#if defined (USE_MDMA_EXTCHANNEL) || defined (TX_NEW_LOGIC)
/**************************************************************************************************
 *  Module Name        : EXTMDMA_Init
 *  Functionality      : External Memory DMA Security bit configuration
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
void EXTMDMA_Init(void)
{

	//  *pREG_SPU0_SECUREP93=0x3;
	adi_mdma_Open (ADI_DMA_MEMDMA_S0,
			&MemDmaStreamMem[0],
			&hMemDmaStream,
			&hSrcDmaChannel,
			&hDestDmaChannel,
			NULL,
			NULL);

	adi_mdma_Open (ADI_DMA_MEMDMA_S3,
			&MemDmaStreamMem1[0],
			&hMemDmaStream1,
			&hSrcDmaChannel1,
			&hDestDmaChannel1,
			NULL,
			NULL);

}
#define SMSIZE3 32
#define DMSIZE3 32

/**************************************************************************************************
 *  Module Name        : EXTMDMA_enable
 *  Functionality      : External DMA enable copy data from external predac buffer to internal buffer
 *  					 add offset to dest_buffer
 *  Input Parameters   : BuffSize, SrcBuff
 *  Output Parameters  : DstBuff
 **************************************************************************************************/
void EXTMDMA_enable(int BuffSize, int SrcBuff, int DstBuff)
{
	adi_mdma_Copy1D(
			hMemDmaStream,
			(void*)DstBuff,
			(void*)SrcBuff,
			ADI_DMA_MSIZE_4BYTES,
			BuffSize);

}
/**************************************************************************************************
 *  Module Name        : Predac_Buffer_Ext_To_Predac_Buffer_Int_DMA
 *  Functionality      : Predac_Buffer_Ext_To_Predac_Buffer_Int_DMA copy data from external predac
 *                       buffer to internal predac buffer
 *  Input Parameters   : BuffSize, SrcBuff
 *  Output Parameters  : DstBuff
 **************************************************************************************************/
void Predac_Buffer_Ext_To_Predac_Buffer_Int_DMA(int BuffSize, int SrcBuff, int DstBuff)
{
	adi_mdma_Copy1D(
			hMemDmaStream1,
			(void*)DstBuff,
			(void*)SrcBuff,
			ADI_DMA_MSIZE_4BYTES,
			BuffSize);
}

#endif /* End of #if defined (USE_MDMA_EXTCHANNEL) || defined (TX_NEW_LOGIC)	*/
/**************************************************************************************************
 *  Module Name        : SRC_Init
 *  Functionality      : To enable the ASRC
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
#ifdef BEO_Framework
#pragma section("Seg_Kernal_Code_L3")
void SRC_Init(void)
{
	#ifdef BEO_Framework
	if(I2S_TDM_MODE == ASRC_TDM_MODE)
	{
		adi_asrc_Open(0u,                    /* Block number */
					 0u,                     /* Device number */
					gAsrcMem0,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc0);

		adi_asrc_Open(0u,                    /* Block number */
					 1u,                     /* Device number */
					gAsrcMem1,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc1);

		adi_asrc_Open(0u,                    /* Block number */
					2u,                      /* Device number */
					gAsrcMem2,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc2);

		adi_asrc_Open(0u,                   /* Block number */
					 3u,                    /* Device number */
					gAsrcMem3,              /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,   /* Memory Size */
					&hAsrc3);

	    adi_asrc_SetSerialFormat(hAsrc0, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc1, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc2, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc3, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);

		adi_asrc_Open(1u,                    /* Block number */
					 0u,                     /* Device number */
					gAsrcMem4,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc4);

		adi_asrc_Open(1u,                    /* Block number */
					1u,                     /* Device number */
					gAsrcMem5,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc5);

		adi_asrc_Open(1u,                    /* Block number */
					2u,                      /* Device number */
					gAsrcMem6,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc6);

		adi_asrc_Open(1u,                   /* Block number */
					 3u,                    /* Device number */
					gAsrcMem7,              /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,   /* Memory Size */
					&hAsrc7);

		adi_asrc_SetSerialFormat(hAsrc4, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc5, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc6, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc7, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_Enable(hAsrc0,true);
		adi_asrc_Enable(hAsrc1,true);
		adi_asrc_Enable(hAsrc2,true);
		adi_asrc_Enable(hAsrc3,true);
		adi_asrc_Enable(hAsrc4,true);
		adi_asrc_Enable(hAsrc5,true);
		adi_asrc_Enable(hAsrc6,true);
		adi_asrc_Enable(hAsrc7,true);
	}
	#else
	adi_asrc_Open(0u,                    /* Block number */
				 0u,                     /* Device number */
				gAsrcMem0,               /* Pointer to Memory */
				ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
				&hAsrc0);

	adi_asrc_Open(0u,                    /* Block number */
				 1u,                     /* Device number */
				gAsrcMem1,               /* Pointer to Memory */
				ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
				&hAsrc1);

	adi_asrc_Open(0u,                    /* Block number */
				2u,                      /* Device number */
				gAsrcMem2,               /* Pointer to Memory */
				ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
				&hAsrc2);

	adi_asrc_Open(0u,                   /* Block number */
				 3u,                    /* Device number */
				gAsrcMem3,              /* Pointer to Memory */
				ADI_ASRC_MEMORY_SIZE,   /* Memory Size */
				&hAsrc3);

	adi_asrc_Enable(hAsrc0,true);
	adi_asrc_Enable(hAsrc1,true);
	adi_asrc_Enable(hAsrc2,true);
	adi_asrc_Enable(hAsrc3,true);
	#endif /* BEO_Framework */
}
#else
#pragma section("Seg_Kernal_Code_L3")
void SRC_Init(void)
{
#ifdef ASRC_ENABLE
	if(I2S_TDM_MODE == ASRC_MODE)
	{
	adi_asrc_Open(0u,                    /* Block number */
			0u,                     /* Device number */
			gAsrcMem0,               /* Pointer to Memory */
			ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
			&hAsrc0);

	adi_asrc_Open(0u,                    /* Block number */
			1u,                     /* Device number */
			gAsrcMem1,               /* Pointer to Memory */
			ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
			&hAsrc1);

	adi_asrc_Open(0u,                    /* Block number */
			2u,                      /* Device number */
			gAsrcMem2,               /* Pointer to Memory */
			ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
			&hAsrc2);

	adi_asrc_Open(0u,                   /* Block number */
			3u,                    /* Device number */
			gAsrcMem3,              /* Pointer to Memory */
			ADI_ASRC_MEMORY_SIZE,   /* Memory Size */
			&hAsrc3);

		adi_asrc_SetSerialFormat(hAsrc0, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc1, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc2, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc3, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_Open(1u,                    /* Block number */
					 0u,                     /* Device number */
					gAsrcMem4,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc4);
		adi_asrc_Open(1u,                    /* Block number */
					1u,                     /* Device number */
					gAsrcMem5,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc5);
		adi_asrc_Open(1u,                    /* Block number */
					2u,                      /* Device number */
					gAsrcMem6,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc6);
		adi_asrc_Open(1u,                   /* Block number */
					3u,                    /* Device number */
					gAsrcMem7,              /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,   /* Memory Size */
					&hAsrc7);
		adi_asrc_SetSerialFormat(hAsrc4, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc5, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc6, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc7, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
	adi_asrc_Enable(hAsrc0,true);
	adi_asrc_Enable(hAsrc1,true);
	adi_asrc_Enable(hAsrc2,true);
	adi_asrc_Enable(hAsrc3,true);
		adi_asrc_Enable(hAsrc4,true);
		adi_asrc_Enable(hAsrc5,true);
		adi_asrc_Enable(hAsrc6,true);
		adi_asrc_Enable(hAsrc7,true);
	}
	else if(I2S_TDM_MODE == ASRC_TDM_MODE)
	{
		adi_asrc_Open(0u,                    /* Block number */
					 0u,                     /* Device number */
					gAsrcMem0,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc0);
		adi_asrc_Open(0u,                    /* Block number */
					 1u,                     /* Device number */
					gAsrcMem1,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc1);
		adi_asrc_Open(0u,                    /* Block number */
					2u,                      /* Device number */
					gAsrcMem2,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc2);
		adi_asrc_Open(0u,                   /* Block number */
					 3u,                    /* Device number */
					gAsrcMem3,              /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,   /* Memory Size */
					&hAsrc3);
	    adi_asrc_SetSerialFormat(hAsrc0, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc1, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc2, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc3, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_Open(1u,                    /* Block number */
					 0u,                     /* Device number */
					gAsrcMem4,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc4);
		adi_asrc_Open(1u,                    /* Block number */
					1u,                     /* Device number */
					gAsrcMem5,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc5);
		adi_asrc_Open(1u,                    /* Block number */
					2u,                      /* Device number */
					gAsrcMem6,               /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,    /* Memory Size */
					&hAsrc6);
		adi_asrc_Open(1u,                   /* Block number */
					 3u,                    /* Device number */
					gAsrcMem7,              /* Pointer to Memory */
					ADI_ASRC_MEMORY_SIZE,   /* Memory Size */
					&hAsrc7);
		adi_asrc_SetSerialFormat(hAsrc4, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc5, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc6, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_SetSerialFormat(hAsrc7, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_TDM, ADI_ASRC_WORD_LENGTH_24);
		adi_asrc_Enable(hAsrc0,true);
		adi_asrc_Enable(hAsrc1,true);
		adi_asrc_Enable(hAsrc2,true);
		adi_asrc_Enable(hAsrc3,true);
		adi_asrc_Enable(hAsrc4,true);
		adi_asrc_Enable(hAsrc5,true);
		adi_asrc_Enable(hAsrc6,true);
		adi_asrc_Enable(hAsrc7,true);
	}
#endif
}
#endif /* BEO_Framework */
/**************************************************************************************************
 *  Module Name        : PCG_Init
 *  Functionality      : To enable the PCG C
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
#ifdef BEO_Framework
#pragma section("Seg_Kernal_Code_L3")
void PCG_Init(void)
{
//	if (SPDIF_Enable == 1)
//	{
//		ADI_PCG_CLK_INFO gClkInfo_C;
//		gClkInfo_C.eClkInput = ADI_PCG_CLK_EXT;                /* Clock Source */
//		gClkInfo_C.nDiv = Mclk_48Khz/64;                                  /* Clock Divisor */
//		gClkInfo_C.bExternalTrigger = false;                   /* External Trigger */
//
//		ADI_PCG_FS_INFO gFsInfo_C;
//		gFsInfo_C.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_CLK_EXT;                	  /* Clock Source */
//		gFsInfo_C.nDiv = Mclk_48Khz;                                    /* Frame Sync Divisor */
//		gFsInfo_C.nPulseWidth = (gFsInfo_C.nDiv)/2u;              /* Pulse Width */
//		gFsInfo_C.nPhase = gClkInfo_C.nDiv/2;                     /* Phase */
//		gFsInfo_C.bExternalTrigger = false;                       /* External Trigger */
//		gFsInfo_C.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */
//
//		adi_pcg_Init(ADI_PCG_DEV_C,&gClkInfo_C,&gFsInfo_C);
//	}
//	else
//	{
		ADI_PCG_CLK_INFO gClkInfo_C;
		gClkInfo_C.eClkInput = ADI_PCG_CLK_EXT;                /* Clock Source */
		gClkInfo_C.nDiv = BEO_CLK_DIV/64;                                  /* Clock Divisor */
		gClkInfo_C.bExternalTrigger = false;                   /* External Trigger */
		gClkInfo_C.bHwTriggerCtl= false;

		ADI_PCG_FS_INFO gFsInfo_C;
		gFsInfo_C.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_CLK_EXT;                	  /* Clock Source */
		gFsInfo_C.nDiv = BEO_CLK_DIV;                                    /* Frame Sync Divisor */
		gFsInfo_C.nPulseWidth = (gFsInfo_C.nDiv)/2u;              /* Pulse Width */
		gFsInfo_C.nPhase = gClkInfo_C.nDiv/2;                     /* Phase */
		gFsInfo_C.bExternalTrigger = false;                       /* External Trigger */
		gFsInfo_C.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */

		adi_pcg_Init(ADI_PCG_DEV_C,&gClkInfo_C,&gFsInfo_C);
//	}

	Asrc_SRU_Reconfigure();
	Prev_Clock_Div_Value = Mclk_48Khz;
}

#else
#pragma section("Seg_Kernal_Code_L3")
void PCG_Init(void)
{
#ifdef I2S_TDM_MODE_ENABLE
	if((I2S_TDM_MODE == I2S_MODE)||(I2S_TDM_MODE == ASRC_MODE)||(I2S_TDM_MODE == ASRC_TDM_MODE))
#endif
	{
#ifdef SPDIF_MODULE
	if (SPDIF_Enable == 1)
	{
		int  CLKDIV = 4;           //  default case FS2_FS1
		int CLKPHASE;

		CLKPHASE = ((3+CLKDIV/2)%CLKDIV);    //To synchronize 64*fs2 with fs1 and it's falling edge with fs2

		ADI_PCG_CLK_INFO gClkInfo_C;
		gClkInfo_C.eClkInput = ADI_PCG_CLK_EXT;      	      /* Clock Source */
		gClkInfo_C.nDiv = 0u;          					      /* Clock Divisor */
		gClkInfo_C.bExternalTrigger = false;                  /* External Trigger */

		ADI_PCG_FS_INFO gFsInfo_C;
		gFsInfo_C.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_FS_EXT;                     /* Clock Source */
		gFsInfo_C.nDiv = CLKDIV;     				              /* Frame Sync Divisor */
		gFsInfo_C.nPulseWidth = CLKDIV/2;                         /* Pulse Width */
		gFsInfo_C.nPhase = CLKPHASE;                              /* Phase */
		gFsInfo_C.bExternalTrigger = true;                        /* External Trigger */
		gFsInfo_C.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */

		ADI_PCG_CLK_INFO gClkInfo_D;
		gClkInfo_D.eClkInput = ADI_PCG_CLK_EXT;      	/* Clock Source */
		gClkInfo_D.nDiv = 0u;          					/* Clock Divisor */
		gClkInfo_D.bExternalTrigger = false;            /* External Trigger */

		ADI_PCG_FS_INFO gFsInfo_D;
		gFsInfo_D.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_FS_EXT;                    /* Clock Source */
		gFsInfo_D.nDiv = 64*CLKDIV;     				         /* Frame Sync Divisor */
		gFsInfo_D.nPulseWidth = 32*CLKDIV;                       /* Pulse Width */
		gFsInfo_D.nPhase = FSPHASE;                              /* Phase */
		gFsInfo_D.bExternalTrigger = true;                       /* External Trigger */
		gFsInfo_D.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;  /* Bypass Mode */

		adi_pcg_Init(ADI_PCG_DEV_C,&gClkInfo_C,&gFsInfo_C);
		adi_pcg_Init(ADI_PCG_DEV_D,&gClkInfo_D,&gFsInfo_D);
	}
	else
#endif
	{
	
		
			ADI_PCG_CLK_INFO gClkInfo_C;
			gClkInfo_C.eClkInput = ADI_PCG_CLK_EXT;                /* Clock Source */
			gClkInfo_C.nDiv = Mclk_48Khz/64;                                  /* Clock Divisor */
			gClkInfo_C.bExternalTrigger = false;                   /* External Trigger */
			gClkInfo_C.bHwTriggerCtl= false;

			ADI_PCG_FS_INFO gFsInfo_C;
			gFsInfo_C.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_CLK_EXT;                	  /* Clock Source */
			gFsInfo_C.nDiv = Mclk_48Khz;                                    /* Frame Sync Divisor */
			gFsInfo_C.nPulseWidth = (gFsInfo_C.nDiv)/2u;              /* Pulse Width */
			gFsInfo_C.nPhase = gClkInfo_C.nDiv/2;                     /* Phase */
			gFsInfo_C.bExternalTrigger = false;                       /* External Trigger */
			gFsInfo_C.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */

			adi_pcg_Init(ADI_PCG_DEV_C,&gClkInfo_C,&gFsInfo_C);
		
		}
	}

#ifdef I2S_TDM_MODE_ENABLE	
	else if(I2S_TDM_MODE == TDM_MODE)
#endif
	{
		ADI_PCG_CLK_INFO gClkInfo_C;
		gClkInfo_C.eClkInput = ADI_PCG_CLK_EXT;                /* Clock Source */
		gClkInfo_C.nDiv = Mclk_48Khz/256;                                  /* Clock Divisor */
		gClkInfo_C.bExternalTrigger = false;                   /* External Trigger */
		gClkInfo_C.bHwTriggerCtl= false;

		ADI_PCG_FS_INFO gFsInfo_C;
		gFsInfo_C.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_CLK_EXT;                	  /* Clock Source */
		gFsInfo_C.nDiv = Mclk_48Khz;                                    /* Frame Sync Divisor */
		gFsInfo_C.nPulseWidth = (gFsInfo_C.nDiv)/256u;              /* Pulse Width */
		gFsInfo_C.nPhase = 0;									  /* Phase */
		gFsInfo_C.bExternalTrigger = false;                       /* External Trigger */
		gFsInfo_C.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */

		adi_pcg_Init(ADI_PCG_DEV_C,&gClkInfo_C,&gFsInfo_C);
	}
#ifdef ASRC_ENABLE
if((I2S_TDM_MODE == ASRC_MODE)||(I2S_TDM_MODE == ASRC_TDM_MODE))
{
	Asrc_SRU_Reconfigure();
}
#endif
	Prev_Clock_Div_Value = Mclk_48Khz;
}
#endif //BEO_Framework

#ifdef BEO_Framework
#pragma section("Seg_Kernal_Code_L3")
void Asrc_SRU_Reconfigure()
{
//	if(I2S_TDM_MODE == ASRC_TDM_MODE)
//	{
		ADI_PCG_CLK_INFO gClkInfo_B;
		gClkInfo_B.eClkInput = ADI_PCG_CLK_EXT;             /* Clock Source */
		#ifdef ASRC_TDM16
		gClkInfo_B.nDiv = 1u;                  				/* Clock Divisor */
		#endif /* ASRC_TDM16 */
		#ifdef ASRC_TDM8
		gClkInfo_B.nDiv = FS_Div_Value/256u;                  				/* Clock Divisor */
		#endif /* ASRC_TDM8 */
		gClkInfo_B.bExternalTrigger = true;                /* External Trigger */
		gClkInfo_B.bHwTriggerCtl= false;

		ADI_PCG_FS_INFO gFsInfo_B;
		gFsInfo_B.eClkInput = ADI_PCG_FS_EXT;                	/* Clock Source */
		gFsInfo_B.nDiv = 512;//FS_Div_Value;                            /* Frame Sync Divisor */
		gFsInfo_B.nPulseWidth = (gFsInfo_B.nDiv)/256u;                /* Pulse Width */
		gFsInfo_B.nPhase = 3;                       /* Phase */
		gFsInfo_B.bExternalTrigger = true;                       /* External Trigger */
		gFsInfo_B.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */

		adi_pcg_Init(ADI_PCG_DEV_B,&gClkInfo_B,&gFsInfo_B);
//	}
}
#endif /* BEO_Framework */
/**************************************************************************************************
 *  Module Name        : SPU_Init
 *  Functionality      : Initialize SPU Service and enabling the SPU
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
#pragma section("Seg_Kernal_Code_L3")
void SPU_Init(void)
{
	/* Memory required for the SPU operation */
	uint8_t SpuMemory[ADI_SPU_MEMORY_SIZE];

	/* SPU handle */
	ADI_SPU_HANDLE hSpu;

	ADI_SPU_RESULT eResult;

	/* Initialize SPU Service */
	eResult= adi_spu_Init(0u, SpuMemory, NULL, NULL, &hSpu);
#ifdef SPDIF_MODULE
	adi_spu_EnableMasterSecure(hSpu, SPORT5A_DMA_SPU_ID, true);
#endif
	adi_spu_EnableMasterSecure(hSpu, SPORT0A_DMA_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, SPORT0B_DMA_SPU_ID, true);
#ifdef DSD2PCM_DEC
	adi_spu_EnableMasterSecure(hSpu, SPORT1A_DMA_SPU_ID, true);
#endif

	adi_spu_EnableMasterSecure(hSpu, SPORT2A_DMA_SPU_ID, true);
	#ifdef BEO_Framework
    adi_spu_EnableMasterSecure(hSpu, SPORT2B_DMA_SPU_ID, true);
	#endif /* BEO_Framework */
	adi_spu_EnableMasterSecure(hSpu, SPORT3A_DMA_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, SPORT3B_DMA_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, SPORT4A_DMA_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, SPORT4B_DMA_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, SPORT6A_DMA_SPU_ID, true);

	if (SPI_Device == 1)
	{
		adi_spu_EnableMasterSecure(hSpu, SPI1_RXDMA_SPU_ID, true);
		adi_spu_EnableMasterSecure(hSpu, SPI1_TXDMA_SPU_ID, true);

	}
	else
	{
		adi_spu_EnableMasterSecure(hSpu, SPI0_TXDMA_SPU_ID, true);
		adi_spu_EnableMasterSecure(hSpu, SPI0_RXDMA_SPU_ID, true);
	}
	adi_spu_EnableMasterSecure(hSpu, MDMA0_SRC_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, MDMA0_DST_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, MDMA3_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, MDMA1_SRC_SPU_ID, true);
	adi_spu_EnableMasterSecure(hSpu, MDMA1_DST_SPU_ID, true);
}
#ifdef DSD2PCM_DEC
/**************************************************************************************************
 *  Module Name        : SystemInitialisation_DSD2PCM
 *  Functionality      :
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
#pragma section("seg_DSD2PCM_Code")
void SystemInitialisation_DSD2PCM()
{
	Kernal_Default_Init_DSD2PCM();
#ifdef DSD2PCM_TESTING
	Default_Command_Config();
	DSD2PCM_COMMAND();
	Frmwk.sampling_fs_micro = 2;
	Frmwk.OutputSampleRate = 2;
#endif
}
/**************************************************************************************************

 *  Module Name        : Kernal_Default_Init_DSD2PCM
 *  Functionality      :
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
void Kernal_Default_Init_DSD2PCM()
{
	Frmwk.autodetect_mode = FORCEPCM3;

	AllocateMemoryKernel_DSD2PCM();

	Free_AllotMemoryPackDac(Frmwk.pack_length_DSD2PCM, Frmwk.predac_length_DSD2PCM, Frmwk.addpredac_length_DSD2PCM);
	Frmwk.SampleBlock 			= Frmwk.IOP.Predac.lengthhalf/NO_OF_PREDAC_CHANNEL;
}
#endif
/**************************************************************************************************
 *  Module Name        : SpdifRxInit
 *  Functionality      : Initialize SPDIF Service and enabling the SPDIF
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
#ifdef SPDIF_MODULE
#pragma section("Seg_Kernal_Code_L3")
void SpdifRxInit(void)
{
	adi_spdif_Rx_Open(1,SpdifRxMemory,ADI_SPDIF_RX_MEMORY_SIZE,&hSpdifRx);

	adi_dai_init(1);
	Result = adi_spdif_Rx_RegisterCallback(hSpdifRx,Spdif_Rx_ISR,NULL);
	adi_spdif_Rx_Enable(hSpdifRx,true);

	adi_spdif_Rx_SetTdmsel(hSpdifRx,ADI_SPDIF_RX_SF_96K_OR_LOWER);
	adi_spdif_Rx_RestartAudio (hSpdifRx);
    Prev_SPDIF_Enable = SPDIF_Enable;
}
#endif
/**************************************************************************************************
 *  Module Name        : Spdif_Rx_Stop
 *  Functionality      : Stop SPDIF Processing
 *  Input Parameters   : None
 *  Output Parameters  : None
 **************************************************************************************************/
#ifdef SPDIF_MODULE
#pragma section("Seg_Kernal_Code_L3")
void Spdif_Rx_Stop(void)
{
	Result = adi_spdif_Rx_RegisterCallback(hSpdifRx,NULL,NULL);
	adi_dai_init(0);
	adi_spdif_Rx_Enable(hSpdifRx,false);
	adi_spdif_Rx_Close(hSpdifRx);
}
#endif
/******************************************************************************
 *  Module Name        : TMU_Init
 *  Functionality      : Initialization of Temp_Measurement
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
void TMU_Init()
{
	/* open the TMU driver */
	result = adi_tmu_Open(0u, TMUDriverMemory, (uint32_t)ADI_TMU_MEMORY_SIZE, &hDevice);
	if(result != ADI_TMU_SUCCESS)
	{
		REPORT_ERROR("Failed to open the TMU Device \n");
	}

	/* Configure the TMU for no Hardware Averaging, Continuous mode, SCLK Div as 3 */
	result = adi_tmu_ConfigureTMU(
			hDevice,
			true,
			true,
			false,
			3
	);
	if(result != ADI_TMU_SUCCESS)
	{
		REPORT_ERROR("Failed to open the TMU Device \n");
	}

	/* Enable TMU */
	result = adi_tmu_Enable(hDevice, true);
	if(result != ADI_TMU_SUCCESS)
	{
		REPORT_ERROR("Failed to open the TMU Device \n");
	}

	/* Enable Temperature conversion */
	result = adi_tmu_EnableConversion(hDevice, true);
	if(result != ADI_TMU_SUCCESS)
	{
		REPORT_ERROR("Failed to open the TMU Device \n");
	}

	/*Set Gain*/
	result = adi_tmu_SetGain_Raw(hDevice, 1.004);
	if(result != ADI_TMU_SUCCESS)
	{
		REPORT_ERROR("Failed to set Gain \n");
	}

	/*Set Offset*/
	result = adi_tmu_SetOffset(hDevice, -4.75);
	if(result != ADI_TMU_SUCCESS)
	{
		REPORT_ERROR("Failed to set Offset \n");
	}
}
/******************************************************************************
 *  Module Name        : TMU_Monitoring
 *  Functionality      : Temp_Measurement
 *  Input Parameters   : None
 *  Output Parameters  : None
 ******************************************************************************/
#pragma section("Seg_Cmd_Code")
#ifdef TMU
void TMU_Monitoring()
{
	/* Read the TMU temperature */
	result = adi_tmu_ReadTemperature(hDevice, &TMU_Value);
	if(result != ADI_TMU_SUCCESS)
	{
		REPORT_ERROR("Failed to open the TMU Device \n");
	}
}
#endif
#ifdef BEO_Framework
#pragma section("Seg_Kernal_Code_L3")
void ASRC_DAI_Init()
{
/*******************************************************************/
	/*	PCGC BIT_CLK AND LR_CLK to SPORT'S	*/
	
	SRU(PCG0_INV_CLKC_O,SPT2_ACLK_I);		//SPORT2A TX
	SRU(PCG0_INV_CLKC_O,SPT2_BCLK_I);		//SPORT2B TX
	SRU(PCG0_INV_CLKC_O,SPT3_ACLK_I); 		//SPORT3A TX
	SRU(PCG0_INV_CLKC_O,SPT3_BCLK_I); 		//SPORT3B TX

	SRU(PCG0_FSC_O,SPT2_AFS_I);			//SPORT2A TX
	SRU(PCG0_FSC_O,SPT2_BFS_I);			//SPORT2B TX
	SRU(PCG0_FSC_O,SPT3_AFS_I);			//SPORT3A TX
	SRU(PCG0_FSC_O,SPT3_BFS_I);			//SPORT3B TX
/*******************************************************************/

/*******************************************************************/
	/*	PCG-C BIT_CLK AND LR_CLK to SRC INPUT	*/

	SRU(PCG0_INV_CLKC_O, SRC0_CLK_IP_I);
	SRU(PCG0_INV_CLKC_O, SRC1_CLK_IP_I);
	SRU(PCG0_INV_CLKC_O, SRC2_CLK_IP_I);
	SRU(PCG0_INV_CLKC_O, SRC3_CLK_IP_I);
	SRU(PCG0_INV_CLKC_O, SRC4_CLK_IP_I);
	SRU(PCG0_INV_CLKC_O, SRC5_CLK_IP_I);
	SRU(PCG0_INV_CLKC_O, SRC6_CLK_IP_I);
	SRU(PCG0_INV_CLKC_O, SRC7_CLK_IP_I);

	SRU(PCG0_FSC_O, SRC0_FS_IP_I);
	SRU(PCG0_FSC_O, SRC1_FS_IP_I);
	SRU(PCG0_FSC_O, SRC2_FS_IP_I);
	SRU(PCG0_FSC_O, SRC3_FS_IP_I);
	SRU(PCG0_FSC_O, SRC4_FS_IP_I);
	SRU(PCG0_FSC_O, SRC5_FS_IP_I);
	SRU(PCG0_FSC_O, SRC6_FS_IP_I);
	SRU(PCG0_FSC_O, SRC7_FS_IP_I);
/********************************************************************************/

/********************************************************************************/
	/*	PCG-B BIT_CLK AND LR_CLK to SRC OUTPUT	*/

	SRU(PCG0_INV_CLKB_O, SRC0_CLK_OP_I);
	SRU(PCG0_INV_CLKB_O, SRC1_CLK_OP_I);
	SRU(PCG0_INV_CLKB_O, SRC2_CLK_OP_I);
	SRU(PCG0_INV_CLKB_O, SRC3_CLK_OP_I);
	SRU(PCG0_INV_CLKB_O, SRC4_CLK_OP_I);
	SRU(PCG0_INV_CLKB_O, SRC5_CLK_OP_I);
	SRU(PCG0_INV_CLKB_O, SRC6_CLK_OP_I);
	SRU(PCG0_INV_CLKB_O, SRC7_CLK_OP_I);

	SRU(DAI1_PB04_O,SRC0_FS_OP_I);
	SRU(DAI1_PB04_O,SRC1_FS_OP_I);
	SRU(DAI1_PB04_O,SRC2_FS_OP_I);
	SRU(DAI1_PB04_O,SRC3_FS_OP_I);
	SRU(DAI1_PB04_O,SRC4_FS_OP_I);
	SRU(DAI1_PB04_O,SRC5_FS_OP_I);
	SRU(DAI1_PB04_O,SRC6_FS_OP_I);
	SRU(DAI1_PB04_O,SRC7_FS_OP_I);
/********************************************************************************/

/********************************************************************************/

	/*	DATA FROM SPORT TO SRC	*/
	SRU(SPT2_AD0_O,SRC0_DAT_IP_I);		// SPORT2A --> SRC0
	SRU(SPT2_AD1_O,SRC1_DAT_IP_I);		// SPORT2A --> SRC1
	SRU(SPT2_BD0_O,SRC2_DAT_IP_I);		// SPORT2B --> SRC2
	SRU(SPT2_BD1_O,SRC3_DAT_IP_I);		// SPORT2B --> SRC3

	SRU(SPT3_AD0_O,SRC4_DAT_IP_I);		// SPORT3A --> SRC4
	SRU(SPT3_AD1_O,SRC5_DAT_IP_I);		// SPORT3A --> SRC5
	SRU(SPT3_BD0_O,SRC6_DAT_IP_I );		// SPORT3B --> SRC6
	SRU(SPT3_BD1_O,SRC7_DAT_IP_I );		// SPORT3B --> SRC7
/********************************************************************************/

/********************************************************************************/
	/*	DATA FROM SRC TO DAI	*/

	SRU(HIGH,DAI1_PBEN10_I);

	SRU(SRC0_DAT_OP_O, DAI1_PB10_I);	// TDM output goes to D1.P10
	SRU(SRC1_DAT_OP_O, SRC0_TDM_OP_I);	// SRC6 --> SRC7, TDM Data
	SRU(SRC2_DAT_OP_O, SRC1_TDM_OP_I);	// SRC5 --> SRC6, TDM Data
	SRU(SRC3_DAT_OP_O, SRC2_TDM_OP_I);	// SRC4 --> SRC5, TDM Data
	SRU(SRC4_DAT_OP_O, SRC3_TDM_OP_I);	// SRC3 --> SRC4, TDM Data
	SRU(SRC5_DAT_OP_O, SRC4_TDM_OP_I);	// SRC2 --> SRC3, TDM Data
	SRU(SRC6_DAT_OP_O, SRC5_TDM_OP_I);	// SRC1 --> SRC2, TDM Data
	SRU(SRC7_DAT_OP_O, SRC6_TDM_OP_I);	// SRC0 --> SRC1, TDM Data
	SRU(LOW, SRC7_TDM_OP_I);

/********************************************************************************/
}
#endif /* BEO_Framework */

#ifdef ASRC_ENABLE
#pragma section("Seg_Kernal_Code_L3")
void ASRC_DAI_Init()
{
	SRU(LOW,DAI0_PBEN05_I);				// 24.576MHZ Crystal Osc Clock
	SRU(DAI0_PB05_O,DAI1_PB12_I);		// 24.576MHZ Crystal Osc Clock --> CODEC
	SRU(DAI0_PB05_O,PCG0_EXTCLKB_I);	// 24.576MHZ Crystal Osc Clock --> PCG-B
	if(I2S_TDM_MODE == ASRC_TDM_MODE)
	{
		SRU(PCG0_INV_CLKB_O,DAI1_PB03_I);	// PCGB_BIT_CLK --> CODEC_BIT_CLK
	}
	else if(I2S_TDM_MODE == ASRC_MODE)
	{
		SRU(PCG0_CLKB_O,DAI1_PB03_I);	// PCGB_BIT_CLK --> CODEC_BIT_CLK
	}
	SRU(PCG0_FSB_O,DAI1_PB04_I);		// PCGB_LR_CLK --> CODEC_LR_CLK

/*******************************************************************/
	/*	PCGC BIT_CLK AND LR_CLK to SPORT'S	*/

	SRU(PCG0_CLKC_O,SPT4_ACLK_I);		//SPORT4A TX
	SRU(PCG0_CLKC_O,SPT4_BCLK_I);		//SPORT4B TX
	SRU(PCG0_CLKC_O,SPT3_ACLK_I); 		//SPORT3A TX
	SRU(PCG0_CLKC_O,SPT3_BCLK_I); 		//SPORT3B TX

	SRU(PCG0_FSC_O,SPT4_AFS_I);			//SPORT4A TX
	SRU(PCG0_FSC_O,SPT4_BFS_I);			//SPORT4B TX
	SRU(PCG0_FSC_O,SPT3_AFS_I);			//SPORT3A TX
	SRU(PCG0_FSC_O,SPT3_BFS_I);			//SPORT3B TX
/*******************************************************************/

/*******************************************************************/
	/*	PCG-C BIT_CLK AND LR_CLK to SRC INPUT	*/

	SRU(PCG0_CLKC_O, SRC0_CLK_IP_I);	// PCG-C BIT_CLK to SRC0_BIT_CLK
	SRU(PCG0_CLKC_O, SRC1_CLK_IP_I);	// PCG-C BIT_CLK to SRC1_BIT_CLK
	SRU(PCG0_CLKC_O, SRC2_CLK_IP_I);	// PCG-C BIT_CLK to SRC2_BIT_CLK
	SRU(PCG0_CLKC_O, SRC3_CLK_IP_I);	// PCG-C BIT_CLK to SRC3_BIT_CLK
	SRU(PCG0_CLKC_O, SRC4_CLK_IP_I);	// PCG-C BIT_CLK to SRC4_BIT_CLK
	SRU(PCG0_CLKC_O, SRC5_CLK_IP_I);	// PCG-C BIT_CLK to SRC5_BIT_CLK
	SRU(PCG0_CLKC_O, SRC6_CLK_IP_I);	// PCG-C BIT_CLK to SRC6_BIT_CLK
	SRU(PCG0_CLKC_O, SRC7_CLK_IP_I);	// PCG-C BIT_CLK to SRC7_BIT_CLK

	SRU(PCG0_FSC_O, SRC0_FS_IP_I);		// PCG-C LR_CLK to SRC0_LR_CLK
	SRU(PCG0_FSC_O, SRC1_FS_IP_I);		// PCG-C LR_CLK to SRC1_LR_CLK
	SRU(PCG0_FSC_O, SRC2_FS_IP_I);		// PCG-C LR_CLK to SRC2_LR_CLK
	SRU(PCG0_FSC_O, SRC3_FS_IP_I);		// PCG-C LR_CLK to SRC3_LR_CLK
	SRU(PCG0_FSC_O, SRC4_FS_IP_I);		// PCG-C LR_CLK to SRC4_LR_CLK
	SRU(PCG0_FSC_O, SRC5_FS_IP_I);		// PCG-C LR_CLK to SRC5_LR_CLK
	SRU(PCG0_FSC_O, SRC6_FS_IP_I);		// PCG-C LR_CLK to SRC6_LR_CLK
	SRU(PCG0_FSC_O, SRC7_FS_IP_I);		// PCG-C LR_CLK to SRC7_LR_CLK
/********************************************************************************/

/********************************************************************************/
	/*	PCG-B BIT_CLK AND LR_CLK to SRC OUTPUT	*/

	SRU(PCG0_CLKB_O, SRC0_CLK_OP_I);	// PCG-B BIT_CLK to SRC0_BIT_CLK
	SRU(PCG0_CLKB_O, SRC1_CLK_OP_I);	// PCG-B BIT_CLK to SRC1_BIT_CLK
	SRU(PCG0_CLKB_O, SRC2_CLK_OP_I);	// PCG-B BIT_CLK to SRC2_BIT_CLK
	SRU(PCG0_CLKB_O, SRC3_CLK_OP_I);	// PCG-B BIT_CLK to SRC3_BIT_CLK
	SRU(PCG0_CLKB_O, SRC4_CLK_OP_I);	// PCG-B BIT_CLK to SRC4_BIT_CLK
	SRU(PCG0_CLKB_O, SRC5_CLK_OP_I);	// PCG-B BIT_CLK to SRC5_BIT_CLK
	SRU(PCG0_CLKB_O, SRC6_CLK_OP_I);	// PCG-B BIT_CLK to SRC6_BIT_CLK
	SRU(PCG0_CLKB_O, SRC7_CLK_OP_I);	// PCG-B BIT_CLK to SRC7_BIT_CLK

	SRU(PCG0_FSB_O,SRC0_FS_OP_I);		// PCG-B LR_CLK to SRC0_LR_CLK
	SRU(PCG0_FSB_O,SRC1_FS_OP_I);		// PCG-B LR_CLK to SRC1_LR_CLK
	SRU(PCG0_FSB_O,SRC2_FS_OP_I);		// PCG-B LR_CLK to SRC2_LR_CLK
	SRU(PCG0_FSB_O,SRC3_FS_OP_I);		// PCG-B LR_CLK to SRC3_LR_CLK
	SRU(PCG0_FSB_O,SRC4_FS_OP_I);		// PCG-B LR_CLK to SRC4_LR_CLK
	SRU(PCG0_FSB_O,SRC5_FS_OP_I);		// PCG-B LR_CLK to SRC5_LR_CLK
	SRU(PCG0_FSB_O,SRC6_FS_OP_I);		// PCG-B LR_CLK to SRC6_LR_CLK
	SRU(PCG0_FSB_O,SRC7_FS_OP_I);		// PCG-B LR_CLK to SRC7_LR_CLK
/********************************************************************************/

/********************************************************************************/
	/*	DATA FROM SPORT TO SRC	*/

	SRU(SPT4_AD0_O,SRC4_DAT_IP_I);		// SPORT4A --> SRC4
	SRU(SPT4_AD1_O,SRC5_DAT_IP_I);		// SPORT4A --> SRC5
	SRU(SPT4_BD0_O,SRC6_DAT_IP_I);		// SPORT4B --> SRC6
	SRU(SPT4_BD1_O,SRC7_DAT_IP_I);		// SPORT4B --> SRC7

	SRU(SPT3_AD0_O,SRC2_DAT_IP_I);		// SPORT3A --> SRC2
	SRU(SPT3_AD1_O,SRC3_DAT_IP_I);		// SPORT3A --> SRC3
	SRU(SPT3_BD0_O,SRC0_DAT_IP_I );		// SPORT3B --> SRC0
	SRU(SPT3_BD1_O,SRC1_DAT_IP_I );		// SPORT3B --> SRC1
/********************************************************************************/

/********************************************************************************/
	/*	DATA FROM SRC TO DAI	*/

	if(I2S_TDM_MODE == ASRC_TDM_MODE)
	{
		SRU(LOW,DAI1_PBEN09_I);
		SRU(LOW,DAI1_PBEN10_I);
		SRU(LOW,DAI1_PBEN11_I);

		SRU(LOW,DAI0_PBEN02_I);
		SRU(LOW,DAI0_PBEN12_I);
		SRU(LOW,DAI0_PBEN19_I);

		SRU(HIGH,DAI1_PBEN08_I);
		SRU(HIGH,DAI0_PBEN01_I);

		SRU(SRC4_DAT_OP_O, DAI1_PB08_I);	// TDM output goes to D1.P08
		SRU(SRC5_DAT_OP_O, SRC4_TDM_OP_I);	// SRC5 --> SRC4, TDM Data
		SRU(SRC6_DAT_OP_O, SRC5_TDM_OP_I);	// SRC6 --> SRC5, TDM Data
		SRU(SRC7_DAT_OP_O, SRC6_TDM_OP_I);	// SRC7 --> SRC6, TDM Data
		SRU(LOW, SRC7_TDM_OP_I);

		SRU(SRC2_DAT_OP_O, DAI0_PB01_I);	// TDM output goes to D0.P01
		SRU(SRC3_DAT_OP_O, SRC2_TDM_OP_I);	// SRC1 --> SRC0, TDM Data
		SRU(SRC0_DAT_OP_O, SRC3_TDM_OP_I);	// SRC2 --> SRC1, TDM Data
		SRU(SRC1_DAT_OP_O, SRC0_TDM_OP_I);	// SRC3 --> SRC2, TDM Data
		SRU(LOW, SRC1_TDM_OP_I);
	}
	else if(I2S_TDM_MODE == ASRC_MODE)
	{
		SRU(HIGH,DAI1_PBEN08_I);
		SRU(HIGH,DAI1_PBEN09_I);
		SRU(HIGH,DAI1_PBEN10_I);
		SRU(HIGH,DAI1_PBEN11_I);
		SRU(HIGH,DAI0_PBEN01_I);
		SRU(HIGH,DAI0_PBEN02_I);
		SRU(HIGH,DAI0_PBEN12_I);
		SRU(HIGH,DAI0_PBEN19_I);

		SRU(SRC4_DAT_OP_O,DAI1_PB08_I);    // SRC4 --> D1.P08
		SRU(SRC5_DAT_OP_O,DAI1_PB09_I);    // SRC5 --> D1.P09
		SRU(SRC6_DAT_OP_O,DAI1_PB10_I);    // SRC6 --> D1.P10
		SRU(SRC7_DAT_OP_O,DAI1_PB11_I);    // SRC7 --> D1.P11

		SRU(SRC2_DAT_OP_O,DAI0_PB01_I);     // SRC2 --> D0.P01
		SRU(SRC3_DAT_OP_O,DAI0_PB02_I);     // SRC3 --> D0.P02
		SRU(SRC0_DAT_OP_O,DAI0_PB12_I);     // SRC0 --> D0.P12
		SRU(SRC1_DAT_OP_O,DAI0_PB19_I);     // SRC1 --> D0.P19
	}
/********************************************************************************/
}
#endif

#ifdef ASRC_ENABLE
#pragma section("Seg_Kernal_Code_L3")
void Asrc_SRU_Reconfigure()
{
	if(I2S_TDM_MODE == ASRC_TDM_MODE)
	{
		ADI_PCG_CLK_INFO gClkInfo_B;
		gClkInfo_B.eClkInput = ADI_PCG_CLK_EXT;             /* Clock Source */
		gClkInfo_B.nDiv = FS_Div_Value/256u;                  /* Clock Divisor */
		gClkInfo_B.bExternalTrigger = false;                /* External Trigger */

		ADI_PCG_FS_INFO gFsInfo_B;
		gFsInfo_B.eClkInput = (ADI_PCG_FRAMESYNC_SOURCE)ADI_PCG_CLK_EXT;                	/* Clock Source */
		gFsInfo_B.nDiv = FS_Div_Value;                            /* Frame Sync Divisor */
		gFsInfo_B.nPulseWidth = (gFsInfo_B.nDiv)/256u;                /* Pulse Width */
		gFsInfo_B.nPhase = 0;                       /* Phase */
		gFsInfo_B.bExternalTrigger = false;                       /* External Trigger */
		gFsInfo_B.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL;   /* Bypass Mode */

		adi_pcg_Init(ADI_PCG_DEV_B,&gClkInfo_B,&gFsInfo_B);
	}
	else if (I2S_TDM_MODE == ASRC_MODE)
	{
		ADI_PCG_CLK_INFO gClkInfo_B;
		gClkInfo_B.eClkInput = ADI_PCG_CLK_EXT;  //Clock Source
		gClkInfo_B.nDiv = FS_Div_Value/64;  //Clock Divisor
		gClkInfo_B.bExternalTrigger = false; // External Trigger

		ADI_PCG_FS_INFO gFsInfo_B;
		gFsInfo_B.eClkInput =(ADI_PCG_FRAMESYNC_SOURCE) ADI_PCG_CLK_EXT;  //clock Source
		gFsInfo_B.nDiv = FS_Div_Value; // Frame Sync Divisor
		gFsInfo_B.nPulseWidth = (gFsInfo_B.nDiv)/2u;  //Pulse Width
		gFsInfo_B.nPhase = gClkInfo_B.nDiv/2; // Phase
		gFsInfo_B.bExternalTrigger = false;  //External Trigger
		gFsInfo_B.eFsBypassMode = ADI_PCG_FSBYPASS_MODE_NORMAL; // Bypass Mode

		adi_pcg_Init(ADI_PCG_DEV_B,&gClkInfo_B,&gFsInfo_B);
	}
}
#endif
