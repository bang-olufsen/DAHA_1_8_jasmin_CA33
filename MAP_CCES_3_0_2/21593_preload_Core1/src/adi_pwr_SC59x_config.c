/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/** @addtogroup Init_Preload_SC59x Processor Initialization Code
 *  @{
 *
 */

/*!
* @file      adi_pwr_SC59x_config.c
*
* @brief     power Service configuration file
*
* @details
*            power Service configuration file
*/

#include "config.h"
#include "adi_pwr_SC59x_config.h"
#include <services/pwr/adi_pwr.h>

#if CONFIG_DMC0
#include "adi_dmc.h"
#endif

#if defined(__ADSPSC594_FAMILY__)
 #if CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_1GHZ
  #include "adi_pwr_SC594_family_1GHz_config.h"
 #elif CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_800MHZ
  #include "adi_pwr_SC594_family_800MHz_config.h"
 #elif CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_600MHZ
  #include "adi_pwr_SC594_family_600MHz_config.h"
 #else
  #error Unexpected
 #endif
#elif defined(__ADSPSC598_FAMILY__)
 #if CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_1GHZ
  #include "adi_pwr_SC598_family_1GHz_config.h"
 #elif CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_800MHZ
  #include "adi_pwr_SC598_family_800MHz_config.h"
 #elif CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_600MHZ
  #include "adi_pwr_SC598_family_600MHz_config.h"
 #else
  #error Unexpected
 #endif
#else
 #error Unexpected
#endif

#if CONFIG_DMC0
 #if defined(__ADSPSC598_FAMILY__) && defined(__ADSPARM__ )
 /* This should be changed if ARM clock source is changed in CDU to any clock other than CCLK2_1 */
 #define cclkclkin_ratio ((float32_t)CFG0_BIT_CGU1_CTL_MSEL*2.0f/3.0f)
 #elif defined(__ADSPSC598_FAMILY__) && defined(__ADSPSHARC__ )
 #define cclkclkin_ratio ((float32_t)CFG0_BIT_CGU0_CTL_MSEL/CFG0_BIT_CGU0_DIV_CSEL)
 #endif
#endif


/**
 * @brief    Initializes clocks, including CGU and CDU modules.
 *
 * @return   Status
 *           - 0: Successful in all the initializations.
 *           - 1: Error.

 */
