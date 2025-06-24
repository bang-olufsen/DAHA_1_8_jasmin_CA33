/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*!
* @file      adi_smpu_SC59x_config.h
*
* @brief     Header file for SMPU configuration .
*
* @details
*
*/

#ifndef ADI_SMPU_SC59X_CONFIG_H
#define ADI_SMPU_SC59X_CONFIG_H

#include <services/smpu/adi_smpu.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t adi_smpu_cfg0_init(bool bDMC0, bool bSPIflash);

#ifdef __cplusplus
}
#endif

#endif /* ADI_SMPU_SC59X_CONFIG_H */
