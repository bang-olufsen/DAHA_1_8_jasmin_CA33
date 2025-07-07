/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Commn.h
*  Description      :   Define MACRO added for all the Project files 
******************************************************************************/
#ifndef COMMN_H
#define COMMN_H

#define BEO_PCM_I2S
//#define BEO_MCPCM
//#define BEO_MAT
//#define BEO_PCM_SPDIF
//#define BEO_DDP

#define SPI_BUFFER_SIZE  40
/*============== Decoder Definition==========================================*/
#define DOLBY_LIB
#ifdef DOLBY_LIB
//	#define DOLBY_CERTIFICATION
	#define DOLBY_DDP
	#define DOLBY_DD
	#define DOLBY_MAT
	#define DOLBY_THD
	#define DOLBY_OAR
	#define DOLBY_CHANNEL_REORDER
	#define DOLBY_DAP
	#define DOLBY_DMX
//	#define DOLBY_MIPS
	#define DOLBY_THD_DS
	#define EXT_DNMIX
    #define EXT_DNMIX_DDP
	#define DTSX_DAP
	#define DOLBY_THD_DA
#endif

/*In order to comment DTSX Decoder, Use the below define alone*/
#define DTSX_DECODER
#define DTS_VIRTUALX
#ifdef DTSX_DECODER
	#define DTSX_LIB
	#define DTSX_CHANREORDER
	#define NEURALX
	#define DOWNSAMPLING_DTSX
	#define TRU_BASS
	#define DTSX_NUM_OUT_CHANNELS 16
	#define DTSX_MIPS_CALC
#endif

#define AAC_DEC
#define MPEGH_DECODER
#define NOISEGEN
#define AURO_3D
#define DOWNSAMPLING
#define DSD2PCM_DEC
//#define DSD2PCM_TESTING

#ifdef DSD2PCM_TESTING

#else
#define MCPCM_DECODER
#define PCM_DEC
#endif
#ifdef AAC_DEC
	#define MPEG4_AAC
#endif
#ifdef PCM_DEC
	#define DE_EMPHASIS_PP
#endif 

#define STATUS_UPDATE


//#define MELODY9

#ifdef MELODY9
#define eARC_ENABLE
#endif

#define I2S_TDM_MODE_ENABLE


#define CUSTOMIZATION
#define COMMAND_PROCESSING
#define TX_NEW_LOGIC
#define SPI_COMMAND
#define DEFAULT_CH_CONFIG	//Default channel config will be updated as 16CH

//#define CORE1_TX
#define MDMA_COPY
#define LED_TOGGLE
#define FRAMEWORK_24CH
//#define SPI1  //To Enable the SPI1 Device
#define DOLBY_L2_BUFFER_POINTER

#ifdef SPI1
	#define	SPI_DEVICE	1
#else
	#define	SPI_DEVICE	0
#endif
#define TWO_HALF    2
#define THREE_HALF	3
#define FOUR_HALF	4
#define FIVE_HALF   5

#ifdef MPEGH_DECODER
#define PACK_LENGTH_MPEGH			    1024*MPEGH_Pack_Factor
#define PREDAC_LENGTH_MPEGH			    1024*MPEGH_Predac_Factor
#define PREDAC_FIFO_LENGTH_MPEGH	    1024*16*FOUR_HALF
#define PREDAC_BUFFER_FIFO_LENGTH_HALF  1024*16
#define MPEGH_RENDERED_OUT_LENGTH       1024
#define MPEGH_MAX_OUTPUT_CHANNEL        16
#define MPEGH_AU_Input_SIZE             (1024 * 32*2)
#endif
#define MPEGH_Pack_Factor               6 
#define MPEGH_Predac_Factor             6
/*==============OPTICAL_MODULE Definition=================================================*/
//#define OPTICAL_MODULE

/*==============I/O Buffer Definition===========================================*/
#define INAUTOBUFSIZEBY2			32*2
#define OUTAUTOBUFSIZEBY2			16*2

#define SAMPLE_BLOCK_MCPCM			256
#define SAMPLE_BLOCK_PCM			256

#ifdef NOISEGEN
#define NOISE_PROCESSING_LENGTH     1024
#define PACK_LENGTH_PCM_INT	 	    256*2*2
#endif
#define NO_OF_SAMPLE_PROCESSING		256
#define SAMPLE_PROCESSING_PP        64
#define NO_OF_TX_SAMPLE_COUNT	    32

