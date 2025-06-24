/*********************************************************************************

Copyright(c) 2014-2019 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.

*********************************************************************************/

/*!
 * @file     adi_spdif_rx_v1.h
 *
 * @brief    Receive S/PDIF src definitions and API
 *
 * @version  $Revision: 37632 $
 *
 * @date     $Date: 2019-10-09 12:35:37 +0530 (Wed, 09 Oct 2019) $
 *
 * @details
 *           This is the primary header file for the receive S/PDIF Driver.
 */

/** @addtogroup SPDIF_RX_Driver Receive S/PDIF Driver
 *  @{
 */

#ifndef __ADI_SPDIF_RX_V1_H__
#define __ADI_SPDIF_RX_V1_H__

/*==============  I N C L U D E S  ===============*/
/* disable misra diagnostics as necessary */
#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_5_1:"Identifiers shall not rely on the significance of more than 31 characters")
#endif /* _MISRA_RULES */

/* Interrupt Manager includes */
#include <services/int/adi_int.h>


/*==============  D E F I N E S  ===============*/

/* IF (ADSP-21xxx Processor family) */
#if defined(__ADSPSC573_FAMILY__)||defined(__ADSPSC589_FAMILY__)
/*! Memory size required to handle a SPDIF instance */
#define ADI_SPDIF_RX_MEMORY_SIZE                  (48u)
/* SPORT driver includes */
#include <drivers/sport/adi_sport.h>

/* ELSE (Other Processor family) */
#elif defined(__ADSP21569_FAMILY__) || defined(__ADSPSC594_FAMILY__)
/*! Memory size required to handle a SPDIF instance */
#define ADI_SPDIF_RX_MEMORY_SIZE                  (12u)
/* ELSE (Other Processor family) */
#else
#error "Processor not supported"
#endif /* __ADSP21xxx__ */

/*! Enumeration of the SPDIF driver specific result codes. */
typedef enum
{
    ADI_SPDIF_RX_SUCCESS,               /*!< Success */
    ADI_SPDIF_RX_FAILED,                /*!< Generic Failure */
    ADI_SPDIF_RX_IN_USE,                /*!< The specific device is in use */
    ADI_SPDIF_RX_NULL_POINTER,          /*!< The input param has null pointers which are invalid */
    ADI_SPDIF_RX_INVALID_PARAM,         /*!< The input param(s) to the function is invalid */
    ADI_SPDIF_RX_INVALID_HANDLE,        /*!< The given handle is invalid */
    ADI_SPDIF_RX_INVALID_STATE,         /*!< The operation cannot be completed at this state */
#if defined(__ADSPSC573_FAMILY__)||defined(__ADSPSC589_FAMILY__)
    ADI_SPDIF_RX_SPORT_NOT_CONFIGURED,  /*!< A valid SPORT device not configured correctly */
    ADI_SPDIF_RX_SPORT_ERROR,           /*!< SPORT driver error */
    ADI_SPDIF_RX_BUF_SUBMIT_FAILED      /*!< Failed to submit an audio buffer */
#else
    ADI_SPDIF_RX_RESTART_FAIL,          /*!< The Spdif Rx restart operation can not be done at the movement */
    ADI_SPDIF_RX_AUTORESTART_ENABLED,   /*!< The Spdif Rx already has Auto restart feature enabled */
    ADI_SPDIF_RX_DAI_IN_USE             /*!< The DAI events of Spdif Rx already has an callback attached */
#endif
} ADI_SPDIF_RX_RESULT;


#if !(defined(__ADSP21569_FAMILY__) || defined(__ADSPSC594_FAMILY__))
/*! Enumeration of SPORT channels that can be mapped to SPDIF */
typedef enum
{
    ADI_SPDIF_RX_SPORT_A = (ADI_HALF_SPORT_A),      /*!< Sport A - First half sport */
    ADI_SPDIF_RX_SPORT_B = (ADI_HALF_SPORT_B)       /*!< Sport B - Second half sport */
} ADI_SPDIF_RX_SPORT_CHANNEL;

