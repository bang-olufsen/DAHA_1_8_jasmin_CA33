/*
 * Copyright (c) 2018-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*!
* @file      adi_pwr_SC594_family_600MHz_config.h
*
* @brief     Header file for Power Service Configuration for 600Hz CCLK operation.
*
* @details
*
*/

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_5_1:"Allow identifiers to be more than 31 characters")
#endif

#ifndef ADI_PWR_SC594_FAMILY_600MHZ_CONFIG_H
#define ADI_PWR_SC594_FAMILY_600MHZ_CONFIG_H

/** @addtogroup Init_Preload_SC59x Processor Initialization Code
 *  @{
 *
 */

/*!
* @file      adi_pwr_SC594_family_600MHz_config.h
*
* @brief     power Service configuration file
*
* @details
*            power Service configuration file
*/

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
SHARC0 & its Accelerators  (CLKO0) : CCLK0_0      :  600 MHz
SHARC1 & its Accelerators  (CLKO1) : CCLK0_0      :  600 MHz
ARM                        (CLKO2) : CCLK1_0      :  600 MHz
DDR                        (CLKO3) : DCLK_1       :  667 MHz
CANFD                      (CLKO4) : OCLK_1       :  100 MHz
SPDIF                      (CLKO5) : SCLK1_EXEN_0 :  300 MHz
SPI                        (CLKO6) : SCLK0_0      :  100 MHz
GigE                       (CLKO7) : SCLK0_1      :  125 MHz
LP                         (CLKO8) : CCLK0_1      :  125 MHz
LP_DDR                     (CLKO9) : SYSCLK_1     :  250 MHz
OSPI_REFCLK                (CLKO10): SYSCLK_0     :  300 MHz
TRACE                      (CLKO12): SCLK0_0      :  100 MHz

CGU0 Initialization Options
---------------------------
fPLL                   :   1200.0 MHz
CCLK                   :   600.0 MHz
SYSCLK                 :   300.0 MHz
SCLK0                  :   100.0 MHz
SCLK1                  :   150.0 MHz
SCLK1_EXEN             :   300.0 MHz
DCLK                   :   600.0 MHz
OCLK                   :   120.0 MHz

MSEL                   :   48
Use DF?                :   No
DF                     :   0
CSEL                   :   2
CCLK to SYSCLK Ratio   :   2:1
S0SEL                  :   3
S1SEL                  :   2
DSEL                   :   2
OSEL                   :   10
Use S1SELEX?           :   Yes
S1SELEX                :   4

CGU1 Initialization Options
---------------------------
fPLL                   :   2000 MHz
CCLK                   :   125.0 MHz
SYSCLK                 :   250.0  MHz
SCLK0                  :   125.0 MHz
SCLK1                  :   125.0 MHz
SCLK1_EXEN             :   250.0 MHz
DCLK                   :   666.7 MHz
OCLK                   :   100.0 MHz

MSEL                   :   80
Use DF?                :   No
DF                     :   0
CSEL                   :   16
S0SEL                  :   2
S1SEL                  :   2
DSEL                   :   3
OSEL                   :   20
Use S1SELEX?           :   No
S1SELEX                :   8
*/
/**********************************************************************************************
 *                      CGU Configuration Number 0
 **********************************************************************************************/

#define CFG0_BIT_CGU0_CLKIN                                25000000 /*!< Macro for SYS_CLKIN */
#define CFG0_BIT_CGU1_CLKIN                                25000000 /*!< Macro for SYS_CLKIN */

/*****************************************CGU1_CLKINSELV**********************************************/
#define CFG0_BIT_CDU0_CLKINSEL                             (ADI_PWR_CDU_CLK_SELECT_CLKIN0) /*!< Macro for CDU CFG0 Selection */

/* CLKO0 : SHARC 0 and its accelerators : CCLK0_0 */
#define CFG0_BIT_CDU0_CFG0_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< Macro for CDU CFG0 Selection */

/* CLKO1 : SHARC 1 and its accelerators : CCLK0_0 */
#define CFG0_BIT_CDU0_CFG1_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< Macro for CDU CFG0 Selection */

/* CLKO2 : ARM : CCLK1_0 */
#define CFG0_BIT_CDU0_CFG2_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< Macro for CDU CFG0 Selection */

/* CLKO3 : DDR CLOCK : DCLK_0 DCLK_1 */
#define CFG0_BIT_CDU0_CFG3_SEL_VALUE                       (ENUM_CDU_CFG_IN1)        /*!< Macro for CDU CFG0 Selection */

/* CLKO4 : CAN : OCLK_0 OCLK_1 */
#define CFG0_BIT_CDU0_CFG4_SEL_VALUE                       (ENUM_CDU_CFG_IN1)        /*!< Macro for CDU CFG0 Selection */