#define NO_OF_INPUT_CHANNEL 		8

#ifdef FRAMEWORK_24CH
	#define NO_OF_PREDAC_CHANNEL		24
#else
	#define NO_OF_PREDAC_CHANNEL		32
#endif

#define NUMMAXCHAN                  NO_OF_PREDAC_CHANNEL
#define PREDAC_INT_NUMCHAN          32

#define PACK_LENGTH_MCPCM 	 	 	NO_OF_SAMPLE_PROCESSING*NO_OF_INPUT_CHANNEL*TWO_HALF
#define PACK_LENGTH_MCPCM_INT 	 	NO_OF_SAMPLE_PROCESSING*NO_OF_INPUT_CHANNEL

/* #define PACK_BUFFER_MAX_SIZE - 16384 * MPEGH_Pack_Factor (16384*6)
Since MPEGH_Pack_Factor is increased from 4 halves to 6 halves based on MPEG-H 2.9.4 library update,
PACK_BUFFER_MAX_SIZE value is updated as 16384*4 = 65536, in order to avoid ldf update and to handle pack buffer in SDK integration.
To compensate the increase in MPEG-H pack size, Predac_FIFO_Base_Ptr using common L2 pointer address has been modified in MPEGH_Kernal.c */

#define PACK_BUFFER_MAX_SIZE        16384*4 //16384*MPEGH_Pack_Factor//(1024*8*MPEGH_Pack_Factor)
#define PACK_LENGTH_PCM_EXT         NO_OF_SAMPLE_PROCESSING*2*TWO_HALF

#define PREDAC_LENGTH_PCM  	 		NO_OF_SAMPLE_PROCESSING*NO_OF_PREDAC_CHANNEL*THREE_HALF
#define PREDAC_LENGTH_MCPCM  	 	NO_OF_SAMPLE_PROCESSING*NO_OF_PREDAC_CHANNEL*THREE_HALF

#ifdef DOWNSAMPLING
#define PACK_LENGTH_PCM_INT_DS_96	512*2*TWO_HALF 	    //2 Channel
#define PACK_LENGTH_PCM_INT_DS_192	1024*2*TWO_HALF 	//2 Channel
#define PACK_LENGTH_MCPCM_DS_96	 	512*NO_OF_INPUT_CHANNEL*TWO_HALF 	//8 Channel
#define PACK_LENGTH_MCPCM_DS_192	1024*NO_OF_INPUT_CHANNEL*TWO_HALF 	//8 Channel
#endif

#define BUFF_MAX_SIZE               NO_OF_SAMPLE_PROCESSING*NUMMAXCHAN


#define DEFAULT_FS					FS_48K

#ifdef AAC_DEC
	#define OUT_BUF_SIZE				2048*NO_OF_PREDAC_CHANNEL
	#define PACK_LENGTH_AAC				1024*2
	#define PREDAC_LENGTH_AAC			1024*NO_OF_PREDAC_CHANNEL*THREE_HALF
	#define METADATASIZE				3072
	#define MPEG4_AACLC                 0  // 0: Supports AAC-LC, He-AAC and He-AACv2 , 1: Supports only AAC-LC
#endif

#if defined  (DSD2PCM_DEC) || defined (DSD2PCM_TESTING)
#define METADATASIZE				3072
//#define INAUTOBUFSIZEBY2_DSD 8*2
#define INAUTOBUFSIZEBY2_DSD 16*2
#define PACK_LENGTH_DSD2PCM  		1024*6*2 //512*6*2
#define PACK_LENGTH_DSD2PCM_2FS 	512*6*2  //256*6*2
#define PACK_LENGTH_DSD2PCM_4FS  	256*6*2  //128*6*2
#define PREDAC_LENGTH_DSD2PCM 		NO_OF_SAMPLE_PROCESSING*NO_OF_PREDAC_CHANNEL*THREE_HALF
#define ADDPREDAC_LENGTH_DSD2PCM 	METADATASIZE*2
#define DEFAULT_FS_DSD				FS_44K
#endif
/*==============Customer_PP Definition=================================================*/

#define FLOAT

#define CUSTOMER_PP

#define CHANNEL_REORDER
#ifdef CUSTOMER_PP
#define FLOAT_PP 1
#define CUSTOMER_PP_CHANNELS 16
#endif
#define PP_BUFF_MAX_SIZE NO_OF_SAMPLE_PROCESSING*16
/*==============================================================================*/
/*============== Framework Definition===========================================*/
#define AUTODETECT1 				0 //NTC
#define FORCEPCM3   				4
#define AUTODETECT3 				9
#define INVALID					   -1