/**
 * This structure holds SPORT configuration parameters.  This structure
 * is used with the following APIs, adi_spdif_Rx_ConfigSport or adi_spdif_Rx_ConfigSport.
 * If either these API's are called, it assumed the application requires a SPORT channel
 * to be mapped to a SPDIF interface.  In the case where a SPDIF interface requires no
 * SPORT channel, simply do not call these APIs and the SPDIF interface will be treated as
 * a physical interface requiring no SPORT.
 */
typedef struct
{
    uint8_t                     SportDevNum;        /*!< SPORT Device number to be used for stereo mode */
    ADI_SPDIF_RX_SPORT_CHANNEL  eSportChnl;         /*!< SPORT channel to be mapped */
    void                        *pSportDevMem;      /*!< Pointer to memory to handle the SPORT device */
    uint32_t                    SportDevMemSize;    /*!< Memory size of pSportDevMem */
    bool                        bLsbFirst;          /*!< SPORT endianess, LSB first */
    bool                        bPack;              /*!< SPORT packing */
} ADI_SPDIF_RX_SPORT_CONFIG;

/*! Enumeration for the S/PDIF RX SPORT call back events */
typedef enum
{
    ADI_SPDIF_RX_EVENT_DMA_ERROR,               /*!< SPORT DMA Error (pArg = None) */
    ADI_SPDIF_RX_EVENT_BUFFER_PROCESSED         /*!< Processed an Audio buffer (pArg = Start address of the processed buffer) */
} ADI_SPDIF_RX_SPORT_EVENT;

/*! Enumeration for serial input format */
typedef enum _ADI_SPDIF_RX_FMT
{
    ADI_SPDIF_RX_FMT_LEFT_JUSTIFIED           = 0,  /*!< Left-justified (Default) */
    ADI_SPDIF_RX_FMT_I2S                      = 1,  /*!< I2S mode */
    ADI_SPDIF_RX_FMT_RIGHT_JUSTIFIED_24_BITS  = 4,  /*!< 24-bit right-justified */
    ADI_SPDIF_RX_FMT_RIGHT_JUSTIFIED_20_BITS  = 5,  /*!< 20-bit right-justified */
    ADI_SPDIF_RX_FMT_RIGHT_JUSTIFIED_18_BITS  = 6,  /*!< 18-bit right-justified */
    ADI_SPDIF_RX_FMT_RIGHT_JUSTIFIED_16_BITS  = 7   /*!< 16-bit right-justified */
} ADI_SPDIF_RX_FMT;
#endif
/*! Enumeration for output signal strength */
typedef enum
{
    /*! In strong mode, bit clock and frame sync signals are continued when the receive notices a loss-of-lock condition */
    ADI_SPDIF_RX_OUT_STRENGTH_STRONG   = ((uint32_t)0u << BITP_SPDIF_RX_CTL_STRENGTH),

    /*! In weak mode, bit clock and frame sync signals are interrupted as soon as the receiver notices a loss-of-lock condition */
    ADI_SPDIF_RX_OUT_STRENGTH_WEAK     = ((uint32_t)1u << BITP_SPDIF_RX_CTL_STRENGTH)

} ADI_SPDIF_RX_OUT_STRENGTH;

/*! Enumeration for the input audio type */
typedef enum
{
    /*! Input audio is PCM data */
    ADI_SPDIF_RX_AUDIO_TYPE_PCM        = ((uint32_t)0u << BITP_SPDIF_RX_STAT_AUDIOTYPE),

    /*! Input audio is Compressed data */
    ADI_SPDIF_RX_AUDIO_TYPE_COMPRESSED = ((uint32_t)1u << BITP_SPDIF_RX_STAT_AUDIOTYPE)
} ADI_SPDIF_RX_AUDIO_TYPE;

/*! Enumeration for the compression type */
typedef enum
{
    /* The compression type is AC3 */
    ADI_SPDIF_RX_COMPRESSION_TYPE_AC3  = ((uint32_t)0u << BITP_SPDIF_RX_STAT_COMPTYPE),

    /* The compression type is DTS */
    ADI_SPDIF_RX_COMPRESSION_TYPE_DTS  = ((uint32_t)1u << BITP_SPDIF_RX_STAT_COMPTYPE)

} ADI_SPDIF_RX_COMPRESSION_TYPE;

