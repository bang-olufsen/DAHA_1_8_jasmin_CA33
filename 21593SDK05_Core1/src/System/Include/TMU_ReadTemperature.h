/*********************************************************************************
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.
*********************************************************************************/

/*****************************************************************************
 * TMU_READTEMPERATURE.h
 *****************************************************************************/

#ifndef __TMUREADTEMPERATURE_H__
#define __TMUREADTEMPERATURE_H__

/* Add your custom header content here */
#include <sys/platform.h>
#include <sys/adi_core.h>
#include "adi_initialize.h"
#include <drivers/tmu/adi_tmu.h>
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************************/
/* Macros for selecting which core to test, enable one of them */
/**********************************************************************************/
#define TEST_CORE0      /* Enable this macro to run the test case on core 0 */
//#define TEST_CORE1      /* Enable this macro to run the test case on core 1 */
//#define TEST_CORE2      /* Enable this macro to run the test case on core 2 */
/**********************************************************************************/

/*MACRO for reporting error to console*/
#define REPORT_ERROR(msg)  \
    do{\
        printf(msg);\
        exit(1);\
    }while(0)

/* Initial delay for reading TMU data*/
#define TMU_DELAY     (0x5FFFFFFFu)

/* Minimum temperature*/
#define MIN_TEMP  (10.0)

/* Maximum temperature*/
#define MAX_TEMP  (80.0)

/* TMU Temperature value */
float TMU_Value;

#ifdef TMU
/* TMU driver handle */
static ADI_TMU_HANDLE hDevice;

/* TMU driver API result code */
static ADI_TMU_RESULT result;

/* TMU driver memory */
static uint8_t TMUDriverMemory[ADI_TMU_MEMORY_SIZE];

int TMU_Enable = 1;
#endif

#endif /* __TMUREADTEMPERATURE_H__ */
