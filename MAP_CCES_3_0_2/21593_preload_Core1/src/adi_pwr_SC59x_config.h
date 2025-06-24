/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*!
* @file      adi_pwr_SC59x_config.h
*
* @brief     Header file for Power Service Configuration.
*
* @details
*
*/

#ifndef INC_ADI_PWR_SC59X_CONFIG_H_
#define INC_ADI_PWR_SC59X_CONFIG_H_

#include <adi_types.h>
#include "config.h"

#if defined(__ADSPSHARC__)
  #include <adi_types.h>
  #include <time.h>
#elif defined __ADSPARM__
  #define DO_CYCLE_COUNT
  #include <cycle_count.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

uint32_t adi_pwr_cfg0_init(void) ;
void adi_configDCLK_1(uint32_t Msel, uint32_t Dsel) ;


#if CONFIG_DMC0
 #if defined(__ADSPSC598_FAMILY__) && defined(__ADSPARM__ )
  #if (CONFIG_DMC0 == ISSI_4Gb_DDR3_667MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_667MHZ)
   #define cclkdclk_ratio (1.8f) /*!< ratio between the core clock and the DDR clock */
  #elif (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ)
   #define cclkdclk_ratio (1.5f) /*!< ratio between the core clock and the DDR clock */
  #elif (CONFIG_DMC0 == ISSI_4Gb_DDR3_900MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_900MHZ)
   #define cclkdclk_ratio (1.34f) /*!< ratio between the core clock and the DDR clock */
  #else
   #error unexpected
  #endif

 #elif defined(__ADSPSC598_FAMILY__) && defined(__ADSPSHARC__ )
  #if (CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_1GHZ)
   #if (CONFIG_DMC0 == ISSI_4Gb_DDR3_667MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_667MHZ)
    #define cclkdclk_ratio (1.5f)   /*!< ratio between the core clock and the DDR clock */
   #elif (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ)
    #define cclkdclk_ratio (1.25f)   /*!< ratio between the core clock and the DDR clock */
   #elif (CONFIG_DMC0 == ISSI_4Gb_DDR3_900MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_900MHZ)
    #define cclkdclk_ratio (1.12f)   /*!< ratio between the core clock and the DDR clock */
   #endif
  #elif (CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_800MHZ)
   #if (CONFIG_DMC0 == ISSI_4Gb_DDR3_667MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_667MHZ)
    #define cclkdclk_ratio (1.2f)   /*!< ratio between the core clock and the DDR clock */
   #elif (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ)
    #define cclkdclk_ratio (1.0f)   /*!< ratio between the core clock and the DDR clock */
   #elif (CONFIG_DMC0 == ISSI_4Gb_DDR3_900MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_900MHZ)
    #define cclkdclk_ratio (0.89f)   /*!< ratio between the core clock and the DDR clock */
   #endif
  #elif (CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_600MHZ)
   #if (CONFIG_DMC0 == ISSI_4Gb_DDR3_667MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_667MHZ)
    #define cclkdclk_ratio (0.9f)   /*!< ratio between the core clock and the DDR clock */
   #elif (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ)
    #define cclkdclk_ratio (0.75f)   /*!< ratio between the core clock and the DDR clock */
   #elif (CONFIG_DMC0 == ISSI_4Gb_DDR3_900MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_900MHZ)
    #define cclkdclk_ratio (0.67f)   /*!< ratio between the core clock and the DDR clock */
   #endif
  #else
   #error unexpected
  #endif

 #elif defined(__ADSPSC594_FAMILY__)
  #if (CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_1GHZ) && \
      (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ ||  CONFIG_DMC0 == WINBOND_2Gb_DDR3_800MHZ)
   #define cclkdclk_ratio (1.25f) /*!< ratio between the core clock and the DDR clock */
  #elif (CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_800MHZ) && \
        (CONFIG_DMC0 == ISSI_4Gb_DDR3_800MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_800MHZ)
   #define cclkdclk_ratio (1.0f)  /*!< ratio between the core clock and the DDR clock */
  #elif (CONFIG_SHARC_CORE_CLOCK == CORE_CLOCK_600MHZ) && \
        (CONFIG_DMC0 == ISSI_4Gb_DDR3_667MHZ || CONFIG_DMC0 == ISSI_8Gb_DDR3_667MHZ)
   #define cclkdclk_ratio (0.9f)  /*!< ratio between the core clock and the DDR clock */
  #else
   #error unexpected
  #endif

 #else
  #error unexpected
 #endif
 float32_t cclk_dclk_r(void);

 #if defined(__ADSPSC598_FAMILY__)
 float32_t cclk_clkin_r(void);
 #endif

 /* delay function */
 #if defined __ADSPARM__
 static __inline__ void Cclkdelay(uint32_t delay)
 {

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
 static void Cclkdelay(uint32_t delay)
 {
   /* Although the clock() function returns a signed value, startCycleCount
    * must be unsigned so that the comparison in the 'while' loop is valid if
    * the emuclk register value wraps around.
    */
   uint32_t startCycleCount;

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

#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_ADI_PWR_SC59X_CONFIG_H_ */