/* CLKO5 : SPDIF : SCLK1_0 */
#define CFG0_BIT_CDU0_CFG5_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< Macro for CDU CFG0 Selection */

/* CLKO6 : SPI : SCLK0_0 OCLK_0 */
#define CFG0_BIT_CDU0_CFG6_SEL_VALUE                       (ENUM_CDU_CFG_IN0)        /*!< Macro for CDU CFG0 Selection */

/* CLKO7 : GigE : SCLK0_0 SCLK0_1 */
#define CFG0_BIT_CDU0_CFG7_SEL_VALUE                       (ENUM_CDU_CFG_IN1)        /*!< Macro for CDU CFG0 Selection */

/* CLKO8 : LP  : OCLK_0 SCLK0_0 CCLK0_1 */
#define CFG0_BIT_CDU0_CFG8_SEL_VALUE                       (ENUM_CDU_CFG_IN2)        /*!< Macro for CDU CFG0 Selection */

/* CLKO9 : LP_DDR : OCLK_0 DCLK0_0 SYSCLKO_1 */
#define CFG0_BIT_CDU0_CFG9_SEL_VALUE                       (ENUM_CDU_CFG_IN2)        /*!< Macro for CDU CFG0 Selection */

/* CLKO10 : OSPI_REFCLK : SYSCLK0_0 SCLK0_0 SCLK1_1 */
#define CFG0_BIT_CDU0_CFG10_SEL_VALUE                      (ENUM_CDU_CFG_IN0)        /*!< Macro for CDU CFG0 Selection */

/* CLKO12 : TRACE : SCLK0_0 SCLK1_1  */
#define CFG0_BIT_CDU0_CFG12_SEL_VALUE                      (ENUM_CDU_CFG_IN0)        /*!< Macro for CDU CFG0 Selection */

/**********************************************************************************************
 *                     CGU Configuration Number 0 Register Values
 **********************************************************************************************/
/*****************************************CGU0_CTL**********************************************/
#define CFG0_BIT_CGU0_CTL_DF                               0        /*!< Macro for CGU0 DF bit */
#define CFG0_BIT_CGU0_CTL_MSEL                             48       /*!< Macro for CGU0 MSEL field */
/*****************************************CGU0_DIV**********************************************/
#define CFG0_BIT_CGU0_DIV_CSEL                             2        /*!< Macro for CGU0 CSEL field */
#define CFG0_BIT_CGU0_DIV_SYSSEL                           4        /*!< Macro for CGU0 SYSSEL field */
#define CFG0_BIT_CGU0_DIV_S0SEL                            3        /*!< Macro for CGU0 S0SEL field */
#define CFG0_BIT_CGU0_DIV_S1SEL                            2        /*!< Macro for CGU0 S1SEL field */
#define CFG0_BIT_CGU0_DIV_DSEL                             2        /*!< Macro for CGU0 DSEL field */
#define CFG0_BIT_CGU0_DIV_OSEL                             10       /*!< Macro for CGU0 OSEL field */
/*****************************************CGU0_DIVEX**********************************************/
#define CFG0_BIT_CGU0_DIV_S1SELEX                          4        /*!< Macro for CGU0 S1SELEX field */

/*****************************************CGU1_CTL**********************************************/
#define CFG0_BIT_CGU1_CTL_DF                               0        /*!< Macro for CGU1 DF bit */
#define CFG0_BIT_CGU1_CTL_MSEL                             80       /*!< Macro for CGU1 MSEL field */
/*****************************************CGU1_DIV**********************************************/
#define CFG0_BIT_CGU1_DIV_CSEL                             16       /*!< Macro for CGU1 CSEL field */
#define CFG0_BIT_CGU1_DIV_SYSSEL                           8        /*!< Macro for CGU1 SYSSEL field */
#define CFG0_BIT_CGU1_DIV_S0SEL                            2        /*!< Macro for CGU1 S0SEL field */
#define CFG0_BIT_CGU1_DIV_S1SEL                            2        /*!< Macro for CGU1 S1SEL field */
#define CFG0_BIT_CGU1_DIV_DSEL                             3        /*!< Macro for CGU1 DSEL field */
#define CFG0_BIT_CGU1_DIV_OSEL                             20       /*!< Macro for CGU1 OSEL field */
/*****************************************CGU1_DIVEX**********************************************/
#define CFG0_BIT_CGU1_DIV_S1SELEX                          8        /*!< Macro for CGU1 S1SELEX field */

/*@}*/

#endif /* define ADI_PWR_SC594_FAMILY_600MHZ_CONFIG_H */

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