/*! Enumeration for the S/PDIF word length */
typedef enum
{
    ADI_SPDIF_RX_WORD_LENGTH_16  = ((uint32_t)0x2u),  /*!< S/PDIF word length is 16 bits */
    ADI_SPDIF_RX_WORD_LENGTH_18  = ((uint32_t)0x4u),  /*!< S/PDIF word length is 18 bits */
    ADI_SPDIF_RX_WORD_LENGTH_22  = ((uint32_t)0x5u),  /*!< S/PDIF word length is 22 bits */
    ADI_SPDIF_RX_WORD_LENGTH_19  = ((uint32_t)0x8u),  /*!< S/PDIF word length is 19 bits */
    ADI_SPDIF_RX_WORD_LENGTH_23  = ((uint32_t)0x9u),  /*!< S/PDIF word length is 23 bits */
    ADI_SPDIF_RX_WORD_LENGTH_20  = ((uint32_t)0xAu),  /*!< S/PDIF word length is 20 bits */
    ADI_SPDIF_RX_WORD_LENGTH_24  = ((uint32_t)0xBu),  /*!< S/PDIF word length is 24 bits */
    ADI_SPDIF_RX_WORD_LENGTH_17  = ((uint32_t)0xCu),  /*!< S/PDIF word length is 17 bits */
    ADI_SPDIF_RX_WORD_LENGTH_21  = ((uint32_t)0xDu)   /*!< S/PDIF word length is 21 bits */

} ADI_SPDIF_RX_WORD_LENGTH;

/*! Enumeration for the S/PDIF channels */
typedef enum
{
    ADI_SPDIF_RX_CHANNEL_A,   /*!< S/PDIF Channel A */
    ADI_SPDIF_RX_CHANNEL_B    /*!< S/PDIF Channel B */
} ADI_SPDIF_RX_CHANNEL;

#if defined(__ADSP21569_FAMILY__) || defined(__ADSPSC594_FAMILY__)
/*! Enumeration for the S/PDIF receiver sampling frequency range */
typedef enum
{
    ADI_SPDIF_RX_SF_96K_OR_LOWER= ((uint32_t)0x0u), /*!< S/PDIF receiver sampling frequency 96K or lower */
    ADI_SPDIF_RX_SF_192K= ((uint32_t)0x1u),    /*!< S/PDIF receiver sampling frequency from 96K to 192K */
    ADI_SPDIF_RX_SF_96K_TO_192K= ((uint32_t)0x3u)            /*!< S/PDIF receiver sampling frequency 192K */
} ADI_SPDIF_RX_SF_RANGE;
#endif

/*! Handle to the S/PDIF Receiver device instance */
typedef struct ADI_SPDIF_RX_DEV* ADI_SPDIF_RX_HANDLE;


/*=======  P U B L I C   P R O T O T Y P E S  ========*/
/*            (globally-scoped functions)             */

