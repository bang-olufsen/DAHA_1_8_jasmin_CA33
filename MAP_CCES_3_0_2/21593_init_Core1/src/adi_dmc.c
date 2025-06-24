/*
 * Copyright (c) 2018-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

#include "adi_dmc.h"

#if CONFIG_DMC0

#include <stdbool.h>
#include <sys/anomaly_macros_rtl.h>

#ifdef _MISRA_RULES
#pragma diag(suppress:misra_rule_16_7:"The adi_dmc_phy_calibration pointer parameter is non-const")
#pragma diag(suppress:misra_rule_19_14:"WA_20000017 use requires a suppression")
#endif

#if (CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ) || \
    (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ) || \
    (CONFIG_DMC0 == ISSI_8Gb_DDR3_900MHZ) || \
    (CONFIG_DMC0 == ISSI_4Gb_DDR3_900MHZ)
 #define DelayTrim 1
 #define Lane0_DQ_Delay 1
 #define Lane1_DQ_Delay 1
#else
 #define DelayTrim 0
 #define Lane0_DQ_Delay 0
 #define Lane1_DQ_Delay 0
#endif

#define DqsTrim 0
#define DQSDIR 0ul
#define Lane0_Dqscode 0ul
#define Lane1_Dqscode 0ul

#define ClkTrim 0
#define CLKDIR 0ul
#define Clkcode 0ul

#define TrigCalib 0ul
#define OfstdCycle 2ul

/* DMC phy ZQ calibration routine
 * The first step in DMC initialization
 */
