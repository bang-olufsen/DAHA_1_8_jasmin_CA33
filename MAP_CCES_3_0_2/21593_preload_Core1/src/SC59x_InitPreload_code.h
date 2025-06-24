/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*****************************************************************************
 * SC59x_InitPreload_code.h
 *****************************************************************************/

#ifndef ADSPSC59X_INITPRELOAD_CODE_H
#define ADSPSC59X_INITPRELOAD_CODE_H

/*!
* @file      SC59x_InitPreload_code.h
*
* @brief     Global header file for SC59x_InitPreload_code.c
*
* @details
*
*/

#include <stdlib.h>
#include <services/pwr/adi_pwr.h>
#include <sys/platform.h>
#include "adi_initialize.h"

#include "config.h"

#include "adi_clockrates_SC59x_config.h"
#include "adi_pwr_SC59x_config.h"
#include "adi_smpu_SC59x_config.h"
#include "adi_canfd_init.h"
#include "adi_emsi_init.h"

#if CONFIG_DMC0
#include "adi_dmc.h"
#include "adi_dmc_SC59x_config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined __ADSPSHARC__
#pragma retain_name /* retain resolved initcode entry */
#endif
uint32_t initcode(ADI_ROM_BOOT_CONFIG* pBootStruct);

#ifdef __cplusplus
}
#endif

#endif /* ADSPSC59X_INITPRELOAD_CODE_H */
