/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/* This file was originally generated based upon the options selected in
 * the Basic Configuration of CGU Initialization configuration dialog.
 * Subsequently it has been manually edited.
 */

#ifndef ADI_PWR_SC598_FAMILY_800MHZ_CONFIG
#define ADI_PWR_SC598_FAMILY_800MHZ_CONFIG

#if !defined(__ADSPSC598_FAMILY__)
# error Only suitable for ADSP-SC598 family parts.
#endif

#include "config.h"

#if CONFIG_SHARC_CORE_CLOCK != CORE_CLOCK_800MHZ
# error CONFIG_SHARC_CORE_CLOCK not defined as expected
#endif

/** @addtogroup Init_Preload_SC59x Processor Initialization Code
 *  @{
 *
 */

/*!
* @file      adi_pwr_SC598_family_800MHz_config.h
*
* @brief     Power Service configuration include file.
*
* @details   Definitions for the power service initialization.
*/

#include <sys/platform.h>

/**********************************************************************************************
 *                     CGU Configuration Number 0
 **********************************************************************************************/
/*
Configuration Number    : 0
SDRAM Mode              : DDR3
SYS_CLKIN0 (MHz)        : 25
Use CGU1 ?              : Yes

CDU Initialization Options
--------------------------
SHARC0 & its Accelerators  (CLKO0) : CCLK0_0          :  812.5 MHz
SHARC1 & its Accelerators  (CLKO1) : CCLK0_0          :  812.5 MHz
ARM                        (CLKO2) : CCLK2_1          : 1200 MHz
DDR                        (CLKO3) : DCLK_2(3rd PLL)  :  800 MHz
CANFD                      (CLKO4) : OCLK_1           :  100 MHz
SPDIF                      (CLKO5) : SCLK1_EXEN_0     :  325 MHz
SPI                        (CLKO6) : OCLK_0           :  125 MHz
GigE                       (CLKO7) : OCLK_0           :  125 MHz
LP                         (CLKO8) : CCLK0_1          :  112.5 MHz
LP_DDR                     (CLKO9) : SYSCLK_1         :  225 MHz
OSPI_REFCLK                (CLKO10): SYSCLK_0         :  406.25 MHz
TRACE                      (CLKO12): SCLK0_0          :  101.56 MHz
EMMC                       (CLKO13): SCLK0_EXEN_1     :  50 MHz
EMMC TIMER CMQ             (CLKO14): (SCLK1_EXEN_1)/2 :  10 MHz


CGU0 Initialization Options
---------------------------
fVCO                   :   3250.00 MHz
fPLL                   :   1625.00 MHz
CCLK                   :    812.50 MHz
CCLK2_0				   :   1083.33 MHz
SYSCLK                 :    406.25 MHz
SCLK0                  :    101.56 MHz
SCLK1                  :    325.00 MHz
SCLK1_EXEN             :    333.33 MHz
DCLK                   :    812.50 MHz
OCLK                   :    125.00 MHz

MSEL                   :   65
Use DF?                :   No
DF                     :   0
CSEL                   :   2
CCLK to SYSCLK Ratio   :   2:1
SYSCLK to SCLK0 Ratio  :   4:1
SYSSEL				   :   4
S0SEL                  :   4
S1SEL                  :   2
DSEL                   :   2
OSEL                   :   13
Use S1SELEX?           :   Yes
S1SELEX                :   5

CGU1 Initialization Options
---------------------------
fVCO                   :   3600.00 MHz
fPLL                   :   1800.00 MHz
CCLK                   :    112.50 MHz
CCLK2_1  			   :   1200.00 MHz
SYSCLK                 :    225.00 MHz
SCLK0                  :     56.25 MHz
SCLK0_EXEN             :     50.00 MHz
SCLK1                  :    112.50 MHz
SCLK1_EXEN             :     20.00 MHz
DCLK                   :    600.00 MHz
OCLK                   :    100.00 MHz

MSEL                   :   72
Use DF?                :   No
DF                     :   0
CSEL                   :   16
SYSSEL				   :   8
S0SEL                  :   4
S1SEL                  :   2
DSEL                   :   3
OSEL                   :   18
Use S0SELEX?           :   Yes
S0SELEX                :   36
Use S1SELEX?           :   Yes
S1SELEX                :   90
*/

/**********************************************************************************************
 *                      CGU Configuration Number 0
 **********************************************************************************************/

#define CFG0_BIT_CGU0_CLKIN                                25000000 /*!< Macro for SYS_CLKIN */
#define CFG0_BIT_CGU1_CLKIN                                25000000 /*!< Macro for SYS_CLKIN */

/*****************************************CGU1_CLKINSELV**********************************************/
#define CFG0_BIT_CDU0_CLKINSEL                             (ADI_PWR_CDU_CLK_SELECT_CLKIN0) /*!< Macro for CDU CFG0 Selection */

#define CFG0_BIT_CDU0_CFG0_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< CLKO0 : SHARC 0 and its accelerators : CCLK0_0 */

#define CFG0_BIT_CDU0_CFG1_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< CLKO1 : SHARC 1 and its accelerators : CCLK0_0 */

#define CFG0_BIT_CDU0_CFG2_SEL_VALUE                       (ENUM_CDU_CFG_IN3)        /*!< CLKO2 : ARM : CCLK2_0 CCLK2_1 */