void adi_dmc_phy_calibration(ADI_DMC_CONFIG *pConfig)
{
  /* Program the ODT and drive strength values */

#if WA_20000117
  uint32_t stat_value = 0x0u;
  uint32_t drv_pu , drv_pd, odt_pu, odt_pd;
  uint32_t ROdt, ClkDqsDrvImpedance;

  *pREG_DMC0_DDR_CA_CTL = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_3 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_2 = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x04010000ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x10000002ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x0u;
  *pREG_DMC0_DDR_ROOT_CTL = 0x0u;
  *pREG_DMC0_DDR_SCRATCH_3 = 0x1ul<<12;
  *pREG_DMC0_DDR_SCRATCH_2 = 0x0ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_ROOT_CTL = 0x04010000ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x10000002ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_3 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_2 = pConfig->ulDDR_ZQCTL0;
  *pREG_DMC0_DDR_ROOT_CTL = 0x04010000ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x0C000002ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_3 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_2 = 0x30000000ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x04010000ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x10000002ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_3 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_2 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_3 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_2 = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x04010000ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x10000002ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_3 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_2 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_3 = 0x0ul;
  *pREG_DMC0_DDR_SCRATCH_2 = 0x50000000ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x04010000ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x10000002ul;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0u;
  *pREG_DMC0_DDR_ROOT_CTL = 0u;
  *pREG_DMC0_DDR_CA_CTL = 0x0C000004u;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_ROOT_CTL = BITM_DMC_DDR_ROOT_CTL_TRIG_RD_XFER_ALL;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0u;
  *pREG_DMC0_DDR_ROOT_CTL = 0u;
  /* calculate ODT PU and PD values */
  stat_value = ((*pREG_DMC0_DDR_SCRATCH_7 & 0x0000FFFFu)<<16);
  stat_value |= (*pREG_DMC0_DDR_SCRATCH_6 & 0xFFFF0000u)>>16;
  ClkDqsDrvImpedance = ((pConfig->ulDDR_ZQCTL0) & BITM_DMC_DDR_ZQ_CTL0_IMPWRDQ) >> BITP_DMC_DDR_ZQ_CTL0_IMPWRDQ;
  ROdt = ((pConfig->ulDDR_ZQCTL0) & BITM_DMC_DDR_ZQ_CTL0_IMPRTT) >> BITP_DMC_DDR_ZQ_CTL0_IMPRTT;
  drv_pu = stat_value & 0x0000003Fu;
  drv_pd = (stat_value>>12) & 0x0000003Fu;
  odt_pu = (drv_pu * ClkDqsDrvImpedance)/ ROdt;
  odt_pd = (drv_pd * ClkDqsDrvImpedance)/ ROdt;
  *pREG_DMC0_DDR_SCRATCH_2 |= ((1uL<<24)                     |
                              ((drv_pd & 0x0000003Fu))       |
                              ((odt_pd & 0x0000003Fu)<<6)    |
                              ((drv_pu & 0x0000003Fu)<<12)   |
                              ((odt_pu & 0x0000003Fu)<<18));
  *pREG_DMC0_DDR_ROOT_CTL = 0x0C010000u;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x08000002u;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0u;
  *pREG_DMC0_DDR_ROOT_CTL = 0u;
  *pREG_DMC0_DDR_ROOT_CTL = 0x04010000u;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0x80000002u;
  dmcdelay(2500u);
  *pREG_DMC0_DDR_CA_CTL = 0u;
  *pREG_DMC0_DDR_ROOT_CTL = 0u;

#else /* WA_20000117 */
  *pREG_DMC0_DDR_ZQ_CTL0 = pConfig->ulDDR_ZQCTL0;
  *pREG_DMC0_DDR_ZQ_CTL1 = pConfig->ulDDR_ZQCTL1;
  *pREG_DMC0_DDR_ZQ_CTL2 = pConfig->ulDDR_ZQCTL2;

  /* Generate the trigger */
  *pREG_DMC0_DDR_CA_CTL = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x00010000ul;
  dmcdelay(8000u);

  /* The [31:26] bits may change if pad ring changes */
  *pREG_DMC0_DDR_CA_CTL = 0x0C000001ul|TrigCalib;
  dmcdelay(8000u);
  *pREG_DMC0_DDR_CA_CTL = 0x0ul;
  *pREG_DMC0_DDR_ROOT_CTL = 0x0ul;
#endif /* WA_20000117 */


#if DqsTrim
  /* DQS duty trim */
  *pREG_DMC0_DDR_LANE0_CTL0 &= ~(BITM_DMC_DDR_LANE0_CTL0_BYPCODE | BITP_DMC_DDR_LANE0_CTL0_BYPSELP | BITM_DMC_DDR_LANE0_CTL0_BYPENB);
  *pREG_DMC0_DDR_LANE1_CTL0 &= ~(BITM_DMC_DDR_LANE1_CTL0_BYPCODE | BITP_DMC_DDR_LANE1_CTL0_BYPSELP | BITM_DMC_DDR_LANE1_CTL0_BYPENB);
  *pREG_DMC0_DDR_LANE0_CTL0 |= (((Lane0_Dqscode<<BITP_DMC_DDR_LANE0_CTL0_BYPCODE) & BITM_DMC_DDR_LANE0_CTL0_BYPCODE) | ((DQSDIR<<BITP_DMC_DDR_LANE0_CTL0_BYPSELP) & BITM_DMC_DDR_LANE0_CTL0_BYPSELP) | BITM_DMC_DDR_LANE0_CTL0_BYPENB);
  *pREG_DMC0_DDR_LANE1_CTL0 |= (((Lane1_Dqscode<<BITP_DMC_DDR_LANE1_CTL0_BYPCODE) & BITM_DMC_DDR_LANE1_CTL0_BYPCODE) | ((DQSDIR<<BITP_DMC_DDR_LANE1_CTL0_BYPSELP) & BITM_DMC_DDR_LANE1_CTL0_BYPSELP) | BITM_DMC_DDR_LANE1_CTL0_BYPENB);
#endif

#if ClkTrim
  /* Clock duty trim */
  *pREG_DMC0_DDR_CA_CTL &= ~(BITM_DMC_DDR_CA_CTL_BYPCODE0 | BITP_DMC_DDR_CA_CTL_BYPCODE1 | BITM_DMC_DDR_CA_CTL_BYPENB | BITM_DMC_DDR_CA_CTL_BYPSELP);
  *pREG_DMC0_DDR_CA_CTL |= ((((Clkcode & 0x3)<<BITP_DMC_DDR_CA_CTL_BYPCODE0) & BITM_DMC_DDR_CA_CTL_BYPCODE0) | ((((Clkcode & 0xC)>>2)<<BITP_DMC_DDR_CA_CTL_BYPCODE1) & BITM_DMC_DDR_CA_CTL_BYPCODE1) | BITM_DMC_DDR_CA_CTL_BYPENB | ((CLKDIR<<BITP_DMC_DDR_CA_CTL_BYPSELP) & BITM_DMC_DDR_CA_CTL_BYPSELP));
#endif
}

