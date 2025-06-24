/*
 * Copyright (c) 2018-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*!
 * @file     adi_dmc_SC594_family_800MHz_config.h
 *
 * @brief    Header file for 800MHz DMC configuration
 *
 * @details
 */

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_5_1:"Allow identifiers to be more than 31 characters")
#endif

#ifndef ADI_DMC_SC594_FAMILY_800MHZ_CONFIG_H
#define ADI_DMC_SC594_FAMILY_800MHZ_CONFIG_H

#include "config.h"

#if CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ ||  CONFIG_DMC0 == WINBOND_2Gb_DDR3_800MHZ

#include <sys/platform.h>

/* DMC0 setup for the newer EV-21593-SOM and EV-SC594-SOM :
 * - uses a single 8GB IS43TR16512BL-125KBL DDR3 chip configured for
 *   800 MHz DCLK.
 * DMC0 setup for the rev A EV-SC594-SOM :
 * - uses a single 4GB IS43TR16256BL-093NBL DDR3 chip configured for
 *   800 MHz DCLK.
 */

/*****************************************DMC_CTL**********************************************/
/*! Constant value, should not be altered*/
#define CFG0_BIT_DMC_CTL_RDTOWR                     5ul

#define CFG0_REG_DMC_CTL_VALUE      (BITM_DMC_CTL_DDR3EN |\
                                     BITM_DMC_CTL_INIT |\
                                     (CFG0_BIT_DMC_CTL_RDTOWR<<BITP_DMC_CTL_RDTOWR) |\
                                     BITM_DMC_CTL_AL_EN)

/*****************************************DMC_CFG**********************************************/
/*! DDR3 memory size selected */
#if CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ
#define CFG0_BIT_DMC_CFG_SDRSIZE                    (ENUM_DMC_CFG_SDRSIZE4G)
#elif CONFIG_DMC0 == WINBOND_2Gb_DDR3_800MHZ
#define CFG0_BIT_DMC_CFG_SDRSIZE                    (ENUM_DMC_CFG_SDRSIZE2G)
#else
#define CFG0_BIT_DMC_CFG_SDRSIZE                    (ENUM_DMC_CFG_SDRSIZE8G)
#endif

/*! Value for the DMC_CFG (DMC Configuration) register. */
#define CFG0_REG_DMC_CFG_VALUE \
  (ENUM_DMC_CFG_IFWID16     | /* Interface Width - always 16-bit */ \
   ENUM_DMC_CFG_SDRWID16    | /* SDRAM Width - always 16-bit */ \
   CFG0_BIT_DMC_CFG_SDRSIZE | /* SDRAM Size */ \
   ENUM_DMC_CFG_EXTBANK1)     /* External Banks - always 1 bank */
/*****************************************DMC_DLLCTL*******************************************/
/*! DLL Calibration RD Count */
#define ADI_DMC_PARAM_DLLCOUNT                    240ul

/*! Data Cycles - ceil( 15ns/DDRclock in Hz) */
#define CFG0_REG_DMC_DATACYC                        12ul

/*! Value for the DMC_DLLCTL (DMC DLL Control) register. */
#define CFG0_REG_DMC_DLLCTL_VALUE \
  ((ADI_DMC_PARAM_DLLCOUNT<<BITP_DMC_DLLCTL_DLLCALRDCNT) | \
   (CFG0_REG_DMC_DATACYC<<BITP_DMC_DLLCTL_DATACYC))

/*****************************************DMC_TR0**********************************************/
/*! Trcd value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TRCD                       11ul
/*! Twtr value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TWTR                       6ul
/*! Trp value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TRP                        11ul
/*! Tras value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TRAS                       28ul
/*! Trc value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TRC                        39ul
/*! Tmrd value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TMRD                       4ul

#define CFG0_REG_DMC_TR0_VALUE      ((CFG0_BIT_DMC_TR0_TRCD<<BITP_DMC_TR0_TRCD)|(CFG0_BIT_DMC_TR0_TWTR<<BITP_DMC_TR0_TWTR)|(CFG0_BIT_DMC_TR0_TRP<<BITP_DMC_TR0_TRP)|(CFG0_BIT_DMC_TR0_TRAS<<BITP_DMC_TR0_TRAS)|(CFG0_BIT_DMC_TR0_TRC<<BITP_DMC_TR0_TRC)|(CFG0_BIT_DMC_TR0_TMRD<<BITP_DMC_TR0_TMRD))

/*****************************************DMC_TR1**********************************************/
/*! Tref value in DDR clock cycles*/
#if !defined(CONFIG_DRAM_TEMP) || CONFIG_DRAM_TEMP == NORMAL_TEMPERATURE
#define CFG0_BIT_DMC_TR1_TREF                        6240ul
#elif CONFIG_DRAM_TEMP == EXTENDED_TEMPERATURE
#define CFG0_BIT_DMC_TR1_TREF                        3120ul
#endif
/*! Trfc value in DDR clock cycles*/
#if CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ
#define CFG0_BIT_DMC_TR1_TRFC                        208ul
#elif CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ
#define CFG0_BIT_DMC_TR1_TRFC                        280ul
#elif CONFIG_DMC0 == WINBOND_2Gb_DDR3_800MHZ
#define CFG0_BIT_DMC_TR1_TRFC                        128ul
#endif

/*! Trrd value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR1_TRRD                        6ul

#define CFG0_REG_DMC_TR1_VALUE      ((CFG0_BIT_DMC_TR1_TREF<<BITP_DMC_TR1_TREF)|(CFG0_BIT_DMC_TR1_TRFC<<BITP_DMC_TR1_TRFC)|(CFG0_BIT_DMC_TR1_TRRD<<BITP_DMC_TR1_TRRD))

/*****************************************DMC_TR2**********************************************/