uint32_t adi_pwr_cfg0_init(void)
{
    uint32_t status = 0u; /*Return zero if there are no errors*/

    /* Structure pointer for CGU0 and CGU1 parameters*/
    ADI_PWR_CGU_PARAM_LIST pADI_CGU_Param_List;

    /* Structure pointer for CDU parameters*/
    ADI_PWR_CDU_PARAM_LIST pADI_CDU_Param_List;

    /* CDU Configuration*/
    pADI_CDU_Param_List.cdu_settings[0].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG0_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[0].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[1].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG1_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[1].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[2].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG2_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[2].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[3].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG3_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[3].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[4].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG4_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[4].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[5].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG5_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[5].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[6].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG6_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[6].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[7].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG7_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[7].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[8].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG8_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[8].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[9].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG9_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[9].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[10].cfg_SEL                    =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG10_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[10].cfg_EN                     =       true;


    pADI_CDU_Param_List.cdu_settings[12].cfg_SEL                    =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG12_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[12].cfg_EN                     =       true;

#if defined(__ADSPSC598_FAMILY__)
    pADI_CDU_Param_List.cdu_settings[13].cfg_SEL                    =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG13_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[13].cfg_EN                     =       true;

    pADI_CDU_Param_List.cdu_settings[14].cfg_SEL                    =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG14_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[14].cfg_EN                     =       true;
#endif

    /* CGU0 Configuration*/
    pADI_CGU_Param_List.cgu0_settings.clocksettings.ctl_MSEL        =       (uint32_t)CFG0_BIT_CGU0_CTL_MSEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.ctl_DF          =       (uint32_t)CFG0_BIT_CGU0_CTL_DF;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_CSEL        =       (uint32_t)CFG0_BIT_CGU0_DIV_CSEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_SYSSEL      =       (uint32_t)CFG0_BIT_CGU0_DIV_SYSSEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_S0SEL       =       (uint32_t)CFG0_BIT_CGU0_DIV_S0SEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_S1SEL       =       (uint32_t)CFG0_BIT_CGU0_DIV_S1SEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.divex_S1SELEX   =       (uint32_t)CFG0_BIT_CGU0_DIV_S1SELEX;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_DSEL        =       (uint32_t)CFG0_BIT_CGU0_DIV_DSEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_OSEL        =       (uint32_t)CFG0_BIT_CGU0_DIV_OSEL;
    pADI_CGU_Param_List.cgu0_settings.clkin                         =       (uint32_t)CFG0_BIT_CGU0_CLKIN;
#if defined(__ADSPSC594_FAMILY__)
    pADI_CGU_Param_List.cgu0_settings.enable_IDLE                   =       false;
#endif
    pADI_CGU_Param_List.cgu0_settings.enable_SCLK1ExDiv             =       true;

    /* CGU1 Configuration*/
    pADI_CGU_Param_List.cgu1_settings.clocksettings.ctl_MSEL        =       (uint32_t)CFG0_BIT_CGU1_CTL_MSEL;
    pADI_CGU_Param_List.cgu1_settings.clocksettings.ctl_DF          =       (uint32_t)CFG0_BIT_CGU1_CTL_DF;
    pADI_CGU_Param_List.cgu1_settings.clocksettings.div_CSEL        =       (uint32_t)CFG0_BIT_CGU1_DIV_CSEL;
    pADI_CGU_Param_List.cgu1_settings.clocksettings.div_SYSSEL      =       (uint32_t)CFG0_BIT_CGU1_DIV_SYSSEL;
    pADI_CGU_Param_List.cgu1_settings.clocksettings.div_S0SEL       =       (uint32_t)CFG0_BIT_CGU1_DIV_S0SEL;
    pADI_CGU_Param_List.cgu1_settings.clocksettings.div_S1SEL       =       (uint32_t)CFG0_BIT_CGU1_DIV_S1SEL;
#if defined(__ADSPSC598_FAMILY__)
    pADI_CGU_Param_List.cgu1_settings.clocksettings.divex_S0SELEX   =       (uint32_t)CFG0_BIT_CGU1_DIV_S0SELEX;
#endif
    pADI_CGU_Param_List.cgu1_settings.clocksettings.divex_S1SELEX   =       (uint32_t)CFG0_BIT_CGU1_DIV_S1SELEX;
    pADI_CGU_Param_List.cgu1_settings.clocksettings.div_DSEL        =       (uint32_t)CFG0_BIT_CGU1_DIV_DSEL;
    pADI_CGU_Param_List.cgu1_settings.clocksettings.div_OSEL        =       (uint32_t)CFG0_BIT_CGU1_DIV_OSEL;
    pADI_CGU_Param_List.cgu1_settings.clkin                         =       (uint32_t)CFG0_BIT_CGU1_CLKIN;
#if defined(__ADSPSC598_FAMILY__)
    pADI_CGU_Param_List.cgu1_settings.enable_SCLK0ExDiv             =       true;
    pADI_CGU_Param_List.cgu1_settings.enable_SCLK1ExDiv             =       true;
#else
    pADI_CGU_Param_List.cgu1_settings.enable_IDLE                   =       false;
    pADI_CGU_Param_List.cgu1_settings.enable_SCLK1ExDiv             =       false;
#endif
    pADI_CGU_Param_List.cgu1_settings.cgu1_clkinsel                 =       (ADI_PWR_CDU_CLK_SELECT)ADI_PWR_CDU_CLK_SELECT_CLKIN0;

#if defined(__ADSPSC598_FAMILY__) && CONFIG_DMC0
    adi_configDCLK_1(CGU2_MSEL, CGU2_DSEL);
#endif

    /* Initialize all the clocks */
    if (adi_pwr_ClockInit(&pADI_CGU_Param_List, &pADI_CDU_Param_List) != ADI_PWR_SUCCESS)
    {
       /* Return non-zero */
       status = 1u;
    }

    return status;
}

