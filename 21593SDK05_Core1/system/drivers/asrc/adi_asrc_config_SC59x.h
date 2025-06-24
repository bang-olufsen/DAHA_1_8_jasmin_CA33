/******************************************************************************

Copyright (c) 2020 Analog Devices.  All Rights Reserved.

This software is proprietary and confidential.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.
*******************************************************************************/

/*!
* @file      adi_asrc_config_SC59x.h
*
* @brief     ASRC driver static configuration Header file
*
* @details
*            ASRC driver static configuration Header file
*/

/** @addtogroup ASRC_Driver Asynchronous Rate Converter (ASRC) Driver
 *  @{
 */
 
 /** @addtogroup ASRC_Driver_Static_Configuration Asynchronous Rate Converter Driver Static Configuration
 *  @{
 */

#ifndef ADI_ASRC_CONFIG_SC59X_H
#define ADI_ASRC_CONFIG_SC59X_H

/* ASRC 0 DAI 0*/

/*! Input Format for ASRC0.\n
    (0) - left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (4) - 24-bit right-justified\n
    (5) - 20-bit right-justified\n
    (6) - 18-bit right-justified\n
    (7) - 16-bit right-justified\n
*/
#define ADI_CFG_ASRC0_INPUT_FORMAT               (0x1u)
/*! Output Format for ASRC0.\n
    (0) - Left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (3) - Right-justified\n 
*/
#define ADI_CFG_ASRC0_OUTPUT_FORMAT              (0x1u)
/*! Serial Output Word Length for ASRC0.\n
    (0) - 24 bits\n
    (1) - 20 bits\n
    (2) - 18 bits\n
    (3) - 16 bits\n
*/
#define ADI_CFG_ASRC0_WORD_LENGTH                (0x0u)
/*! Auto Mute Enable for ASRC0.\n
    (0) - Disable Auto Mute\n
    (1) - Enable Auto Mute\n
*/
#define ADI_CFG_ASRC0_AUTO_MUTE_ENABLE           (0x0u)
/*! Bypass Enable for ASRC0.\n
    (0) - Disable Bypass\n
	(1) - Enable Bypass\n
*/
#define ADI_CFG_ASRC0_BYPASS_ENABLE              (0x0u)
/*! Dither Enable before truncation for ASRC0.\n
    (0) - Truncation Only\n
    (1) - Dithering before truncation\n
 */
#define ADI_CFG_ASRC0_DITHER_ENABLE              (0x0u)
/*! Matched Phase Slave Enable for ASRC0.\n
    (0) - Matched Phase Slave Disable\n
    (1) - Matched Phase Slave Enable\n
 */
#define ADI_CFG_ASRC0_MATCHED_PHASE_ENABLE       (0x0u)
/*! De-Emphasis Type for ASRC0.\n
    (0) - No de-emphasis\n
    (1) - 32 kHz\n
    (2) - 44.1 kHz\n
    (3) - 48 kHz\n
*/
#define ADI_CFG_ASRC0_DEEMPHASIS_TYPE            (0x0u)

/* ASRC 1 DAI 0*/

/*! Input Format for ASRC1.\n
    (0) - left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (4) - 24-bit right-justified\n
    (5) - 20-bit right-justified\n
    (6) - 18-bit right-justified\n
    (7) - 16-bit right-justified\n
*/
#define ADI_CFG_ASRC1_INPUT_FORMAT               (0x1u)
/*! Output Format for ASRC1.\n
    (0) - Left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (3) - Right-justified\n 
*/
#define ADI_CFG_ASRC1_OUTPUT_FORMAT              (0x1u)
/*! Serial Output Word Length for ASRC1.\n
    (0) - 24 bits\n
    (1) - 20 bits\n
    (2) - 18 bits\n
    (3) - 16 bits\n
*/
#define ADI_CFG_ASRC1_WORD_LENGTH                (0x0u)
/*! Auto Mute Enable for ASRC1.\n
    (0) - Disable Auto Mute\n
    (1) - Enable Auto Mute\n
*/
#define ADI_CFG_ASRC1_AUTO_MUTE_ENABLE           (0x0u)
/*! Bypass Enable for ASRC1.\n
    (0) - Disable Bypass\n
	(1) - Enable Bypass\n
*/
#define ADI_CFG_ASRC1_BYPASS_ENABLE              (0x0u)
/*! Dither Enable before truncation for ASRC1.\n
    (0) - Truncation Only\n
    (1) - Dithering before truncation\n
 */
