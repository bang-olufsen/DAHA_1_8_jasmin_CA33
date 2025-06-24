/*
 * Copyright (c) 2018-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*!
* @file      adi_dmc.h
*
* @brief     DMC Configuration header file
*
* @details
*            DMC Configuration header file
*/

#ifndef ADI_DMC_H
#define ADI_DMC_H

#include "config.h"

#if CONFIG_DMC0

#include <sys/platform.h>
#include <stdbool.h>
#if defined(__ADSPSHARC__)
  #include <adi_types.h>
  #include <time.h>
#elif defined __ADSPARM__
  #define DO_CYCLE_COUNT
  #include <cycle_count.h>
#endif
#include "adi_pwr_SC59x_config.h"

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_5_1:"Identifiers (internal and external) shall not rely on the significance of more than 31 characters")
#pragma diag(suppress:misra_rule_20_12:"Making use of time.h function clock for cycle counting.")
#endif

typedef enum
{
  ADI_DMC_SUCCESS=0u,
  ADI_DMC_FAILURE
}ADI_DMC_RESULT;

/* structure which holds DMC register values */
typedef struct
{

  uint32_t ulDDR_DLLCTLCFG;               /*!< Content of DDR DLLCTL and DMC_CFG register     */
  uint32_t ulDDR_EMR2EMR3;                /*!< Content of the DDR EMR2 and EMR3 Register      */
  uint32_t ulDDR_CTL;                     /*!< Content of the DDR Control                   */
  uint32_t ulDDR_MREMR1;                  /*!< Content of the DDR MR and EMR1 Register      */
  uint32_t ulDDR_TR0;                     /*!< Content of the DDR Timing Register      */
  uint32_t ulDDR_TR1;                     /*!< Content of the DDR Timing Register      */
  uint32_t ulDDR_TR2;                     /*!< Content of the DDR Timing Register      */
  uint32_t ulDDR_ZQCTL0;                  /*!< Content of ZQCTL0 register */
  uint32_t ulDDR_ZQCTL1;                  /*!< Content of ZQCTL1 register */
  uint32_t ulDDR_ZQCTL2;                  /*!< Content of ZQCTL2 register */

}ADI_DMC_CONFIG;

/* delay function */
#if defined __ADSPARM__
static __inline__ void dmcdelay(uint32_t delay)
{
  /* Convert DDR cycles to core clock cycles */
  delay = (uint32_t)((float32_t)delay * cclkdclk_ratio);

  CCNTR_INIT;
  CCNTR_START;
  /* Wait for the appropriate number of cycles */
  while (CCNTR_READ < delay) {
    /* Wait */
  }
  CCNTR_STOP;
}
#elif defined __ADSPSHARC__
#pragma inline
static void dmcdelay(uint32_t delay)
{
  /* Although the clock() function returns a signed value, startCycleCount
   * must be unsigned so that the comparison in the 'while' loop is valid if
   * the emuclk register value wraps around.
   */
  uint32_t startCycleCount;

  /* Convert DDR cycles to core clock cycles */
  delay = (uint32_t)((float32_t)delay * cclk_dclk_r());

  /*
   * Wait for the appropriate number of cycles. On SHARC processors, the
   * clock() function in the run-time library will return the cycle count in
   * the emuclk register.
   */
  startCycleCount = clock();
  while (((uint32_t)(clock()) - startCycleCount) < delay) {
    /* Wait */
  }
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* reset dmc lanes */
void adi_dmc_lane_reset(bool reset);
/* enter/exit self refresh mode */
void adi_dmc_self_refresh(bool enter);
/* program dmc controller timing registers */
ADI_DMC_RESULT adi_dmc_ctrl_init(ADI_DMC_CONFIG *pConfig);
/* trigger Zq calibration*/
void adi_dmc_phy_calibration(ADI_DMC_CONFIG *pConfig);

#ifdef __cplusplus
}
#endif

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif

#endif /* CONFIG_DMC0 */

#endif /* ADI_DMC_H */