#define NO_ERROR 					0
#define HEADER_PLACE_WRITTEN_ERROR 	1
#define STREAM_NOT_DETECTED 		2
#define FILLED_SPACE_ERROR 			3
#define EMPTY_SPACE_ERROR 			4
#define DECODER_ERROR				5
/*===============================================================================*/
#define TRUE						1
#define FALSE						0
#define BEO_Framework	/* Define is only used for MAP soundbar Framework */
#ifdef BEO_Framework
#define ASRC_TDM16	/* ASRC TDM -16 not Support is for Melody -9 , we can use MAP platform for validation*/
//#define ASRC_TDM8		/* ASRC TDM -8 Support is for Melody -9 */
#endif
//#define ASRC_ENABLE
#ifdef I2S_TDM_MODE_ENABLE
#define I2S_MODE 0
#define TDM_MODE 1
#endif
#define ASRC_MODE 2
#define ASRC_TDM_MODE  3
#ifdef PCM_DEC
#define LPCMDelayBuffer_size		18432  //Lpcm delay for 96k and 192k(16384+(256*2*4))
#endif

#define SOUNDBAR

#define FS_32K  	0x00
#define FS_44K  	0x01
#define FS_48K  	0x02
#define FS_64K  	0x04
#define FS_88K  	0x05
#define FS_96K  	0x06
#define FS_128K  	0x08
#define FS_176K  	0x09
#define FS_192K  	0x0A


#define MCLK_192KHZ   64
#define MCLK_96KHZ    64
#define MCLK_48KHZ    64

#define BEO_CLK_DIV   64

#define COUNT_2CH 32*2
#define COUNT_4CH 32*4

#define NOP1 asm("nop;");
#define NOP10 asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");asm("nop;");

#define MP_OFFSET	(uint32_t)0x28000000  // SHARED MEMORY CONVERSION (NW to BW) OFFSET FOR CORE 1 BUFFERS
#define MP_OFFSET1	(uint32_t)0x28800000  // SHARED MEMORY CONVERSION (NW to BW) OFFSET FOR CORE 2 BUFFERS

#define  STREAM_TYPE_FORMUTE	0x82E3
#define TOTAL_NO_OF_ASSIGN_LINES 5
#ifdef DEFAULT_CH_CONFIG
	#ifdef MPEGH_DECODER
		#define  MPEGH_DEFAULT_ASSIGN_LINES         0xD6321
		#define  MPEGH_DEFAULT_SPEAKER_MASK         5583
		#define  MPEGH_DEFAULT_CICP_TARGET_INDEX 	300
		#define  MPEGH_DEFAULT_TARGET_LOUDNESS      0x2
	#endif
#else
	#ifdef MPEGH_DECODER
		#define  MPEGH_DEFAULT_ASSIGN_LINES         0x26D31
		#define  MPEGH_DEFAULT_SPEAKER_MASK         4431
		#define  MPEGH_DEFAULT_CICP_TARGET_INDEX 	19
		#define  MPEGH_DEFAULT_TARGET_LOUDNESS      0x2
	#endif
#endif
/*
	bit 0 - PCMZERO		- Mute enabled
	bit 1 - PCM			- Mute enabled
	bit 2 - DOLBY		- No mute	
	bit 3 - DTSLDCD		- No mute
	bit 4 - DTSDVD		- No mute
	bit 5 - MPEGL1		- Mute enabled
	bit 6 - MPEGL2L3	- Mute enabled 		
	bit 7 - HDCD		- Mute enabled
	bit 8 - AAC			- No mute
	bit 9 - WMAPRO		- Mute enabled
	bit 10 - DDPLUS		- No mute
	bit 11 - TRUEHD		- No mute
	bit 12 - DTSMA		- No mute
	bit 13 - DTSHR 		- No mute
	bit 14 - DTSLBR		- No mute
	bit 15 - UNKNOWN	- Mute enabled
*/

#endif
/*============== Auro Definitions==========================================*/
#ifdef AURO_3D
#define BUFF_MAX_SIZE_IP_AURO 256*8
#define BUFF_MAX_SIZE_AURO 256*16
#define BUFF_MAX_SIZE_AURO_HALF 128*16
#define BUFF_MAX_SIZE_AURO_THD96 256*8
#define BUFF_MAX_SIZE_AURO_MAT 256*32
#define AURO_SAMPLE_BLOCK96 512
#define AURO_INPUT_CHANNELS 8
#define AURO_DS_SAMPLE_BLOCK 128
#define AURO_ERROR_HANDLING
#endif