/*! Tfaw value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TFAW                          32ul
/*! Trtp value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TRTP                          6ul
/*! Txp value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TXP                           5ul
/*! Tcke value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TCKE                          4ul

#define CFG0_REG_DMC_TR2_VALUE      ((CFG0_BIT_DMC_TR2_TFAW<<BITP_DMC_TR2_TFAW)|(CFG0_BIT_DMC_TR2_TRTP<<BITP_DMC_TR2_TRTP)|(CFG0_BIT_DMC_TR2_TXP<<BITP_DMC_TR2_TXP)|(CFG0_BIT_DMC_TR2_TCKE<<BITP_DMC_TR2_TCKE))

/****************************************DMC  DLLCTLCFG**********************************************/

/*! The DMC_CFG and DMC_DLLCTL values are combined for ulDDR_DLLCTLCFG field. */
#define CFG0_REG_DDR_DLLCTLCFG \
  (CFG0_REG_DMC_CFG_VALUE |    \
   (CFG0_REG_DMC_DLLCTL_VALUE<<16))

/****************************************DMC  MR0**********************************************/

/*! Constant value, should not be altered*/
#define CFG0_BIT_DMC_MR0_BLEN                           0ul
/*! CAS Read latency bit 0 value*/
#define CFG0_BIT_DMC_MR0_CL0                            0ul
/*! CAS Read latency [2:1] bits*/
#define CFG0_BIT_DMC_MR0_CL                             7ul
/*! Constant value, should not be altered*/
#define CFG0_BIT_DMC_MR0_DLLRST                         1ul
/*! Write recovery value*/
#define CFG0_BIT_DMC_MR0_WRRECOV                        6ul

#define CFG0_REG_DMC_MR0_VALUE             ((CFG0_BIT_DMC_MR0_BLEN<<BITP_DMC_MR_BLEN)|(CFG0_BIT_DMC_MR0_CL0<<BITP_DMC_MR_CL0)|(CFG0_BIT_DMC_MR0_CL<<BITP_DMC_MR_CL)|(CFG0_BIT_DMC_MR0_DLLRST<<BITP_DMC_MR_DLLRST)|(CFG0_BIT_DMC_MR0_WRRECOV<<BITP_DMC_MR_WRRECOV))

/****************************************DMC  MR1**********************************************/
/*! Constant value, should not be altered*/
#define CFG0_BIT_DMC_MR1_DLLEN                            0ul
/*! Bit 0 of the output DS*/
#define CFG0_BIT_DMC_MR1_DIC0                             0ul
/*! Bit 0 of the ODT*/
#define CFG0_BIT_DMC_MR1_RTT0                             0ul
/*! Additive latency setting*/
#define CFG0_BIT_DMC_MR1_AL                               0ul
/*! Bit 1 of the output DS*/
#define CFG0_BIT_DMC_MR1_DIC1                             0ul
/*! Bit 1 of the ODT*/
#define CFG0_BIT_DMC_MR1_RTT1                             1ul
/*! Bit 2 of the ODT*/
#define CFG0_BIT_DMC_MR1_RTT2                             0ul
#define CFG0_BIT_DMC_MR1_TDQS                             0ul
#define CFG0_BIT_DMC_MR1_QOFF                             0ul

#define CFG0_REG_DMC_MR1_VALUE ((CFG0_BIT_DMC_MR1_DLLEN<<BITP_DMC_MR1_DLLEN)|(CFG0_BIT_DMC_MR1_DIC0<<BITP_DMC_MR1_DIC0)|(CFG0_BIT_DMC_MR1_RTT0<<BITP_DMC_MR1_RTT0)|(CFG0_BIT_DMC_MR1_AL<<BITP_DMC_MR1_AL)|(CFG0_BIT_DMC_MR1_DIC1<<BITP_DMC_MR1_DIC1)|(CFG0_BIT_DMC_MR1_RTT1<<BITP_DMC_MR1_RTT1)|(CFG0_BIT_DMC_MR1_RTT2<<BITP_DMC_MR1_RTT2)|(CFG0_BIT_DMC_MR1_TDQS<<BITP_DMC_MR1_TDQS)|(CFG0_BIT_DMC_MR1_QOFF<<BITP_DMC_MR1_QOFF)|BITM_DMC_MR1_WL)

/**************************************** DMC  MR2MR3**********************************************/
/*! CAS write latency*/
#define CFG0_BIT_DMC_MR2_CWL                              3ul

/*! Self Refresh Temperature Range*/
#if !defined(CONFIG_DRAM_TEMP) || CONFIG_DRAM_TEMP == NORMAL_TEMPERATURE
#define CFG0_REG_DMC_MR2_VALUE (CFG0_BIT_DMC_MR2_CWL<<BITP_DMC_MR2_CWL)
#elif CONFIG_DRAM_TEMP == EXTENDED_TEMPERATURE
#define CFG0_REG_DMC_MR2_VALUE ((CFG0_BIT_DMC_MR2_CWL<<BITP_DMC_MR2_CWL)|BITM_DMC_MR2_SRT)
#endif

#define CFG0_REG_DMC_MR2MR3      (((CFG0_REG_DMC_MR2_VALUE)<<16)|BITM_DMC_EMR3_MPR)

#define CFG0_REG_DMC_MRMR1        (CFG0_REG_DMC_MR1_VALUE|(CFG0_REG_DMC_MR0_VALUE<<16))

#endif /* CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ */

#endif /* ifndef ADI_DMC_SC594_FAMILY_800MHZ_CONFIG_H */

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