#ifdef __cplusplus
extern "C" {
#endif

/* Open the S/PDIF RX device */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_Open (
                                      uint32_t const        nDeviceNum,
                                      void                  *const pDeviceMemory,
                                      uint32_t              nMemorySize,
                                      ADI_SPDIF_RX_HANDLE   *const phDevice
                                      );

/* Close the S/PDIF RX instance */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_Close (ADI_SPDIF_RX_HANDLE const hDevice);

/* Enable/Disable the S/PDIF RX device */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_Enable (ADI_SPDIF_RX_HANDLE const hDevice, bool bEnable);

/* Register application callback with the driver */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_RegisterCallback (ADI_SPDIF_RX_HANDLE const hDevice, ADI_CALLBACK  pfCallback, void *pCBparam);

/* Control the output signal string of the S/PDIF RX device */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_SetOutputSignalStrength (ADI_SPDIF_RX_HANDLE  const hDevice, ADI_SPDIF_RX_OUT_STRENGTH eStrength);

/* Enable/Disable the fast clock in the S/PDIF RX device */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_EnableFastLock (ADI_SPDIF_RX_HANDLE const hDevice, bool bEnable);

/* Enable/Disable the automatic audio restart in the S/PDIF RX device */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_EnableAutoAudioRestart (ADI_SPDIF_RX_HANDLE const hDevice, bool bEnable);

/* Manually Restart Audio */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_RestartAudio (ADI_SPDIF_RX_HANDLE const hDevice);

/* Get the loss of lock status from the RX */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_GetLossOfLockStatus (ADI_SPDIF_RX_HANDLE const hDevice, bool *pbLostLock);

/* Get the lock status */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_GetLockStatus (ADI_SPDIF_RX_HANDLE const hDevice, bool *pbLocked);

/* Get the Ored validity bits of channel A and B */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_GetORedValidityBits (ADI_SPDIF_RX_HANDLE const hDevice, uint32_t *pBit);

/* Get the Audio Type */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_GetAudioType (ADI_SPDIF_RX_HANDLE const hDevice, ADI_SPDIF_RX_AUDIO_TYPE *peAudioType);

/* Get the compression type if audio type is compressed data */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_GetCompressionType (ADI_SPDIF_RX_HANDLE const hDevice, ADI_SPDIF_RX_COMPRESSION_TYPE *peCompressionType);

/* Get the compression mode */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_GetCompressionMode (ADI_SPDIF_RX_HANDLE const hDevice, uint32_t *pnMode);

/* Get the word length */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_GetWordLength (ADI_SPDIF_RX_HANDLE const hDevice, ADI_SPDIF_RX_CHANNEL eChannel, ADI_SPDIF_RX_WORD_LENGTH *peWordLength);

/* Get the channel status for the given channel */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_GetChannelStatus (ADI_SPDIF_RX_HANDLE const hDevice, ADI_SPDIF_RX_CHANNEL eChannel, uint8_t *pBuffer);

/* Control the RESET state of the S/PDIF RX device*/
ADI_SPDIF_RX_RESULT adi_spdif_Rx_ResetReceiver (ADI_SPDIF_RX_HANDLE  const hDevice);

#if !(defined(__ADSP21569_FAMILY__) || defined(__ADSPSC594_FAMILY__))
/* Configure the SPORT device */
ADI_SPDIF_RX_RESULT   adi_spdif_Rx_ConfigSport (ADI_SPDIF_RX_HANDLE const hDevice, ADI_SPDIF_RX_SPORT_CONFIG *pConfig);

/* Submits a buffer to the SPDIF instance  */
ADI_SPDIF_RX_RESULT  adi_spdif_Rx_SubmitBuffer(ADI_SPDIF_RX_HANDLE const hDevice, void *pBuffer, uint32_t BufferSize);

/* Peek function for non-OS application to check if a processed buffer is available or not */
ADI_SPDIF_RX_RESULT  adi_spdif_Rx_IsBufAvailable(ADI_SPDIF_RX_HANDLE const hDevice, bool *pbIsBufAvailable);

/* Gets address of a processed buffer */
ADI_SPDIF_RX_RESULT  adi_spdif_Rx_GetBuffer(ADI_SPDIF_RX_HANDLE const hDevice, void **ppBuffer);

/* Register a callback for reporting SPORT events */
ADI_SPDIF_RX_RESULT  adi_spdif_Rx_RegisterSportCallback(ADI_SPDIF_RX_HANDLE const hDevice, ADI_CALLBACK pfCallback, void *pCBParam);


#else
/* Set Tdmsel for the Spdif receiver */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_SetTdmsel (
                                                ADI_SPDIF_RX_HANDLE  const hDevice,
                                                ADI_SPDIF_RX_SF_RANGE eSfrange
                                            );

#endif

#if defined(__ADSPSC594_FAMILY__)
/* Set Tdmdiv for the Spdif receiver */
ADI_SPDIF_RX_RESULT adi_spdif_Rx_SetTdmdiv (
                                                ADI_SPDIF_RX_HANDLE  const hDevice,
												uint16_t 			nDivisor
                                            );
#endif

#ifdef __cplusplus
}
#endif

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

#endif /* __ADI_SPDIF_RX_V1_H__ */


/*@}*/