/*============== Dolby Decoder Definitions==========================================*/
#ifdef DOLBY_LIB
#define SAMPLEBLOCK_DDPLUS 					1536

#define TrueHD_DEC_Samples					40
#define TrueHD_DEC_Blk 						32
#define TrueHD_DEC_Blk_96K 					32		/*AU for 96K Straight Sampling */
#define TrueHD_DEC_Blk_192K 				32		/*AU for 192K Straight Sampling*/

#define SAMPLEBLOCK_TRUEHD 					TrueHD_DEC_Samples*TrueHD_DEC_Blk 			/* 1280 */
#define SAMPLEBLOCK_TRUEHD_96K 				TrueHD_DEC_Samples*2*TrueHD_DEC_Blk_96K		/* 1280 * 2 */
#define SAMPLEBLOCK_TRUEHD_192K 			TrueHD_DEC_Samples*4*TrueHD_DEC_Blk_192K	/* 1280 * 4 */

#define MAT_DEC_Samples	 					480
#define MAT_DEC_Blk	     					1

#define SAMPLEBLOCK_MATPCM 					MAT_DEC_Samples*MAT_DEC_Blk									//480*1

#if defined (DOLBY_DDP) || defined (DOLBY_DD) || defined(DOLBY_CERTIFICATION) || defined(AURO_3D)
#define ASF48K								0x00
#define ASF96K								0x01
#define ASF192K								0x02
#define ASF44K1								0x08
#define ASF88K2								0x09
#define ASF176K4 							0x0a
#define ASF_UNSPECIFIED						0x0f
#endif

#if defined (DOLBY_DDP) || defined (DOLBY_DD) || defined(DOLBY_CERTIFICATION)
#define ADDPREDAC_LENGTH_DDP	    		SAMPLEBLOCK_DDPLUS*12*THREE_HALF  // (1024+5)*3


#define PACK_LENGTH_DDP 	 				6144	/* Pack length for DDP */
#define PACK_LENGTH_DD	 	 	 			1536	/* Pack length for DD */

#define PREDAC_LEN_DDP_CIDK_RT  			SAMPLEBLOCK_DDPLUS*NO_OF_PREDAC_CHANNEL 				/* 1536 * 24 */
#define PREDAC_LENGTH_DDP 	 				SAMPLEBLOCK_DDPLUS*NO_OF_PREDAC_CHANNEL*THREE_HALF		/* 1536*24*3 */

#endif /* DOLBY_DDP || DOLBY_DD*/
#if defined (DOLBY_THD) || defined (DOLBY_MAT)|| defined(DOLBY_CERTIFICATION)


#define TRUEHD_AUOUT8CHANNEL_48K			40*32
#define TRUEHD_AUOUT8CHANNEL_96K			80*32
#define TRUEHD_AUOUT8CHANNEL_192K			160*8

#define DECODERBLOCKSIZE_48K				TrueHD_DEC_Samples
#define DECODERBLOCKSIZE_96K				TrueHD_DEC_Samples*2
#define DECODERBLOCKSIZE_192K				TrueHD_DEC_Samples*4

#define TRUEHD_INPUTBUFFERSIZE    			85536
#define TRUEHD_OUTPUTBUFFERSIZE_48K 		SAMPLEBLOCK_TRUEHD*16
#define TRUEHD_OUTPUTBUFFERSIZE_96K 		SAMPLEBLOCK_TRUEHD_96K*8
#define TRUEHD_OUTPUTBUFFERSIZE_192K 		SAMPLEBLOCK_TRUEHD_192K*6
#define TRUEHD_PACKBUFFERSIZEBYTWO_MAT		7680
#define MLP_INPUT_BUF_LENGTH				1000
#define PREDAC_LEN_TRUEHD_CIDK_RT_48K  		TrueHD_DEC_Samples*TrueHD_DEC_Blk*NO_OF_PREDAC_CHANNEL //40 * 32 * 24
#define PREDAC_LEN_TRUEHD_CIDK_RT_96K  		TrueHD_DEC_Samples*2*TrueHD_DEC_Blk*NO_OF_PREDAC_CHANNEL //81920 //40 * 2 * 32 * 24
#define PREDAC_LEN_TRUEHD_CIDK_RT_192K  	TrueHD_DEC_Samples*4*TrueHD_DEC_Blk*NO_OF_PREDAC_CHANNEL//163840 //40 * 4 * 32 * 24