/*  DMC lane reset routine
 *  DMC lane reset should be performed when DMC clock is changed
 *  Sequence: Before changing the DDR clock frequency reset the lane, call cgu routine to change the DMC clock frequency
 *        Then take DMC lanes out of reset
 */
void adi_dmc_lane_reset(bool reset)
{

  if (reset) {
    *pREG_DMC0_DDR_LANE0_CTL0 |= BITM_DMC_DDR_LANE0_CTL0_CB_RSTDLL;
    *pREG_DMC0_DDR_LANE1_CTL0 |= BITM_DMC_DDR_LANE1_CTL0_CB_RSTDLL;
  } else {
    *pREG_DMC0_DDR_LANE0_CTL0 &= ~BITM_DMC_DDR_LANE0_CTL0_CB_RSTDLL;
    *pREG_DMC0_DDR_LANE1_CTL0 &= ~BITM_DMC_DDR_LANE1_CTL0_CB_RSTDLL;
  }
  dmcdelay(9000u);
}


/* dmc_ctrl_init() configures DMC controller
 * It returns ADI_DMC_SUCCESS on success and ADI_DMC_FAILURE on failure
 */

ADI_DMC_RESULT adi_dmc_ctrl_init(ADI_DMC_CONFIG *pConfig)
{

  uint32_t phyphase,rd_cnt,t_EMR1,t_EMR3, t_CTL,data_cyc;

  /* program timing registers*/
  *pREG_DMC0_CFG = (pConfig->ulDDR_DLLCTLCFG) & 0xFFFFul;
  *pREG_DMC0_TR0 = pConfig->ulDDR_TR0;
  *pREG_DMC0_TR1 = pConfig->ulDDR_TR1;
  *pREG_DMC0_TR2 = pConfig->ulDDR_TR2;

  /* program shadow registers */
  *pREG_DMC0_MR   = ((pConfig->ulDDR_MREMR1) >> 16ul) & 0xFFFFul;
  *pREG_DMC0_MR1  = (pConfig->ulDDR_MREMR1) & 0xFFFFul;
  *pREG_DMC0_MR2  = (pConfig->ulDDR_EMR2EMR3)>>16ul & 0xFFFFul;
  *pREG_DMC0_EMR3 = (pConfig->ulDDR_EMR2EMR3) & 0xFFFFul;

  /* program Dll timing register */
  *pREG_DMC0_DLLCTL = ((pConfig->ulDDR_DLLCTLCFG) >> 16ul) & 0xFFFFul;

  dmcdelay(2000u);

  *pREG_DMC0_DDR_CA_CTL |= BITM_DMC_DDR_CA_CTL_SW_REFRESH;

  dmcdelay(5u);

  *pREG_DMC0_DDR_ROOT_CTL |= BITM_DMC_DDR_ROOT_CTL_SW_REFRESH | (OfstdCycle << BITP_DMC_DDR_ROOT_CTL_PIPE_OFSTDCYCLE);

  /* Start DMC initialization */
  *pREG_DMC0_CTL = pConfig->ulDDR_CTL;

  dmcdelay(722000u);

  /* Add necessary delay depending on the configuration */
  t_EMR1 = (pConfig->ulDDR_MREMR1 & BITM_DMC_MR1_WL)>>BITP_DMC_MR1_WL;
  if(t_EMR1 != 0u)
  {
     dmcdelay(600u);
     while(((*pREG_DMC0_MR1 & BITM_DMC_MR1_WL)>>BITP_DMC_MR1_WL) != 0ul) { }
  }


  t_EMR3 = (pConfig->ulDDR_EMR2EMR3 & BITM_DMC_EMR3_MPR)>>BITP_DMC_EMR3_MPR;
  if(t_EMR3 != 0u)
  {
     dmcdelay(2000u);
     while(((*pREG_DMC0_EMR3 & BITM_DMC_EMR3_MPR)>>BITP_DMC_EMR3_MPR) != 0ul) { }
  }


  t_CTL = (pConfig->ulDDR_CTL & BITM_DMC_CTL_RL_DQS)>>BITP_DMC_CTL_RL_DQS;
  if(t_CTL != 0u)
  {
     dmcdelay(600u);
     while(((*pREG_DMC0_CTL & BITM_DMC_CTL_RL_DQS)>>BITP_DMC_CTL_RL_DQS) != 0ul)
     {
     }
  }

  /* check if DMC initialization finished, if not return error */
  while((*pREG_DMC0_STAT & BITM_DMC_STAT_INITDONE) != BITM_DMC_STAT_INITDONE) {
  }


  /* End of DMC controller configuration, Start of Phy control registers */

  /* toggle DCYCLE */

  *pREG_DMC0_DDR_LANE0_CTL1 |= BITM_DMC_DDR_LANE0_CTL1_COMP_DCYCLE;
  *pREG_DMC0_DDR_LANE1_CTL1 |= BITM_DMC_DDR_LANE1_CTL1_COMP_DCYCLE;

  dmcdelay(10u);

  *pREG_DMC0_DDR_LANE0_CTL1 &= (~BITM_DMC_DDR_LANE0_CTL1_COMP_DCYCLE);
  *pREG_DMC0_DDR_LANE1_CTL1 &= (~BITM_DMC_DDR_LANE1_CTL1_COMP_DCYCLE);

  /* toggle RSTDAT */
  *pREG_DMC0_DDR_LANE0_CTL0 |= BITM_DMC_DDR_LANE0_CTL0_CB_RSTDAT;
  *pREG_DMC0_DDR_LANE0_CTL0 &= (~BITM_DMC_DDR_LANE0_CTL0_CB_RSTDAT);

  *pREG_DMC0_DDR_LANE1_CTL0 |= BITM_DMC_DDR_LANE1_CTL0_CB_RSTDAT;
  *pREG_DMC0_DDR_LANE1_CTL0 &= (~BITM_DMC_DDR_LANE1_CTL0_CB_RSTDAT);

  dmcdelay(2500u);

  /* Program phyphase*/

  phyphase = (*pREG_DMC0_STAT & BITM_DMC_STAT_PHYRDPHASE)>>BITP_DMC_STAT_PHYRDPHASE;
  data_cyc = (phyphase << BITP_DMC_DLLCTL_DATACYC) & BITM_DMC_DLLCTL_DATACYC;
  rd_cnt = ((pConfig->ulDDR_DLLCTLCFG) >> 16);
  rd_cnt <<= BITP_DMC_DLLCTL_DLLCALRDCNT;
  rd_cnt &= BITM_DMC_DLLCTL_DLLCALRDCNT;

  *pREG_DMC0_DLLCTL = rd_cnt|data_cyc;

  *pREG_DMC0_CTL = (pConfig->ulDDR_CTL & (~BITM_DMC_CTL_INIT) & (~BITM_DMC_CTL_RL_DQS));

#if DelayTrim
  /* DQ delay trim*/
	uint32_t WL_code_LDQS, WL_code_UDQS;

	/* For LDQS */
	*pREG_DMC0_DDR_LANE0_CTL1 |= 0x000000D0;
	dmcdelay(2500u);
	*pREG_DMC0_DDR_ROOT_CTL = 0x00400000u;
	dmcdelay(2500u);
	*pREG_DMC0_DDR_ROOT_CTL = 0u;
	WL_code_LDQS = (*pREG_DMC0_DDR_SCRATCH_4 & 0x001F0000u) >> 16;
	*pREG_DMC0_DDR_LANE0_CTL1 &= ~(BITM_DMC_DDR_LANE0_CTL1_BYPCODE|BITM_DMC_DDR_LANE0_CTL1_BYPDELCHAINEN);
	*pREG_DMC0_DDR_LANE0_CTL1 |= (((WL_code_LDQS + Lane0_DQ_Delay)<<BITP_DMC_DDR_LANE0_CTL1_BYPCODE) & BITM_DMC_DDR_LANE0_CTL1_BYPCODE)|BITM_DMC_DDR_LANE0_CTL1_BYPDELCHAINEN;
	dmcdelay(2500u);

	/* For UDQS */
	*pREG_DMC0_DDR_LANE1_CTL1 |= 0x000000D0u;
	dmcdelay(2500u);
	*pREG_DMC0_DDR_ROOT_CTL = 0x00800000u;
	dmcdelay(2500u);
	*pREG_DMC0_DDR_ROOT_CTL = 0u;
	WL_code_UDQS = (*pREG_DMC0_DDR_SCRATCH_5 & 0x001F0000u) >> 16;
	*pREG_DMC0_DDR_LANE1_CTL1 &= ~(BITM_DMC_DDR_LANE1_CTL1_BYPCODE|BITM_DMC_DDR_LANE1_CTL1_BYPDELCHAINEN);
	*pREG_DMC0_DDR_LANE1_CTL1 |= (((WL_code_UDQS + Lane1_DQ_Delay)<<BITP_DMC_DDR_LANE1_CTL1_BYPCODE) & BITM_DMC_DDR_LANE1_CTL1_BYPCODE)|BITM_DMC_DDR_LANE1_CTL1_BYPDELCHAINEN;
	dmcdelay(2500u);
#endif

  return ADI_DMC_SUCCESS;

}

