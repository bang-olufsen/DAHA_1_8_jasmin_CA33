/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*!
* @file      adi_canfd_init.h
*
* @brief     Header file for CANFD initialization.
*
* @details
*
*/

#ifndef ADI_CANFD_INIT_H
#define ADI_CANFD_INIT_H

#include "config.h"

#if !defined(INIT_CANFD)
#define INIT_CANFD 0
#endif

#if INIT_CANFD

#ifdef __cplusplus
extern "C" {
#endif

void adi_canfd_init (void);

#ifdef __cplusplus
}
#endif

#endif /* INIT_CANFD */

#endif /* ADI_CANFD_INIT_H */