#define PREDAC_LENGTH_TRUEHD_48K			SAMPLEBLOCK_TRUEHD*NO_OF_PREDAC_CHANNEL*4
#define PREDAC_LENGTH_TRUEHD_96K			SAMPLEBLOCK_TRUEHD_96K*NO_OF_PREDAC_CHANNEL*4
#define PREDAC_LENGTH_TRUEHD_192K 			SAMPLEBLOCK_TRUEHD_192K*NO_OF_PREDAC_CHANNEL*4
#define PACK_LENGTH_TRUEHD       			18944*2 //twice the buffer length
#define ADDPREDAC_LENGTH_TrueHD 			SAMPLEBLOCK_TRUEHD*12*4

#define MAT_MAX_OBJ							32
#define MAT_PCM_Block_size					MAT_DEC_Samples*MAT_MAX_OBJ
#define MAT_STREAM_PROFILE_MLP  			1	//MAT - TRUEHD
#define MAT_STREAM_PROFILE_PCM_OBJ			2	//MAT - PCM OBJRECT BASED
#define MAT_STREAM_PROFILE_PCM_CH			3	//MAT - PCM CHANNEL BASED
#define MAT_PCM_MD_Block_size				MAT_DEC_Samples*12											//480*12
#define PREDAC_LENGTH_MATPCM_48K 			SAMPLEBLOCK_MATPCM*NO_OF_PREDAC_CHANNEL*FOUR_HALF			//480*1*24*3

#define ADDPREDAC_LENGTH_MATPCM_48K     	MAT_DEC_Samples*MAT_DEC_Blk*12*FOUR_HALF					//480*1*12*3


#define MAT_44k  							0x00
#define MAT_48k  							0x01
#define IEC_UNLOCKED 						0
#define DS_INPUT_DATA_SIZE 					1920
#endif /* (DOLBY_THD) || (DOLBY_MAT) */
/*============== PP Definition=================================================*/

	#define MAX_DEC_BLK_SIZE 					30720 //1536 * 16 - DDP blk size, 1280 * 16 - THD blk size

	#define NUM_CHANNLES 						16

	#define METADATASIZE_INT_HALF				3072
	#define METADATASIZE_INT					6144
	#define MAX_EVO_UNPACKED_MD_SIZE 			7168
	#define MAX_MD_LENGHTH_TRUEHD 				(TrueHD_DEC_Samples*12)
	#define MAX_MD_LENGHTH_MATPCM 				1920
	#define MD_BUFFER_SDRAM_LENGTH 				(2*512*12)
	#define MD_BUFFER_SDRAM_LENGTH_HALF 		(MD_BUFFER_SDRAM_LENGTH/2)

	#define DPF_MD_ID_EVOLUTION 				0x00100080
	#define DPF_MD_ID_EVENT_PINCFG 				0x00100011
	#define MAGIC_HEADER 						0x3e7ada7a

	#define NO_OF_CACHE_MD_SDRAM 				3
	#define TOTAL_MD_CACHE_SIZE 				(NO_OF_CACHE_MD_SDRAM*MAX_EVO_UNPACKED_MD_SIZE)
	#define OARI_MAT_MD_SIZE 					24
	#define MAX_MD_LENGHTH_DDPLUS 				SAMPLEBLOCK_DDPLUS
#endif /* DOLBY_LIB */

/*================================ Neural X ================================*/
#ifdef NEURALX
	#define DTSXCHANNELS 32
	#define DOLBY_NEURALX
#endif //NEURALX

#define EXT_BUFFER_DATA_SIZE 73*1024
/*================================ Virtual X ================================*/
#ifdef DTS_VIRTUALX
	#define DTS_VIRTUALX_INPUT_CH 12
	#define DTS_VIRTUALX_OUTPUT_CH 32
    #define DTSVX_ENABLE_OPTION 1          		//Set DTSVX_ENABLE_OPTION as 1 to enable virtualX option1 mode and Set DTSVX_ENABLE_OPTION as 2 to enable VirtualX option2 mode(Default - SpkrOut:886B & disable direct mode)
#endif //DTS_VIRTUAL

#define TMU
#define SPDIF_MODULE
#ifdef SPDIF_MODULE
#define FSPHASE                     3      //To synchronize fs2 with fs1
#endif