#define CFG0_BIT_CDU0_CFG3_SEL_VALUE                       (ENUM_CDU_CFG_IN1)        /*!< CLKO3 : DDR CLOCK : DCLK_0 DCLK_1 */

#define CFG0_BIT_CDU0_CFG4_SEL_VALUE                       (ENUM_CDU_CFG_IN1)        /*!< CLKO4 : CAN : OCLK_1 */

#define CFG0_BIT_CDU0_CFG5_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< CLKO5 : SPDIF : SCLK1_0 */

#define CFG0_BIT_CDU0_CFG6_SEL_VALUE                       (ENUM_CDU_CFG_IN1)        /*!< CLKO6 : SPI : SCLK0_0 OCLK_0 */

#define CFG0_BIT_CDU0_CFG7_SEL_VALUE                       (ENUM_CDU_CFG_IN2)        /*!< CLKO7 : GigE : SCLK0_0 SCLK0_1 */

#define CFG0_BIT_CDU0_CFG8_SEL_VALUE                       (ENUM_CDU_CFG_IN2)        /*!< CLKO8 : LP  : OCLK_0 SCLK0_0 CCLK0_1 */

#define CFG0_BIT_CDU0_CFG9_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< CLKO9 : LP_DDR : OCLK_0 DCLK_0 SYSCLKO_1 */

#define CFG0_BIT_CDU0_CFG10_SEL_VALUE                      (ENUM_CDU_CFG_IN0)        /*!< CLKO10 : OSPI_REFCLK : SYSCLK0_0 SCLK0_0 SCLK1_1 */

#define CFG0_BIT_CDU0_CFG12_SEL_VALUE                      (ENUM_CDU_CFG_IN0)        /*!< CLKO12 : TRACE : SCLK0_0 */

#define CFG0_BIT_CDU0_CFG13_SEL_VALUE                      (ENUM_CDU_CFG_IN1)        /*!< CLKO13 : EMMC : OCLK_0 SCLK0_1 DCLK_0/2 DCLK_1/2  */

#define CFG0_BIT_CDU0_CFG14_SEL_VALUE                      (ENUM_CDU_CFG_IN1)        /*!< CLKO14 : EMMC TIMER CMQ : SCLK1_1/2  */

/**********************************************************************************************
 *                     CGU Configuration Number 0 Register Values
 **********************************************************************************************/
/*****************************************CGU0_CTL**********************************************/
#define CFG0_BIT_CGU0_CTL_DF                               0        /*!< Macro for CGU0 DF bit */
#define CFG0_BIT_CGU0_CTL_MSEL                             65       /*!< Macro for CGU0 MSEL field */
/*****************************************CGU0_DIV**********************************************/
#define CFG0_BIT_CGU0_DIV_CSEL                             2        /*!< Macro for CGU0 CSEL field */
#define CFG0_BIT_CGU0_DIV_SYSSEL                           4        /*!< Macro for CGU0 SYSSEL field */
#define CFG0_BIT_CGU0_DIV_S0SEL                            4        /*!< Macro for CGU0 S0SEL field */
#define CFG0_BIT_CGU0_DIV_S1SEL                            2        /*!< Macro for CGU0 S1SEL field */
#define CFG0_BIT_CGU0_DIV_DSEL                             2        /*!< Macro for CGU0 DSEL field */
#define CFG0_BIT_CGU0_DIV_OSEL                             13       /*!< Macro for CGU0 OSEL field */
/*****************************************CGU0_DIVEX**********************************************/
#define CFG0_BIT_CGU0_DIV_S1SELEX                          5        /*!< Macro for CGU0 S1SELEX field */

/*****************************************CGU1_CTL**********************************************/
#define CFG0_BIT_CGU1_CTL_DF                               0        /*!< Macro for CGU1 DF bit */
#define CFG0_BIT_CGU1_CTL_MSEL                             72       /*!< Macro for CGU1 MSEL field */
/*****************************************CGU1_DIV**********************************************/
#define CFG0_BIT_CGU1_DIV_CSEL                             16       /*!< Macro for CGU1 CSEL field */
#define CFG0_BIT_CGU1_DIV_SYSSEL                           8        /*!< Macro for CGU1 SYSSEL field */
#define CFG0_BIT_CGU1_DIV_S0SEL                            4        /*!< Macro for CGU1 S0SEL field */
#define CFG0_BIT_CGU1_DIV_S1SEL                            2        /*!< Macro for CGU1 S1SEL field */
#define CFG0_BIT_CGU1_DIV_DSEL                             3        /*!< Macro for CGU1 DSEL field */
#define CFG0_BIT_CGU1_DIV_OSEL                             18       /*!< Macro for CGU1 OSEL field */
/*****************************************CGU1_DIVEX**********************************************/
#define CFG0_BIT_CGU1_DIV_S0SELEX                          36       /*!< Macro for CGU1 S1SELEX field */
#define CFG0_BIT_CGU1_DIV_S1SELEX                          90       /*!< Macro for CGU1 S1SELEX field */

#if CONFIG_DMC0

/*****************************************CGU2_CTL**********************************************/
#define CGU2_MSEL         				                   64       /*!< Macro for CGU2 MSEL field */
/*****************************************CGU2_DIV**********************************************/
#define CGU2_DSEL         				                   2        /*!< Macro for CGU2 DSEL field */

#endif
/*@}*/

#endif /* #ifndef ADI_PWR_SC598_FAMILY_800MHZ_CONFIG */