/* In order to preserve ddr content while changing DMC clock, put memory in self refresh mode
 *
 * sequence: program DMC controller to enter self refresh mode. No further access should be issued to ddr memory
 *       call cgu routines to change DMC clock
 *       exit self-refresh mode
 *
 */
void adi_dmc_self_refresh(bool enter)
{

  if (enter) {
    while((*pREG_DMC0_STAT & BITM_DMC_STAT_IDLE)==0ul) { }

    /*Set the SRREQ bit to enter self refresh mode*/
    *pREG_DMC0_CTL |= BITM_DMC_CTL_SRREQ;

    /*Wait for self refresh acknowledge from the controller*/
    while((*pREG_DMC0_STAT & BITM_DMC_STAT_SRACK)==0ul) { }

  } else {
    /*clear the SRREQ bit to exit self refresh mode*/
    *pREG_DMC0_CTL &= ~BITM_DMC_CTL_SRREQ;

    /*Wait for self refresh acknowledge from the controller*/
    while((*pREG_DMC0_STAT & BITM_DMC_STAT_SRACK)!=0ul) { }

    /*Wait for the DMC to be in IDLE state*/
    while((*pREG_DMC0_STAT & BITM_DMC_STAT_IDLE)==0ul) { }

    *pREG_DMC0_CTL |= BITM_DMC_CTL_DLLCAL;
    /*Wait for DLL calib*/
    while((*pREG_DMC0_STAT & BITM_DMC_STAT_DLLCALDONE)==0ul) { }

  }
}

#endif /* CONFIG_DMC0 */
