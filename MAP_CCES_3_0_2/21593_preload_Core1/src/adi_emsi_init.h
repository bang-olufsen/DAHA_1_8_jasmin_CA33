/*
 * Copyright (c) 2021-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*!
* @file      adi_emsi_init.h
*
* @brief     Header file for EMSI initialization configuration.
*
* @details
*
*/

#ifndef ADI_EMSI_INIT_H
#define ADI_EMSI_INIT_H

#include "config.h"

#if !defined(INIT_EMSI)
#define INIT_EMSI 0
#endif

#if INIT_EMSI

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int32_t adi_emsi_init(void);

#ifdef __cplusplus
}
#endif

#endif /* INIT_EMSI */

#endif /* ADI_EMSI_INIT_H */