#if defined(__ADSPSC598_FAMILY__) && CONFIG_DMC0

/*
 * Configures and enables DDR clock from CGU2
 * This clock when enabled bypass the DDR clock selected from CDU03.
 */
void adi_configDCLK_1(uint32_t Msel, uint32_t Dsel)
{

    Msel--;
    Dsel--;

    /* MSEL update */
    /*     Clear BYPASSB, DSEL_DIV_CHG and MSELDF_CHG */
    *pREG_MISCREG_PLL2_CONTROL &= ~(BITM_MISCREG_PLL2_CONTROL_BYPASSB | BITM_MISCREG_PLL2_CONTROL_MSELDF_CHG | BITM_MISCREG_PLL2_CONTROL_DSEL_DIV_CHG) ;
    Cclkdelay(20);
    /* update MSEL */
    *pREG_MISCREG_PLL2_CONTROL &= ~BITM_MISCREG_PLL2_CONTROL_MSEL;
    *pREG_MISCREG_PLL2_CONTROL |= ((Msel << BITP_MISCREG_PLL2_CONTROL_MSEL)& BITM_MISCREG_PLL2_CONTROL_MSEL);
    /* set MSELDF_CHG */
    *pREG_MISCREG_PLL2_CONTROL |= BITM_MISCREG_PLL2_CONTROL_MSELDF_CHG;
    Cclkdelay(768);
    /* Convert Clkin cycles to core clock cycles */
    Cclkdelay((uint32_t)((float32_t)2048 * cclk_clkin_r()));
    /* Set BYPASSB control bit */
    *pREG_MISCREG_PLL2_CONTROL |= BITM_MISCREG_PLL2_CONTROL_BYPASSB;

    /* DCLK Divider update */
    /*    Clear BYPASSB, DSEL_DIV_CHG and MSELDF_CHG */
    *pREG_MISCREG_PLL2_CONTROL &= ~(BITM_MISCREG_PLL2_CONTROL_BYPASSB | BITM_MISCREG_PLL2_CONTROL_MSELDF_CHG | BITM_MISCREG_PLL2_CONTROL_DSEL_DIV_CHG) ;
    /* update DSEL */
    *pREG_MISCREG_PLL2_CONTROL &= ~BITM_MISCREG_PLL2_CONTROL_DSEL;
    *pREG_MISCREG_PLL2_CONTROL |= ((Dsel<< BITP_MISCREG_PLL2_CONTROL_DSEL)& BITM_MISCREG_PLL2_CONTROL_DSEL);
    /* set DSEL_DIV_CHG */
    *pREG_MISCREG_PLL2_CONTROL |= BITM_MISCREG_PLL2_CONTROL_DSEL_DIV_CHG;
    Cclkdelay(768);
    /* Set BYPASSB control bit */
    *pREG_MISCREG_PLL2_CONTROL |= BITM_MISCREG_PLL2_CONTROL_BYPASSB;

    /* Set the DDRCLK_FROM_3RDPLL [11] bit to connect the 3rd PLL DCLK to DMC */
    *pREG_MISCREG_PLL2_CONTROL |= BITM_MISCREG_PLL2_CONTROL_DDRCLK_FROM_3RDPLL;
}

#endif

#if CONFIG_DMC0

float32_t cclk_dclk_r(void)
{
    return cclkdclk_ratio;
}

#if defined(__ADSPSC598_FAMILY__)
float32_t cclk_clkin_r(void)
{
    return cclkclkin_ratio;
}
#endif

#endif

/*@}*/