#define ADI_CFG_ASRC1_DITHER_ENABLE              (0x0u)
/*! Matched Phase Slave Enable for ASRC1.\n
    (0) - Matched Phase Slave Disable\n
    (1) - Matched Phase Slave Enable\n
 */
#define ADI_CFG_ASRC1_MATCHED_PHASE_ENABLE       (0x0u)
/*! De-Emphasis Type for ASRC1.\n
    (0) - No de-emphasis\n
    (1) - 32 kHz\n
    (2) - 44.1 kHz\n
    (3) - 48 kHz\n
*/
#define ADI_CFG_ASRC1_DEEMPHASIS_TYPE            (0x0u)

/* ASRC 2 DAI 0*/

/*! Input Format for ASRC2.\n
    (0) - left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (4) - 24-bit right-justified\n
    (5) - 20-bit right-justified\n
    (6) - 18-bit right-justified\n
    (7) - 16-bit right-justified\n
*/
#define ADI_CFG_ASRC2_INPUT_FORMAT               (0x1u)
/*! Output Format for ASRC2.\n
    (0) - Left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (3) - Right-justified\n 
*/
#define ADI_CFG_ASRC2_OUTPUT_FORMAT              (0x1u)
/*! Serial Output Word Length for ASRC2.\n
    (0) - 24 bits\n
    (1) - 20 bits\n
    (2) - 18 bits\n
    (3) - 16 bits\n
*/
#define ADI_CFG_ASRC2_WORD_LENGTH                (0x0u)
/*! Auto Mute Enable for ASRC2.\n
    (0) - Disable Auto Mute\n
    (1) - Enable Auto Mute\n
*/
#define ADI_CFG_ASRC2_AUTO_MUTE_ENABLE           (0x0u)
/*! Bypass Enable for ASRC2.\n
    (0) - Disable Bypass\n
	(1) - Enable Bypass\n
*/
#define ADI_CFG_ASRC2_BYPASS_ENABLE              (0x0u)
/*! Dither Enable before truncation for ASRC2.\n
    (0) - Truncation Only\n
    (1) - Dithering before truncation\n
 */
#define ADI_CFG_ASRC2_DITHER_ENABLE              (0x0u)
/*! Matched Phase Slave Enable for ASRC2.\n
    (0) - Matched Phase Slave Disable\n
    (1) - Matched Phase Slave Enable\n
 */
#define ADI_CFG_ASRC2_MATCHED_PHASE_ENABLE       (0x0u)
/*! De-Emphasis Type for ASRC2.\n
    (0) - No de-emphasis\n
    (1) - 32 kHz\n
    (2) - 44.1 kHz\n
    (3) - 48 kHz\n
*/
#define ADI_CFG_ASRC2_DEEMPHASIS_TYPE            (0x0u)

/* ASRC 3 DAI 0*/

/*! Input Format for ASRC3.\n
    (0) - left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (4) - 24-bit right-justified\n
    (5) - 20-bit right-justified\n
    (6) - 18-bit right-justified\n
    (7) - 16-bit right-justified\n
*/
#define ADI_CFG_ASRC3_INPUT_FORMAT               (0x1u)
/*! Output Format for ASRC3.\n
    (0) - Left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (3) - Right-justified\n 
*/
#define ADI_CFG_ASRC3_OUTPUT_FORMAT              (0x1u)
/*! Serial Output Word Length for ASRC3.\n
    (0) - 24 bits\n
    (1) - 20 bits\n
    (2) - 18 bits\n
    (3) - 16 bits\n
*/
#define ADI_CFG_ASRC3_WORD_LENGTH                (0x0u)
/*! Auto Mute Enable for ASRC3.\n
    (0) - Disable Auto Mute\n
    (1) - Enable Auto Mute\n
*/
#define ADI_CFG_ASRC3_AUTO_MUTE_ENABLE           (0x0u)
/*! Bypass Enable for ASRC3.\n
    (0) - Disable Bypass\n
	(1) - Enable Bypass\n
*/
#define ADI_CFG_ASRC3_BYPASS_ENABLE              (0x0u)
/*! Dither Enable before truncation for ASRC3.\n
    (0) - Truncation Only\n
    (1) - Dithering before truncation\n
 */
#define ADI_CFG_ASRC3_DITHER_ENABLE              (0x0u)
/*! Matched Phase Slave Enable for ASRC3.\n
    (0) - Matched Phase Slave Disable\n
    (1) - Matched Phase Slave Enable\n
 */
