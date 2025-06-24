/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/** @addtogroup Init_Preload_SC59x Processor Initialization Code
 *  @{
 *
 */

/*!
 * @file     adi_dmc_SC59x_config.c
 *
 * @brief    DMC controller configuration source.
 *
 * @version  2.11.0
 *
 * @date     31-Jan-2022
 *
 * @details  This is the source file for the DMC controller initialization
 */

#include <sys/platform.h>
#include <stdint.h>
#include "adi_dmc_SC59x_config.h"

#if CONFIG_DMC0 != DMC_NONE

#if defined(__ADSPSC594_FAMILY__)
 #if (CONFIG_DMC0 == ISSI_8Gb_DDR3_667MHZ) || \
     (CONFIG_DMC0 == ISSI_4Gb_DDR3_667MHZ)
  #include "adi_dmc_SC594_family_667MHz_config.h"
 #elif (CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ) || \
       (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ) || \
	   (CONFIG_DMC0 == WINBOND_2Gb_DDR3_800MHZ)
  #include "adi_dmc_SC594_family_800MHz_config.h"
 #else
  #error unexpected
 #endif
#elif defined(__ADSPSC598_FAMILY__)
 #if (CONFIG_DMC0 == ISSI_8Gb_DDR3_667MHZ) || \
     (CONFIG_DMC0 == ISSI_4Gb_DDR3_667MHZ)
  #include "adi_dmc_SC598_family_667MHz_config.h"
 #elif (CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ) || \
       (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ)
  #include "adi_dmc_SC598_family_800MHz_config.h"
 #elif (CONFIG_DMC0 == ISSI_8Gb_DDR3_900MHZ) || \
       (CONFIG_DMC0 == ISSI_4Gb_DDR3_900MHZ)
  #include "adi_dmc_SC598_family_900MHz_config.h"
 #else
  #error unexpected
 #endif
#else
 #error unexpected
#endif

/**
 * @brief    Initializes DMC controller.
 *
 * @return   Status
 *           - 0: Successful in initializing DMC controller.
 *           - 1: Error.
 */
uint32_t adi_dmc_cfg0_init(void)
{
    uint32_t status = 0u;

    static ADI_DMC_CONFIG config =
    {
            CFG0_REG_DDR_DLLCTLCFG,
            CFG0_REG_DMC_MR2MR3,
            CFG0_REG_DMC_CTL_VALUE,
            CFG0_REG_DMC_MRMR1,
            CFG0_REG_DMC_TR0_VALUE,
            CFG0_REG_DMC_TR1_VALUE,
            CFG0_REG_DMC_TR2_VALUE,
#if (CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ) || \
    (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ) || \
    (CONFIG_DMC0 == ISSI_8Gb_DDR3_900MHZ) || \
    (CONFIG_DMC0 == ISSI_4Gb_DDR3_900MHZ) || \
	(CONFIG_DMC0 == WINBOND_2Gb_DDR3_800MHZ)
            0x00785a64ul, /* 0x78 (Data/DQS ODT)
                             0x5a (90ohms Data/DQS/DM/CLK Drive Strength)
                             0x64 (100ohms Address/Command Drive Strength) */
#else
            0x00786464ul, /* 0x78 (Data/DQS ODT)
                             0x64 (100ohms Data/DQS/DM/CLK Drive Strength)
                             0x64 (100ohms Address/Command Drive Strength) */
#endif
            0ul,
            0x70000000ul
    };


    /* Initialize DMC PHY registers */
    adi_dmc_phy_calibration(&config);

    /* Initialize DMC Controller */
    if(adi_dmc_ctrl_init(&config) != ADI_DMC_SUCCESS)
    {
       /* Assign error status return value */
       status = 1u;
    }

#ifdef __ADI_HAS_DDRPFB__
    /* Invalidate the DDR prefetch buffer after DMC initialization. The
    ** invalidation bit must be cleared manually. */
    *pREG_DDRPFB0_CTL0 |= BITM_DDRPFB_CTL0_DATA_INVALIDATION;
    *pREG_DDRPFB0_CTL0 &= ~BITM_DDRPFB_CTL0_DATA_INVALIDATION;
#endif

    return status;
}

#endif /* CONFIG_DMC0 != DMC_NONE */

/*@}*/