#define ADI_CFG_ASRC3_MATCHED_PHASE_ENABLE       (0x0u)
/*! De-Emphasis Type for ASRC3.\n
    (0) - No de-emphasis\n
    (1) - 32 kHz\n
    (2) - 44.1 kHz\n
    (3) - 48 kHz\n
*/
#define ADI_CFG_ASRC3_DEEMPHASIS_TYPE            (0x0u)

/* ASRC 0 DAI 1*/

/*! Input Format for ASRC4.\n
    (0) - left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (4) - 24-bit right-justified\n
    (5) - 20-bit right-justified\n
    (6) - 18-bit right-justified\n
    (7) - 16-bit right-justified\n
*/
#define ADI_CFG_ASRC4_INPUT_FORMAT               (0x1u)
/*! Output Format for ASRC4.\n
    (0) - Left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (3) - Right-justified\n 
*/
#define ADI_CFG_ASRC4_OUTPUT_FORMAT              (0x1u)
/*! Serial Output Word Length for ASRC4.\n
    (0) - 24 bits\n
    (1) - 20 bits\n
    (2) - 18 bits\n
    (3) - 16 bits\n
*/
#define ADI_CFG_ASRC4_WORD_LENGTH                (0x0u)
/*! Auto Mute Enable for ASRC4.\n
    (0) - Disable Auto Mute\n
    (1) - Enable Auto Mute\n
*/
#define ADI_CFG_ASRC4_AUTO_MUTE_ENABLE           (0x0u)
/*! Bypass Enable for ASRC4.\n
    (0) - Disable Bypass\n
	(1) - Enable Bypass\n
*/
#define ADI_CFG_ASRC4_BYPASS_ENABLE              (0x0u)
/*! Dither Enable before truncation for ASRC4.\n
    (0) - Truncation Only\n
    (1) - Dithering before truncation\n
 */
#define ADI_CFG_ASRC4_DITHER_ENABLE              (0x0u)
/*! Matched Phase Slave Enable for ASRC4.\n
    (0) - Matched Phase Slave Disable\n
    (1) - Matched Phase Slave Enable\n
 */
#define ADI_CFG_ASRC4_MATCHED_PHASE_ENABLE       (0x0u)
/*! De-Emphasis Type for ASRC4.\n
    (0) - No de-emphasis\n
    (1) - 32 kHz\n
    (2) - 44.1 kHz\n
    (3) - 48 kHz\n
*/
#define ADI_CFG_ASRC4_DEEMPHASIS_TYPE            (0x0u)

/* ASRC 1 DAI 1*/

/*! Input Format for ASRC5.\n
    (0) - left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (4) - 24-bit right-justified\n
    (5) - 20-bit right-justified\n
    (6) - 18-bit right-justified\n
    (7) - 16-bit right-justified\n
*/
#define ADI_CFG_ASRC5_INPUT_FORMAT               (0x1u)
/*! Output Format for ASRC5.\n
    (0) - Left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (3) - Right-justified\n 
*/
#define ADI_CFG_ASRC5_OUTPUT_FORMAT              (0x1u)
/*! Serial Output Word Length for ASRC5.\n
    (0) - 24 bits\n
    (1) - 20 bits\n
    (2) - 18 bits\n
    (3) - 16 bits\n
*/
#define ADI_CFG_ASRC5_WORD_LENGTH                (0x0u)
/*! Auto Mute Enable for ASRC5.\n
    (0) - Disable Auto Mute\n
    (1) - Enable Auto Mute\n
*/
#define ADI_CFG_ASRC5_AUTO_MUTE_ENABLE           (0x0u)
/*! Bypass Enable for ASRC5.\n
    (0) - Disable Bypass\n
	(1) - Enable Bypass\n
*/
#define ADI_CFG_ASRC5_BYPASS_ENABLE              (0x0u)
/*! Dither Enable before truncation for ASRC5.\n
    (0) - Truncation Only\n
    (1) - Dithering before truncation\n
 */
#define ADI_CFG_ASRC5_DITHER_ENABLE              (0x0u)
/*! Matched Phase Slave Enable for ASRC5.\n
    (0) - Matched Phase Slave Disable\n
    (1) - Matched Phase Slave Enable\n
 */
#define ADI_CFG_ASRC5_MATCHED_PHASE_ENABLE       (0x0u)
/*! De-Emphasis Type for ASRC5.\n
    (0) - No de-emphasis\n
    (1) - 32 kHz\n
    (2) - 44.1 kHz\n
    (3) - 48 kHz\n
*/
#define ADI_CFG_ASRC5_DEEMPHASIS_TYPE            (0x0u)

/* ASRC 2 DAI 1*/

/*! Input Format for ASRC6.\n
    (0) - left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (4) - 24-bit right-justified\n
    (5) - 20-bit right-justified\n
    (6) - 18-bit right-justified\n
    (7) - 16-bit right-justified\n
*/
#define ADI_CFG_ASRC6_INPUT_FORMAT               (0x1u)
/*! Output Format for ASRC6.\n
    (0) - Left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (3) - Right-justified\n 
*/
#define ADI_CFG_ASRC6_OUTPUT_FORMAT              (0x1u)
/*! Serial Output Word Length for ASRC6.\n
    (0) - 24 bits\n
    (1) - 20 bits\n
    (2) - 18 bits\n
    (3) - 16 bits\n
*/
#define ADI_CFG_ASRC6_WORD_LENGTH                (0x0u)
/*! Auto Mute Enable for ASRC6.\n
    (0) - Disable Auto Mute\n
    (1) - Enable Auto Mute\n
*/
#define ADI_CFG_ASRC6_AUTO_MUTE_ENABLE           (0x0u)
/*! Bypass Enable for ASRC6.\n
    (0) - Disable Bypass\n
	(1) - Enable Bypass\n
*/
#define ADI_CFG_ASRC6_BYPASS_ENABLE              (0x0u)
/*! Dither Enable before truncation for ASRC6.\n
    (0) - Truncation Only\n
    (1) - Dithering before truncation\n
 */
#define ADI_CFG_ASRC6_DITHER_ENABLE              (0x0u)
/*! Matched Phase Slave Enable for ASRC6.\n
    (0) - Matched Phase Slave Disable\n
    (1) - Matched Phase Slave Enable\n
 */
#define ADI_CFG_ASRC6_MATCHED_PHASE_ENABLE       (0x0u)
/*! De-Emphasis Type for ASRC6.\n
    (0) - No de-emphasis\n
    (1) - 32 kHz\n
    (2) - 44.1 kHz\n
    (3) - 48 kHz\n
*/
#define ADI_CFG_ASRC6_DEEMPHASIS_TYPE            (0x0u)

/* ASRC 3 DAI 1*/

/*! Input Format for ASRC7.\n
    (0) - left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (4) - 24-bit right-justified\n
    (5) - 20-bit right-justified\n
    (6) - 18-bit right-justified\n
    (7) - 16-bit right-justified\n
*/
#define ADI_CFG_ASRC7_INPUT_FORMAT               (0x1u)
/*! Output Format for ASRC7.\n
    (0) - Left-justified\n
    (1) - I2S\n
    (2) - TDM\n
    (3) - Right-justified\n 
*/
#define ADI_CFG_ASRC7_OUTPUT_FORMAT              (0x1u)
/*! Serial Output Word Length for ASRC7.\n
    (0) - 24 bits\n
    (1) - 20 bits\n
    (2) - 18 bits\n
    (3) - 16 bits\n
*/
#define ADI_CFG_ASRC7_WORD_LENGTH                (0x0u)
/*! Auto Mute Enable for ASRC7.\n
    (0) - Disable Auto Mute\n
    (1) - Enable Auto Mute\n
*/
#define ADI_CFG_ASRC7_AUTO_MUTE_ENABLE           (0x0u)
/*! Bypass Enable for ASRC7.\n
    (0) - Disable Bypass\n
	(1) - Enable Bypass\n
*/
#define ADI_CFG_ASRC7_BYPASS_ENABLE              (0x0u)
/*! Dither Enable before truncation for ASRC7.\n
    (0) - Truncation Only\n
    (1) - Dithering before truncation\n
 */
#define ADI_CFG_ASRC7_DITHER_ENABLE              (0x0u)
/*! Matched Phase Slave Enable for ASRC7.\n
    (0) - Matched Phase Slave Disable\n
    (1) - Matched Phase Slave Enable\n
 */
#define ADI_CFG_ASRC7_MATCHED_PHASE_ENABLE       (0x0u)
/*! De-Emphasis Type for ASRC7.\n
    (0) - No de-emphasis\n
    (1) - 32 kHz\n
    (2) - 44.1 kHz\n
    (3) - 48 kHz\n
*/
#define ADI_CFG_ASRC7_DEEMPHASIS_TYPE            (0x0u)

#endif /* ADI_ASRC_CONFIG_SC59X_H */

/*@}*/

/*@}*/
